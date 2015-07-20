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
#ifndef _STRUS_RPC_SERVERC_HPP_INCLUDED
#define _STRUS_RPC_SERVERC_HPP_INCLUDED
#include <uv.h>
#include <stddef.h>

struct strus_handlerdata_t;
struct strus_globalctx_t;

typedef int (*request_handler_f)(
		struct strus_handlerdata_t* handlerdata,
		unsigned char* readbuf,
		size_t readbufsize,
		unsigned char** output,
		size_t* outputsize);

typedef int (*init_handlerdata_f)(
		struct strus_handlerdata_t* handler,
		struct strus_globalctx_t* glbctx);

typedef void (*done_handlerdata_f)(
		struct strus_handlerdata_t* handler);


typedef struct strus_handlerdata_t
{
	char _reserved[64];
} strus_handlerdata_t;

typedef struct strus_globalctx_t
{
	void* data;
	init_handlerdata_f init_handlerdata;
	done_handlerdata_f done_handlerdata;
	request_handler_f request_handler;
	FILE* logf;
} strus_globalctx_t;

int strus_run_server( unsigned short port, unsigned int nofThreads, strus_globalctx_t* glbctx);

#endif


