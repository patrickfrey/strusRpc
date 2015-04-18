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
#include <nn.h>
#include <reqrep.h>
#include <netinet/in.h>
#include <stdint.h>
#include <errno.h>

using namespace strus;

static void packUint( std::string& buf, uint32_t size)
{
	uint32_t vv = htonl( size);
	buf.append( (const char*)&vv, 4);
}

RpcClientMessaging::RpcClientMessaging( const char* config)
{
	m_sock = nn_socket( AF_SP, NN_REQ);
	if (m_sock < 0) switch (errno)
	{
		case EAFNOSUPPORT:
			throw std::runtime_error( "error connecting to server (nanomsg: specified address family is not supported)");
		case EINVAL:
			throw std::runtime_error( "error connecting to server (nanomsg: unknown protocol)");
		case EMFILE:
			throw std::runtime_error( "error connecting to server (nanomsg: the limit on the total number of open SP sockets or OS limit for file descriptors has been reached");
		case ETERM:
			throw std::runtime_error( "error connecting to server (nanomsg: the library is terminating");
		default:
			throw std::runtime_error( "error connecting to server (socket create)");
	}
	if (nn_connect( m_sock, config) < 0) switch (errno)
	{
		case EBADF:
			throw std::runtime_error( "error connecting to server (nanomsg: the provided socket is invalid");
		case EMFILE:
			throw std::runtime_error( "error connecting to server (nanomsg: maximum number of active endpoints was reached");
		case ETERM:
			throw std::runtime_error( "error connecting to server (nanomsg: the library is terminating");
		case EINVAL:
			throw std::runtime_error( "error connecting to server (nanomsg: the syntax of the supplied address is invalid");
		case ENAMETOOLONG:
			throw std::runtime_error( "error connecting to server (nanomsg: the supplied address is too long");
		case EPROTONOSUPPORT:
			throw std::runtime_error( "error connecting to server (nanomsg: the requested transport protocol is not supported");
		case ENODEV:
			throw std::runtime_error( "error connecting to server (nanomsg: address specifies a nonexistent interface");
		default:
			throw std::runtime_error( "error connecting to server (nanomsg: unknown error)");
	}
}

RpcClientMessaging::~RpcClientMessaging()
{
	if (m_recvbuf) nn_freemsg( m_recvbuf);
	nn_close( m_sock);
}

void RpcClientMessaging::send_req( const char* msg, std::size_t msgsize)
{
	if (m_recvbuf) nn_freemsg( m_recvbuf);
	m_recvbuf = 0;
	if (nn_send( m_sock, msg, msgsize, 0) < 0) switch (errno)
	{
		case EFAULT:
			throw std::runtime_error( "error sending request to server (nanomsg: buf is NULL or len is NN_MSG and the message pointer (pointed to by buf) is NULL");
		case EBADF:
			throw std::runtime_error( "error sending request to server (nanomsg: the provided socket is invalid");
		case ENOTSUP:
			throw std::runtime_error( "error sending request to server (nanomsg: the operation is not supported by this socket type");
		case EFSM:
			throw std::runtime_error( "error sending request to server (nanomsg: the operation cannot be performed on this socket at the moment because the socket is not in the appropriate state");
		case EAGAIN:
			throw std::runtime_error( "error sending request to server (nanomsg: non-blocking mode was requested and the message cannot be sent at the moment");
		case EINTR:
			throw std::runtime_error( "error sending request to server (nanomsg: the operation was interrupted by delivery of a signal before the message was sent");
		case ETIMEDOUT:
			throw std::runtime_error( "error sending request to server (nanomsg: timeout on socket");
		case ETERM:
			throw std::runtime_error( "error sending request to server (nanomsg: the library is terminating");
		default:
			throw std::runtime_error( "error sending request to server (nanomsg: unknown error)");
	}
}

void RpcClientMessaging::recv_rep( const char*& msg, std::size_t& msgsize)
{
	if (m_recvbuf) nn_freemsg( m_recvbuf);
	m_recvbuf = 0;
	msgsize = nn_recv( m_sock, &m_recvbuf, NN_MSG, 0);
	if (msgsize < 0) switch (errno)
	{
		case EBADF:
			throw std::runtime_error( "error receiving request from server (nanomsg: the provided socket is invalid");
		case ENOTSUP:
			throw std::runtime_error( "error receiving request from server (nanomsg: the operation is not supported by this socket type");
		case EFSM:
			throw std::runtime_error( "error receiving request from server (nanomsg: the operation cannot be performed on this socket at the moment because the socket is not in the appropriate state");
		case EAGAIN:
			throw std::runtime_error( "error receiving request from server (nanomsg: non-blocking mode was requested and there’s no message to receive at the moment");
		case EINTR:
			throw std::runtime_error( "error receiving request from server (nanomsg: the operation was interrupted by delivery of a signal before the message was received.");
		case ETIMEDOUT:
			throw std::runtime_error( "error receiving request from server (nanomsg: timeout on socket");
		case ETERM:
			throw std::runtime_error( "error receiving request from server (nanomsg: the library is terminating");
		default:
			throw std::runtime_error( "error receiving request from server (nanomsg: unknown error)");
	}
	msg = (const char*)m_recvbuf;
}

std::string RpcClientMessaging::sendRequest( const std::string& content)
{
	if (m_messageBuffer.size() > 1)
	{
		packUint( m_messageBuffer, content.size());
		m_messageBuffer.append( content);
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());
		const char* msg;
		std::size_t msgsize;
		recv_rep( msg, msgsize);
		return std::string( msg, msgsize);
	}
	else
	{
		send_req( content.c_str(), content.size());
		const char* msg;
		std::size_t msgsize;
		recv_rep( msg, msgsize);
		return std::string( msg, msgsize);
	}
}

void RpcClientMessaging::sendMessage( const std::string& content)
{
	if (m_messageBuffer.size() == 0)
	{
		m_messageBuffer.push_back( (unsigned char)0xFF);
	}
	packUint( m_messageBuffer, content.size());
	m_messageBuffer.append( content);
}

std::string RpcClientMessaging::synchronize()
{
	if (m_messageBuffer.size() > 0)
	{
		send_req( m_messageBuffer.c_str(), m_messageBuffer.size());
		const char* msg;
		std::size_t msgsize;
		recv_rep( msg, msgsize);
		return std::string( msg, msgsize);
		m_messageBuffer.clear();
	}
	return std::string();
}

