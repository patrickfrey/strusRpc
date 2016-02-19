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
#ifndef _STRUS_RPC_OBJECTS_HPP_INCLUDED
#define _STRUS_RPC_OBJECTS_HPP_INCLUDED
#include "rpcInterfaceStub.hpp"
#include "objectIds_gen.hpp"
#include "strus/aggregatorFunctionInstanceInterface.hpp"
#include "strus/aggregatorFunctionInterface.hpp"
#include "strus/analyzerErrorBufferInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/documentAnalyzerContextInterface.hpp"
#include "strus/documentAnalyzerInterface.hpp"
#include "strus/documentClassDetectorInterface.hpp"
#include "strus/normalizerFunctionContextInterface.hpp"
#include "strus/normalizerFunctionInstanceInterface.hpp"
#include "strus/normalizerFunctionInterface.hpp"
#include "strus/queryAnalyzerInterface.hpp"
#include "strus/segmenterContextInterface.hpp"
#include "strus/segmenterInstanceInterface.hpp"
#include "strus/segmenterInterface.hpp"
#include "strus/textProcessorInterface.hpp"
#include "strus/tokenizerFunctionContextInterface.hpp"
#include "strus/tokenizerFunctionInstanceInterface.hpp"
#include "strus/tokenizerFunctionInterface.hpp"
#include "strus/attributeReaderInterface.hpp"
#include "strus/databaseBackupCursorInterface.hpp"
#include "strus/databaseClientInterface.hpp"
#include "strus/databaseCursorInterface.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/databaseTransactionInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "strus/forwardIteratorInterface.hpp"
#include "strus/invAclIteratorInterface.hpp"
#include "strus/metaDataReaderInterface.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/postingJoinOperatorInterface.hpp"
#include "strus/queryEvalInterface.hpp"
#include "strus/queryInterface.hpp"
#include "strus/queryProcessorInterface.hpp"
#include "strus/statisticsBuilderInterface.hpp"
#include "strus/statisticsIteratorInterface.hpp"
#include "strus/statisticsProcessorInterface.hpp"
#include "strus/statisticsViewerInterface.hpp"
#include "strus/storageAlterMetaDataTableInterface.hpp"
#include "strus/storageClientInterface.hpp"
#include "strus/storageDocumentInterface.hpp"
#include "strus/storageDocumentUpdateInterface.hpp"
#include "strus/storageDumpInterface.hpp"
#include "strus/storageInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/storageTransactionInterface.hpp"
#include "strus/summarizerFunctionContextInterface.hpp"
#include "strus/summarizerFunctionInstanceInterface.hpp"
#include "strus/summarizerFunctionInterface.hpp"
#include "strus/valueIteratorInterface.hpp"
#include "strus/weightingFunctionContextInterface.hpp"
#include "strus/weightingFunctionInstanceInterface.hpp"
#include "strus/weightingFunctionInterface.hpp"

namespace strus {

class AggregatorFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::AggregatorFunctionInstanceInterface
		,public strus::AggregatorFunctionInstanceConst
{
public:
	virtual ~AggregatorFunctionInstanceImpl();

	AggregatorFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AggregatorFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual double evaluate( const analyzer::Document& p1) const;
};

class AggregatorFunctionImpl
		:public RpcInterfaceStub
		,public strus::AggregatorFunctionInterface
		,public strus::AggregatorFunctionConst
{
public:
	virtual ~AggregatorFunctionImpl();

	AggregatorFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AggregatorFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual AggregatorFunctionInstanceInterface* createInstance( const std::vector<std::string>& p1) const;
	virtual const char* getDescription( ) const;
};

class AnalyzerObjectBuilderImpl
		:public RpcInterfaceStub
		,public strus::AnalyzerObjectBuilderInterface
		,public strus::AnalyzerObjectBuilderConst
{
public:
	virtual ~AnalyzerObjectBuilderImpl();

	AnalyzerObjectBuilderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AnalyzerObjectBuilder, objId_, ctx_, isConst_, errorhnd_){}

