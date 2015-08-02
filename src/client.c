/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#include "client.h"
#include "hexdump.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <uv.h>

#define DEFAULT_PORT 7181
#define CONNECTION_MAXBUFSIZE (1<<24)
#define CONNECTION_BUFSIZE (1<<14)
#define STRUS_LOWLEVEL_DEBUG
#undef STRUS_LOG_REQUEST_TIME

typedef struct strus_connection_t
{
	uv_loop_t loop;				/* event loop */
	uv_tcp_t tcp;				/* tcp socket handle */
	uv_connect_t connect;			/* connect structure */
	uv_getaddrinfo_t addrinforeq;		/* request structure for getaddrinfo */
	struct addrinfo* addrinfores;		/* result of getaddrinfo */
	struct addrinfo* addrinfoitr;		/* getaddrinfo iterator */
	uv_write_t writereq;			/* request structure for write */
	int syserrno;				/* system errno in case of error */
	FILE* logf;				/* where to log error and info messages */
	char buf[ CONNECTION_BUFSIZE];		/* memory blocks served for malloc in read */
	unsigned char* output;			/* buffer for output*/
	uint32_t outputsize;			/* sizeof buffer for output in bytes */
	uint32_t outputpos;			/* sizeof read output in bytes */
	size_t outputstate;			/* state of output reader */
	double reqstart;			/* timestamp start re */
	int closed;				/* 1=close was already called, 0=not yet called */
} strus_connection_t;

