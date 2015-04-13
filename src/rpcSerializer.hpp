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
#include "rpcRemoteEndPoint.hpp"
#include "strus/index.hpp"
#include "strus/documentAnalyzerInterface.hpp"
#include "strus/arithmeticVariant.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/databaseOptions.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/databaseCursorInterface.hpp"
#include "strus/storageInterface.hpp"
#include "strus/tokenizerConfig.hpp"
#include "strus/normalizerConfig.hpp"
#include "strus/summarizerConfig.hpp"
#include "strus/summarizerFunctionInterface.hpp"
#include "strus/summarizerClosureInterface.hpp"
#include "strus/weightingConfig.hpp"
#include "strus/queryInterface.hpp"
#include "strus/weightedDocument.hpp"
#include "strus/resultDocument.hpp"
#include "strus/analyzer/token.hpp"
#include "strus/analyzer/term.hpp"
#include "strus/analyzer/metaData.hpp"
#include "strus/analyzer/attribute.hpp"
#include "strus/analyzer/document.hpp"

namespace strus {

class RpcSerializer
{
public:
	RpcSerializer(){}
	RpcSerializer( const RpcSerializer& o)
		:m_content(o.m_content){}
	RpcSerializer( unsigned char classId_, unsigned int objId_);

	void packObject( unsigned char classId_, unsigned int objId_);
	void packString( const std::string& str);
	void packCharp( const char* buf);
	void packCharpp( const char** buf);
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
	void packFeatureOptions( const DocumentAnalyzerInterface::FeatureOptions& val);
	void packSummarizerConfig( const SummarizerConfig& val);
	void packSummaryElement( const SummarizerClosureInterface::SummaryElement& val);
	void packWeightingConfig( const WeightingConfig& val);
	void packCompareOperator( const QueryInterface::CompareOperator& val);
	void packFeatureParameter( const SummarizerFunctionInterface::FeatureParameter& val);
	void packSlice( DatabaseCursorInterface::Slice& val);
	void packAnalyzerDocument( const analyzer::Document& val);
	void packAnalyzerAttribute( const analyzer::Attribute& val);
	void packAnalyzerMetaData( const analyzer::MetaData& val);
	void packAnalyzerTerm( const analyzer::Term& val);
	void packAnalyzerToken( const analyzer::Token& val);
	void packWeightedDocument( const WeightedDocument& val);
	void packResultDocument( const ResultDocument& val);
	
	void packCrc32();

	const std::string& content() const
	{
		return m_content;
	}

private:
	char const* m_itr;
	const char* m_end;
	std::string m_content;
};

enum RpcReturnType
{
	MsgTypeException_BadAlloc,
	MsgTypeException_RuntimeError,
	MsgTypeException_LogicError,
	MsgTypeAnswer
};

class RpcDeserializer
{
public:
	RpcDeserializer( const std::string& content_)
		:m_content(content_)
	{
		m_itr = m_content.c_str();
		m_end = m_content.c_str() + m_content.size();
	}

	void unpackObject( unsigned char& classId_, unsigned int& objId_);
	std::string unpackString();
	const char* unpackConstCharp();
	const char** unpackConstCharpp();
	void unpackBuffer( const char*& buf, std::size_t& size);
	bool unpackBool();
	unsigned char unpackByte();
	Index unpackIndex();
	GlobalCounter unpackGlobalCounter();
	unsigned int unpackUint();
	int unpackInt();
	float unpackFloat();
	std::size_t unpackSize();
	ArithmeticVariant unpackArithmeticVariant();

	DatabaseOptions unpackDatabaseOptions();
	DatabaseInterface::ConfigType unpackDatabaseConfigType();
	StorageInterface::ConfigType unpackStorageConfigType();
	TokenizerConfig unpackTokenizerConfig();
	NormalizerConfig unpackNormalizerConfig();
	DocumentAnalyzerInterface::FeatureOptions unpackFeatureOptions();
	SummarizerConfig unpackSummarizerConfig();
	SummarizerClosureInterface::SummaryElement unpackSummaryElement();
	WeightingConfig unpackWeightingConfig();
	QueryInterface::CompareOperator unpackCompareOperator();
	DatabaseCursorInterface::Slice unpackSlice();
	analyzer::Document unpackAnalyzerDocument();
	analyzer::Attribute unpackAnalyzerAttribute();
	analyzer::MetaData unpackAnalyzerMetaData();
	analyzer::Term unpackAnalyzerTerm();
	analyzer::Token unpackAnalyzerToken();
	WeightedDocument unpackWeightedDocument();
	ResultDocument unpackResultDocument();
	bool unpackCrc32();

	const std::string& content() const
	{
		return m_content;
	}

private:
	char const* m_itr;
	const char* m_end;
	std::string m_content;
	std::vector<const char*> m_charpp_buf;
};

}//namespace
#endif

