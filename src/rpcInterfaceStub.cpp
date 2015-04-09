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
#include <stdexcept>
#include <limits>

using namespace strus;

static utils::Mutex g_mutex_objIdCnt;
int unsigned RpcInterfaceStub::m_objIdCnt = 0;

RpcInterfaceStub::RpcInterfaceStub( unsigned char classId_, unsigned int objId_, const RpcRemoteEndPoint& endpoint_)
	:m_classId(classId_),m_objId(objId_),m_endpoint(endpoint_)
{}

RpcInterfaceStub::RpcInterfaceStub( unsigned char classId_, const RpcRemoteEndPoint& endpoint_)
	:m_classId(classId_),m_objId(0),m_endpoint(endpoint_)
{
	utils::ScopedLock lock( g_mutex_objIdCnt);
	if (RpcInterfaceStub::m_objIdCnt >= std::numeric_limits<uint32_t>::max())
	{
		throw std::runtime_error("too many remote objects created (RPC)");
	}
	m_objId = ++RpcInterfaceStub::m_objIdCnt;
}

RpcInterfaceStub::RpcInterfaceStub( const RpcInterfaceStub& o)
	:m_classId(o.m_classId),m_objId(o.m_objId),m_endpoint(o.m_endpoint){}

RpcInterfaceStub::RpcInterfaceStub()
	:m_classId(0),m_objId(0),m_endpoint(){}



