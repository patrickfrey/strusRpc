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
#include "rpcMessage.hpp"
#include "private/utils.hpp"
#include <stdexcept>
#include <cstring>
#include <limits>
#include <netinet/in.h>
#include <stdint.h>

using namespace strus;

namespace {

template <int>
static void pack( std::string& buf, const void* ptr);
template <int>
static void unpack( char const*& itr, const char* end, void* ptr);

template <>
void pack<1>( std::string& buf, const void* ptr)
{
	buf.push_back( ((const char*)ptr)[0]);
}
template <>
void unpack<1>( char const*& itr, const char* end, void* ptr)
{
	if (itr+1 > end) throw std::runtime_error( "message to small to encode next byte");
	*(char*)ptr = *itr++;
}

template <>
void pack<2>( std::string& buf, const void* ptr)
{
	uint16_t vv = htons( *(const uint16_t*)ptr);
	buf.append( (const char*)&vv, 2);
}
template <>
void unpack<2>( char const*& itr, const char* end, void* ptr)
{
	if (itr+2 > end) throw std::runtime_error( "message to small to encode next word");
	uint16_t val;
	std::memcpy( &val, itr, 2);
	itr += 2;
	*(uint16_t*)ptr = ntohs( val);
}

template <>
void pack<4>( std::string& buf, const void* ptr)
{
	uint32_t vv = htonl( *(const uint32_t*)ptr);
	buf.append( (const char*)&vv, 4);
}
template <>
void unpack<4>( char const*& itr, const char* end, void* ptr)
{
	if (itr+4 > end) throw std::runtime_error( "message to small to encode next dword");
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	*(uint32_t*)ptr = ntohl( val);
}

template <>
void pack<8>( std::string& buf, const void* ptr)
{
	uint32_t vhi = htonl( *((const uint64_t*)ptr) >> 32);
	uint32_t vlo = htonl( *((const uint64_t*)ptr) & 0xffFFffFFUL);
	
	buf.append( (const char*)&vhi, 4);
	buf.append( (const char*)&vlo, 4);
}
template <>
void unpack<8>( char const*& itr, const char* end, void* ptr)
{
	if (itr+8 > end) throw std::runtime_error( "message to small to encode next qword");
	uint32_t vlo;
	uint32_t vhi;
	unpack<4>( itr, end, &vhi);
	unpack<4>( itr, end, &vlo);
	*(uint64_t*)ptr = ((uint64_t)vhi << 32) + vlo;
}



template <typename SCALAR>
void packScalar( std::string& buf, const SCALAR& val)
{
	pack<sizeof(SCALAR)>( buf, &val);
}
template <typename SCALAR>
SCALAR unpackScalar( char const*& itr, const char* end)
{
	SCALAR val;
	unpack<sizeof(SCALAR)>( itr, end, &val);
	return val;
}
}

void RcpMessage::packObject( unsigned char classId_, unsigned int objId_)
{
	if (objId_ > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "object id out of range");
	packScalar( m_content, classId_);
	packScalar( m_content, (uint32_t)objId_);
}

void RcpMessage::packString( const std::string& str)
{
	if (str.size() > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "string size out of range");
	packScalar( m_content, (uint32_t)str.size());
	m_content.append( str);
	
}

void RcpMessage::packCharp( const char* buf)
{
	m_content.append( buf);
	m_content.push_back( '\0');
}

void RcpMessage::packBuffer( const char* buf, std::size_t size)
{
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "buffer size out of range");
	packScalar( m_content, (uint32_t)size);
	m_content.append( buf, size);
}

void RcpMessage::packBool( bool val)
{
	m_content.push_back( val?1:0);
}

void RcpMessage::packByte( unsigned char val)
{
	m_content.push_back( val);
}

void RcpMessage::packIndex( const Index& index)
{
	packScalar( m_content, index);
}

void RcpMessage::packGlobalCounter( const GlobalCounter& index)
{
	packScalar( m_content, index);
}

void RcpMessage::packUint( unsigned int val)
{
	if (val > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "packed uint out of range");
	packScalar( m_content, (uint32_t)val);
}

void RcpMessage::packInt( int val)
{
	if (val > std::numeric_limits<int32_t>::max()
	||  val < std::numeric_limits<int32_t>::min()) throw std::runtime_error( "packed int out of range");
	packScalar( m_content, (int32_t)val);
}

void RcpMessage::packFloat( float val)
{
	pack<sizeof(float)>( m_content, &val);
}

void RcpMessage::packSize( std::size_t size)
{
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "packed size out of range");
	packScalar( m_content, (uint32_t)size);
}