	virtual const TextProcessorInterface* getTextProcessor( ) const;
	virtual SegmenterInterface* createSegmenter( const std::string& p1) const;
	virtual DocumentAnalyzerInterface* createDocumentAnalyzer( const std::string& p1) const;
	virtual QueryAnalyzerInterface* createQueryAnalyzer( ) const;
};

class AttributeReaderImpl
		:public RpcInterfaceStub
		,public strus::AttributeReaderInterface
		,public strus::AttributeReaderConst
{
public:
	virtual ~AttributeReaderImpl();

	AttributeReaderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AttributeReader, objId_, ctx_, isConst_, errorhnd_){}

	virtual Index elementHandle( const char* p1) const;
	virtual void skipDoc( const Index& p1);
	virtual std::string getValue( const Index& p1) const;
	virtual std::vector<std::string> getAttributeNames( ) const;
};

class DatabaseBackupCursorImpl
		:public RpcInterfaceStub
		,public strus::DatabaseBackupCursorInterface
		,public strus::DatabaseBackupCursorConst
{
public:
	virtual ~DatabaseBackupCursorImpl();

	DatabaseBackupCursorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseBackupCursor, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4);
};

class DatabaseClientImpl
		:public RpcInterfaceStub
		,public strus::DatabaseClientInterface
		,public strus::DatabaseClientConst
{
public:
	virtual ~DatabaseClientImpl();

	DatabaseClientImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseClient, objId_, ctx_, isConst_, errorhnd_){}

	virtual DatabaseTransactionInterface* createTransaction( );
	virtual DatabaseCursorInterface* createCursor( const DatabaseOptions& p1) const;
	virtual DatabaseBackupCursorInterface* createBackupCursor( ) const;
	virtual void writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4);
	virtual void removeImm( const char* p1, std::size_t p2);
	virtual bool readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const;
};

class DatabaseCursorImpl
		:public RpcInterfaceStub
		,public strus::DatabaseCursorInterface
		,public strus::DatabaseCursorConst
{
public:
	virtual ~DatabaseCursorImpl();

	DatabaseCursorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseCursor, objId_, ctx_, isConst_, errorhnd_){}

	virtual DatabaseCursorInterface::Slice seekUpperBound( const char* p1, std::size_t p2, std::size_t p3);
	virtual DatabaseCursorInterface::Slice seekFirst( const char* p1, std::size_t p2);
	virtual DatabaseCursorInterface::Slice seekLast( const char* p1, std::size_t p2);
	virtual DatabaseCursorInterface::Slice seekNext( );
	virtual DatabaseCursorInterface::Slice seekPrev( );
	virtual DatabaseCursorInterface::Slice key( ) const;
	virtual DatabaseCursorInterface::Slice value( ) const;
};

class DatabaseImpl
		:public RpcInterfaceStub
		,public strus::DatabaseInterface
		,public strus::DatabaseConst
{
public:
	virtual ~DatabaseImpl();

	DatabaseImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_Database, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool exists( const std::string& p1) const;
	virtual DatabaseClientInterface* createClient( const std::string& p1) const;
	virtual bool createDatabase( const std::string& p1) const;
	virtual bool restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const;
	virtual bool destroyDatabase( const std::string& p1) const;
	virtual const char* getConfigDescription( DatabaseInterface::ConfigType p1) const;
	virtual const char** getConfigParameters( DatabaseInterface::ConfigType p1) const;
};

class DatabaseTransactionImpl
		:public RpcInterfaceStub
		,public strus::DatabaseTransactionInterface
		,public strus::DatabaseTransactionConst
{
public:
	virtual ~DatabaseTransactionImpl();

	DatabaseTransactionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseTransaction, objId_, ctx_, isConst_, errorhnd_){}

	virtual DatabaseCursorInterface* createCursor( const DatabaseOptions& p1) const;
	virtual void write( const char* p1, std::size_t p2, const char* p3, std::size_t p4);
	virtual void remove( const char* p1, std::size_t p2);
	virtual void removeSubTree( const char* p1, std::size_t p2);
	virtual bool commit( );
	virtual void rollback( );
};