static void on_getaddrinfo(uv_getaddrinfo_t* req, int status, struct addrinfo* res);
static void on_alloc( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
static void on_write( uv_write_t* req, int status);
static void on_close( uv_handle_t* handle);
static void on_connect( uv_connect_t* connection, int status);
static void on_walk_cleanup( uv_handle_t* handle, void* conn_);

#ifdef STRUS_LOG_REQUEST_TIME
static double gettimestamp()
{
	struct timeval now;
	gettimeofday( &now, NULL);
	return (double)now.tv_usec / 1000000.0 + now.tv_sec;
}

static void log_time( FILE* out, double start, const char* msg)
{
	double now = gettimestamp();
	fprintf( out, "time %s %.4f seconds\n", msg, now - start);
	start = now;
}
#endif



typedef struct service_address_t
{
	char hostname[ 256];
	char portstr[ 16];
	unsigned short port;
} service_address_t;

static void init_service_address( service_address_t* saddr)
{
	saddr->port = DEFAULT_PORT;
	saddr->hostname[0] = '\0';
	saddr->portstr[0] = '\0';
}

static int parse_service_address( service_address_t* saddr, const char* config)
{
	char const* portstr;
	size_t configlen;
	size_t hostnamelen;

	init_service_address( saddr);
	portstr = strchr( config, '\0');
	configlen = (size_t)(portstr - config);
	hostnamelen = configlen;
	if (hostnamelen >= sizeof(saddr->hostname))
	{
		return ENOMEM;
	}
	for (; portstr > config && (*(portstr-1) != ':'); --hostnamelen,--portstr){}
	if (portstr > config)
	{
		hostnamelen -= 1;
	}
	else
	{
		hostnamelen = configlen;
	}
	memcpy( saddr->hostname, config, hostnamelen);
	saddr->hostname[ hostnamelen] = 0;

	if (portstr > config)
	{
		unsigned int portno = 0;
		unsigned int ii=0;
		for (; *portstr; ++portstr,++ii)
		{
			if (*portstr < '0' || *portstr > '9' || portno > 65535)
			{
				return EINVAL;
			}
			saddr->portstr[ii] = *portstr;
			portno = portno * 10 + (*portstr - '0');
		}
		saddr->port = (unsigned short)portno;
		saddr->portstr[ii] = '\0';
	}
	return 0;
}



strus_connection_t* strus_create_connection(
		const char* config, FILE* logf, int* errno_)
{
	strus_connection_t* rt;
	service_address_t saddr;
	struct addrinfo hints;

	*errno_ = parse_service_address( &saddr, config);
	if (*errno_ != 0) return NULL;

	rt = (strus_connection_t*)calloc( 1, sizeof( strus_connection_t));
	if (rt == NULL)
	{
		*errno_ = ENOMEM;
		return NULL;
	}
	rt->logf = logf;
#ifdef STRUS_LOG_REQUEST_TIME
	rt->reqstart = gettimestamp();
#endif
	*errno_ = uv_loop_init( &rt->loop);
	if (*errno_) goto ERROREXIT;

	uv_tcp_init( &rt->loop, &rt->tcp);
	rt->loop.data = rt;
	uv_tcp_keepalive( &rt->tcp, 1, 60);
	uv_tcp_nodelay( &rt->tcp, 1);
	rt->logf = stderr;

	rt->addrinforeq.data = rt;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = IPPROTO_TCP; /* TCP protocol */

	*errno_ = uv_getaddrinfo( &rt->loop, &rt->addrinforeq, on_getaddrinfo, saddr.hostname, saddr.portstr, &hints);
	if (*errno_ != 0) goto ERROREXIT;
	uv_run( &rt->loop, UV_RUN_DEFAULT);
	if (rt->syserrno)
	{
		*errno_ = rt->syserrno;
		goto ERROREXIT;
	}
#ifdef STRUS_LOG_REQUEST_TIME
	log_time( rt->logf, rt->reqstart, "connection");
#endif
	return rt;

ERROREXIT:
	if (rt) strus_destroy_connection( rt);
	if (*errno_ < 0) *errno_ = -*errno_;
	return NULL;
}

void strus_close_connection(
		strus_connection_t* conn)
{
	int close_rt;
	uv_walk( &conn->loop, on_walk_cleanup, conn);
	do
	{
		uv_run( &conn->loop, UV_RUN_DEFAULT);
		close_rt = uv_loop_close( &conn->loop);
	} while (-close_rt == EBUSY);
	if (close_rt != 0 && conn->logf) fprintf( conn->logf, "failed to cleanup all connection handles (%d)\n", (int)close_rt);
}

void strus_destroy_connection(
		strus_connection_t* conn)
{
	uv_stop( &conn->loop);
	if (!conn->closed)
	{
		strus_close_connection( conn);
		conn->closed = 1/*true*/;
	}
	if (conn->output != NULL)
	{
		free( conn->output);
		conn->output = NULL;
	}
	if (conn->logf != NULL && conn->logf != stderr && conn->logf != stdout)
	{
		fclose( conn->logf);
		conn->logf = NULL;
	}
	free( conn);
}

int strus_request(
		strus_connection_t* conn,
		const unsigned char* input, size_t inputsize,
		unsigned char** output, size_t* outputsize)
{
	uint32_t msgsize = htonl( inputsize);
	uv_buf_t msg[2];
	msg[0].base = (char*)&msgsize;
	msg[0].len = sizeof(msgsize);
	msg[1].base = (char*)input;
	msg[1].len = inputsize;

#ifdef STRUS_LOWLEVEL_DEBUG
	if (conn->logf) strus_hexdump( conn->logf, "REQUEST SIZE", (unsigned char*)&msgsize, sizeof( msgsize));
	if (conn->logf) strus_hexdump( conn->logf, "REQUEST", input, inputsize);
#endif
	conn->syserrno = 0;
#ifdef STRUS_LOG_REQUEST_TIME
	conn->reqstart = gettimestamp();
#endif
	conn->syserrno = uv_write( &conn->writereq, (uv_stream_t*)&conn->tcp, msg, 2, on_write);
	uv_run( &conn->loop, UV_RUN_DEFAULT);
	if (conn->syserrno == 0)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		if (conn->logf) strus_hexdump( conn->logf, "ANSWER", conn->output, conn->outputsize);
#endif
		*output = conn->output;
		*outputsize = conn->outputpos;
	}
	else
	{
		if (conn->logf) fprintf( conn->logf, "error in request: %s\n", uv_strerror( conn->syserrno));
	}
#ifdef STRUS_LOG_REQUEST_TIME
	log_time( conn->logf, conn->reqstart, "request");
#endif
	conn->outputstate = 0;
	conn->output = 0;
	conn->outputpos = 0;
	conn->outputsize = 0;
	conn->reqstart = 0.0;
	if (conn->syserrno < 0) conn->syserrno = -conn->syserrno;
	return conn->syserrno;
}

