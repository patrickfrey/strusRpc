#include "server.h"
#include "hexdump.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <uv.h>
#include <uv-version.h>

#define UV_VERSION_NUM (UV_VERSION_MAJOR*100 + UV_VERSION_MINOR)
#undef STRUS_LOWLEVEL_DEBUG

/* Shared global data */
static strus_globalctx_t* g_glbctx=0;
static uv_tcp_t g_server;

#define CONNECTION_MAXBUFSIZE (1<<24)
#define CONNECTION_BUFSIZE (1<<14)


typedef struct strus_connection_t
{
	strus_handlerdata_t handlerdata;	/* data of request handler */
	enum {
		CTX_READDATASIZE,
		CTX_READDATA,
		CTX_PROCESS,
		CTX_TERMINATED
	} state;				/* current request state */
	unsigned int id;			/* connection id */
	uv_tcp_t tcp;				/* tcp connection handle */
	unsigned char* readbuf;			/* buffer for read request */
	uint32_t readbufpos;			/* number of bytes filled of read request buffer */
	uint32_t readbufsize;			/* size of read request buffer */
	uint32_t hdrbytes;			/* number of bytes read in state CTX_READDATASIZE */
	uv_shutdown_t shutdown_req;		/* preallocated shutdown request data structure */
	uv_buf_t write_reqbuf;			/* preallocated buffer for request */
	uv_work_t work_req;			/* preallocated work request data structure */
	uv_write_t write_req;			/* preallocated write request data structure */
	const unsigned char* output;		/* output of request */
	size_t outputsize;			/* size of output of request */
	char buf[ CONNECTION_BUFSIZE];		/* memory blocks served for malloc in read */
} strus_connection_t;

static void strus_free_connection( strus_connection_t* ctx)
{
	if (ctx)
	{
		if (ctx->readbuf) free( ctx->readbuf);
		g_glbctx->done_handlerdata( &ctx->handlerdata);
		free( ctx);
	}
}

static void strus_init_request( strus_connection_t* conn)
{
	conn->hdrbytes = 0;
	conn->readbufpos = 0;
	conn->readbufsize = 0;
	conn->state = CTX_READDATASIZE;
	if (conn->readbuf != NULL)
	{
		free( conn->readbuf);
		conn->readbuf = 0;
	}
	conn->output = 0;
	conn->outputsize = 0;
}

static void log_error_request( strus_connection_t* ctx, const char* msg)
{
	fprintf( g_glbctx->logf, "[conn %u] ERROR processing request: %s\n", ctx->id, msg);
}

static void log_error_conn_sys( strus_connection_t* ctx, const char* msg, int err)
{
	fprintf( g_glbctx->logf, "[conn %u] ERROR %s (%s)\n", ctx->id, msg, strerror(err));
}

static void log_error_conn( strus_connection_t* ctx, const char* msg)
{
	fprintf( g_glbctx->logf, "[conn %u] ERROR %s\n", ctx->id, msg);
}

static void log_error_sys( const char* msg, int err)
{
	fprintf( g_glbctx->logf, "[server] ERROR %s (%s)\n", msg, strerror(err));
}

static void log_error( const char* msg)
{
	fprintf( g_glbctx->logf, "[server] ERROR %s\n", msg);
}

static void log_message( const char* msg)
{
	fprintf( g_glbctx->logf, "[server] %s\n", msg);
}

static void log_message_conn( strus_connection_t* ctx, const char* msg)
{
	fprintf( g_glbctx->logf, "[conn %u] %s\n", ctx->id, msg);
}


/* Forward declaration of callback functions: */
#if (UV_VERSION_NUM>10)
static void on_alloc( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
#else
static uv_buf_t on_alloc( uv_handle_t* handle, size_t suggested_size);
static void on_read( uv_stream_t* handle, ssize_t nread, uv_buf_t buf);
#endif
static void on_write( uv_write_t* req, int status);
static void on_shutdown( uv_shutdown_t* handle, int status);
static void on_close( uv_handle_t* handle);
static void on_connected( uv_stream_t* stream, int status);
static void on_signal( uv_signal_t *handle, int signum);
static void on_work( uv_work_t *req);
static void on_complete_work( uv_work_t *req, int status);

/* Forward declaration for push request handler work on queue: */
static void push_work_queue( strus_connection_t* conn);


#if (UV_VERSION_NUM>10)
static void on_alloc( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	buf->base = conn->buf;
	if (suggested_size < CONNECTION_BUFSIZE)
	{
		buf->len = suggested_size;
	}
	else
	{
		buf->len = CONNECTION_BUFSIZE;
	}
	/* ... safe because our on_read() allocations never overlap */
}
#else
static uv_buf_t on_alloc( uv_handle_t* handle, size_t suggested_size)
{
	uv_buf_t rt;
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	rt.base = conn->buf;
	if (suggested_size < CONNECTION_BUFSIZE)
	{
		rt.len = suggested_size;
	}
	else
	{
		rt.len = CONNECTION_BUFSIZE;
	}
	/* ... safe because our on_read() allocations never overlap */
	return rt;
}
#endif

static void on_close( uv_handle_t* handle)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	strus_free_connection( conn);
}