class DocumentAnalyzerContextImpl
		:public RpcInterfaceStub
		,public strus::DocumentAnalyzerContextInterface
		,public strus::DocumentAnalyzerContextConst
{
public:
	virtual ~DocumentAnalyzerContextImpl();

	DocumentAnalyzerContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzerContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putInput( const char* p1, std::size_t p2, bool p3);
	virtual bool analyzeNext( analyzer::Document& p1);
};

class DocumentAnalyzerImpl
		:public RpcInterfaceStub
		,public strus::DocumentAnalyzerInterface
		,public strus::DocumentAnalyzerConst
{
public:
	virtual ~DocumentAnalyzerImpl();

	DocumentAnalyzerImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzer, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addSearchIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5);
	virtual void addForwardIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5);
	virtual void defineMetaData( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void defineAggregatedMetaData( const std::string& p1, AggregatorFunctionInstanceInterface* p2);
	virtual void defineAttribute( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void defineSubDocument( const std::string& p1, const std::string& p2);
	virtual analyzer::Document analyze( const std::string& p1, const DocumentClass& p2) const;
	virtual DocumentAnalyzerContextInterface* createContext( const DocumentClass& p1) const;
};

class DocumentClassDetectorImpl
		:public RpcInterfaceStub
		,public strus::DocumentClassDetectorInterface
		,public strus::DocumentClassDetectorConst
{
public:
	virtual ~DocumentClassDetectorImpl();

	DocumentClassDetectorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentClassDetector, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool detect( DocumentClass& p1, const char* p2, std::size_t p3) const;
};

class ForwardIteratorImpl
		:public RpcInterfaceStub
		,public strus::ForwardIteratorInterface
		,public strus::ForwardIteratorConst
{
public:
	virtual ~ForwardIteratorImpl();

	ForwardIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ForwardIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual void skipDoc( const Index& p1);
	virtual Index skipPos( const Index& p1);
	virtual std::string fetch( );
};

class InvAclIteratorImpl
		:public RpcInterfaceStub
		,public strus::InvAclIteratorInterface
		,public strus::InvAclIteratorConst
{
public:
	virtual ~InvAclIteratorImpl();

	InvAclIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_InvAclIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual Index skipDoc( const Index& p1);
};

class MetaDataReaderImpl
		:public RpcInterfaceStub
		,public strus::MetaDataReaderInterface
		,public strus::MetaDataReaderConst
{
public:
	virtual ~MetaDataReaderImpl();

	MetaDataReaderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_MetaDataReader, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool hasElement( const std::string& p1) const;
	virtual Index elementHandle( const std::string& p1) const;
	virtual Index nofElements( ) const;
	virtual void skipDoc( const Index& p1);
	virtual ArithmeticVariant getValue( const Index& p1) const;
	virtual const char* getType( const Index& p1) const;
	virtual const char* getName( const Index& p1) const;
};

class NormalizerFunctionContextImpl
		:public RpcInterfaceStub
		,public strus::NormalizerFunctionContextInterface
		,public strus::NormalizerFunctionContextConst
{
public:
	virtual ~NormalizerFunctionContextImpl();

	NormalizerFunctionContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerFunctionContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::string normalize( const char* p1, std::size_t p2);
};

class NormalizerFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::NormalizerFunctionInstanceInterface
		,public strus::NormalizerFunctionInstanceConst
{
public:
	virtual ~NormalizerFunctionInstanceImpl();

	NormalizerFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual NormalizerFunctionContextInterface* createFunctionContext( ) const;
};

class NormalizerFunctionImpl
		:public RpcInterfaceStub
		,public strus::NormalizerFunctionInterface
		,public strus::NormalizerFunctionConst
{
public:
	virtual ~NormalizerFunctionImpl();

	NormalizerFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual NormalizerFunctionInstanceInterface* createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const;
	virtual const char* getDescription( ) const;
};

class PostingIteratorImpl
		:public RpcInterfaceStub
		,public strus::PostingIteratorInterface
		,public strus::PostingIteratorConst
{
public:
	virtual ~PostingIteratorImpl();

	PostingIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual Index skipDoc( const Index& p1);
	virtual Index skipDocCandidate( const Index& p1);
	virtual Index skipPos( const Index& p1);
	virtual const char* featureid( ) const;
	virtual Index documentFrequency( ) const;
	virtual unsigned int frequency( );
	virtual Index docno( ) const;
	virtual Index posno( ) const;
};

class PostingJoinOperatorImpl
		:public RpcInterfaceStub
		,public strus::PostingJoinOperatorInterface
		,public strus::PostingJoinOperatorConst
{
public:
	virtual ~PostingJoinOperatorImpl();

	PostingJoinOperatorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingJoinOperator, objId_, ctx_, isConst_, errorhnd_){}

	virtual PostingIteratorInterface* createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2, unsigned int p3) const;
	virtual PostingJoinOperatorInterface::Description getDescription( ) const;
};