const char* strus_lasterror(
		struct strus_connection_t* conn)
{
	return uv_strerror( conn->syserrno);
}

static void try_connect( strus_connection_t* conn)
{
	struct addrinfo *address = conn->addrinfoitr;
	int syerr = 0;

	for (; address; address = conn->addrinfoitr = address->ai_next)
	{
		if (address->ai_family == AF_INET)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			char addrbuf[ 64];
			if (0!=uv_ip4_name( (const struct sockaddr_in*)address->ai_addr, addrbuf, sizeof(addrbuf)))
			{
				addrbuf[0] = 0;
			}
			if (conn->logf) fprintf( conn->logf, "getaddrinfo try IPv4 '%s'\n", addrbuf);
#endif
			memset( &conn->connect, 0, sizeof(conn->connect));
			conn->connect.data = conn;
			syerr = uv_tcp_connect( &conn->connect, &conn->tcp, address->ai_addr, on_connect);
			if (syerr != 0)
			{
				conn->syserrno = syerr;
				if (conn->logf) fprintf( conn->logf, "error trying to connect IPv4: %s\n", uv_strerror(syerr));
			}
			else
			{
				break;
			}
		}
		else if (address->ai_family == AF_INET6)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			char addrbuf[ 64];
			if (0!=uv_ip6_name( (const struct sockaddr_in6*)address->ai_addr, addrbuf, sizeof(addrbuf)))
			{
				addrbuf[0] = 0;
			}
			if (conn->logf) fprintf( conn->logf, "getaddrinfo try IPv6 '%s'\n", addrbuf);
#endif
			memset( &conn->connect, 0, sizeof(conn->connect));
			conn->connect.data = conn;
			syerr = uv_tcp_connect( &conn->connect, &conn->tcp, address->ai_addr, on_connect);
			if (syerr != 0)
			{
				conn->syserrno = syerr;
				if (conn->logf) fprintf( conn->logf, "error trying to connect IPv6: %s\n", uv_strerror(syerr));
			}
			else
			{
				break;
			}
		}
	}
	if (!address)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		if (conn->logf) fprintf( conn->logf, "getaddrinfo failed to resolve address\n");
#endif
		uv_freeaddrinfo( conn->addrinfores);
		uv_stop( &conn->loop);
	}
}

static void on_getaddrinfo( uv_getaddrinfo_t* req, int status, struct addrinfo* res)
{
	strus_connection_t* conn = (strus_connection_t*)( req->data);
#ifdef STRUS_LOWLEVEL_DEBUG
	if (conn->logf) fprintf( conn->logf, "getaddrinfo callback called\n");
#endif
	if (status != 0)
	{
		uv_freeaddrinfo( res);
		conn->syserrno = status;
		uv_stop( &conn->loop);
		return;
	}
	conn->addrinfores = res;
	conn->addrinfoitr = res;

	try_connect( conn);
}

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

void on_connect( uv_connect_t* connection, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( connection->data);
#ifdef STRUS_LOWLEVEL_DEBUG
	if (conn->logf) fprintf( conn->logf, "connect callback called\n");
#endif
	if (status)
	{
		conn->syserrno = status;
		if (conn->logf) fprintf( conn->logf, "error connecting: %s\n", uv_strerror( status));

		conn->addrinfoitr = conn->addrinfoitr->ai_next;
		try_connect( conn);
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		if (conn->logf) fprintf( conn->logf, "got connected\n");
#endif
		uv_freeaddrinfo( conn->addrinfores);
		conn->tcp.data = conn;
		uv_stop( &conn->loop);
	}
}

static void on_close( uv_handle_t* handle)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	if (conn->logf) fprintf( conn->logf, "close callback called\n");
#endif
}

