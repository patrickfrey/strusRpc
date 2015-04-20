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
#ifndef _STRUS_RPC_INTERFACE_STUB_HPP_INCLUDED
#define _STRUS_RPC_INTERFACE_STUB_HPP_INCLUDED
#include "strus/rpcClientMessagingInterface.hpp"
#include "constConstructor.hpp"
#include <string>

namespace strus {

class RpcInterfaceStub
{
public:
	virtual ~RpcInterfaceStub(){}

	RpcInterfaceStub( unsigned char classId_, unsigned int objId_, RpcClientMessagingInterface* messaging_);
	RpcInterfaceStub( const RpcInterfaceStub& o);
	RpcInterfaceStub();

	unsigned char classId() const					{return m_classId;}
	unsigned int objId() const					{return m_objId;}

	void enter() const;
	const ConstConstructor* constConstructor() const		{return &m_constConstructor;}

	std::string rpc_sendRequest( const std::string& msg) const;
	void rpc_sendMessage( const std::string& msg) const;
	void rpc_synchronize() const;

	RpcClientMessagingInterface* messaging() const			{return m_messaging;}

private:
	void handleError( const std::string& msgstr) const;

private:
	unsigned char m_classId;
	unsigned int m_objId;
	mutable RpcClientMessagingInterface* m_messaging;
	ConstConstructor m_constConstructor;
};

}//namespace
#endif


