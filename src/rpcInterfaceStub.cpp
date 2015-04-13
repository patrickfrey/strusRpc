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
#include "private/utils.hpp"
#include "rpcInterfaceStub.hpp"
#include "rpcSerializer.hpp"
#include <stdexcept>
#include <limits>

#define STRUS_RPC_TEST
#ifdef STRUS_RPC_TEST
#include "rpcServer.hpp"
#endif

using namespace strus;

RpcInterfaceStub::RpcInterfaceStub( unsigned char classId_, unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
	:m_classId(classId_),m_objId(objId_),m_endpoint(endpoint_)
{}

RpcInterfaceStub::RpcInterfaceStub( const RpcInterfaceStub& o)
	:m_classId(o.m_classId),m_objId(o.m_objId),m_endpoint(o.m_endpoint){}

RpcInterfaceStub::RpcInterfaceStub()
	:m_classId(0),m_objId(0),m_endpoint(){}


void RpcInterfaceStub::enter() const
{
	m_constConstructor.reset();
}

#ifdef STRUS_RPC_TEST
static RpcServer g_srv;
static std::string g_answer;
#endif

void RpcInterfaceStub::rpc_send( const std::string& msg) const
{
#ifdef STRUS_RPC_TEST
	g_answer = g_srv.handleRequest( msg);
#endif
}

static void handleResultError( const std::string& msgstr)
{
	if (msgstr.empty()) throw std::runtime_error( "got no answer from server");
	RpcDeserializer msg( msgstr);
	RpcReturnType returntype = (RpcReturnType)msg.unpackByte();
	switch (returntype)
	{
		case MsgTypeException_BadAlloc:
			throw std::runtime_error( std::string("method call failed: ") + msg.unpackString());
		case MsgTypeException_RuntimeError:
			throw std::runtime_error( std::string("method call failed: ") + msg.unpackString());
		case MsgTypeException_LogicError:
			throw std::logic_error( std::string("method call failed: ") + msg.unpackString());
		case MsgTypeAnswer:
			break;
	}
}

std::string RpcInterfaceStub::rpc_recv() const
{
#ifdef STRUS_RPC_TEST
	handleResultError( g_answer);
	return g_answer;
#endif
}

void RpcInterfaceStub::rpc_waitAnswer() const
{
#ifdef STRUS_RPC_TEST
	if (g_answer.empty()) return;
	handleResultError( g_answer);
#endif
}


