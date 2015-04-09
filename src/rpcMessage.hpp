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
#include "strus/arithmeticVariant.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/databaseOptions.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/storageInterface.hpp"
#include "strus/tokenizerConfig.hpp"
#include "strus/normalizerConfig.hpp"
#include "strus/summarizerConfig.hpp"
#include "strus/summarizerFunctionInterface.hpp"
#include "strus/weightingConfig.hpp"
#include "strus/queryInterface.hpp"

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

	void packDatabaseOptions( const DatabaseOptions& val);
	void packDatabaseConfigType( const DatabaseInterface::ConfigType& val);
	void packStorageConfigType( const StorageInterface::ConfigType& val);
	void packTokenizerConfig( const TokenizerConfig& val);
	void packNormalizerConfig( const NormalizerConfig& val);
	void packSummarizerConfig( const SummarizerConfig& val);
	void packWeightingConfig( const WeightingConfig& val);
	void packCompareOperator( const QueryInterface::CompareOperator& val);
	void packFeatureParameter( const SummarizerFunctionInterface::FeatureParameter& val);
	void packCrc32();

	unsigned int unpackObject( char const*& itr, const char* end, unsigned char& classId_);
	std::string unpackString( char const*& itr, const char* end);
	const char* unpackCharp( char const*& itr, const char* end);
	const char* unpackBuffer( char const*& itr, const char* end, std::size_t& size);
	bool unpackBool( char const*& itr, const char* end);
	unsigned char unpackByte( char const*& itr, const char* end);
	Index unpackIndex( char const*& itr, const char* end);
	GlobalCounter unpackGlobalCounter( char const*& itr, const char* end);
	unsigned int unpackUint( char const*& itr, const char* end);
	int unpackInt( char const*& itr, const char* end);
	float unpackFloat( char const*& itr, const char* end);
	std::size_t unpackSize( char const*& itr, const char* end);
	ArithmeticVariant unpackArithmeticVariant( char const*& itr, const char* end);

	DatabaseOptions unpackDatabaseOptions( char const*& itr, const char* end);
	DatabaseInterface::ConfigType unpackDatabaseConfigType( char const*& itr, const char* end);
	StorageInterface::ConfigType unpackStorageConfigType( char const*& itr, const char* end);
	TokenizerConfig unpackTokenizerConfig( char const*& itr, const char* end);
	NormalizerConfig unpackNormalizerConfig( char const*& itr, const char* end);
	SummarizerConfig unpackSummarizerConfig( char const*& itr, const char* end);
	WeightingConfig unpackWeightingConfig( char const*& itr, const char* end);
	QueryInterface::CompareOperator unpackCompareOperator( char const*& itr, const char* end);
	bool unpackCrc32( char const*& itr, const char* end);

	const std::string& content() const
	{
		return m_content;
	}

private:
	std::string m_content;
};

}//namespace
#endif

