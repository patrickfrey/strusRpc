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
#include <netinet/in.h>
#include <stdint.h>
using namespace strus;

static void packUint( std::string& buf, uint32_t size)
{
	uint32_t vv = htonl( size);
	buf.append( (const char*)&vv, 4);
}

static void unpackUint( char const*& itr, const char* end, void* ptr)
{
	if (itr+4 > end) throw std::runtime_error( "message to small to encode next dword");
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	*(uint32_t*)ptr = ntohl( val);
}


RpcClientMessaging::RpcClientMessaging( const char* config)
{
	m_messageBuffer.push_back( 0xFF);
}

RpcClientMessaging::~RpcClientMessaging(){}

std::string RpcClientMessaging::sendRequest( const std::string& content)
{
	if (m_messageBuffer.size() > 1)
	{
		packUint( m_messageBuffer, content.size());
		m_messageBuffer.append( content);
	}
	else
	{
		send content as request
	}
}

void RpcClientMessaging::sendMessage( const std::string& content)
{
	packUint( m_messageBuffer, content.size());
	m_messageBuffer.append( content);
}

std::string RpcClientMessaging::synchronize()
{
	send m_messageBuffer as request
	m_messageBuffer.clear();
	m_messageBuffer.push_back( 0xFF);
}

