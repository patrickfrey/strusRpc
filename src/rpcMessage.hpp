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
#ifndef _STRUS_RPC_MESSAGE_STUB_HPP_INCLUDED
#define _STRUS_RPC_MESSAGE_STUB_HPP_INCLUDED
#include <string>
#include "rpcInterfaceStub.hpp"
#include "strus/index.hpp"

namespace strus {

class RcpMessage
{
public:
	RcpMessage(){}
	RcpMessage( const RcpMessage& o)
		:m_content(o.m_content){}
	RcpMessage( unsigned char classId_, unsigned int objId_);

	void packObject( unsigned char classId_, unsigned int objId_);
	void packString( const std::string& str);
	void packCharp( const char* buf);
	void packBuffer( const char* buf, std::size_t size);
	void packBool( bool val);
	void packByte( unsigned char val);
	void packIndex( const Index& index);
	void packGlobalCounter( const GlobalCounter& index);
	void packUint( unsigned int val);
	void packInt( int val);
	void packFloat( float val);
	void packSize( std::size_t size);
	void packArithmeticVariant( const ArithmeticVariant& val);
	void packCrc32();

	unsigned int unpackObject( char const*& itr, unsigned char& classId_);
	std::string unpackString( char const*& itr);
	const char* unpackCharp( char const*& itr);
	const char* unpackBuffer( char const*& itr, std::size_t& size);
	bool unpackBool( char const*& itr);
	unsigned char unpackByte( char const*& itr);
	Index unpackIndex( char const*& itr);
	GlobalCounter unpackGlobalCounter( char const*& itr);
	unsigned int unpackUint( char const*& itr);
	int unpackInt( char const*& itr);
	float unpackFloat( char const*& itr);
	std::size_t unpackSize( char const*& itr);
	ArithmeticVariant unpackArithmeticVariant( char const*& itr);
	bool unpackCrc32( char const*& itr);

	const std::string& content() const
	{
		return m_content;
	}

private:
	std::string m_content;
};

}//namespace
#endif