void RcpMessage::packArithmeticVariant( const ArithmeticVariant& val)
{
	packByte( (unsigned char)val.type);
	switch (val.type)
	{
		case ArithmeticVariant::Null: break;
		case ArithmeticVariant::Int: packInt( val.variant.Int); break;
		case ArithmeticVariant::UInt: packUint( val.variant.UInt); break;
		case ArithmeticVariant::Float: packFloat( val.variant.Float); break;
	}
}

void RcpMessage::packDatabaseOptions( const DatabaseOptions& val)
{
	packUint( val.opt());
}

void RcpMessage::packDatabaseConfigType( const DatabaseInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RcpMessage::packStorageConfigType( const StorageInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RcpMessage::packTokenizerConfig( const TokenizerConfig& val)
{
	packString( val.name());
	packSize( val.arguments().size());
	std::vector<std::string>::const_iterator
		ai = val.arguments().begin(),
		ae = val.arguments().end();
	for (; ai != ae; ++ai)
	{
		packString( *ai);
	}
}

void RcpMessage::packNormalizerConfig( const NormalizerConfig& val)
{
	packString( val.name());
	packSize( val.arguments().size());
	std::vector<std::string>::const_iterator
		ai = val.arguments().begin(),
		ae = val.arguments().end();
	for (; ai != ae; ++ai)
	{
		packString( *ai);
	}
}

void RcpMessage::packSummarizerConfig( const SummarizerConfig& val)
{
	std::map<std::string,ArithmeticVariant>::const_iterator
		ni = val.numericParameters().begin(), ne = val.numericParameters().end();
	packSize( val.numericParameters().size());
	for (; ni != ne; ++ni)
	{
		packString( ni->first);
		packArithmeticVariant( ni->second);
	}
	std::map<std::string,std::string>::const_iterator
		ti = val.textualParameters().begin(), te = val.textualParameters().end();
	packSize( val.textualParameters().size());
	for (; ti != te; ++ti)
	{
		packString( ti->first);
		packString( ti->second);
	}
	std::map<std::string,std::string>::const_iterator
		fi = val.featureParameters().begin(), fe = val.featureParameters().end();
	packSize( val.featureParameters().size());
	for (; fi != fe; ++fi)
	{
		packString( fi->first);
		packString( fi->second);
	}
}

void RcpMessage::packWeightingConfig( const WeightingConfig& val)
{
	std::map<std::string,ArithmeticVariant>::const_iterator
		ni = val.numericParameters().begin(), ne = val.numericParameters().end();
	packSize( val.numericParameters().size());
	for (; ni != ne; ++ni)
	{
		packString( ni->first);
		packArithmeticVariant( ni->second);
	}
}

void RcpMessage::packCompareOperator( const QueryInterface::CompareOperator& val)
{
	packByte( (unsigned char)val);
}

void RcpMessage::packFeatureParameter( const SummarizerFunctionInterface::FeatureParameter& val)
{
	packUint( val.classidx());
	const RpcInterfaceStub* obj = dynamic_cast<const RpcInterfaceStub*>( val.feature().postingIterator());
	if (!obj) throw std::runtime_error( "passing non RPC interface object in RPC call");
	packObject( obj->classId(), obj->objId());
	packSize( val.feature().variables().size());
	std::vector<SummarizationVariable>::const_iterator
		vi = val.feature().variables().begin(),
		ve = val.feature().variables().end();
	for (; vi != ve; ++vi)
	{
		packString( vi->name());
		const RpcInterfaceStub* so = dynamic_cast<const RpcInterfaceStub*>( vi->itr());
		if (!so) throw std::runtime_error( "passing non RPC interface object in RPC call");
		packObject( so->classId(), so->objId());
	}
}

void RcpMessage::packCrc32()
{
	packScalar( m_content, utils::Crc32::calc( m_content.c_str(), m_content.size()));
}

unsigned int RcpMessage::unpackObject( char const*& itr, const char* end, unsigned char& classId_)
{
	classId_ = unpackScalar<char>( itr, end);
	return unpackScalar<uint32_t>( itr, end);
}

std::string RcpMessage::unpackString( char const*& itr, const char* end)
{
	std::string rt;
	uint32_t size = unpackScalar<uint32_t>( itr, end);
	if (itr+size > end) throw std::runtime_error( "message to small to encode next string");
	rt.append( itr, size);
	itr += size;
	return rt;
}

const char* RcpMessage::unpackCharp( char const*& itr, const char* end)
{
	const char* start = itr;
	while (itr < end && *itr) ++itr;
	if (itr == end)
	{
		throw std::runtime_error( "message to small to encode next C string");
	}
	++itr;
	return start;
}

const char* RcpMessage::unpackBuffer( char const*& itr, const char* end, std::size_t& size)
{
	size = unpackScalar<uint32_t>( itr, end);
	const char* rt = itr;
	itr += size;
	return rt;
}

bool RcpMessage::unpackBool( char const*& itr, const char* end)
{
	return (*itr++ != 0)?true:false;
}

unsigned char RcpMessage::unpackByte( char const*& itr, const char* end)
{
	return *itr++;
}

Index RcpMessage::unpackIndex( char const*& itr, const char* end)
{
	return unpackScalar<Index>( itr, end);
}

GlobalCounter RcpMessage::unpackGlobalCounter( char const*& itr, const char* end)
{
	return unpackScalar<GlobalCounter>( itr, end);
}

unsigned int RcpMessage::unpackUint( char const*& itr, const char* end)
{
	return unpackScalar<uint32_t>( itr, end);
}

int RcpMessage::unpackInt( char const*& itr, const char* end)
{
	return unpackScalar<uint32_t>( itr, end);
}

float RcpMessage::unpackFloat( char const*& itr, const char* end)
{
	return unpackScalar<float>( itr, end);
}

std::size_t RcpMessage::unpackSize( char const*& itr, const char* end)
{
	return unpackScalar<uint32_t>( itr, end);
}

ArithmeticVariant RcpMessage::unpackArithmeticVariant( char const*& itr, const char* end)
{
	ArithmeticVariant::Type type = (ArithmeticVariant::Type)unpackByte( itr, end);
	switch (type)
	{
		case ArithmeticVariant::Null: return ArithmeticVariant();
		case ArithmeticVariant::Int: return ArithmeticVariant( unpackInt(itr,end));
		case ArithmeticVariant::UInt: return ArithmeticVariant( unpackUint(itr,end));
		case ArithmeticVariant::Float: return ArithmeticVariant( unpackFloat(itr,end));
	}
	throw std::runtime_error( "unknown type of arithmetic variant");
}

bool RcpMessage::unpackCrc32( char const*& itr, const char* end)
{
	uint32_t crc = utils::Crc32::calc( m_content.c_str(), itr - m_content.c_str());
	return crc == unpackScalar<uint32_t>( itr, end);
}

DatabaseOptions RcpMessage::unpackDatabaseOptions( char const*& itr, const char* end)
{
	return DatabaseOptions( unpackUint( itr, end));
}

DatabaseInterface::ConfigType RcpMessage::unpackDatabaseConfigType( char const*& itr, const char* end)
{
	return DatabaseInterface::ConfigType( unpackByte( itr, end));
}

StorageInterface::ConfigType RcpMessage::unpackStorageConfigType( char const*& itr, const char* end)
{
	return StorageInterface::ConfigType( unpackByte( itr, end));
}

TokenizerConfig RcpMessage::unpackTokenizerConfig( char const*& itr, const char* end)
{
	std::string name = unpackString( itr, end);
	std::size_t ii=0,size = unpackSize( itr, end);
	std::vector<std::string> arguments;
	for (; ii<size; ++ii)
	{
		arguments.push_back( unpackString( itr, end));
	}
	return TokenizerConfig( name, arguments);
}

NormalizerConfig RcpMessage::unpackNormalizerConfig( char const*& itr, const char* end)
{
	std::string name = unpackString( itr, end);
	std::size_t ii=0,size = unpackSize( itr, end);
	std::vector<std::string> arguments;
	for (; ii<size; ++ii)
	{
		arguments.push_back( unpackString( itr, end));
	}
	return NormalizerConfig( name, arguments);
}

SummarizerConfig RcpMessage::unpackSummarizerConfig( char const*& itr, const char* end)
{
	SummarizerConfig rt;
	{
		std::size_t ii=0,size = unpackSize( itr, end);
		for (; ii<size; ++ii)
		{
			rt.defineNumericParameter( 
				unpackString( itr, end), unpackArithmeticVariant( itr, end));
		}
	}
	{
		std::size_t ii=0,size = unpackSize( itr, end);
		for (; ii<size; ++ii)
		{
			rt.defineTextualParameter( 
				unpackString( itr, end), unpackString( itr, end));
		}
	}
	{
		std::size_t ii=0,size = unpackSize( itr, end);
		for (; ii<size; ++ii)
		{
			rt.defineFeatureParameter( 
				unpackString( itr, end), unpackString( itr, end));
		}
	}
	return rt;
}

WeightingConfig RcpMessage::unpackWeightingConfig( char const*& itr, const char* end)
{
	WeightingConfig rt;
	{
		std::size_t ii=0,size = unpackSize( itr, end);
		for (; ii<size; ++ii)
		{
			rt.defineNumericParameter( 
				unpackString( itr, end), unpackArithmeticVariant( itr, end));
		}
	}
	return rt;
}

QueryInterface::CompareOperator RcpMessage::unpackCompareOperator( char const*& itr, const char* end)
{
	return QueryInterface::CompareOperator( unpackByte( itr, end));
}