static void on_shutdown( uv_shutdown_t* req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->data);
	if (status != 0)
	{
		log_error_conn_sys( conn, "error in shutdown", status);
	}
	if (!uv_is_closing((uv_handle_t*) req->handle))
	{
		uv_close( (uv_handle_t*)req->handle, on_close);
	}
}

static void on_write( uv_write_t* req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->handle->data);
	if (status)
	{
		log_error_conn_sys( conn, "write error", status);
		uv_close( (uv_handle_t*)req->handle, on_close);
	}
	strus_init_request( conn);
	uv_read_start( (uv_stream_t*)&conn->tcp, on_alloc, on_read);
}

#if (UV_VERSION_NUM>10)
static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
#else
static void on_read( uv_stream_t* handle, ssize_t nread, uv_buf_t bufstruct)
{
	const uv_buf_t* buf = &bufstruct;
#endif
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	unsigned char* dp;
	unsigned int nn;
	unsigned int bufidx = 0;

	if (nread > 0)
	{
		switch (conn->state)
		{
			case CTX_READDATASIZE:
				dp = (unsigned char*)&conn->readbufsize + conn->hdrbytes;
				nn = (unsigned int)nread;
				if (nn > sizeof(int32_t) - conn->hdrbytes)
				{
					nn = sizeof(int32_t) - conn->hdrbytes;
				}
				conn->hdrbytes += nn;
				memcpy( dp, buf->base, nn);
				bufidx += nn;
				if (conn->hdrbytes == sizeof(int32_t))
				{
					conn->state = CTX_READDATA;
					conn->readbufsize = ntohl( conn->readbufsize);
					if (conn->readbufsize > CONNECTION_MAXBUFSIZE)
					{
						log_error_conn( conn, "request message size out of range");
						uv_close( (uv_handle_t*)handle, on_close);
						return;
					}
					conn->readbuf = (unsigned char*)malloc( conn->readbufsize);
					if (conn->readbuf == NULL)
					{
						log_error_conn( conn, "memory allocation error (request buffer)");
						uv_close( (uv_handle_t*)handle, on_close);
						return;
					}
				}
				else
				{
					return;
				}
				/*no break here!*/
			case CTX_READDATA:
				if (buf->len < nread)
				{
					nn = buf->len - bufidx;
				}
				else
				{
					nn = nread - bufidx;
				}
				if (nn > conn->readbufsize - conn->readbufpos)
				{
					log_error_conn( conn, "data size mismatch in request");
					uv_close( (uv_handle_t*)handle, on_close);
					return;
				}
				memcpy( conn->readbuf + conn->readbufpos, (unsigned char*)buf->base + bufidx, nn);
				conn->readbufpos += nn;
				if (conn->readbufpos < conn->readbufsize)
				{
					/* ... have to read more */
					return;
				}
				conn->state = CTX_PROCESS;
				uv_read_stop( handle);
				/*no break here!*/
			case CTX_PROCESS:
				push_work_queue( conn);
				break;
			case CTX_TERMINATED:
				log_error_conn( conn, "got request data after termination");
				uv_close( (uv_handle_t*)handle, on_close);
				break;
		}
	}
	else
	{
		if (nread == UV_EOF)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			log_message_conn( conn, "got eof");
#endif
			conn->state = CTX_TERMINATED;
			uv_shutdown( &conn->shutdown_req, handle, on_shutdown);
		}
		else
		{
			log_error_conn_sys( conn, "disconnected", nread);
			uv_close( (uv_handle_t*)handle, on_close);
		}
	}
}

static void on_connected( uv_stream_t* stream, int status)
{
	static int connection_id_cnt = 0;
	strus_connection_t* conn = 0;
	int res = 0;

	if (status != 0)
	{
		log_error_sys( "connection refused", status);
		return;
	}
	conn = (strus_connection_t*)calloc( 1, sizeof( strus_connection_t));
	if (!conn)
	{
		log_error( "connection refused: out of memory");
		goto ERROR_CLEANUP;
	}
	res = uv_tcp_init( stream->loop, &conn->tcp);
	if (res)
	{
		log_error_sys( "connection refused: init tcp context failed", res);
		goto ERROR_CLEANUP;
	}
	res = uv_accept( stream, (uv_stream_t*)&conn->tcp);
	if (res)
	{ 
		log_error_sys( "error in accept connection", res);
		goto ERROR_CLEANUP;
	}
	res = g_glbctx->init_handlerdata( &conn->handlerdata);
	if (res)
	{
		log_error( "error in initializing connection handler data");
		goto ERROR_CLEANUP;
	}
	conn->id = ++connection_id_cnt;
	conn->tcp.data = conn;
	uv_read_start((uv_stream_t*)&conn->tcp, on_alloc, on_read);
	return;

ERROR_CLEANUP:
	strus_free_connection( conn);
}

