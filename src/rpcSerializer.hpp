/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_MESSAGE_STUB_HPP_INCLUDED
#define _STRUS_RPC_MESSAGE_STUB_HPP_INCLUDED
#include <string>
#include "rpcInterfaceStub.hpp"
#include "strus/index.hpp"
#include "strus/textProcessorInterface.hpp"
#include "strus/analyzer/segmenterOptions.hpp"
#include "strus/analyzer/documentClass.hpp"
#include "strus/documentAnalyzerInterface.hpp"
#include "strus/queryAnalyzerInterface.hpp"
#include "strus/queryAnalyzerContextInterface.hpp"
#include "strus/numericVariant.hpp"
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
#include "strus/documentTermIteratorInterface.hpp"
#include "strus/weightedDocument.hpp"
#include "strus/resultDocument.hpp"
#include "strus/metaDataRestrictionInterface.hpp"
#include "strus/statisticsProcessorInterface.hpp"
#include "strus/statisticsViewerInterface.hpp"
#include "strus/vectorStorageSearchInterface.hpp"
#include "strus/analyzer/token.hpp"
#include "strus/analyzer/patternLexem.hpp"
#include "strus/analyzer/tokenMarkup.hpp"
#include "strus/analyzer/positionBind.hpp"
#include "strus/analyzer/patternMatcherStatistics.hpp"
#include "strus/analyzer/patternMatcherResult.hpp"
#include "strus/analyzer/documentTerm.hpp"
#include "strus/analyzer/documentMetaData.hpp"
#include "strus/analyzer/documentAttribute.hpp"
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
	void packBufferFloat( const double* buf, std::size_t size);
	void packBool( bool val);
	void packByte( unsigned char val);
	void packIndex( const Index& index);
	void packGlobalCounter( const GlobalCounter& index);
	void packUint( unsigned int val);
	void packInt( int val);
	void packUint64( uint64_t val);
	void packInt64( int64_t val);
	void packFloat( float val);
	void packDouble( double val);
	void packSize( std::size_t size);
	void packNumericVariant( const NumericVariant& val);
	void packDocumentClass( const analyzer::DocumentClass& prop);
	void packTermStatistics( const TermStatistics& stats);
	void packGlobalStatistics( const GlobalStatistics& stats);
	void packMetaDataRestrictionCompareOperator( MetaDataRestrictionInterface::CompareOperator val);

	void packDatabaseOptions( const DatabaseOptions& val);
	void packDatabaseConfigType( const DatabaseInterface::ConfigType& val);
	void packStorageConfigType( const StorageInterface::ConfigType& val);
	void packFeatureOptions( const analyzer::FeatureOptions& val);
	void packSummaryElement( const SummaryElement& val);
	void packSummarizationVariable( const SummarizationVariable& val);
	void packDocumentTermIteratorTerm( const DocumentTermIteratorInterface::Term& term);
	void packSlice( DatabaseCursorInterface::Slice& val);
	void packAnalyzerQueryTerm( const analyzer::QueryTerm& val);
	void packAnalyzerQueryTermExpression( const analyzer::QueryTermExpression& val);
	void packAnalyzerDocumentAttribute( const analyzer::DocumentAttribute& val);
	void packAnalyzerDocumentMetaData( const analyzer::DocumentMetaData& val);
	void packAnalyzerDocumentTerm( const analyzer::DocumentTerm& val);
	void packAnalyzerDocument( const analyzer::Document& val);
	void packAnalyzerToken( const analyzer::Token& val);
	void packAnalyzerGroupBy( const QueryAnalyzerContextInterface::GroupBy& groupBy);
	void packAnalyzerPatternLexem( const analyzer::PatternLexem& val);
	void packAnalyzerTokenMarkup( const analyzer::TokenMarkup& val);
	void packAnalyzerPatternMatcherResult( const analyzer::PatternMatcherResult& val);
	void packAnalyzerPatternMatcherStatistics( const analyzer::PatternMatcherStatistics& val);
	void packSegmenterOptions( const analyzer::SegmenterOptions& opts);
	void packWeightedDocument( const WeightedDocument& val);
	void packResultDocument( const ResultDocument& val);
	void packQueryResult( const QueryResult& val);
	void packFeatureParameter( const QueryEvalInterface::FeatureParameter& val);
	void packDocumentStatisticsType( const StorageClientInterface::DocumentStatisticsType& val);
	void packStatisticsViewerDocumentFrequencyChange( const StatisticsViewerInterface::DocumentFrequencyChange& val);
	void packQueryProcessorFunctionType( const QueryProcessorInterface::FunctionType& val);
	void packTextProcessorFunctionType( const TextProcessorInterface::FunctionType& val);
	void packPostingJoinOperatorDescription( const PostingJoinOperatorInterface::Description& val);
	void packFunctionDescription( const FunctionDescription& val);
	void packVectorStorageSearchResult( const VectorStorageSearchInterface::Result& val);

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
	std::vector<double> unpackBufferFloat();
	bool unpackBool();
	unsigned char unpackByte();
	Index unpackIndex();
	GlobalCounter unpackGlobalCounter();
	unsigned int unpackUint();
	int unpackInt();
	uint64_t unpackUint64();
	int64_t unpackInt64();
	float unpackFloat();
	double unpackDouble();
	std::size_t unpackSize();
	NumericVariant unpackNumericVariant();
	analyzer::DocumentClass unpackDocumentClass();
	TermStatistics unpackTermStatistics();
	GlobalStatistics unpackGlobalStatistics();
	MetaDataRestrictionInterface::CompareOperator unpackMetaDataRestrictionCompareOperator();

	DatabaseOptions unpackDatabaseOptions();
	DatabaseInterface::ConfigType unpackDatabaseConfigType();
	StorageInterface::ConfigType unpackStorageConfigType();
	analyzer::FeatureOptions unpackFeatureOptions();
	SummaryElement unpackSummaryElement();
	DocumentTermIteratorInterface::Term unpackDocumentTermIteratorTerm();
	DatabaseCursorInterface::Slice unpackSlice();
	analyzer::QueryTerm unpackAnalyzerQueryTerm();
	analyzer::QueryTermExpression unpackAnalyzerQueryTermExpression();
	analyzer::DocumentAttribute unpackAnalyzerDocumentAttribute();
	analyzer::DocumentMetaData unpackAnalyzerDocumentMetaData();
	analyzer::DocumentTerm unpackAnalyzerDocumentTerm();
	analyzer::Document unpackAnalyzerDocument();
	analyzer::Token unpackAnalyzerToken();
	QueryAnalyzerContextInterface::GroupBy unpackAnalyzerGroupBy();
	analyzer::PatternLexem unpackAnalyzerPatternLexem();
	analyzer::TokenMarkup unpackAnalyzerTokenMarkup();
	analyzer::PatternMatcherResult unpackAnalyzerPatternMatcherResult();
	analyzer::PatternMatcherStatistics unpackAnalyzerPatternMatcherStatistics();
	analyzer::SegmenterOptions unpackSegmenterOptions();
	WeightedDocument unpackWeightedDocument();
	ResultDocument unpackResultDocument();
	QueryResult unpackQueryResult();
	QueryEvalInterface::FeatureParameter unpackFeatureParameter();
	StorageClientInterface::DocumentStatisticsType unpackDocumentStatisticsType();
	StatisticsViewerInterface::DocumentFrequencyChange unpackStatisticsViewerDocumentFrequencyChange();
	QueryProcessorInterface::FunctionType unpackQueryProcessorFunctionType();
	TextProcessorInterface::FunctionType unpackTextProcessorFunctionType();
	PostingJoinOperatorInterface::Description unpackPostingJoinOperatorDescription();
	FunctionDescription unpackFunctionDescription();
	VectorStorageSearchInterface::Result unpackVectorStorageSearchResult();

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

