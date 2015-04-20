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
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>
#include <errno.h>

using namespace strus;

RpcClientMessaging::RpcClientMessaging( const char* config)
{
	char hostnamebuf[ 256];
	int port = 7181;
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	char const* portstr = std::strchr( config, ':');
	const char* hostname = config;
	if (portstr)
	{
		std::size_t nn = (std::size_t)(portstr - config);
		if (nn >= sizeof(hostnamebuf))
		{
			throw std::runtime_error( "invalid host configuration (host name length)");
		}
		std::memcpy( hostnamebuf, config, nn);
		hostnamebuf[ nn] = 0;
		hostname = hostnamebuf;

		++portstr;
		port = 0;
		for (; *portstr; ++portstr)
		{
			if (*portstr < '0' || *portstr < '9' || port > 65535)
			{
				throw std::runtime_error( "rpc client messaging invalid host configuration");
			}
			port = port * 10 + (*portstr - '0');
		}
	}
	memset(&hints, 0, sizeof( struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */
	
	int ai = getaddrinfo( hostname, NULL, &hints, &result);
	if (ai != 0)
	{
		throw std::runtime_error( std::string( "getaddrinfo: ") + gai_strerror(ai));
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		m_sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (m_sock < 0) continue;
	
		if (connect( m_sock, rp->ai_addr, rp->ai_addrlen) > 0)
		{
			break;
		}
		close( m_sock);
	}
	if (!rp)
	{
		freeaddrinfo(result);
		throw std::runtime_error( errorstr("rpc client messaging could not connect"));
	}
	freeaddrinfo( result);
}

static void packMessageLen( std::string& buf, uint32_t size)
{
	uint32_t vv = htonl( size);
	buf.append( (const char*)&vv, 4);
}

std::string RpcClientMessaging::errorstr( const char* msg)
{
	char errmsg[32];
	snprintf( errmsg, sizeof(errmsg), "%d", errno);
	return std::string( msg) + "(errno " + errmsg + ")";
}

RpcClientMessaging::~RpcClientMessaging()
{
	close( m_sock);
}

void RpcClientMessaging::send_req( const char* msg, std::size_t msgsize)
{
	int nn = write( m_sock, msg, msgsize);
	if (nn < 0)
	{
		throw std::runtime_error( errorstr("rpc client messaging error sending"));
	}
}

std::string RpcClientMessaging::recv_rep()
{
	std::string rt;
	enum {bufsize=4096};
	char buf[ bufsize];
	for (;;)
	{
		int nn = read( m_sock, buf, bufsize);
		if (nn <= 0)
		{
			if (nn == 0) break;
			throw std::runtime_error( errorstr( "rpc client messaging error reading from socket"));
		}
		rt.append( buf, nn);
	}
	return rt;
}

std::string RpcClientMessaging::sendRequest( const std::string& content)
{
	if (m_messageBuffer.size() > 1)
	{
		packMessageLen( m_messageBuffer, content.size());
		m_messageBuffer.append( content);
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());
		m_messageBuffer.clear();
		return recv_rep();
	}
	else
	{
		send_req( content.c_str(), content.size());
		return recv_rep();
	}
}

void RpcClientMessaging::sendMessage( const std::string& content)
{
	if (m_messageBuffer.size() == 0)
	{
		m_messageBuffer.push_back( (unsigned char)0xFF);
	}
	packMessageLen( m_messageBuffer, content.size());
	m_messageBuffer.append( content);
}

std::string RpcClientMessaging::synchronize()
{
	if (m_messageBuffer.size() > 0)
	{
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());
		m_messageBuffer.clear();
		return recv_rep();
	}
	return std::string();
}