static void on_signal( uv_signal_t *handle, int signum)
{
	const char* msg = "received signal unknown";
	switch (signum)
	{
		case SIGINT:	msg = "received signal SIGINT"; break;
		case SIGILL:	msg = "received signal SIGILL"; break;
		case SIGABRT:	msg = "received signal SIGABRT"; break;
		case SIGFPE:	msg = "received signal SIGFPE"; break;
		case SIGSEGV:	msg = "received signal SIGSEGV"; break;
		case SIGTERM:	msg = "received signal SIGTERM"; break;
		case SIGHUP:	msg = "received signal SIGHUP"; break;
	}
	if (signum == SIGHUP)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		log_message( msg);
#endif
	}
	else
	{
		log_message( msg);
		log_message( "shutting down server now ...");
		uv_signal_stop( handle);
		uv_stop( g_server.loop);
	}
}


static void on_work( uv_work_t *req)
{
	strus_connection_t* conn = (strus_connection_t*)( req->data);
	int err = 0;
	uint32_t msghdr;

#ifdef STRUS_LOWLEVEL_DEBUG
	log_message_conn( conn, "started request");
	strus_hexdump( g_glbctx->logf, "REQUEST", conn->readbuf, conn->readbufpos);
#endif
	err = g_glbctx->request_handler(
		&conn->handlerdata, conn->readbuf, conn->readbufpos, sizeof(uint32_t), &conn->output, &conn->outputsize);
	if (err)
	{
		log_error_request( conn, (char*)conn->output);
		uv_close( (uv_handle_t*)&conn->tcp, on_close);
		return;
	}
	memset( &conn->write_req, 0, sizeof( conn->write_req));
	conn->write_req.data = conn;
	conn->write_reqbuf.base = (char*)conn->output;
	conn->write_reqbuf.len = conn->outputsize;
	msghdr = htonl( conn->outputsize - sizeof( uint32_t));
	memcpy( conn->write_reqbuf.base, &msghdr, sizeof( uint32_t));
}

void on_complete_work( uv_work_t *req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->data);
	if (status == UV_ECANCELED)
	{
		log_message_conn( conn, "request execution canceled");
		uv_close( (uv_handle_t*)&conn->tcp, on_close);
	}
	else if (status != 0)
	{
		log_error_conn( conn, "error in request, aborted");
		uv_close( (uv_handle_t*)&conn->tcp, on_close);
	}
	else
	{
		int err;
#ifdef STRUS_LOWLEVEL_DEBUG
		strus_hexdump( g_glbctx->logf, "ANSWER", conn->output, conn->outputsize);
#endif
		err = uv_write( &conn->write_req, (uv_stream_t*)&conn->tcp, &conn->write_reqbuf, 1, on_write);
		if (err)
		{
			log_error_conn_sys( conn, "write error", err);
			uv_close( (uv_handle_t*)&conn->tcp, on_close);
		}
#ifdef STRUS_LOWLEVEL_DEBUG
		else
		{
			log_message_conn( conn, "completed request");
		}
#endif
	}
}

static void push_work_queue( strus_connection_t* conn)
{
	memset( &conn->work_req, 0, sizeof(conn->work_req));
	conn->work_req.data = (void*)conn;
	uv_queue_work( g_server.loop, &conn->work_req, on_work, on_complete_work);
}

int strus_run_server( unsigned short port, unsigned int nofThreads, strus_globalctx_t* glbctx)
{
	int res;
	struct sockaddr_in addr;
#define NOF_SIGNALS 7
	int signalar[ NOF_SIGNALS] = {SIGINT,SIGILL,SIGABRT,SIGFPE,SIGSEGV,SIGTERM,SIGHUP};
	uv_signal_t signal[ NOF_SIGNALS];
	int ii;

	if (g_glbctx)
	{
		log_error( "cannot run two server instances");
		return -1;
	}
	g_glbctx = glbctx;

	memset( &g_server, 0, sizeof(g_server));
	uv_tcp_init( uv_default_loop(), &g_server);

	for (ii=0; ii<NOF_SIGNALS; ++ii)
	{
		uv_signal_init( g_server.loop, &signal[ ii]);
		uv_signal_start( &signal[ ii], on_signal, signalar[ ii]);
	}
#if (UV_VERSION_NUM>10)
	uv_ip4_addr( "0.0.0.0", port, &addr);
	res = uv_tcp_bind( &g_server, (const struct sockaddr*) &addr, 0);
#else
	addr = uv_ip4_addr( "0.0.0.0", port);
	res = uv_tcp_bind( &g_server, addr);
#endif
	if (res < 0)
	{
		log_error_sys( "error in bind", res);
		return -1;
	}
	res = uv_listen( (uv_stream_t*)&g_server, 256, on_connected);
	if (res < 0)
	{
		log_error_sys( "error in listen", res);
		return -2;
	}
	res = uv_run( g_server.loop, UV_RUN_DEFAULT);
	if (res != 0)
	{
		log_error( "server event loop was aborted");
	}
#if (UV_VERSION_NUM>10)
	uv_loop_close( g_server.loop);
#endif
	g_glbctx = 0;
	return res;
}