class QueryAnalyzerImpl
		:public RpcInterfaceStub
		,public strus::QueryAnalyzerInterface
		,public strus::QueryAnalyzerConst
{
public:
	virtual ~QueryAnalyzerImpl();

	QueryAnalyzerImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryAnalyzer, objId_, ctx_, isConst_, errorhnd_){}

	virtual void definePhraseType( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual std::vector<analyzer::Term> analyzePhrase( const std::string& p1, const std::string& p2) const;
	virtual std::vector<analyzer::TermVector> analyzePhraseBulk( const std::vector<QueryAnalyzerInterface::Phrase>& p1) const;
};

class QueryEvalImpl
		:public RpcInterfaceStub
		,public strus::QueryEvalInterface
		,public strus::QueryEvalConst
{
public:
	virtual ~QueryEvalImpl();

	QueryEvalImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryEval, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addTerm( const std::string& p1, const std::string& p2, const std::string& p3);
	virtual void addSelectionFeature( const std::string& p1);
	virtual void addRestrictionFeature( const std::string& p1);
	virtual void addExclusionFeature( const std::string& p1);
	virtual void addSummarizerFunction( const std::string& p1, SummarizerFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3, const std::string& p4);
	virtual void addWeightingFunction( const std::string& p1, WeightingFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3, float p4);
	virtual QueryInterface* createQuery( const StorageClientInterface* p1) const;
};

class QueryImpl
		:public RpcInterfaceStub
		,public strus::QueryInterface
		,public strus::QueryConst
{
public:
	virtual ~QueryImpl();

	QueryImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_Query, objId_, ctx_, isConst_, errorhnd_){}

	virtual void pushTerm( const std::string& p1, const std::string& p2);
	virtual void pushExpression( const PostingJoinOperatorInterface* p1, std::size_t p2, int p3, unsigned int p4);
	virtual void attachVariable( const std::string& p1);
	virtual void defineFeature( const std::string& p1, float p2);
	virtual void defineTermStatistics( const std::string& p1, const std::string& p2, const TermStatistics& p3);
	virtual void defineGlobalStatistics( const GlobalStatistics& p1);
	virtual void defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4);
	virtual void addDocumentEvaluationSet( const std::vector<Index>& p1);
	virtual void setMaxNofRanks( std::size_t p1);
	virtual void setMinRank( std::size_t p1);
	virtual void addUserName( const std::string& p1);
	virtual QueryResult evaluate( );
};

