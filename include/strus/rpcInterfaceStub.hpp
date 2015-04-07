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
#include <string>
#include "strus/index.hpp"

namespace strus {
namespace rpc {

class RcpInterfaceStub
{
public:
	class RemoteEndPoint
	{
	public:
		RemoteEndPoint();
		RemoteEndPoint( const char* config);
		RemoteEndPoint( const RemoteEndPoint& o);
	};

	class Message
	{
	public:
		Message(){}
		Message( const Message& o)
			:m_content(o.m_content){}
		Message( unsigned char classId_, unsigned int objId_);

		void packObject( unsigned char classId_, unsigned int objId_);
		void packString( const std::string& str);
		void packCharp( const char* buf);
		void packBuffer( const char* buf, std::size_t size);
		void packBool( bool val);
		void packIndex( const Index& index);
		void packGlobalCounter( const GlobalCounter& index);
		void packUint( unsigned int val);
		void packInt( unsigned int val);
		void packFloat( float val);
		void packSize( std::size_t size);

		unsigned int unpackObject( std::size_t& itr, unsigned char& classId_);
		std::string unpackString( std::size_t& itr);
		const char* unpackCharp( std::size_t& itr);
		const char* unpackBuffer( std::size_t& itr, std::size_t& size);
		bool unpackBool( std::size_t& itr);
		Index unpackIndex( std::size_t& itr);
		GlobalCounter unpackGlobalCounter( std::size_t& itr);
		unsigned int unpackUint( std::size_t& itr);
		int unpackInt( std::size_t& itr);
		float unpackFloat( std::size_t& itr);
		std::size_t unpackSize( std::size_t& itr);

		const std::string& content() const
		{
			return m_content;
		}

	private:
		std::string m_content;
	};

public:
	virtual ~RcpInterfaceStub(){}

	RcpInterfaceStub( unsigned char classId_, const RemoteEndPoint& endpoint_);
	RcpInterfaceStub( const RcpInterfaceStub& o);
	RcpInterfaceStub();

	unsigned char classId() const			{return m_classId;}
	unsigned int objId() const			{return m_objId;}

	void sendMessage( const std::string& msg);

private:
	static unsigned int m_objIdCnt;
	unsigned char m_classId;
	unsigned int m_objId;
	RemoteEndPoint m_endpoint;
};

}}//namespace
#endif


