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
#include "rpcClientMessaging.hpp"
extern "C" {
#include "client.h"
#include "hexdump.h"
}
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <arpa/inet.h>

using namespace strus;

#undef STRUS_LOWLEVEL_DEBUG

RpcClientMessaging::RpcClientMessaging( const char* config)
	:m_conn(0),m_starttime(0.0),m_conn_open(false)
{
	int syserr = 0;
	m_conn = strus_create_connection( config, stderr, &syserr);
	if (!m_conn) throw std::runtime_error( std::string( "could not connect to server: ") + strerror(syserr));
}

RpcClientMessaging::~RpcClientMessaging()
{
	if (m_conn)
	{
		if (m_conn_open) strus_close_connection( m_conn);
		strus_destroy_connection( m_conn);
	}
}

static void packMessageLen( std::string& buf, uint32_t size)
{
	uint32_t vv = htonl( size);
	buf.append( (const char*)&vv, 4);
}

static std::string resultString( unsigned char* result, std::size_t resultsize)
{
	try
	{
		std::string rt( (char*)result, resultsize);
		std::free( result);
		return rt;
	}
	catch (const std::bad_alloc&)
	{
		std::free( result);
		throw std::bad_alloc();
	}
}

std::string RpcClientMessaging::sendRequest( const std::string& content)
{
	unsigned char* result = 0;
	std::size_t resultsize = 0;

	if (m_messageBuffer.size() > 1)
	{
		packMessageLen( m_messageBuffer, content.size());
		m_messageBuffer.append( content);
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send multipart request to server [" << m_messageBuffer.size() << " bytes]" << std::endl;
#endif
		int ec = strus_request(
				m_conn,
				(const unsigned char*)m_messageBuffer.c_str(), m_messageBuffer.size(),
				&result, &resultsize);

		m_messageBuffer.clear();
		if (ec) throw std::runtime_error( std::string( "send request failed: ") + strus_lasterror( m_conn));
		return resultString( result, resultsize);
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send request to server [" << content.size() << " bytes]" << std::endl;
#endif
		int ec = strus_request(
				m_conn,
				(const unsigned char*)content.c_str(), content.size(),
				&result, &resultsize);

		if (ec) throw std::runtime_error( std::string( "send request failed: ") + strus_lasterror( m_conn));
		return resultString( result, resultsize);
	}
}

void RpcClientMessaging::sendMessage( const std::string& content)
{
	if (m_messageBuffer.size() == 0)
	{
		m_messageBuffer.push_back( (unsigned char)0xFF);
	}
	packMessageLen( m_messageBuffer, content.size());
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "append request to out buffer [" << content.size() << " bytes]" << std::endl;
#endif
	m_messageBuffer.append( content);
}

std::string RpcClientMessaging::synchronize()
{
	unsigned char* result = 0;
	std::size_t resultsize = 0;
	if (m_messageBuffer.size() > 0)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send synchronize request to server [" << m_messageBuffer.size() << " bytes]" << std::endl;
#endif
		int ec = strus_request(
				m_conn,
				(const unsigned char*)m_messageBuffer.c_str(), m_messageBuffer.size(),
				&result, &resultsize);

		m_messageBuffer.clear();
		if (ec) throw std::runtime_error( std::string( "send synchronize failed: ") + strus_lasterror( m_conn));
		return resultString( result, resultsize);
	}
	return std::string();
}

void RpcClientMessaging::close()
{
	if (m_conn)
	{
		strus_close_connection( m_conn);
		m_conn_open = true;
	}
}