class QueryProcessorImpl
		:public RpcInterfaceStub
		,public strus::QueryProcessorInterface
		,public strus::QueryProcessorConst
{
public:
	virtual ~QueryProcessorImpl();

	QueryProcessorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryProcessor, objId_, ctx_, isConst_, errorhnd_){}

	virtual void definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2);
	virtual const PostingJoinOperatorInterface* getPostingJoinOperator( const std::string& p1) const;
	virtual void defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2);
	virtual const WeightingFunctionInterface* getWeightingFunction( const std::string& p1) const;
	virtual void defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2);
	virtual const SummarizerFunctionInterface* getSummarizerFunction( const std::string& p1) const;
	virtual std::vector<std::string> getFunctionList( QueryProcessorInterface::FunctionType p1) const;
};

class SegmenterContextImpl
		:public RpcInterfaceStub
		,public strus::SegmenterContextInterface
		,public strus::SegmenterContextConst
{
public:
	virtual ~SegmenterContextImpl();

	SegmenterContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SegmenterContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putInput( const char* p1, std::size_t p2, bool p3);
	virtual bool getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4);
};

class SegmenterInstanceImpl
		:public RpcInterfaceStub
		,public strus::SegmenterInstanceInterface
		,public strus::SegmenterInstanceConst
{
public:
	virtual ~SegmenterInstanceImpl();

	SegmenterInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SegmenterInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void defineSelectorExpression( int p1, const std::string& p2);
	virtual void defineSubSection( int p1, int p2, const std::string& p3);
	virtual SegmenterContextInterface* createContext( const DocumentClass& p1) const;
};

class SegmenterImpl
		:public RpcInterfaceStub
		,public strus::SegmenterInterface
		,public strus::SegmenterConst
{
public:
	virtual ~SegmenterImpl();

	SegmenterImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_Segmenter, objId_, ctx_, isConst_, errorhnd_){}

	virtual const char* mimeType( ) const;
	virtual SegmenterInstanceInterface* createInstance( ) const;
};

class StatisticsBuilderImpl
		:public RpcInterfaceStub
		,public strus::StatisticsBuilderInterface
		,public strus::StatisticsBuilderConst
{
public:
	virtual ~StatisticsBuilderImpl();

	StatisticsBuilderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StatisticsBuilder, objId_, ctx_, isConst_, errorhnd_){}

	virtual void setNofDocumentsInsertedChange( int p1);
	virtual void addDfChange( const char* p1, const char* p2, int p3);
	virtual void start( );
	virtual void rollback( );
	virtual bool fetchMessage( const char*& p1, std::size_t& p2);
};

class StatisticsIteratorImpl
		:public RpcInterfaceStub
		,public strus::StatisticsIteratorInterface
		,public strus::StatisticsIteratorConst
{
public:
	virtual ~StatisticsIteratorImpl();

	StatisticsIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StatisticsIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool getNext( const char*& p1, std::size_t& p2);
};

class StatisticsProcessorImpl
		:public RpcInterfaceStub
		,public strus::StatisticsProcessorInterface
		,public strus::StatisticsProcessorConst
{
public:
	virtual ~StatisticsProcessorImpl();

	StatisticsProcessorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StatisticsProcessor, objId_, ctx_, isConst_, errorhnd_){}

	virtual StatisticsViewerInterface* createViewer( const char* p1, std::size_t p2) const;
	virtual StatisticsBuilderInterface* createBuilder( const StatisticsProcessorInterface::BuilderOptions& p1) const;
};

class StatisticsViewerImpl
		:public RpcInterfaceStub
		,public strus::StatisticsViewerInterface
		,public strus::StatisticsViewerConst
{
public:
	virtual ~StatisticsViewerImpl();

	StatisticsViewerImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StatisticsViewer, objId_, ctx_, isConst_, errorhnd_){}

	virtual int nofDocumentsInsertedChange( );
	virtual bool nextDfChange( StatisticsViewerInterface::DocumentFrequencyChange& p1);
};

