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
#ifndef _STRUS_RPC_SERVER_H_INCLUDED
#define _STRUS_RPC_SERVER_H_INCLUDED
#include <stddef.h>
#include <stdio.h>

struct strus_handlerdata_t;
struct strus_globalctx_t;

/* Request handler function */
typedef int (*request_handler_f)(
		struct strus_handlerdata_t* handlerdata,	/* data of the request handler (this) */
		const unsigned char* readbuf,			/* pointer to request input */
		size_t readbufsize,				/* sizeof of readbuf in bytes */
		size_t outputhdrsize,				/* number of bytes to reserve in the header of the output to be patched by the caller (server) */
		const unsigned char** output,			/* returned pointer to output of the request handler */
		size_t* outputsize);				/* returned size of the request answer in bytes */

/* Create handler data */
typedef int (*init_handlerdata_f)(
		struct strus_handlerdata_t* handler);		/* data of the request handler (this) to initialize */

/* Dispose handler data */
typedef void (*done_handlerdata_f)(
		struct strus_handlerdata_t* handler);		/* data of the request handler (this) to deinitialize */


typedef struct strus_handlerdata_t
{
	char _reserved[64];
} strus_handlerdata_t;

typedef struct strus_globalctx_t
{
	init_handlerdata_f init_handlerdata;			/* request handler constructor */
	done_handlerdata_f done_handlerdata;			/* request handler destructor */
	request_handler_f request_handler;			/* request handler function */
	FILE* logf;						/* file to log to */
} strus_globalctx_t;

int strus_run_server( unsigned short port, unsigned int nofThreads, strus_globalctx_t* glbctx);

#endif


