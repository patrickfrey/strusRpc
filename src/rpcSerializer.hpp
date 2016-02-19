/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2015 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public
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
#include "strus/textProcessorInterface.hpp"
#include "strus/documentClass.hpp"
#include "strus/documentAnalyzerInterface.hpp"
#include "strus/queryAnalyzerInterface.hpp"
#include "strus/arithmeticVariant.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/termStatistics.hpp"
#include "strus/globalStatistics.hpp"
#include "strus/databaseOptions.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/databaseCursorInterface.hpp"
#include "strus/storageInterface.hpp"
#include "strus/storageClientInterface.hpp"
#include "strus/summarizerFunctionInterface.hpp"
#include "strus/summarizerFunctionContextInterface.hpp"
#include "strus/queryInterface.hpp"
#include "strus/queryEvalInterface.hpp"
#include "strus/queryProcessorInterface.hpp"
#include "strus/weightedDocument.hpp"
#include "strus/resultDocument.hpp"
#include "strus/statisticsProcessorInterface.hpp"
#include "strus/statisticsViewerInterface.hpp"
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

	void packSessionId( unsigned int id_);
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
	void packDouble( double val);
	void packSize( std::size_t size);
	void packArithmeticVariant( const ArithmeticVariant& val);
	void packDocumentClass( const DocumentClass& prop);
	void packTermStatistics( const TermStatistics& stats);
	void packGlobalStatistics( const GlobalStatistics& stats);

	void packDatabaseOptions( const DatabaseOptions& val);
	void packDatabaseConfigType( const DatabaseInterface::ConfigType& val);
	void packStorageConfigType( const StorageInterface::ConfigType& val);
	void packFeatureOptions( const DocumentAnalyzerInterface::FeatureOptions& val);
	void packSummaryElement( const SummarizerFunctionContextInterface::SummaryElement& val);
	void packCompareOperator( const QueryInterface::CompareOperator& val);
	void packSummarizationVariable( const SummarizationVariable& val);
	void packSlice( DatabaseCursorInterface::Slice& val);
	void packAnalyzerDocument( const analyzer::Document& val);
	void packAnalyzerAttribute( const analyzer::Attribute& val);
	void packAnalyzerMetaData( const analyzer::MetaData& val);
	void packAnalyzerTerm( const analyzer::Term& val);
	void packAnalyzerTermVector( const analyzer::TermVector& val);
	void packAnalyzerToken( const analyzer::Token& val);
	void packWeightedDocument( const WeightedDocument& val);
	void packResultDocument( const ResultDocument& val);
	void packQueryResult( const QueryResult& val);
	void packFeatureParameter( const QueryEvalInterface::FeatureParameter& val);
	void packPhrase( const QueryAnalyzerInterface::Phrase& val);
	void packDocumentStatisticsType( const StorageClientInterface::DocumentStatisticsType& val);
	void packStatisticsProcessorBuilderOptions( const StatisticsProcessorInterface::BuilderOptions& val);
	void packStatisticsViewerDocumentFrequencyChange( const StatisticsViewerInterface::DocumentFrequencyChange& val);
	void packQueryProcessorFunctionType( const QueryProcessorInterface::FunctionType& val);
	void packTextProcessorFunctionType( const TextProcessorInterface::FunctionType& val);
	void packPostingJoinOperatorDescription( const PostingJoinOperatorInterface::Description& val);
	void packWeightingFunctionDescription( const WeightingFunctionInterface::Description& val);
	void packSummarizerFunctionDescription( const SummarizerFunctionInterface::Description& val);
	void packCrc32();
	const std::string& content() const
	{
		return m_content;
	}

private:
	std::string m_content;
};

enum RpcReturnType
{
	MsgTypeError,
	MsgTypeAnswer,
	MsgTypeSynchronize
};

class RpcDeserializer
{
public:
	RpcDeserializer( const char* start_, std::size_t size_)
		:m_start(start_),m_itr(start_),m_end(start_+size_)
	{}

	unsigned int unpackSessionId();
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
	double unpackDouble();
	std::size_t unpackSize();
	ArithmeticVariant unpackArithmeticVariant();
	DocumentClass unpackDocumentClass();
	TermStatistics unpackTermStatistics();
	GlobalStatistics unpackGlobalStatistics();

	DatabaseOptions unpackDatabaseOptions();
	DatabaseInterface::ConfigType unpackDatabaseConfigType();
	StorageInterface::ConfigType unpackStorageConfigType();
	DocumentAnalyzerInterface::FeatureOptions unpackFeatureOptions();
	SummarizerFunctionContextInterface::SummaryElement unpackSummaryElement();
	QueryInterface::CompareOperator unpackCompareOperator();
	DatabaseCursorInterface::Slice unpackSlice();
	analyzer::Document unpackAnalyzerDocument();
	analyzer::Attribute unpackAnalyzerAttribute();
	analyzer::MetaData unpackAnalyzerMetaData();
	analyzer::Term unpackAnalyzerTerm();
	analyzer::TermVector unpackAnalyzerTermVector();
	analyzer::Token unpackAnalyzerToken();
	WeightedDocument unpackWeightedDocument();
	ResultDocument unpackResultDocument();
	QueryResult unpackQueryResult();
	QueryEvalInterface::FeatureParameter unpackFeatureParameter();
	QueryAnalyzerInterface::Phrase unpackPhrase();
	StorageClientInterface::DocumentStatisticsType unpackDocumentStatisticsType();
	StatisticsProcessorInterface::BuilderOptions unpackStatisticsProcessorBuilderOptions();
	StatisticsViewerInterface::DocumentFrequencyChange unpackStatisticsViewerDocumentFrequencyChange();
	QueryProcessorInterface::FunctionType unpackQueryProcessorFunctionType();
	TextProcessorInterface::FunctionType unpackTextProcessorFunctionType();
	PostingJoinOperatorInterface::Description unpackPostingJoinOperatorDescription();
	WeightingFunctionInterface::Description unpackWeightingFunctionDescription();
	SummarizerFunctionInterface::Description unpackSummarizerFunctionDescription();
	bool unpackCrc32();

	std::size_t position() const
	{
		return (std::size_t)(m_itr - m_start);
	}
	std::size_t size() const
	{
		return (std::size_t)(m_end - m_start);
	}

private:
	const char* m_start;
	char const* m_itr;
	const char* m_end;
	std::vector<const char*> m_charpp_buf;
};

}//namespace
#endif

