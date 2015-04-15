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
#include "rpcSerializer.hpp"
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
static void unpack( char const*&, const char*, void* ptr);

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

void RpcSerializer::packObject( unsigned char classId_, unsigned int objId_)
{
	if (objId_ > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "object id out of range");
	packScalar( m_content, classId_);
	packScalar( m_content, (uint32_t)objId_);
}

void RpcSerializer::packString( const std::string& str)
{
	if (str.size() > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "string size out of range");
	packScalar( m_content, (uint32_t)str.size());
	m_content.append( str);
	
}

void RpcSerializer::packCharp( const char* buf)
{
	m_content.append( buf);
	m_content.push_back( '\0');
}

void RpcSerializer::packCharpp( const char** buf)
{
	char const** bi = buf;
	for (; *bi; ++bi){}
	packSize( bi - buf);
	const char** be = bi;
	for (bi = buf; bi != be; ++bi)
	{
		packCharp( *bi);
	}
}

void RpcSerializer::packBuffer( const char* buf, std::size_t size)
{
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "buffer size out of range");
	packScalar( m_content, (uint32_t)size);
	m_content.append( buf, size);
}

void RpcSerializer::packBool( bool val)
{
	m_content.push_back( val?1:0);
}

void RpcSerializer::packByte( unsigned char val)
{
	m_content.push_back( val);
}

void RpcSerializer::packIndex( const Index& index)
{
	packScalar( m_content, index);
}

void RpcSerializer::packGlobalCounter( const GlobalCounter& index)
{
	packScalar( m_content, index);
}

void RpcSerializer::packUint( unsigned int val)
{
	if (val > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "packed uint out of range");
	packScalar( m_content, (uint32_t)val);
}

void RpcSerializer::packInt( int val)
{
	if (val > std::numeric_limits<int32_t>::max()
	||  val < std::numeric_limits<int32_t>::min()) throw std::runtime_error( "packed int out of range");
	packScalar( m_content, (int32_t)val);
}

void RpcSerializer::packFloat( float val)
{
	pack<sizeof(float)>( m_content, &val);
}

void RpcSerializer::packSize( std::size_t size)
{
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( "packed size out of range");
	packScalar( m_content, (uint32_t)size);
}

void RpcSerializer::packArithmeticVariant( const ArithmeticVariant& val)
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

void RpcSerializer::packDatabaseOptions( const DatabaseOptions& val)
{
	packUint( val.opt());
}

