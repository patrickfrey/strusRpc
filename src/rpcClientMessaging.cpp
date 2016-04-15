/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "rpcClientMessaging.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"
#include "strus/errorBufferInterface.hpp"
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
#include "strus/base/stdint.h"
#include <errno.h>
#include <arpa/inet.h>


using namespace strus;

#undef STRUS_LOWLEVEL_DEBUG

RpcClientMessaging::RpcClientMessaging( const char* config, ErrorBufferInterface* errorhnd_)
	:m_conn(0),m_starttime(0.0),m_conn_open(false),m_errorhnd(errorhnd_)
{
	int syserr = 0;
	m_conn = strus_create_connection( config, stderr, &syserr);
	if (!m_conn) throw strus::runtime_error( _TXT("could not connect to server: %s"), strerror(syserr));
	m_conn_open = true;
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
	try
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
			if (ec) throw strus::runtime_error( _TXT("send request failed: %s"), strus_lasterror( m_conn));
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
	
			if (ec) throw strus::runtime_error( _TXT( "send request failed: %s"), strus_lasterror( m_conn));
			return resultString( result, resultsize);
		}
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error in send request of RPC client: %s"), *m_errorhnd, std::string());
}

void RpcClientMessaging::sendMessage( const std::string& content)
{
	try
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
	CATCH_ERROR_MAP( _TXT("error in send message of RPC client: %s"), *m_errorhnd);
}

std::string RpcClientMessaging::synchronize()
{
	try
	{
		unsigned char* result = 0;
		std::size_t resultsize = 0;
		if (m_messageBuffer.size() > 0)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			std::cerr << _TXT("send synchronize request to server ") << "[" << m_messageBuffer.size() << " bytes]" << std::endl;
#endif
			int ec = strus_request(
					m_conn,
					(const unsigned char*)m_messageBuffer.c_str(), m_messageBuffer.size(),
					&result, &resultsize);
	
			m_messageBuffer.clear();
			if (ec) throw strus::runtime_error( _TXT("send synchronize failed: "), strus_lasterror( m_conn));
			return resultString( result, resultsize);
		}
		return std::string();
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error in send synchronize of RPC client: %s"), *m_errorhnd, std::string());
}

void RpcClientMessaging::close()
{
	if (m_conn && m_conn_open)
	{
		strus_close_connection( m_conn);
		m_conn_open = false;
	}
}

