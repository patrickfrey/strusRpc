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
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <uv.h>

#define CONNECTION_MAXBUFSIZE (1<<24)
#define CONNECTION_BUFSIZE (1<<14)
#undef STRUS_LOWLEVEL_DEBUG

typedef struct strus_connection_t
{
	uv_loop_t loop;				/* event loop */
	uv_tcp_t tcp;				/* tcp socket handle */
	uv_connect_t connect;			/* connect structure */
	uv_write_t writereq;			/* request structure for write */
	int syserrno;				/* system errno in case of error */
	FILE* logf;				/* where to log error and info messages */
	char buf[ CONNECTION_BUFSIZE];		/* memory blocks served for malloc in read */
	unsigned char* output;			/* buffer for output*/
	uint32_t outputsize;			/* sizeof buffer for output in bytes */
	uint32_t outputpos;			/* sizeof read output in bytes */
	size_t outputstate;			/* state of output reader */
} strus_connection_t;

static void on_alloc( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
static void on_write( uv_write_t* req, int status);
static void on_close( uv_handle_t* handle);
static void on_connect( uv_connect_t* connection, int status);


strus_connection_t* strus_create_connection(
		const char* ip, unsigned short port, int* errno_)
{
	strus_connection_t* rt;
	struct sockaddr_in addr;

	rt = (strus_connection_t*)calloc( 1, sizeof( strus_connection_t));
	if (rt == NULL)
	{
		*errno_ = ENOMEM;
		return NULL;
	}
	*errno_ = uv_loop_init( &rt->loop);
	if (*errno_) goto ERROREXIT;

	uv_tcp_init( &rt->loop, &rt->tcp);
	rt->loop.data = rt;
	uv_tcp_keepalive( &rt->tcp, 1, 60);
	uv_tcp_nodelay( &rt->tcp, 1);
	rt->logf = stderr;

	*errno_ = uv_ip4_addr( ip, port, &addr);
	if (*errno_) goto ERROREXIT;

	rt->connect.data = rt;
	*errno_ = uv_tcp_connect( &rt->connect, &rt->tcp, (const struct sockaddr*)&addr, on_connect);
	if (*errno_) goto ERROREXIT;

	uv_run( &rt->loop, UV_RUN_ONCE);
	if (rt->syserrno)
	{
		*errno_ = rt->syserrno;
		if (*errno_) goto ERROREXIT;
	}
	return rt;

ERROREXIT:
	if (rt) strus_destroy_connection( rt);
	return NULL;
}

void strus_close_connection(
		strus_connection_t* conn)
{
	uv_close( (uv_handle_t*)&conn->tcp, on_close);
	uv_run( &conn->loop, UV_RUN_ONCE);
}

void strus_destroy_connection(
		strus_connection_t* conn)
{
	uv_stop( &conn->loop);
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
		const unsigned char** output, size_t* outputsize)
{
	uint32_t msgsize = htonl( inputsize);
	uv_buf_t msg[2];
	msg[0].base = (char*)&msgsize;
	msg[0].len = sizeof(msgsize);
	msg[1].base = (char*)input;
	msg[1].len = inputsize;

	conn->syserrno = uv_write( &conn->writereq, (uv_stream_t*)&conn->tcp, msg, 2, on_write);
	while (uv_loop_alive( &conn->loop))
	{
		uv_run( &conn->loop, UV_RUN_ONCE);
	}
	if (conn->syserrno == 0)
	{
		*output = conn->output;
		*outputsize = conn->outputpos;
		conn->output = 0;
		conn->outputpos = 0;
		conn->outputsize = 0;
	}
	return conn->syserrno;
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
	if (status)
	{
		conn->syserrno = status;
		fprintf( conn->logf, "error connecting: %d\n", status);
	}
}

static void on_close( uv_handle_t* handle)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	if (conn->logf)
	{
		fprintf( conn->logf, "connection closed\n");
	}
}

static void on_write( uv_write_t* req, int status)
{
	strus_connection_t* conn = (strus_connection_t*)( req->handle->data);
	if (status)
	{
		if (conn->logf)
		{
			fprintf( conn->logf, "error in write (%d)\n", status);
		}
		uv_close( (uv_handle_t*)req->handle, on_close);
		conn->syserrno = status;
	}
	else if (conn->logf)
	{
		fprintf( conn->logf, "sent request\n");
	}
	uv_read_start( (uv_stream_t*)&conn->tcp, on_alloc, on_read);
}

static void on_read( uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	strus_connection_t* conn = (strus_connection_t*)( handle->data);
	unsigned char* dp;
	unsigned int nn;
	unsigned int bufidx = 0;

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
					if (conn->logf) fprintf( conn->logf, "request message size out of range\n");
					uv_close( (uv_handle_t*)handle, on_close);
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
			if (conn->logf) fprintf( conn->logf, "data size mismatch in request\n");
			uv_close( (uv_handle_t*)handle, on_close);
			return;
		}
		memcpy( conn->output + conn->outputpos, (unsigned char*)buf->base + bufidx, nn);
		conn->outputpos += nn;
		if (conn->outputpos == conn->outputsize)
		{
			uv_read_stop( handle);
			if (conn->logf) fprintf( conn->logf, "got request (%d)\n", conn->outputpos);
		}
	}
	else
	{
		if (conn->logf) fprintf( conn->logf, "disconnected (%d)\n", (int)nread);
		uv_close( (uv_handle_t*)handle, on_close);
	}
}
