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
#include "strus/rpcInterfaceStub.hpp"
#include <stdexcept>
#include <limits>

using namespace strus;
using namespace strus::rpc;

static utils::Mutex g_mutex_ptrIdCnt;
int unsigned RcpInterfaceStub::m_ptrIdCnt = 0;

RcpInterfaceStub::RcpInterfaceStub( unsigned short objectId_)
	:m_objectId(objectId_),m_ptrId(0)
{
	if (RcpInterfaceStub::m_ptrIdCnt >= std::numeric_limits<unsigned int>::max())
	{
		throw std::runtime_error("too many remote objects created (RPC)");
	}
	utils::ScopedLock lock( g_mutex_ptrIdCnt);
	m_ptrId = ++RcpInterfaceStub::m_ptrIdCnt;
}

RcpInterfaceStub::RcpInterfaceStub( const RcpInterfaceStub& o)
	:m_objectId(o.m_objectId),m_ptrId(o.m_ptrId){}

RcpInterfaceStub::RcpInterfaceStub()
	:m_objectId(0),m_ptrId(0){}



