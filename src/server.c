#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STRUS_LOWLEVEL_DEBUG

/* Shared global data */
static strus_globalctx_t* g_glbctx=0;
#define CONNECTION_MAXBUFSIZE (1<<24)
#define CONNECTION_BUFSIZE 8192
#define CONNECTION_INIT_CHUNKSIZE 8192


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
	int32_t readbufpos;			/* number of bytes filled of read request buffer */
	int32_t readbufsize;			/* size of read request buffer */
	int32_t hdrbytes;			/* number of bytes read in state CTX_READDATASIZE */
	uv_shutdown_t shutdown_req;		/* preallocated shutdown request data structure */
	uv_buf_t reqbuf;			/* preallocated buffer for request */
	uv_write_t write_req;			/* preallocated write request data structure */
	unsigned char* output;			/* output of request */
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

static void log_error_request( strus_connection_t* ctx, const char* msg)
{
	fprintf( g_glbctx->logf, "[conn %u] error processing request: %s\n", ctx->id, msg);
}

static void log_error_conn_sys( strus_connection_t* ctx, const char* msg, int err)
{
	fprintf( g_glbctx->logf, "[conn %u] %s (%s)\n", ctx->id, msg, strerror(err));
}

static void log_error_conn( strus_connection_t* ctx, const char* msg)
{
	fprintf( g_glbctx->logf, "[conn %u] %s\n", ctx->id, msg);
}

static void log_error_sys( const char* msg, int err)
{
	fprintf( g_glbctx->logf, "[server] %s (%s)\n", msg, strerror(err));
}

static void log_error( const char* msg)
{
	fprintf( g_glbctx->logf, "[server] %s\n", msg);
}

static void on_alloc( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	buf->base = conn->buf;
	buf->len = CONNECTION_BUFSIZE;
	/* ... safe because our on_read() allocations never overlap */
}

static void on_close( uv_handle_t* handle)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	strus_free_connection( conn);
}

static void on_shutdown( uv_shutdown_t* handle, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	if (status != 0)
	{
		log_error_conn_sys( conn, "error on shutdown", status);
	}
	uv_close( (uv_handle_t*)handle, on_close);
}

static void on_write( uv_write_t* req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->handle->data);
	if (status)
	{
		log_error_conn_sys( conn, "write error", status);
		uv_close( (uv_handle_t*)req->handle, on_close);
	}
	conn->state = CTX_READDATASIZE;
}

static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	unsigned char* dp;
	unsigned int nn;
	unsigned int bufidx = 0;
	int err = 0;

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
					conn->readbufsize = htonl( conn->readbufsize);
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
				conn->state = CTX_READDATA;
				/*no break here!*/
			case CTX_READDATA:
				nn = buf->len - bufidx;
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
				/*no break here!*/
			case CTX_PROCESS:
				err = g_glbctx->request_handler(
					&conn->handlerdata, conn->readbuf, conn->readbufpos, &conn->output, &conn->outputsize);
				if (err)
				{
					log_error_request( conn, (char*)conn->output);
					uv_close( (uv_handle_t*)handle, on_close);
					return;
				}
				memset( &conn->write_req, 0, sizeof(conn->write_req));
				conn->write_req.data = conn;
				conn->reqbuf = uv_buf_init( (char*)conn->output, conn->outputsize);
				err = uv_write( &conn->write_req, handle, &conn->reqbuf, 1, on_write);
				if (err)
				{
					log_error_conn_sys( conn, "write error", err);
					uv_close( (uv_handle_t*)handle, on_close);
					break;
				}
				break;
			case CTX_TERMINATED:
				log_error_conn( conn, "got request data after termination");
				uv_close( (uv_handle_t*)handle, on_close);
				break;
		}
	}
	else
	{
		int err = -nread;
		if (err == UV_EOF)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			log_error_conn( conn, "got eof");
#endif
			conn->state = CTX_TERMINATED;
			uv_shutdown( &conn->shutdown_req, handle, on_shutdown);
		}
		else
		{
			log_error_conn_sys( conn, "disconnected", err);
		}
		uv_close( (uv_handle_t*)handle, on_close);
	}
}

void on_connected( uv_stream_t* stream, int status) {
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
	res = g_glbctx->init_handlerdata( &conn->handlerdata, g_glbctx);
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

int strus_run_server( unsigned short port, unsigned int nofThreads, strus_globalctx_t* glbctx)
{
	uv_tcp_t server;
	int res;
	struct sockaddr_in addr;

	if (g_glbctx)
	{
		log_error( "cannot run two server instances");
		return -1;
	}
	g_glbctx = glbctx;

	memset( &server, 0, sizeof(server));
	uv_ip4_addr("0.0.0.0", port, &addr);

	uv_tcp_init( uv_default_loop(), &server);
	res = uv_tcp_bind( &server, (const struct sockaddr*) &addr, 0);
	if (res < 0)
	{
		log_error_sys( "error in bind", res);
		return -1;
	}
	res = uv_listen( (uv_stream_t*)&server, 256, on_connected);
	if (res < 0)
	{ 
		log_error_sys( "error in listen", res);
		return -2;
	}
	if (0!=uv_run( server.loop, UV_RUN_DEFAULT))
	{
		log_error_sys( "server event loop was aborted", res);
		return -3;
	}
	g_glbctx = 0;
	return 0;
}

