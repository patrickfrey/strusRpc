/*
 * Copyright (c) 2015 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_OBJECTS_HPP_INCLUDED
#define _STRUS_RPC_OBJECTS_HPP_INCLUDED
#include "rpcInterfaceStub.hpp"
#include "objectIds_gen.hpp"
#include "strus/aggregatorFunctionInstanceInterface.hpp"
#include "strus/aggregatorFunctionInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/contentIteratorInterface.hpp"
#include "strus/contentStatisticsContextInterface.hpp"
#include "strus/contentStatisticsInterface.hpp"
#include "strus/documentAnalyzerContextInterface.hpp"
#include "strus/documentAnalyzerInterface.hpp"
#include "strus/documentAnalyzerMapInterface.hpp"
#include "strus/documentClassDetectorInterface.hpp"
#include "strus/normalizerFunctionInstanceInterface.hpp"
#include "strus/normalizerFunctionInterface.hpp"
#include "strus/patternLexerContextInterface.hpp"
#include "strus/patternLexerInstanceInterface.hpp"
#include "strus/patternLexerInterface.hpp"
#include "strus/patternMatcherContextInterface.hpp"
#include "strus/patternMatcherInstanceInterface.hpp"
#include "strus/patternMatcherInterface.hpp"
#include "strus/patternTermFeederInstanceInterface.hpp"
#include "strus/patternTermFeederInterface.hpp"
#include "strus/queryAnalyzerContextInterface.hpp"
#include "strus/queryAnalyzerInterface.hpp"
#include "strus/segmenterContextInterface.hpp"
#include "strus/segmenterInstanceInterface.hpp"
#include "strus/segmenterInterface.hpp"
#include "strus/segmenterMarkupContextInterface.hpp"
#include "strus/textProcessorInterface.hpp"
#include "strus/tokenizerFunctionInstanceInterface.hpp"
#include "strus/tokenizerFunctionInterface.hpp"
#include "strus/tokenMarkupContextInterface.hpp"
#include "strus/tokenMarkupInstanceInterface.hpp"
#include "strus/aclReaderInterface.hpp"
#include "strus/attributeReaderInterface.hpp"
#include "strus/databaseBackupCursorInterface.hpp"
#include "strus/databaseClientInterface.hpp"
#include "strus/databaseCursorInterface.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/databaseTransactionInterface.hpp"
#include "strus/documentTermIteratorInterface.hpp"
#include "strus/forwardIteratorInterface.hpp"
#include "strus/invAclIteratorInterface.hpp"
#include "strus/metaDataReaderInterface.hpp"
#include "strus/metaDataRestrictionInstanceInterface.hpp"
#include "strus/metaDataRestrictionInterface.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/postingJoinOperatorInterface.hpp"
#include "strus/queryEvalInterface.hpp"
#include "strus/queryInterface.hpp"
#include "strus/queryProcessorInterface.hpp"
#include "strus/scalarFunctionInstanceInterface.hpp"
#include "strus/scalarFunctionInterface.hpp"
#include "strus/scalarFunctionParserInterface.hpp"
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
#include "strus/vectorStorageClientInterface.hpp"
#include "strus/vectorStorageDumpInterface.hpp"
#include "strus/vectorStorageInterface.hpp"
#include "strus/vectorStorageSearchInterface.hpp"
#include "strus/vectorStorageTransactionInterface.hpp"
#include "strus/weightingFunctionContextInterface.hpp"
#include "strus/weightingFunctionInstanceInterface.hpp"
#include "strus/weightingFunctionInterface.hpp"

namespace strus {

class AclReaderImpl
		:public RpcInterfaceStub
		,public strus::AclReaderInterface
		,public strus::AclReaderConst
{
public:
	virtual ~AclReaderImpl();

	AclReaderImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AclReader, objId_, ctx_, isConst_, errorhnd_){}

	virtual void skipDoc( const Index& p1);
	virtual std::vector<std::string> getReadAccessList( ) const;
};

class AggregatorFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::AggregatorFunctionInstanceInterface
		,public strus::AggregatorFunctionInstanceConst
{
public:
	virtual ~AggregatorFunctionInstanceImpl();

	AggregatorFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_AggregatorFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual NumericVariant evaluate( const analyzer::Document& p1) const;
	virtual analyzer::FunctionView view( ) const;
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
	virtual DocumentAnalyzerInterface* createDocumentAnalyzer( const SegmenterInterface* p1, const analyzer::SegmenterOptions& p2) const;
	virtual QueryAnalyzerInterface* createQueryAnalyzer( ) const;
	virtual DocumentAnalyzerMapInterface* createDocumentAnalyzerMap( ) const;
	virtual DocumentClassDetectorInterface* createDocumentClassDetector( ) const;
	virtual ContentStatisticsInterface* createContentStatistics( ) const;
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
	virtual std::vector<std::string> getNames( ) const;
};

class ContentIteratorImpl
		:public RpcInterfaceStub
		,public strus::ContentIteratorInterface
		,public strus::ContentIteratorConst
{
public:
	virtual ~ContentIteratorImpl();

	ContentIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ContentIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool getNext( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4);
};

class ContentStatisticsContextImpl
		:public RpcInterfaceStub
		,public strus::ContentStatisticsContextInterface
		,public strus::ContentStatisticsContextConst
{
public:
	virtual ~ContentStatisticsContextImpl();

	ContentStatisticsContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ContentStatisticsContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putContent( const std::string& p1, const std::string& p2, const analyzer::DocumentClass& p3);
	virtual analyzer::ContentStatisticsResult statistics( );
	virtual int nofDocuments( ) const;
};

class ContentStatisticsImpl
		:public RpcInterfaceStub
		,public strus::ContentStatisticsInterface
		,public strus::ContentStatisticsConst
{
public:
	virtual ~ContentStatisticsImpl();

	ContentStatisticsImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ContentStatistics, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addLibraryElement( const std::string& p1, const std::string& p2, int p3, int p4, int p5, TokenizerFunctionInstanceInterface* p6, const std::vector<NormalizerFunctionInstanceInterface*>& p7);
	virtual ContentStatisticsContextInterface* createContext( ) const;
	virtual analyzer::ContentStatisticsView view( ) const;
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
	virtual void close( );
	virtual std::string config( ) const;
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
	virtual DatabaseCursorInterface::Slice seekUpperBoundRestricted( const char* p1, std::size_t p2, const char* p3, std::size_t p4);
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
	virtual const char* getConfigDescription( const DatabaseInterface::ConfigType& p1) const;
	virtual const char** getConfigParameters( const DatabaseInterface::ConfigType& p1) const;
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

	virtual void addSearchIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const analyzer::FeatureOptions& p5);
	virtual void addForwardIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const analyzer::FeatureOptions& p5);
	virtual void defineMetaData( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void defineAggregatedMetaData( const std::string& p1, AggregatorFunctionInstanceInterface* p2);
	virtual void defineAttribute( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void defineSubDocument( const std::string& p1, const std::string& p2);
	virtual void defineSubContent( const std::string& p1, const analyzer::DocumentClass& p2);
	virtual void addPatternLexem( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void definePatternMatcherPostProc( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternTermFeederInstanceInterface* p3);
	virtual void definePatternMatcherPreProc( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternLexerInstanceInterface* p3, const std::vector<std::string>& p4);
	virtual void addSearchIndexFeatureFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3, const analyzer::FeatureOptions& p4);
	virtual void addForwardIndexFeatureFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3, const analyzer::FeatureOptions& p4);
	virtual void defineMetaDataFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3);
	virtual void defineAttributeFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3);
	virtual analyzer::Document analyze( const std::string& p1, const analyzer::DocumentClass& p2) const;
	virtual DocumentAnalyzerContextInterface* createContext( const analyzer::DocumentClass& p1) const;
	virtual analyzer::DocumentAnalyzerView view( ) const;
};

class DocumentAnalyzerMapImpl
		:public RpcInterfaceStub
		,public strus::DocumentAnalyzerMapInterface
		,public strus::DocumentAnalyzerMapConst
{
public:
	virtual ~DocumentAnalyzerMapImpl();

	DocumentAnalyzerMapImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzerMap, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addAnalyzer( const std::string& p1, const std::string& p2, DocumentAnalyzerInterface* p3);
	virtual analyzer::Document analyze( const std::string& p1, const analyzer::DocumentClass& p2) const;
	virtual DocumentAnalyzerContextInterface* createContext( const analyzer::DocumentClass& p1) const;
	virtual analyzer::DocumentAnalyzerMapView view( ) const;
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

	virtual void defineDocumentSchemeDetector( const std::string& p1, const std::string& p2, const std::vector<std::string>& p3, const std::vector<std::string>& p4);
	virtual bool detect( analyzer::DocumentClass& p1, const char* p2, std::size_t p3, bool p4) const;
};

class DocumentTermIteratorImpl
		:public RpcInterfaceStub
		,public strus::DocumentTermIteratorInterface
		,public strus::DocumentTermIteratorConst
{
public:
	virtual ~DocumentTermIteratorImpl();

	DocumentTermIteratorImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentTermIterator, objId_, ctx_, isConst_, errorhnd_){}

	virtual Index skipDoc( const Index& p1);
	virtual bool nextTerm( DocumentTermIteratorInterface::Term& p1);
	virtual unsigned int termDocumentFrequency( const Index& p1) const;
	virtual std::string termValue( const Index& p1) const;
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

	virtual Index elementHandle( const std::string& p1) const;
	virtual Index nofElements( ) const;
	virtual void skipDoc( const Index& p1);
	virtual NumericVariant getValue( const Index& p1) const;
	virtual const char* getType( const Index& p1) const;
	virtual const char* getName( const Index& p1) const;
	virtual std::vector<std::string> getNames( ) const;
};

class MetaDataRestrictionInstanceImpl
		:public RpcInterfaceStub
		,public strus::MetaDataRestrictionInstanceInterface
		,public strus::MetaDataRestrictionInstanceConst
{
public:
	virtual ~MetaDataRestrictionInstanceImpl();

	MetaDataRestrictionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_MetaDataRestrictionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool match( const Index& p1) const;
};

class MetaDataRestrictionImpl
		:public RpcInterfaceStub
		,public strus::MetaDataRestrictionInterface
		,public strus::MetaDataRestrictionConst
{
public:
	virtual ~MetaDataRestrictionImpl();

	MetaDataRestrictionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_MetaDataRestriction, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addCondition( const MetaDataRestrictionInterface::CompareOperator& p1, const std::string& p2, const NumericVariant& p3, bool p4);
	virtual MetaDataRestrictionInstanceInterface* createInstance( ) const;
	virtual std::string tostring( ) const;
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

	virtual std::string normalize( const char* p1, std::size_t p2) const;
	virtual analyzer::FunctionView view( ) const;
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

class PatternLexerContextImpl
		:public RpcInterfaceStub
		,public strus::PatternLexerContextInterface
		,public strus::PatternLexerContextConst
{
public:
	virtual ~PatternLexerContextImpl();

	PatternLexerContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternLexerContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<analyzer::PatternLexem> match( const char* p1, std::size_t p2);
	virtual void reset( );
};

class PatternLexerInstanceImpl
		:public RpcInterfaceStub
		,public strus::PatternLexerInstanceInterface
		,public strus::PatternLexerInstanceConst
{
public:
	virtual ~PatternLexerInstanceImpl();

	PatternLexerInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternLexerInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void defineOption( const std::string& p1, double p2);
	virtual void defineLexemName( unsigned int p1, const std::string& p2);
	virtual void defineLexem( unsigned int p1, const std::string& p2, unsigned int p3, unsigned int p4, analyzer::PositionBind p5);
	virtual void defineSymbol( unsigned int p1, unsigned int p2, const std::string& p3);
	virtual unsigned int getSymbol( unsigned int p1, const std::string& p2) const;
	virtual const char* getLexemName( unsigned int p1) const;
	virtual bool compile( );
	virtual PatternLexerContextInterface* createContext( ) const;
	virtual analyzer::FunctionView view( ) const;
};

class PatternLexerImpl
		:public RpcInterfaceStub
		,public strus::PatternLexerInterface
		,public strus::PatternLexerConst
{
public:
	virtual ~PatternLexerImpl();

	PatternLexerImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternLexer, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<std::string> getCompileOptionNames( ) const;
	virtual PatternLexerInstanceInterface* createInstance( ) const;
	virtual const char* getDescription( ) const;
};

class PatternMatcherContextImpl
		:public RpcInterfaceStub
		,public strus::PatternMatcherContextInterface
		,public strus::PatternMatcherContextConst
{
public:
	virtual ~PatternMatcherContextImpl();

	PatternMatcherContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternMatcherContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putInput( const analyzer::PatternLexem& p1);
	virtual std::vector<analyzer::PatternMatcherResult> fetchResults( );
	virtual analyzer::PatternMatcherStatistics getStatistics( ) const;
	virtual void reset( );
};

class PatternMatcherInstanceImpl
		:public RpcInterfaceStub
		,public strus::PatternMatcherInstanceInterface
		,public strus::PatternMatcherInstanceConst
{
public:
	virtual ~PatternMatcherInstanceImpl();

	PatternMatcherInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternMatcherInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void defineOption( const std::string& p1, double p2);
	virtual void defineTermFrequency( unsigned int p1, double p2);
	virtual void pushTerm( unsigned int p1);
	virtual void pushExpression( PatternMatcherInstanceInterface::JoinOperation p1, std::size_t p2, unsigned int p3, unsigned int p4);
	virtual void pushPattern( const std::string& p1);
	virtual void attachVariable( const std::string& p1);
	virtual void definePattern( const std::string& p1, const std::string& p2, bool p3);
	virtual bool compile( );
	virtual PatternMatcherContextInterface* createContext( ) const;
	virtual analyzer::FunctionView view( ) const;
};

class PatternMatcherImpl
		:public RpcInterfaceStub
		,public strus::PatternMatcherInterface
		,public strus::PatternMatcherConst
{
public:
	virtual ~PatternMatcherImpl();

	PatternMatcherImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternMatcher, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<std::string> getCompileOptionNames( ) const;
	virtual PatternMatcherInstanceInterface* createInstance( ) const;
	virtual const char* getDescription( ) const;
};

class PatternTermFeederInstanceImpl
		:public RpcInterfaceStub
		,public strus::PatternTermFeederInstanceInterface
		,public strus::PatternTermFeederInstanceConst
{
public:
	virtual ~PatternTermFeederInstanceImpl();

	PatternTermFeederInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternTermFeederInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void defineLexem( unsigned int p1, const std::string& p2);
	virtual void defineSymbol( unsigned int p1, unsigned int p2, const std::string& p3);
	virtual unsigned int getLexem( const std::string& p1) const;
	virtual std::vector<std::string> lexemTypes( ) const;
	virtual unsigned int getSymbol( unsigned int p1, const std::string& p2) const;
	virtual analyzer::FunctionView view( ) const;
};

class PatternTermFeederImpl
		:public RpcInterfaceStub
		,public strus::PatternTermFeederInterface
		,public strus::PatternTermFeederConst
{
public:
	virtual ~PatternTermFeederImpl();

	PatternTermFeederImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_PatternTermFeeder, objId_, ctx_, isConst_, errorhnd_){}

	virtual PatternTermFeederInstanceInterface* createInstance( ) const;
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
	virtual Index length( ) const;
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

class QueryAnalyzerContextImpl
		:public RpcInterfaceStub
		,public strus::QueryAnalyzerContextInterface
		,public strus::QueryAnalyzerContextConst
{
public:
	virtual ~QueryAnalyzerContextImpl();

	QueryAnalyzerContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryAnalyzerContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putField( int p1, const std::string& p2, const std::string& p3);
	virtual void groupElements( int p1, const std::vector<int>& p2, const QueryAnalyzerContextInterface::GroupBy& p3, bool p4);
	virtual analyzer::QueryTermExpression analyze( );
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

	virtual void addElement( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void addPatternLexem( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4);
	virtual void definePatternMatcherPostProc( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternTermFeederInstanceInterface* p3);
	virtual void definePatternMatcherPreProc( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternLexerInstanceInterface* p3, const std::vector<std::string>& p4);
	virtual void addElementFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3);
	virtual void declareElementPriority( const std::string& p1, int p2);
	virtual QueryAnalyzerContextInterface* createContext( ) const;
	virtual analyzer::QueryAnalyzerView view( ) const;
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
	virtual void addWeightingFunction( const std::string& p1, WeightingFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3, const std::string& p4);
	virtual void defineWeightingFormula( ScalarFunctionInterface* p1);
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

	virtual void pushTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void pushDocField( const std::string& p1, const std::string& p2);
	virtual void pushExpression( const PostingJoinOperatorInterface* p1, unsigned int p2, int p3, unsigned int p4);
	virtual void attachVariable( const std::string& p1);
	virtual void defineFeature( const std::string& p1, double p2);
	virtual void defineTermStatistics( const std::string& p1, const std::string& p2, const TermStatistics& p3);
	virtual void defineGlobalStatistics( const GlobalStatistics& p1);
	virtual void addMetaDataRestrictionCondition( const MetaDataRestrictionInterface::CompareOperator& p1, const std::string& p2, const NumericVariant& p3, bool p4);
	virtual void addDocumentEvaluationSet( const std::vector<Index>& p1);
	virtual void addAccess( const std::string& p1);
	virtual void setMaxNofRanks( std::size_t p1);
	virtual void setMinRank( std::size_t p1);
	virtual void setWeightingVariableValue( const std::string& p1, double p2);
	virtual void setDebugMode( bool p1);
	virtual QueryResult evaluate( ) const;
	virtual std::string tostring( ) const;
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
	virtual std::vector<std::string> getFunctionList( const QueryProcessorInterface::FunctionType& p1) const;
	virtual void defineScalarFunctionParser( const std::string& p1, ScalarFunctionParserInterface* p2);
	virtual const ScalarFunctionParserInterface* getScalarFunctionParser( const std::string& p1) const;
};

class ScalarFunctionInstanceImpl
		:public RpcInterfaceStub
		,public strus::ScalarFunctionInstanceInterface
		,public strus::ScalarFunctionInstanceConst
{
public:
	virtual ~ScalarFunctionInstanceImpl();

	ScalarFunctionInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ScalarFunctionInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual void setVariableValue( const std::string& p1, double p2);
	virtual double call( const double* p1, unsigned int p2) const;
	virtual std::string tostring( ) const;
};

class ScalarFunctionImpl
		:public RpcInterfaceStub
		,public strus::ScalarFunctionInterface
		,public strus::ScalarFunctionConst
{
public:
	virtual ~ScalarFunctionImpl();

	ScalarFunctionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ScalarFunction, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<std::string> getVariables( ) const;
	virtual unsigned int getNofArguments( ) const;
	virtual void setDefaultVariableValue( const std::string& p1, double p2);
	virtual ScalarFunctionInstanceInterface* createInstance( ) const;
	virtual std::string tostring( ) const;
};

class ScalarFunctionParserImpl
		:public RpcInterfaceStub
		,public strus::ScalarFunctionParserInterface
		,public strus::ScalarFunctionParserConst
{
public:
	virtual ~ScalarFunctionParserImpl();

	ScalarFunctionParserImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_ScalarFunctionParser, objId_, ctx_, isConst_, errorhnd_){}

	virtual ScalarFunctionInterface* createFunction( const std::string& p1, const std::vector<std::string>& p2) const;
	virtual const char* getDescription( ) const;
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
	virtual SegmenterContextInterface* createContext( const analyzer::DocumentClass& p1) const;
	virtual SegmenterMarkupContextInterface* createMarkupContext( const analyzer::DocumentClass& p1, const std::string& p2) const;
	virtual analyzer::FunctionView view( ) const;
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
	virtual SegmenterInstanceInterface* createInstance( const analyzer::SegmenterOptions& p1) const;
	virtual ContentIteratorInterface* createContentIterator( const char* p1, std::size_t p2, const analyzer::DocumentClass& p3, const analyzer::SegmenterOptions& p4) const;
	virtual const char* getDescription( ) const;
};

class SegmenterMarkupContextImpl
		:public RpcInterfaceStub
		,public strus::SegmenterMarkupContextInterface
		,public strus::SegmenterMarkupContextConst
{
public:
	virtual ~SegmenterMarkupContextImpl();

	SegmenterMarkupContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_SegmenterMarkupContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool getNext( SegmenterPosition& p1, const char*& p2, std::size_t& p3);
	virtual unsigned int segmentSize( const SegmenterPosition& p1);
	virtual std::string tagName( const SegmenterPosition& p1) const;
	virtual int tagLevel( const SegmenterPosition& p1) const;
	virtual void putOpenTag( const SegmenterPosition& p1, std::size_t p2, const std::string& p3);
	virtual void putAttribute( const SegmenterPosition& p1, std::size_t p2, const std::string& p3, const std::string& p4);
	virtual void putCloseTag( const SegmenterPosition& p1, std::size_t p2, const std::string& p3);
	virtual std::string getContent( ) const;
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
	virtual bool fetchMessage( const void*& p1, std::size_t& p2);
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

	virtual bool getNext( const void*& p1, std::size_t& p2);
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

	virtual StatisticsViewerInterface* createViewer( const void* p1, std::size_t p2) const;
	virtual StatisticsBuilderInterface* createBuilder( ) const;
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
	virtual bool nextDfChange( TermStatisticsChange& p1);
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

	virtual std::string config( ) const;
	virtual PostingIteratorInterface* createTermPostingIterator( const std::string& p1, const std::string& p2, const Index& p3) const;
	virtual PostingIteratorInterface* createBrowsePostingIterator( const MetaDataRestrictionInterface* p1, const Index& p2) const;
	virtual PostingIteratorInterface* createFieldPostingIterator( const std::string& p1, const std::string& p2) const;
	virtual ForwardIteratorInterface* createForwardIterator( const std::string& p1) const;
	virtual DocumentTermIteratorInterface* createDocumentTermIterator( const std::string& p1) const;
	virtual InvAclIteratorInterface* createInvAclIterator( const std::string& p1) const;
	virtual AclReaderInterface* createAclReader( ) const;
	virtual Index nofDocumentsInserted( ) const;
	virtual Index documentFrequency( const std::string& p1, const std::string& p2) const;
	virtual Index maxDocumentNumber( ) const;
	virtual Index documentNumber( const std::string& p1) const;
	virtual Index termTypeNumber( const std::string& p1) const;
	virtual bool isForwardIndexTerm( const std::string& p1) const;
	virtual ValueIteratorInterface* createTermTypeIterator( ) const;
	virtual ValueIteratorInterface* createTermValueIterator( ) const;
	virtual ValueIteratorInterface* createDocIdIterator( ) const;
	virtual ValueIteratorInterface* createUserNameIterator( ) const;
	virtual Index documentStatistics( const Index& p1, const StorageClientInterface::DocumentStatisticsType& p2, const std::string& p3) const;
	virtual MetaDataReaderInterface* createMetaDataReader( ) const;
	virtual MetaDataRestrictionInterface* createMetaDataRestriction( ) const;
	virtual AttributeReaderInterface* createAttributeReader( ) const;
	virtual StorageTransactionInterface* createTransaction( );
	virtual StatisticsIteratorInterface* createAllStatisticsIterator( bool p1);
	virtual StatisticsIteratorInterface* createChangeStatisticsIterator( );
	virtual const StatisticsProcessorInterface* getStatisticsProcessor( ) const;
	virtual StorageDocumentInterface* createDocumentChecker( const std::string& p1, const std::string& p2) const;
	virtual bool checkStorage( std::ostream& p1) const;
	virtual void close( );
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
	virtual void setMetaData( const std::string& p1, const NumericVariant& p2);
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

	virtual void addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void clearSearchIndexTerm( const std::string& p1);
	virtual void clearForwardIndexTerm( const std::string& p1);
	virtual void setMetaData( const std::string& p1, const NumericVariant& p2);
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

	virtual StorageClientInterface* createClient( const std::string& p1, const DatabaseInterface* p2, const StatisticsProcessorInterface* p3) const;
	virtual bool createStorage( const std::string& p1, const DatabaseInterface* p2) const;
	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable( const std::string& p1, const DatabaseInterface* p2) const;
	virtual const char* getConfigDescription( const StorageInterface::ConfigType& p1) const;
	virtual const char** getConfigParameters( const StorageInterface::ConfigType& p1) const;
	virtual StorageDumpInterface* createDump( const std::string& p1, const DatabaseInterface* p2, const std::string& p3) const;
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
	virtual const StatisticsProcessorInterface* getStatisticsProcessor( const std::string& p1) const;
	virtual const VectorStorageInterface* getVectorStorage( const std::string& p1) const;
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
	virtual void updateMetaData( const Index& p1, const std::string& p2, const NumericVariant& p3);
	virtual void updateDocumentFrequency( const std::string& p1, const std::string& p2, int p3);
	virtual bool commit( );
	virtual void rollback( );
	virtual unsigned int nofDocumentsAffected( ) const;
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

	virtual void addSummarizationFeature( const std::string& p1, PostingIteratorInterface* p2, const std::vector<SummarizationVariable>& p3, double p4, const TermStatistics& p5);
	virtual void setVariableValue( const std::string& p1, double p2);
	virtual std::vector<SummaryElement> getSummary( const Index& p1);
	virtual std::string debugCall( const Index& p1);
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
	virtual void addNumericParameter( const std::string& p1, const NumericVariant& p2);
	virtual void defineResultName( const std::string& p1, const std::string& p2);
	virtual std::vector<std::string> getVariables( ) const;
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
	virtual FunctionDescription getDescription( ) const;
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
	virtual const SegmenterInterface* getSegmenterByName( const std::string& p1) const;
	virtual const SegmenterInterface* getSegmenterByMimeType( const std::string& p1) const;
	virtual analyzer::SegmenterOptions getSegmenterOptions( const std::string& p1) const;
	virtual const TokenizerFunctionInterface* getTokenizer( const std::string& p1) const;
	virtual const NormalizerFunctionInterface* getNormalizer( const std::string& p1) const;
	virtual const AggregatorFunctionInterface* getAggregator( const std::string& p1) const;
	virtual const PatternLexerInterface* getPatternLexer( const std::string& p1) const;
	virtual const PatternMatcherInterface* getPatternMatcher( const std::string& p1) const;
	virtual const PatternTermFeederInterface* getPatternTermFeeder( ) const;
	virtual bool detectDocumentClass( analyzer::DocumentClass& p1, const char* p2, std::size_t p3, bool p4) const;
	virtual void defineDocumentClassDetector( DocumentClassDetectorInterface* p1);
	virtual void defineSegmenter( const std::string& p1, SegmenterInterface* p2);
	virtual void defineSegmenterOptions( const std::string& p1, const analyzer::SegmenterOptions& p2);
	virtual void defineTokenizer( const std::string& p1, TokenizerFunctionInterface* p2);
	virtual void defineNormalizer( const std::string& p1, NormalizerFunctionInterface* p2);
	virtual void defineAggregator( const std::string& p1, AggregatorFunctionInterface* p2);
	virtual void definePatternLexer( const std::string& p1, PatternLexerInterface* p2);
	virtual void definePatternMatcher( const std::string& p1, PatternMatcherInterface* p2);
	virtual std::vector<std::string> getFunctionList( const TextProcessorInterface::FunctionType& p1) const;
};

class TokenMarkupContextImpl
		:public RpcInterfaceStub
		,public strus::TokenMarkupContextInterface
		,public strus::TokenMarkupContextConst
{
public:
	virtual ~TokenMarkupContextImpl();

	TokenMarkupContextImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenMarkupContext, objId_, ctx_, isConst_, errorhnd_){}

	virtual void putMarkup( const SegmenterPosition& p1, std::size_t p2, const SegmenterPosition& p3, std::size_t p4, const analyzer::TokenMarkup& p5, unsigned int p6);
	virtual std::string markupDocument( const SegmenterInstanceInterface* p1, const analyzer::DocumentClass& p2, const std::string& p3) const;
};

class TokenMarkupInstanceImpl
		:public RpcInterfaceStub
		,public strus::TokenMarkupInstanceInterface
		,public strus::TokenMarkupInstanceConst
{
public:
	virtual ~TokenMarkupInstanceImpl();

	TokenMarkupInstanceImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenMarkupInstance, objId_, ctx_, isConst_, errorhnd_){}

	virtual TokenMarkupContextInterface* createContext( ) const;
	virtual analyzer::FunctionView view( ) const;
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
	virtual std::vector<analyzer::Token> tokenize( const char* p1, std::size_t p2) const;
	virtual analyzer::FunctionView view( ) const;
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
	virtual void skipPrefix( const char* p1, std::size_t p2);
	virtual std::vector<std::string> fetchValues( std::size_t p1);
};

class VectorStorageClientImpl
		:public RpcInterfaceStub
		,public strus::VectorStorageClientInterface
		,public strus::VectorStorageClientConst
{
public:
	virtual ~VectorStorageClientImpl();

	VectorStorageClientImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_VectorStorageClient, objId_, ctx_, isConst_, errorhnd_){}

	virtual VectorStorageSearchInterface* createSearcher( const Index& p1, const Index& p2) const;
	virtual VectorStorageTransactionInterface* createTransaction( );
	virtual std::vector<std::string> conceptClassNames( ) const;
	virtual std::vector<Index> conceptFeatures( const std::string& p1, const Index& p2) const;
	virtual unsigned int nofConcepts( const std::string& p1) const;
	virtual std::vector<Index> featureConcepts( const std::string& p1, const Index& p2) const;
	virtual std::vector<double> featureVector( const Index& p1) const;
	virtual std::string featureName( const Index& p1) const;
	virtual Index featureIndex( const std::string& p1) const;
	virtual double vectorSimilarity( const std::vector<double>& p1, const std::vector<double>& p2) const;
	virtual unsigned int nofFeatures( ) const;
	virtual std::string config( ) const;
	virtual void close( );
};

class VectorStorageDumpImpl
		:public RpcInterfaceStub
		,public strus::VectorStorageDumpInterface
		,public strus::VectorStorageDumpConst
{
public:
	virtual ~VectorStorageDumpImpl();

	VectorStorageDumpImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_VectorStorageDump, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool nextChunk( const char*& p1, std::size_t& p2);
};

class VectorStorageImpl
		:public RpcInterfaceStub
		,public strus::VectorStorageInterface
		,public strus::VectorStorageConst
{
public:
	virtual ~VectorStorageImpl();

	VectorStorageImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_VectorStorage, objId_, ctx_, isConst_, errorhnd_){}

	virtual bool createStorage( const std::string& p1, const DatabaseInterface* p2) const;
	virtual VectorStorageClientInterface* createClient( const std::string& p1, const DatabaseInterface* p2) const;
	virtual VectorStorageDumpInterface* createDump( const std::string& p1, const DatabaseInterface* p2, const std::string& p3) const;
	virtual bool runBuild( const std::string& p1, const std::string& p2, const DatabaseInterface* p3) const;
};

class VectorStorageSearchImpl
		:public RpcInterfaceStub
		,public strus::VectorStorageSearchInterface
		,public strus::VectorStorageSearchConst
{
public:
	virtual ~VectorStorageSearchImpl();

	VectorStorageSearchImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_VectorStorageSearch, objId_, ctx_, isConst_, errorhnd_){}

	virtual std::vector<VectorQueryResult> findSimilar( const std::vector<double>& p1, unsigned int p2) const;
	virtual std::vector<VectorQueryResult> findSimilarFromSelection( const std::vector<Index>& p1, const std::vector<double>& p2, unsigned int p3) const;
	virtual void close( );
};

class VectorStorageTransactionImpl
		:public RpcInterfaceStub
		,public strus::VectorStorageTransactionInterface
		,public strus::VectorStorageTransactionConst
{
public:
	virtual ~VectorStorageTransactionImpl();

	VectorStorageTransactionImpl( unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
		:RpcInterfaceStub( (unsigned char)ClassId_VectorStorageTransaction, objId_, ctx_, isConst_, errorhnd_){}

	virtual void addFeature( const std::string& p1, const std::vector<double>& p2);
	virtual void defineFeatureConceptRelation( const std::string& p1, const Index& p2, const Index& p3);
	virtual bool commit( );
	virtual void rollback( );
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

	virtual void addWeightingFeature( const std::string& p1, PostingIteratorInterface* p2, double p3, const TermStatistics& p4);
	virtual void setVariableValue( const std::string& p1, double p2);
	virtual double call( const Index& p1);
	virtual std::string debugCall( const Index& p1);
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
	virtual void addNumericParameter( const std::string& p1, const NumericVariant& p2);
	virtual WeightingFunctionContextInterface* createFunctionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2, const GlobalStatistics& p3) const;
	virtual std::vector<std::string> getVariables( ) const;
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

	virtual WeightingFunctionInstanceInterface* createInstance( const QueryProcessorInterface* p1) const;
	virtual FunctionDescription getDescription( ) const;
};
} //namespace
#endif