class StorageAlterMetaDataTableImpl
		:public RpcInterfaceStub
		,public strus::StorageAlterMetaDataTableInterface
		,public strus::StorageAlterMetaDataTableConst
{
public:
	virtual ~StorageAlterMetaDataTableImpl();

	StorageAlterMetaDataTableImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageAlterMetaDataTable, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addElement( const std::string& p1, const std::string& p2);
	virtual void alterElement( const std::string& p1, const std::string& p2, const std::string& p3);
	virtual void renameElement( const std::string& p1, const std::string& p2);
	virtual void deleteElement( const std::string& p1);
	virtual void clearElement( const std::string& p1);
	virtual bool commit( );
	virtual void rollback( );
};

class StorageClientImpl
		:public RpcInterfaceStub
		,public strus::StorageClientInterface
		,public strus::StorageClientConst
{
public:
	virtual ~StorageClientImpl();

	StorageClientImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageClient, objId_, ctx_, isConst_, errorhnd_){}

	virtual PostingIteratorInterface* createTermPostingIterator( const std::string& p1, const std::string& p2) const;
	virtual ForwardIteratorInterface* createForwardIterator( const std::string& p1) const;
	virtual InvAclIteratorInterface* createInvAclIterator( const std::string& p1) const;
	virtual Index nofDocumentsInserted( ) const;
	virtual Index documentFrequency( const std::string& p1, const std::string& p2) const;
	virtual Index maxDocumentNumber( ) const;
	virtual Index documentNumber( const std::string& p1) const;
	virtual ValueIteratorInterface* createTermTypeIterator( ) const;
	virtual ValueIteratorInterface* createTermValueIterator( ) const;
	virtual ValueIteratorInterface* createDocIdIterator( ) const;
	virtual ValueIteratorInterface* createUserNameIterator( ) const;
	virtual Index documentStatistics( const Index& p1, const StorageClientInterface::DocumentStatisticsType& p2, const std::string& p3) const;
	virtual MetaDataReaderInterface* createMetaDataReader( ) const;
	virtual AttributeReaderInterface* createAttributeReader( ) const;
	virtual StorageTransactionInterface* createTransaction( );
	virtual StatisticsIteratorInterface* createInitStatisticsIterator( bool p1);
	virtual StatisticsIteratorInterface* createUpdateStatisticsIterator( );
	virtual const StatisticsProcessorInterface* getStatisticsProcessor( ) const;
	virtual StorageDocumentInterface* createDocumentChecker( const std::string& p1, const std::string& p2) const;
	virtual bool checkStorage( std::ostream& p1) const;
	virtual StorageDumpInterface* createDump( ) const;
};

class StorageDocumentImpl
		:public RpcInterfaceStub
		,public strus::StorageDocumentInterface
		,public strus::StorageDocumentConst
{
public:
	virtual ~StorageDocumentImpl();

	StorageDocumentImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDocument, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void setMetaData( const std::string& p1, const ArithmeticVariant& p2);
	virtual void setAttribute( const std::string& p1, const std::string& p2);
	virtual void setUserAccessRight( const std::string& p1);
	virtual void done( );
};

class StorageDocumentUpdateImpl
		:public RpcInterfaceStub
		,public strus::StorageDocumentUpdateInterface
		,public strus::StorageDocumentUpdateConst
{
public:
	virtual ~StorageDocumentUpdateImpl();

	StorageDocumentUpdateImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDocumentUpdate, objId_, ctx_, isConst_, errorhnd_){}

	virtual void setMetaData( const std::string& p1, const ArithmeticVariant& p2);
	virtual void setAttribute( const std::string& p1, const std::string& p2);
	virtual void clearAttribute( const std::string& p1);
	virtual void setUserAccessRight( const std::string& p1);
	virtual void clearUserAccessRight( const std::string& p1);
	virtual void clearUserAccessRights( );
	virtual void done( );
};

class StorageDumpImpl
		:public RpcInterfaceStub
		,public strus::StorageDumpInterface
		,public strus::StorageDumpConst
{
public:
	virtual ~StorageDumpImpl();

	StorageDumpImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDump, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool nextChunk( const char*& p1, std::size_t& p2);
};

