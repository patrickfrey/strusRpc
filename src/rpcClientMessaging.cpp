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
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>
#include <errno.h>

using namespace strus;

#undef STRUS_LOWLEVEL_DEBUG
#define DEFAULT_PORT "7181"

struct ServiceAddress
{
	char hostname[ 256];
	char port[ 8];

	void init()
	{
		std::memcpy( port, DEFAULT_PORT, std::strlen( DEFAULT_PORT)+1);
		hostname[0] = '\0';
	}

	ServiceAddress()
	{
		init();
	}
	explicit ServiceAddress( const char* config);
};


ServiceAddress::ServiceAddress( const char* config)
{
	init();
	char const* portstr = std::strchr( config, '\0');
	std::size_t configlen = (std::size_t)(portstr - config);
	std::size_t hostnamelen = configlen;
	if (hostnamelen >= sizeof(hostname))
	{
		throw std::runtime_error( "invalid host configuration (host name length)");
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
	std::memcpy( hostname, config, hostnamelen);
	hostname[ hostnamelen] = 0;

	if (portstr > config)
	{
		unsigned int portno = 0;
		unsigned int ii=0;
		for (; *portstr; ++portstr,++ii)
		{
			if (*portstr < '0' || *portstr > '9' || portno > 65535)
			{
				throw std::runtime_error( "rpc client messaging invalid host configuration");
			}
			portno = portno * 10 + (*portstr - '0');
			port[ii] = *portstr;
		}
	}
}

RpcClientMessaging::RpcClientMessaging( const char* config)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;

	memset(&hints, 0, sizeof( struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = IPPROTO_TCP; /* Any protocol */
	
	ServiceAddress address( config);

#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "resolving address hostname '" << address.hostname << "' port " << address.port << std::endl;
#endif
	int ai = getaddrinfo( address.hostname, address.port, &hints, &result);
	if (ai != 0)
	{
		throw std::runtime_error( std::string( "getaddrinfo: ") + gai_strerror(ai));
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		m_sock = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (m_sock < 0) continue;

		if (connect( m_sock, rp->ai_addr, rp->ai_addrlen) != -1)
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
	if (errno == 0)
	{
		return std::string( msg);
	}
	else
	{
		char errmsg[32];
		snprintf( errmsg, sizeof(errmsg), "%d", errno);
		return std::string( msg) + " (errno " + errmsg + ")";
	}
}

RpcClientMessaging::~RpcClientMessaging()
{
	close( m_sock);
}

void RpcClientMessaging::send_req( const char* msg, std::size_t msgsize)
{
	uint32_t msgsizebuf = htonl( msgsize);
	if (0>write( m_sock, &msgsizebuf, sizeof(msgsizebuf)))
	{
		throw std::runtime_error( errorstr("rpc client messaging error sending"));
	}
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
	uint32_t msgsizebuf;
	unsigned int msgsizebufpos = 0;

	while (msgsizebufpos < sizeof(msgsizebuf))
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "read sizeof reply from server" << std::endl;
#endif
		int nn = read( m_sock, (char*)&msgsizebuf + msgsizebufpos, sizeof(msgsizebuf)-msgsizebufpos);
		if (nn <= 0)
		{
			if (nn == 0) break;
			throw std::runtime_error( errorstr( "rpc client messaging error reading from socket"));
		}
		msgsizebufpos += (uint32_t)nn;
	}
	uint32_t msgsize = ntohl( msgsizebuf);
	while (rt.size() < msgsize)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "read reply of server" << std::endl;
#endif
		int nn = read( m_sock, buf, bufsize);
		if (nn <= 0)
		{
			if (nn == 0) break;
			throw std::runtime_error( errorstr( "rpc client messaging error reading from socket"));
		}
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "got answer from server [" << nn << " bytes]" << std::endl;
#endif
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
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send multipart request to server [" << m_messageBuffer.size() << " bytes]" << std::endl;
#endif
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());

		m_messageBuffer.clear();
		return recv_rep();
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send request to server [" << content.size() << " bytes]" << std::endl;
#endif
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
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "append request to out buffer [" << content.size() << " bytes]" << std::endl;
#endif
	m_messageBuffer.append( content);
}

std::string RpcClientMessaging::synchronize()
{
	if (m_messageBuffer.size() > 0)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "send synchronize request to server [" << m_messageBuffer.size() << " bytes]" << std::endl;
#endif
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());
		m_messageBuffer.clear();
		return recv_rep();
	}
	return std::string();
}