static void on_write( uv_write_t* req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->handle->data);
#ifdef STRUS_LOWLEVEL_DEBUG
	if (conn->logf) fprintf( conn->logf, "write callback called\n");
#endif
	if (status)
	{
		if (conn->syserrno == 0)
		{
			conn->syserrno = status;
		}
		if (conn->logf) fprintf( conn->logf, "error in write (%s)\n", uv_strerror( status));
		uv_close( (uv_handle_t*)req->handle, on_close);
		uv_stop( &conn->loop);
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		if (conn->logf) fprintf( conn->logf, "sent request\n");
#endif
		uv_read_start( (uv_stream_t*)&conn->tcp, on_alloc, on_read);
	}
}

static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	unsigned char* dp;
	unsigned int nn;
	unsigned int bufidx = 0;

#ifdef STRUS_LOWLEVEL_DEBUG
	if (conn->logf) fprintf( conn->logf, "read callback called (nread %d)\n", (int)nread);
#endif
	if (nread > 0)
	{
		if (conn->outputstate < sizeof(conn->outputsize))
		{
			dp = (unsigned char*)&conn->outputsize + conn->outputstate;
			nn = (unsigned int)nread;
			if (nn > sizeof(int32_t) - conn->outputstate)
			{
				nn = sizeof(int32_t) - conn->outputstate;
			}
			conn->outputstate += nn;
			memcpy( dp, buf->base, nn);
			bufidx += nn;
			if (conn->outputstate == sizeof(int32_t))
			{
				conn->outputsize = ntohl( conn->outputsize);
				conn->outputpos = 0;
				if (conn->outputsize > CONNECTION_MAXBUFSIZE)
				{
					conn->syserrno = EINVAL;
					if (conn->logf) fprintf( conn->logf, "request message size out of range\n");
					uv_close( (uv_handle_t*)handle, on_close);
					uv_stop( &conn->loop);
					return;
				}
				if (conn->output != NULL)
				{
					free (conn->output);
				}
				conn->output = (unsigned char*)malloc( conn->outputsize);
				if (conn->output == NULL)
				{
					conn->syserrno = ENOMEM;
					uv_close( (uv_handle_t*)handle, on_close);
					uv_stop( &conn->loop);
					return;
				}
			}
			else
			{
				return; /*... to read more*/
			}
		}
		if (buf->len < nread)
		{
			nn = buf->len - bufidx;
		}
		else
		{
			nn = nread - bufidx;
		}
		if (nn > conn->outputsize - conn->outputpos)
		{
			fprintf( stderr, "REQUEST state=%d, nn=%d, pos=%d, size=%d\n", (int)conn->outputstate, (int)nn, (int)conn->outputpos, (int)conn->outputsize);
			conn->syserrno = EINVAL;
			if (conn->logf) fprintf( conn->logf, "data size mismatch in request\n");
			uv_close( (uv_handle_t*)handle, on_close);
			uv_stop( &conn->loop);
			return;
		}
		memcpy( conn->output + conn->outputpos, (unsigned char*)buf->base + bufidx, nn);
		conn->outputpos += nn;
		if (conn->outputpos == conn->outputsize)
		{
			uv_stop( &conn->loop);
#ifdef STRUS_LOWLEVEL_DEBUG
			if (conn->logf) fprintf( conn->logf, "got request (%d)\n", conn->outputpos);
#endif
		}
	}
	else
	{
		if (conn->syserrno == 0)
		{
			conn->syserrno = nread;
		}
		if (conn->logf) fprintf( conn->logf, "disconnected (%s)\n", uv_strerror((int)nread));
		uv_close( (uv_handle_t*)handle, on_close);
		uv_stop( &conn->loop);
	}
}

static void on_walk_cleanup( uv_handle_t* handle, void* conn_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	strus_connection_t* conn = (strus_connection_t*)conn_;
	if (conn->logf) fprintf( conn->logf, "called walk cleanup callback\n");
#endif
	/*if (!uv_is_closing((uv_handle_t*)handle))*/
	uv_close( handle, on_close);
}