void RpcSerializer::packDatabaseConfigType( const DatabaseInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packStorageConfigType( const StorageInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packTokenizerConfig( const TokenizerConfig& val)
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

void RpcSerializer::packNormalizerConfig( const NormalizerConfig& val)
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

void RpcSerializer::packFeatureOptions( const DocumentAnalyzerInterface::FeatureOptions& val)
{
	packUint( val.opt());
}

void RpcSerializer::packSummarizerConfig( const SummarizerConfig& val)
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

void RpcSerializer::packSummaryElement( const SummarizerClosureInterface::SummaryElement& val)
{
	packString( val.text());
	packFloat( val.weight());
}

void RpcSerializer::packWeightingConfig( const WeightingConfig& val)
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

void RpcSerializer::packCompareOperator( const QueryInterface::CompareOperator& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packFeatureParameter( const SummarizerFunctionInterface::FeatureParameter& val)
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

void RpcSerializer::packSlice( DatabaseCursorInterface::Slice& val)
{
	packBuffer( val.ptr(), val.size());
}

void RpcSerializer::packAnalyzerDocument( const analyzer::Document& val)
{
	packString( val.subDocumentTypeName());
	std::vector<analyzer::Attribute>::const_iterator ai = val.attributes().begin(), ae = val.attributes().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packAnalyzerAttribute( *ai);
	}
	std::vector<analyzer::MetaData>::const_iterator mi = val.metadata().begin(), me = val.metadata().end();
	packSize( me-mi);
	for (; mi != me; ++mi)
	{
		packAnalyzerMetaData( *mi);
	}
	std::vector<analyzer::Term>::const_iterator si = val.searchIndexTerms().begin(), se = val.searchIndexTerms().end();
	packSize( se-si);
	for (; si != se; ++si)
	{
		packAnalyzerTerm( *si);
	}
	std::vector<analyzer::Term>::const_iterator fi = val.forwardIndexTerms().begin(), fe = val.forwardIndexTerms().end();
	packSize( fe-fi);
	for (; fi != fe; ++fi)
	{
		packAnalyzerTerm( *fi);
	}
}

void RpcSerializer::packAnalyzerAttribute( const analyzer::Attribute& val)
{
	packString( val.name());
	packString( val.value());
}

void RpcSerializer::packAnalyzerMetaData( const analyzer::MetaData& val)
{
	packString( val.name());
	packString( val.value());
}

void RpcSerializer::packAnalyzerTerm( const analyzer::Term& val)
{
	packString( val.type());
	packString( val.value());
	packUint( val.pos());
}

void RpcSerializer::packAnalyzerToken( const analyzer::Token& val)
{
	packUint( val.docpos);
	packUint( val.strpos);
	packUint( val.strsize);
}

void RpcSerializer::packWeightedDocument( const WeightedDocument& val)
{
	packIndex( val.docno());
	packFloat( val.weight());
}

void RpcSerializer::packResultDocument( const ResultDocument& val)
{
	packWeightedDocument( val);
	std::vector<ResultDocument::Attribute>::const_iterator
		ai = val.attributes().begin(), ae = val.attributes().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packString( ai->name());
		packString( ai->value());
		packFloat( ai->weight());
	}
}

void RpcSerializer::packCrc32()
{
	packScalar( m_content, utils::Crc32::calc( m_content.c_str(), m_content.size()));
}

void RpcDeserializer::unpackObject( unsigned char& classId_, unsigned int& objId_)
{
	classId_ = unpackScalar<char>( m_itr, m_end);
	objId_ = unpackScalar<uint32_t>( m_itr, m_end);
}

std::string RpcDeserializer::unpackString()
{
	std::string rt;
	uint32_t size = unpackScalar<uint32_t>( m_itr, m_end);
	if (m_itr+size > m_end) throw std::runtime_error( "message to small to encode next string");
	rt.append( m_itr, size);
	m_itr += size;
	return rt;
}

const char* RpcDeserializer::unpackConstCharp()
{
	const char* start = m_itr;
	while (m_itr < m_end && *m_itr) ++m_itr;
	if (m_itr == m_end)
	{
		throw std::runtime_error( "message to small to encode next C string");
	}
	++m_itr;
	return start;
}

const char** RpcDeserializer::unpackConstCharpp()
{
	std::size_t ii=0,size = unpackSize();
	m_charpp_buf.clear();
	m_charpp_buf.reserve( size);
	for (; ii<size; ++ii)
	{
		m_charpp_buf.push_back( unpackConstCharp());
	}
	return (const char**)m_charpp_buf.data();
}

void RpcDeserializer::unpackBuffer( const char*& buf, std::size_t& size)
{
	size = unpackScalar<uint32_t>( m_itr, m_end);
	buf = m_itr;
	m_itr += size;
}

bool RpcDeserializer::unpackBool()
{
	return (*m_itr++ != 0)?true:false;
}

unsigned char RpcDeserializer::unpackByte()
{
	return *m_itr++;
}

Index RpcDeserializer::unpackIndex()
{
	return unpackScalar<Index>( m_itr, m_end);
}

GlobalCounter RpcDeserializer::unpackGlobalCounter()
{
	return unpackScalar<GlobalCounter>( m_itr, m_end);
}

unsigned int RpcDeserializer::unpackUint()
{
	return unpackScalar<uint32_t>( m_itr, m_end);
}

int RpcDeserializer::unpackInt()
{
	return unpackScalar<uint32_t>( m_itr, m_end);
}

float RpcDeserializer::unpackFloat()
{
	return unpackScalar<float>( m_itr, m_end);
}

std::size_t RpcDeserializer::unpackSize()
{
	return unpackScalar<uint32_t>( m_itr, m_end);
}

ArithmeticVariant RpcDeserializer::unpackArithmeticVariant()
{
	ArithmeticVariant::Type type = (ArithmeticVariant::Type)unpackByte();
	switch (type)
	{
		case ArithmeticVariant::Null: return ArithmeticVariant();
		case ArithmeticVariant::Int: return ArithmeticVariant( unpackInt());
		case ArithmeticVariant::UInt: return ArithmeticVariant( unpackUint());
		case ArithmeticVariant::Float: return ArithmeticVariant( unpackFloat());
	}
	throw std::runtime_error( "unknown type of arithmetic variant");
}

bool RpcDeserializer::unpackCrc32()
{
	uint32_t crc = utils::Crc32::calc( m_start, m_end - 4);
	return crc == unpackScalar<uint32_t>( m_end-4, m_end);
}

DatabaseOptions RpcDeserializer::unpackDatabaseOptions()
{
	return DatabaseOptions( unpackUint());
}

DatabaseInterface::ConfigType RpcDeserializer::unpackDatabaseConfigType()
{
	return DatabaseInterface::ConfigType( unpackByte());
}

StorageInterface::ConfigType RpcDeserializer::unpackStorageConfigType()
{
	return StorageInterface::ConfigType( unpackByte());
}

TokenizerConfig RpcDeserializer::unpackTokenizerConfig()
{
	std::string name = unpackString();
	std::size_t ii=0,size = unpackSize();
	std::vector<std::string> arguments;
	for (; ii<size; ++ii)
	{
		arguments.push_back( unpackString());
	}
	return TokenizerConfig( name, arguments);
}

NormalizerConfig RpcDeserializer::unpackNormalizerConfig()
{
	std::string name = unpackString();
	std::size_t ii=0,size = unpackSize();
	std::vector<std::string> arguments;
	for (; ii<size; ++ii)
	{
		arguments.push_back( unpackString());
	}
	return NormalizerConfig( name, arguments);
}

DocumentAnalyzerInterface::FeatureOptions RpcDeserializer::unpackFeatureOptions()
{
	return DocumentAnalyzerInterface::FeatureOptions( unpackUint());
}

SummarizerConfig RpcDeserializer::unpackSummarizerConfig()
{
	SummarizerConfig rt;
	{
		std::size_t ii=0,size = unpackSize();
		for (; ii<size; ++ii)
		{
			rt.defineNumericParameter( 
				unpackString(), unpackArithmeticVariant());
		}
	}
	{
		std::size_t ii=0,size = unpackSize();
		for (; ii<size; ++ii)
		{
			rt.defineTextualParameter( 
				unpackString(), unpackString());
		}
	}
	{
		std::size_t ii=0,size = unpackSize();
		for (; ii<size; ++ii)
		{
			rt.defineFeatureParameter( 
				unpackString(), unpackString());
		}
	}
	return rt;
}

SummarizerClosureInterface::SummaryElement RpcDeserializer::unpackSummaryElement()
{
	return SummarizerClosureInterface::SummaryElement( unpackString(), unpackFloat());
}

WeightingConfig RpcDeserializer::unpackWeightingConfig()
{
	WeightingConfig rt;
	{
		std::size_t ii=0,size = unpackSize();
		for (; ii<size; ++ii)
		{
			rt.defineNumericParameter( 
				unpackString(), unpackArithmeticVariant());
		}
	}
	return rt;
}

QueryInterface::CompareOperator RpcDeserializer::unpackCompareOperator()
{
	return QueryInterface::CompareOperator( unpackByte());
}

DatabaseCursorInterface::Slice RpcDeserializer::unpackSlice()
{
	const char* buf;
	std::size_t size;
	unpackBuffer( buf, size);
	DatabaseCursorInterface::Slice rt( buf, size);
	return rt;
}

analyzer::Document RpcDeserializer::unpackAnalyzerDocument()
{
	analyzer::Document rt;
	rt.setSubDocumentTypeName( unpackString());
	std::size_t ii=0,size=unpackSize();
	for (; ii<size; ++ii)
	{
		rt.setAttribute( unpackString(), unpackString());
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		rt.setMetaData( unpackString(), unpackString());
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		rt.addSearchIndexTerm( unpackString(), unpackString(), unpackUint());
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		rt.addForwardIndexTerm( unpackString(), unpackString(), unpackUint());
	}
	return rt;
}

analyzer::Attribute RpcDeserializer::unpackAnalyzerAttribute()
{
	return analyzer::Attribute( unpackString(), unpackString());
}

analyzer::MetaData RpcDeserializer::unpackAnalyzerMetaData()
{
	return analyzer::MetaData( unpackString(), unpackString());
}

analyzer::Term RpcDeserializer::unpackAnalyzerTerm()
{
	return analyzer::Term( unpackString(), unpackString(), unpackUint());
}

analyzer::Token RpcDeserializer::unpackAnalyzerToken()
{
	return analyzer::Token( unpackUint(), unpackUint(), unpackUint());
}

WeightedDocument RpcDeserializer::unpackWeightedDocument()
{
	return WeightedDocument( unpackIndex(), unpackFloat());
}

ResultDocument RpcDeserializer::unpackResultDocument()
{
	ResultDocument rt( unpackWeightedDocument());
	std::size_t ii=0,size=unpackSize();
	for (; ii<size; ++ii)
	{
		rt.addAttribute( unpackString(), unpackString(), unpackFloat());
	}
	return rt;
}