class StorageImpl
		:public RpcInterfaceStub
		,public strus::StorageInterface
		,public strus::StorageConst
{
public:
	virtual ~StorageImpl();

	StorageImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_Storage, objId_, ctx_, isConst_, errorhnd_){}

	virtual StorageClientInterface* createClient( const std::string& p1, DatabaseClientInterface* p2, const StatisticsProcessorInterface* p3) const;
	virtual bool createStorage( const std::string& p1, DatabaseClientInterface* p2) const;
	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable( DatabaseClientInterface* p1) const;
	virtual const char* getConfigDescription( StorageInterface::ConfigType p1) const;
	virtual const char** getConfigParameters( StorageInterface::ConfigType p1) const;
};

class StorageObjectBuilderImpl
		:public RpcInterfaceStub
		,public strus::StorageObjectBuilderInterface
		,public strus::StorageObjectBuilderConst
{
public:
	virtual ~StorageObjectBuilderImpl();

	StorageObjectBuilderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageObjectBuilder, objId_, ctx_, isConst_, errorhnd_){}

	virtual const StorageInterface* getStorage( ) const;
	virtual const DatabaseInterface* getDatabase( const std::string& p1) const;
	virtual const QueryProcessorInterface* getQueryProcessor( ) const;
	virtual const StatisticsProcessorInterface* getStatisticsProcessor( ) const;
	virtual StorageClientInterface* createStorageClient( const std::string& p1) const;
	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable( const std::string& p1) const;
	virtual QueryEvalInterface* createQueryEval( ) const;
};

class StorageTransactionImpl
		:public RpcInterfaceStub
		,public strus::StorageTransactionInterface
		,public strus::StorageTransactionConst
{
public:
	virtual ~StorageTransactionImpl();

	StorageTransactionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageTransaction, objId_, ctx_, isConst_, errorhnd_){}

	virtual StorageDocumentInterface* createDocument( const std::string& p1);
	virtual StorageDocumentUpdateInterface* createDocumentUpdate( const Index& p1);
	virtual void deleteDocument( const std::string& p1);
	virtual void deleteUserAccessRights( const std::string& p1);
	virtual void updateMetaData( const Index& p1, const std::string& p2, const ArithmeticVariant& p3);
	virtual bool commit( );
	virtual void rollback( );
};

class SummarizerFunctionContextImpl
		:public RpcInterfaceStub
		,public strus::SummarizerFunctionContextInterface
		,public strus::SummarizerFunctionContextConst
{
public:
	virtual ~SummarizerFunctionContextImpl();

	SummarizerFunctionContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerFunctionContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addSummarizationFeature( const std::string& p1, PostingIteratorInterface* p2, const std::vector<SummarizationVariable>& p3, float p4, const TermStatistics& p5);
	virtual std::vector<SummarizerFunctionContextInterface::SummaryElement> getSummary( const Index& p1);
};

class SummarizerFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::SummarizerFunctionInstanceInterface
		,public strus::SummarizerFunctionInstanceConst
{
public:
	virtual ~SummarizerFunctionInstanceImpl();

	SummarizerFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addStringParameter( const std::string& p1, const std::string& p2);
	virtual void addNumericParameter( const std::string& p1, const ArithmeticVariant& p2);
	virtual SummarizerFunctionContextInterface* createFunctionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2, const GlobalStatistics& p3) const;
	virtual std::string tostring( ) const;
};

class SummarizerFunctionImpl
		:public RpcInterfaceStub
		,public strus::SummarizerFunctionInterface
		,public strus::SummarizerFunctionConst
{
public:
	virtual ~SummarizerFunctionImpl();

	SummarizerFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual SummarizerFunctionInstanceInterface* createInstance( const QueryProcessorInterface* p1) const;
	virtual SummarizerFunctionInterface::Description getDescription( ) const;
};

class TextProcessorImpl
		:public RpcInterfaceStub
		,public strus::TextProcessorInterface
		,public strus::TextProcessorConst
{
public:
	virtual ~TextProcessorImpl();

	TextProcessorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TextProcessor, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addResourcePath( const std::string& p1);
	virtual std::string getResourcePath( const std::string& p1) const;
	virtual const TokenizerFunctionInterface* getTokenizer( const std::string& p1) const;
	virtual const NormalizerFunctionInterface* getNormalizer( const std::string& p1) const;
	virtual const AggregatorFunctionInterface* getAggregator( const std::string& p1) const;
	virtual bool detectDocumentClass( DocumentClass& p1, const char* p2, std::size_t p3) const;
	virtual void defineDocumentClassDetector( DocumentClassDetectorInterface* p1);
	virtual void defineTokenizer( const std::string& p1, TokenizerFunctionInterface* p2);
	virtual void defineNormalizer( const std::string& p1, NormalizerFunctionInterface* p2);
	virtual void defineAggregator( const std::string& p1, AggregatorFunctionInterface* p2);
	virtual std::vector<std::string> getFunctionList( TextProcessorInterface::FunctionType p1) const;
};

class TokenizerFunctionContextImpl
		:public RpcInterfaceStub
		,public strus::TokenizerFunctionContextInterface
		,public strus::TokenizerFunctionContextConst
{
public:
	virtual ~TokenizerFunctionContextImpl();

	TokenizerFunctionContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerFunctionContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<analyzer::Token> tokenize( const char* p1, std::size_t p2);
};

class TokenizerFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::TokenizerFunctionInstanceInterface
		,public strus::TokenizerFunctionInstanceConst
{
public:
	virtual ~TokenizerFunctionInstanceImpl();

	TokenizerFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool concatBeforeTokenize( ) const;
	virtual TokenizerFunctionContextInterface* createFunctionContext( ) const;
};

class TokenizerFunctionImpl
		:public RpcInterfaceStub
		,public strus::TokenizerFunctionInterface
		,public strus::TokenizerFunctionConst
{
public:
	virtual ~TokenizerFunctionImpl();

	TokenizerFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual TokenizerFunctionInstanceInterface* createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const;
	virtual const char* getDescription( ) const;
};

class ValueIteratorImpl
		:public RpcInterfaceStub
		,public strus::ValueIteratorInterface
		,public strus::ValueIteratorConst
{
public:
	virtual ~ValueIteratorImpl();

	ValueIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ValueIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual void skip( const char* p1, std::size_t p2);
	virtual std::vector<std::string> fetchValues( std::size_t p1);
};

class WeightingFunctionContextImpl
		:public RpcInterfaceStub
		,public strus::WeightingFunctionContextInterface
		,public strus::WeightingFunctionContextConst
{
public:
	virtual ~WeightingFunctionContextImpl();

	WeightingFunctionContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingFunctionContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addWeightingFeature( const std::string& p1, PostingIteratorInterface* p2, float p3, const TermStatistics& p4);
	virtual double call( const Index& p1);
};

class WeightingFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::WeightingFunctionInstanceInterface
		,public strus::WeightingFunctionInstanceConst
{
public:
	virtual ~WeightingFunctionInstanceImpl();

	WeightingFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addStringParameter( const std::string& p1, const std::string& p2);
	virtual void addNumericParameter( const std::string& p1, const ArithmeticVariant& p2);
	virtual WeightingFunctionContextInterface* createFunctionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2, const GlobalStatistics& p3) const;
	virtual std::string tostring( ) const;
};

class WeightingFunctionImpl
		:public RpcInterfaceStub
		,public strus::WeightingFunctionInterface
		,public strus::WeightingFunctionConst
{
public:
	virtual ~WeightingFunctionImpl();

	WeightingFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual WeightingFunctionInstanceInterface* createInstance( ) const;
	virtual WeightingFunctionInterface::Description getDescription( ) const;
};
} //namespace
#endif
