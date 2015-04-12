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
#ifndef _STRUS_RPC_OBJECTS_HPP_INCLUDED
#define _STRUS_RPC_OBJECTS_HPP_INCLUDED
#include "rpcInterfaceStub.hpp"
#include "strus/databaseBackupCursorInterface.hpp"
#include "strus/queryEvalInterface.hpp"
#include "strus/storageTransactionInterface.hpp"
#include "strus/storageClientInterface.hpp"
#include "strus/databaseInterface.hpp"
#include "strus/storagePeerInterface.hpp"
#include "strus/invAclIteratorInterface.hpp"
#include "strus/databaseClientInterface.hpp"
#include "strus/queryProcessorInterface.hpp"
#include "strus/summarizerClosureInterface.hpp"
#include "strus/weightingFunctionInterface.hpp"
#include "strus/storageDumpInterface.hpp"
#include "strus/queryInterface.hpp"
#include "strus/docnoRangeAllocatorInterface.hpp"
#include "strus/metaDataReaderInterface.hpp"
#include "strus/storageInterface.hpp"
#include "strus/forwardIteratorInterface.hpp"
#include "strus/databaseTransactionInterface.hpp"
#include "strus/summarizerFunctionInterface.hpp"
#include "strus/weightingClosureInterface.hpp"
#include "strus/databaseCursorInterface.hpp"
#include "strus/peerStorageTransactionInterface.hpp"
#include "strus/attributeReaderInterface.hpp"
#include "strus/storagePeerTransactionInterface.hpp"
#include "strus/storageAlterMetaDataTableInterface.hpp"
#include "strus/postingIteratorInterface.hpp"
#include "strus/postingJoinOperatorInterface.hpp"
#include "strus/storageDocumentInterface.hpp"
#include "strus/tokenizerInstanceInterface.hpp"
#include "strus/segmenterInstanceInterface.hpp"
#include "strus/tokenizerInterface.hpp"
#include "strus/normalizerConstructorInterface.hpp"
#include "strus/documentAnalyzerInstanceInterface.hpp"
#include "strus/segmenterInterface.hpp"
#include "strus/tokenizerConstructorInterface.hpp"
#include "strus/normalizerInstanceInterface.hpp"
#include "strus/queryAnalyzerInterface.hpp"
#include "strus/textProcessorInterface.hpp"
#include "strus/normalizerInterface.hpp"
#include "strus/documentAnalyzerInterface.hpp"

namespace strus {

enum ClassId
{
	ClassId_AttributeReader,
	ClassId_DatabaseBackupCursor,
	ClassId_DatabaseClient,
	ClassId_DatabaseCursor,
	ClassId_Database,
	ClassId_DatabaseTransaction,
	ClassId_DocnoRangeAllocator,
	ClassId_DocumentAnalyzerInstance,
	ClassId_DocumentAnalyzer,
	ClassId_ForwardIterator,
	ClassId_InvAclIterator,
	ClassId_MetaDataReader,
	ClassId_NormalizerConstructor,
	ClassId_NormalizerInstance,
	ClassId_Normalizer,
	ClassId_PeerStorageTransaction,
	ClassId_PostingIterator,
	ClassId_PostingJoinOperator,
	ClassId_QueryAnalyzer,
	ClassId_QueryEval,
	ClassId_Query,
	ClassId_QueryProcessor,
	ClassId_SegmenterInstance,
	ClassId_Segmenter,
	ClassId_StorageAlterMetaDataTable,
	ClassId_StorageClient,
	ClassId_StorageDocument,
	ClassId_StorageDump,
	ClassId_Storage,
	ClassId_StoragePeer,
	ClassId_StoragePeerTransaction,
	ClassId_StorageTransaction,
	ClassId_SummarizerClosure,
	ClassId_SummarizerFunction,
	ClassId_TextProcessor,
	ClassId_TokenizerConstructor,
	ClassId_TokenizerInstance,
	ClassId_Tokenizer,
	ClassId_WeightingClosure,
	ClassId_WeightingFunction
};

class AttributeReaderImpl
		:public RpcInterfaceStub
		,public strus::AttributeReaderInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_elementHandle,
		Method_skipDoc,
		Method_getValue
	};

	virtual ~AttributeReaderImpl();

	explicit AttributeReaderImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_AttributeReader, endpoint_){}

	AttributeReaderImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_AttributeReader, objId_, endpoint_){}

	virtual Index elementHandle( const char* p1) const;
	virtual void skipDoc( const Index& p1);
	virtual std::string getValue( const Index& p1) const;
};

class DatabaseBackupCursorImpl
		:public RpcInterfaceStub
		,public strus::DatabaseBackupCursorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_fetch
	};

	virtual ~DatabaseBackupCursorImpl();

	explicit DatabaseBackupCursorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseBackupCursor, endpoint_){}

	DatabaseBackupCursorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseBackupCursor, objId_, endpoint_){}

	virtual bool fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4);
};

class DatabaseClientImpl
		:public RpcInterfaceStub
		,public strus::DatabaseClientInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_close,
		Method_createTransaction,
		Method_createCursor,
		Method_createBackupCursor,
		Method_writeImm,
		Method_removeImm,
		Method_readValue
	};

	virtual ~DatabaseClientImpl();

	explicit DatabaseClientImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseClient, endpoint_){}

	DatabaseClientImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseClient, objId_, endpoint_){}

	virtual void close( );
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
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_seekUpperBound,
		Method_seekFirst,
		Method_seekLast,
		Method_seekNext,
		Method_seekPrev,
		Method_key,
		Method_value
	};

	virtual ~DatabaseCursorImpl();

	explicit DatabaseCursorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseCursor, endpoint_){}

	DatabaseCursorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseCursor, objId_, endpoint_){}

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
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createClient,
		Method_createDatabase,
		Method_restoreDatabase,
		Method_destroyDatabase,
		Method_getConfigDescription,
		Method_getConfigParameters
	};

	virtual ~DatabaseImpl();

	explicit DatabaseImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Database, endpoint_){}

	DatabaseImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Database, objId_, endpoint_){}

	virtual DatabaseClientInterface* createClient( const std::string& p1) const;
	virtual void createDatabase( const std::string& p1) const;
	virtual void restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const;
	virtual void destroyDatabase( const std::string& p1) const;
	virtual const char* getConfigDescription( DatabaseInterface::ConfigType p1) const;
	virtual const char** getConfigParameters( DatabaseInterface::ConfigType p1) const;
};

class DatabaseTransactionImpl
		:public RpcInterfaceStub
		,public strus::DatabaseTransactionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createCursor,
		Method_write,
		Method_remove,
		Method_removeSubTree,
		Method_commit,
		Method_rollback
	};

	virtual ~DatabaseTransactionImpl();

	explicit DatabaseTransactionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseTransaction, endpoint_){}

	DatabaseTransactionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DatabaseTransaction, objId_, endpoint_){}

	virtual DatabaseCursorInterface* createCursor( const DatabaseOptions& p1) const;
	virtual void write( const char* p1, std::size_t p2, const char* p3, std::size_t p4);
	virtual void remove( const char* p1, std::size_t p2);
	virtual void removeSubTree( const char* p1, std::size_t p2);
	virtual void commit( );
	virtual void rollback( );
};

class DocnoRangeAllocatorImpl
		:public RpcInterfaceStub
		,public strus::DocnoRangeAllocatorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_allocDocnoRange,
		Method_deallocDocnoRange
	};

	virtual ~DocnoRangeAllocatorImpl();

	explicit DocnoRangeAllocatorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocnoRangeAllocator, endpoint_){}

	DocnoRangeAllocatorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocnoRangeAllocator, objId_, endpoint_){}

	virtual Index allocDocnoRange( const Index& p1);
	virtual bool deallocDocnoRange( const Index& p1, const Index& p2);
};

class DocumentAnalyzerInstanceImpl
		:public RpcInterfaceStub
		,public strus::DocumentAnalyzerInstanceInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putInput,
		Method_analyzeNext
	};

	virtual ~DocumentAnalyzerInstanceImpl();

	explicit DocumentAnalyzerInstanceImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzerInstance, endpoint_){}

	DocumentAnalyzerInstanceImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzerInstance, objId_, endpoint_){}

	virtual void putInput( const char* p1, std::size_t p2, bool p3);
	virtual bool analyzeNext( analyzer::Document& p1);
};

class DocumentAnalyzerImpl
		:public RpcInterfaceStub
		,public strus::DocumentAnalyzerInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSearchIndexFeature,
		Method_addForwardIndexFeature,
		Method_defineMetaData,
		Method_defineAttribute,
		Method_defineSubDocument,
		Method_analyze,
		Method_createInstance
	};

	virtual ~DocumentAnalyzerImpl();

	explicit DocumentAnalyzerImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzer, endpoint_){}

	DocumentAnalyzerImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_DocumentAnalyzer, objId_, endpoint_){}

	virtual void addSearchIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5);
	virtual void addForwardIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5);
	virtual void defineMetaData( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4);
	virtual void defineAttribute( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4);
	virtual void defineSubDocument( const std::string& p1, const std::string& p2);
	virtual analyzer::Document analyze( const std::string& p1) const;
	virtual DocumentAnalyzerInstanceInterface* createInstance( ) const;
};

class ForwardIteratorImpl
		:public RpcInterfaceStub
		,public strus::ForwardIteratorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_skipPos,
		Method_fetch
	};

	virtual ~ForwardIteratorImpl();

	explicit ForwardIteratorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_ForwardIterator, endpoint_){}

	ForwardIteratorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_ForwardIterator, objId_, endpoint_){}

	virtual void skipDoc( const Index& p1);
	virtual Index skipPos( const Index& p1);
	virtual std::string fetch( );
};

class InvAclIteratorImpl
		:public RpcInterfaceStub
		,public strus::InvAclIteratorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc
	};

	virtual ~InvAclIteratorImpl();

	explicit InvAclIteratorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_InvAclIterator, endpoint_){}

	InvAclIteratorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_InvAclIterator, objId_, endpoint_){}

	virtual Index skipDoc( const Index& p1);
};

class MetaDataReaderImpl
		:public RpcInterfaceStub
		,public strus::MetaDataReaderInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_hasElement,
		Method_elementHandle,
		Method_nofElements,
		Method_skipDoc,
		Method_getValue,
		Method_getType,
		Method_getName
	};

	virtual ~MetaDataReaderImpl();

	explicit MetaDataReaderImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_MetaDataReader, endpoint_){}

	MetaDataReaderImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_MetaDataReader, objId_, endpoint_){}

	virtual bool hasElement( const std::string& p1) const;
	virtual Index elementHandle( const std::string& p1) const;
	virtual Index nofElements( ) const;
	virtual void skipDoc( const Index& p1);
	virtual ArithmeticVariant getValue( const Index& p1) const;
	virtual const char* getType( const Index& p1) const;
	virtual const char* getName( const Index& p1) const;
};

class NormalizerConstructorImpl
		:public RpcInterfaceStub
		,public strus::NormalizerConstructorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_create
	};

	virtual ~NormalizerConstructorImpl();

	explicit NormalizerConstructorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerConstructor, endpoint_){}

	NormalizerConstructorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerConstructor, objId_, endpoint_){}

	virtual NormalizerInterface* create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const;
};

class NormalizerInstanceImpl
		:public RpcInterfaceStub
		,public strus::NormalizerInstanceInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_normalize
	};

	virtual ~NormalizerInstanceImpl();

	explicit NormalizerInstanceImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerInstance, endpoint_){}

	NormalizerInstanceImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_NormalizerInstance, objId_, endpoint_){}

	virtual std::string normalize( const char* p1, std::size_t p2);
};

class NormalizerImpl
		:public RpcInterfaceStub
		,public strus::NormalizerInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance
	};

	virtual ~NormalizerImpl();

	explicit NormalizerImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Normalizer, endpoint_){}

	NormalizerImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Normalizer, objId_, endpoint_){}

	virtual NormalizerInstanceInterface* createInstance( ) const;
};

class PeerStorageTransactionImpl
		:public RpcInterfaceStub
		,public strus::PeerStorageTransactionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_updateNofDocumentsInsertedChange,
		Method_updateDocumentFrequencyChange,
		Method_commit,
		Method_rollback
	};

	virtual ~PeerStorageTransactionImpl();

	explicit PeerStorageTransactionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PeerStorageTransaction, endpoint_){}

	PeerStorageTransactionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PeerStorageTransaction, objId_, endpoint_){}

	virtual void updateNofDocumentsInsertedChange( const GlobalCounter& p1);
	virtual void updateDocumentFrequencyChange( const char* p1, const char* p2, const GlobalCounter& p3);
	virtual void commit( );
	virtual void rollback( );
};

class PostingIteratorImpl
		:public RpcInterfaceStub
		,public strus::PostingIteratorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_skipPos,
		Method_featureid,
		Method_subExpressions,
		Method_documentFrequency,
		Method_frequency,
		Method_docno,
		Method_posno
	};

	virtual ~PostingIteratorImpl();

	explicit PostingIteratorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingIterator, endpoint_){}

	PostingIteratorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingIterator, objId_, endpoint_){}

	virtual Index skipDoc( const Index& p1);
	virtual Index skipPos( const Index& p1);
	virtual const char* featureid( ) const;
	virtual std::vector<const PostingIteratorInterface*> subExpressions( bool p1) const;
	virtual GlobalCounter documentFrequency( ) const;
	virtual unsigned int frequency( );
	virtual Index docno( ) const;
	virtual Index posno( ) const;
};

class PostingJoinOperatorImpl
		:public RpcInterfaceStub
		,public strus::PostingJoinOperatorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createResultIterator
	};

	virtual ~PostingJoinOperatorImpl();

	explicit PostingJoinOperatorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingJoinOperator, endpoint_){}

	PostingJoinOperatorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_PostingJoinOperator, objId_, endpoint_){}

	virtual PostingIteratorInterface* createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2) const;
};

class QueryAnalyzerImpl
		:public RpcInterfaceStub
		,public strus::QueryAnalyzerInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_definePhraseType,
		Method_analyzePhrase
	};

	virtual ~QueryAnalyzerImpl();

	explicit QueryAnalyzerImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryAnalyzer, endpoint_){}

	QueryAnalyzerImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryAnalyzer, objId_, endpoint_){}

	virtual void definePhraseType( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4);
	virtual std::vector<analyzer::Term> analyzePhrase( const std::string& p1, const std::string& p2) const;
};

class QueryEvalImpl
		:public RpcInterfaceStub
		,public strus::QueryEvalInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addTerm,
		Method_addSelectionFeature,
		Method_addRestrictionFeature,
		Method_addSummarizer,
		Method_addWeightingFunction,
		Method_createQuery
	};

	virtual ~QueryEvalImpl();

	explicit QueryEvalImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryEval, endpoint_){}

	QueryEvalImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryEval, objId_, endpoint_){}

	virtual void addTerm( const std::string& p1, const std::string& p2, const std::string& p3);
	virtual void addSelectionFeature( const std::string& p1);
	virtual void addRestrictionFeature( const std::string& p1);
	virtual void addSummarizer( const std::string& p1, const std::string& p2, const SummarizerConfig& p3);
	virtual void addWeightingFunction( const std::string& p1, const WeightingConfig& p2, const std::vector<std::string>& p3);
	virtual QueryInterface* createQuery( const StorageClientInterface* p1) const;
};

class QueryImpl
		:public RpcInterfaceStub
		,public strus::QueryInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_pushTerm,
		Method_pushExpression,
		Method_pushDuplicate,
		Method_attachVariable,
		Method_defineFeature,
		Method_defineMetaDataRestriction,
		Method_setMaxNofRanks,
		Method_setMinRank,
		Method_setUserName,
		Method_evaluate
	};

	virtual ~QueryImpl();

	explicit QueryImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Query, endpoint_){}

	QueryImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Query, objId_, endpoint_){}

	virtual void pushTerm( const std::string& p1, const std::string& p2);
	virtual void pushExpression( const std::string& p1, std::size_t p2, int p3);
	virtual void pushDuplicate( );
	virtual void attachVariable( const std::string& p1);
	virtual void defineFeature( const std::string& p1, float p2);
	virtual void defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4);
	virtual void setMaxNofRanks( std::size_t p1);
	virtual void setMinRank( std::size_t p1);
	virtual void setUserName( const std::string& p1);
	virtual std::vector<ResultDocument> evaluate( );
};

class QueryProcessorImpl
		:public RpcInterfaceStub
		,public strus::QueryProcessorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_definePostingJoinOperator,
		Method_getPostingJoinOperator,
		Method_defineWeightingFunction,
		Method_getWeightingFunction,
		Method_defineSummarizerFunction,
		Method_getSummarizerFunction
	};

	virtual ~QueryProcessorImpl();

	explicit QueryProcessorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryProcessor, endpoint_){}

	QueryProcessorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_QueryProcessor, objId_, endpoint_){}

	virtual void definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2);
	virtual const PostingJoinOperatorInterface* getPostingJoinOperator( const std::string& p1) const;
	virtual void defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2);
	virtual const WeightingFunctionInterface* getWeightingFunction( const std::string& p1) const;
	virtual void defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2);
	virtual const SummarizerFunctionInterface* getSummarizerFunction( const std::string& p1) const;
};

class SegmenterInstanceImpl
		:public RpcInterfaceStub
		,public strus::SegmenterInstanceInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putInput,
		Method_getNext
	};

	virtual ~SegmenterInstanceImpl();

	explicit SegmenterInstanceImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SegmenterInstance, endpoint_){}

	SegmenterInstanceImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SegmenterInstance, objId_, endpoint_){}

	virtual void putInput( const char* p1, std::size_t p2, bool p3);
	virtual bool getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4);
};

class SegmenterImpl
		:public RpcInterfaceStub
		,public strus::SegmenterInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineSelectorExpression,
		Method_defineSubSection,
		Method_createInstance
	};

	virtual ~SegmenterImpl();

	explicit SegmenterImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Segmenter, endpoint_){}

	SegmenterImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Segmenter, objId_, endpoint_){}

	virtual void defineSelectorExpression( int p1, const std::string& p2);
	virtual void defineSubSection( int p1, int p2, const std::string& p3);
	virtual SegmenterInstanceInterface* createInstance( ) const;
};

class StorageAlterMetaDataTableImpl
		:public RpcInterfaceStub
		,public strus::StorageAlterMetaDataTableInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addElement,
		Method_alterElement,
		Method_renameElement,
		Method_deleteElement,
		Method_clearElement,
		Method_commit,
		Method_rollback
	};

	virtual ~StorageAlterMetaDataTableImpl();

	explicit StorageAlterMetaDataTableImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageAlterMetaDataTable, endpoint_){}

	StorageAlterMetaDataTableImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageAlterMetaDataTable, objId_, endpoint_){}

	virtual void addElement( const std::string& p1, const std::string& p2);
	virtual void alterElement( const std::string& p1, const std::string& p2, const std::string& p3);
	virtual void renameElement( const std::string& p1, const std::string& p2);
	virtual void deleteElement( const std::string& p1);
	virtual void clearElement( const std::string& p1);
	virtual void commit( );
	virtual void rollback( );
};

class StorageClientImpl
		:public RpcInterfaceStub
		,public strus::StorageClientInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_close,
		Method_createTermPostingIterator,
		Method_createForwardIterator,
		Method_createInvAclIterator,
		Method_globalNofDocumentsInserted,
		Method_localNofDocumentsInserted,
		Method_globalDocumentFrequency,
		Method_localDocumentFrequency,
		Method_maxDocumentNumber,
		Method_documentNumber,
		Method_createMetaDataReader,
		Method_createAttributeReader,
		Method_createDocnoRangeAllocator,
		Method_createTransaction,
		Method_createPeerStorageTransaction,
		Method_defineStoragePeerInterface,
		Method_createDocumentChecker,
		Method_checkStorage,
		Method_createDump
	};

	virtual ~StorageClientImpl();

	explicit StorageClientImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageClient, endpoint_){}

	StorageClientImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageClient, objId_, endpoint_){}

	virtual void close( );
	virtual PostingIteratorInterface* createTermPostingIterator( const std::string& p1, const std::string& p2) const;
	virtual ForwardIteratorInterface* createForwardIterator( const std::string& p1) const;
	virtual InvAclIteratorInterface* createInvAclIterator( const std::string& p1) const;
	virtual GlobalCounter globalNofDocumentsInserted( ) const;
	virtual Index localNofDocumentsInserted( ) const;
	virtual GlobalCounter globalDocumentFrequency( const std::string& p1, const std::string& p2) const;
	virtual Index localDocumentFrequency( const std::string& p1, const std::string& p2) const;
	virtual Index maxDocumentNumber( ) const;
	virtual Index documentNumber( const std::string& p1) const;
	virtual MetaDataReaderInterface* createMetaDataReader( ) const;
	virtual AttributeReaderInterface* createAttributeReader( ) const;
	virtual DocnoRangeAllocatorInterface* createDocnoRangeAllocator( );
	virtual StorageTransactionInterface* createTransaction( );
	virtual PeerStorageTransactionInterface* createPeerStorageTransaction( );
	virtual void defineStoragePeerInterface( const StoragePeerInterface* p1, bool p2);
	virtual StorageDocumentInterface* createDocumentChecker( const std::string& p1, const std::string& p2) const;
	virtual void checkStorage( std::ostream& p1) const;
	virtual StorageDumpInterface* createDump( ) const;
};

class StorageDocumentImpl
		:public RpcInterfaceStub
		,public strus::StorageDocumentInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSearchIndexTerm,
		Method_addForwardIndexTerm,
		Method_setMetaData,
		Method_setAttribute,
		Method_setUserAccessRight,
		Method_done
	};

	virtual ~StorageDocumentImpl();

	explicit StorageDocumentImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDocument, endpoint_){}

	StorageDocumentImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDocument, objId_, endpoint_){}

	virtual void addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3);
	virtual void setMetaData( const std::string& p1, const ArithmeticVariant& p2);
	virtual void setAttribute( const std::string& p1, const std::string& p2);
	virtual void setUserAccessRight( const std::string& p1);
	virtual void done( );
};

class StorageDumpImpl
		:public RpcInterfaceStub
		,public strus::StorageDumpInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_nextChunk
	};

	virtual ~StorageDumpImpl();

	explicit StorageDumpImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDump, endpoint_){}

	StorageDumpImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageDump, objId_, endpoint_){}

	virtual bool nextChunk( const char*& p1, std::size_t& p2);
};

class StorageImpl
		:public RpcInterfaceStub
		,public strus::StorageInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createClient,
		Method_createStorage,
		Method_createAlterMetaDataTable,
		Method_getConfigDescription,
		Method_getConfigParameters
	};

	virtual ~StorageImpl();

	explicit StorageImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Storage, endpoint_){}

	StorageImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Storage, objId_, endpoint_){}

	virtual StorageClientInterface* createClient( const std::string& p1, DatabaseClientInterface* p2) const;
	virtual void createStorage( const std::string& p1, DatabaseClientInterface* p2) const;
	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable( DatabaseClientInterface* p1) const;
	virtual const char* getConfigDescription( StorageInterface::ConfigType p1) const;
	virtual const char** getConfigParameters( StorageInterface::ConfigType p1) const;
};

class StoragePeerImpl
		:public RpcInterfaceStub
		,public strus::StoragePeerInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createTransaction
	};

	virtual ~StoragePeerImpl();

	explicit StoragePeerImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StoragePeer, endpoint_){}

	StoragePeerImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StoragePeer, objId_, endpoint_){}

	virtual StoragePeerTransactionInterface* createTransaction( ) const;
};

class StoragePeerTransactionImpl
		:public RpcInterfaceStub
		,public strus::StoragePeerTransactionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_populateNofDocumentsInsertedChange,
		Method_populateDocumentFrequencyChange,
		Method_try_commit,
		Method_final_commit,
		Method_rollback
	};

	virtual ~StoragePeerTransactionImpl();

	explicit StoragePeerTransactionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StoragePeerTransaction, endpoint_){}

	StoragePeerTransactionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StoragePeerTransaction, objId_, endpoint_){}

	virtual void populateNofDocumentsInsertedChange( int p1);
	virtual void populateDocumentFrequencyChange( const char* p1, const char* p2, int p3, bool p4);
	virtual void try_commit( );
	virtual void final_commit( );
	virtual void rollback( );
};

class StorageTransactionImpl
		:public RpcInterfaceStub
		,public strus::StorageTransactionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createDocument,
		Method_deleteDocument,
		Method_deleteUserAccessRights,
		Method_commit,
		Method_rollback
	};

	virtual ~StorageTransactionImpl();

	explicit StorageTransactionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageTransaction, endpoint_){}

	StorageTransactionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_StorageTransaction, objId_, endpoint_){}

	virtual StorageDocumentInterface* createDocument( const std::string& p1, const Index& p2);
	virtual void deleteDocument( const std::string& p1);
	virtual void deleteUserAccessRights( const std::string& p1);
	virtual void commit( );
	virtual void rollback( );
};

class SummarizerClosureImpl
		:public RpcInterfaceStub
		,public strus::SummarizerClosureInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getSummary
	};

	virtual ~SummarizerClosureImpl();

	explicit SummarizerClosureImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerClosure, endpoint_){}

	SummarizerClosureImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerClosure, objId_, endpoint_){}

	virtual std::vector<SummarizerClosureInterface::SummaryElement> getSummary( const Index& p1);
};

class SummarizerFunctionImpl
		:public RpcInterfaceStub
		,public strus::SummarizerFunctionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_numericParameterNames,
		Method_textualParameterNames,
		Method_featureParameterClassNames,
		Method_createClosure
	};

	virtual ~SummarizerFunctionImpl();

	explicit SummarizerFunctionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerFunction, endpoint_){}

	SummarizerFunctionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_SummarizerFunction, objId_, endpoint_){}

	virtual const char** numericParameterNames( ) const;
	virtual const char** textualParameterNames( ) const;
	virtual const char** featureParameterClassNames( ) const;
	virtual SummarizerClosureInterface* createClosure( const StorageClientInterface* p1, const QueryProcessorInterface* p2, MetaDataReaderInterface* p3, const std::vector<SummarizerFunctionInterface::FeatureParameter>& p4, const std::vector<std::string>& p5, const std::vector<ArithmeticVariant>& p6) const;
};

class TextProcessorImpl
		:public RpcInterfaceStub
		,public strus::TextProcessorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addResourcePath,
		Method_getResourcePath,
		Method_getTokenizer,
		Method_getNormalizer,
		Method_defineTokenizer,
		Method_defineNormalizer
	};

	virtual ~TextProcessorImpl();

	explicit TextProcessorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TextProcessor, endpoint_){}

	TextProcessorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TextProcessor, objId_, endpoint_){}

	virtual void addResourcePath( const std::string& p1);
	virtual std::string getResourcePath( const std::string& p1) const;
	virtual const TokenizerConstructorInterface* getTokenizer( const std::string& p1) const;
	virtual const NormalizerConstructorInterface* getNormalizer( const std::string& p1) const;
	virtual void defineTokenizer( const std::string& p1, const TokenizerConstructorInterface* p2);
	virtual void defineNormalizer( const std::string& p1, const NormalizerConstructorInterface* p2);
};

class TokenizerConstructorImpl
		:public RpcInterfaceStub
		,public strus::TokenizerConstructorInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_create
	};

	virtual ~TokenizerConstructorImpl();

	explicit TokenizerConstructorImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerConstructor, endpoint_){}

	TokenizerConstructorImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerConstructor, objId_, endpoint_){}

	virtual TokenizerInterface* create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const;
};

class TokenizerInstanceImpl
		:public RpcInterfaceStub
		,public strus::TokenizerInstanceInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_tokenize
	};

	virtual ~TokenizerInstanceImpl();

	explicit TokenizerInstanceImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerInstance, endpoint_){}

	TokenizerInstanceImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_TokenizerInstance, objId_, endpoint_){}

	virtual std::vector<analyzer::Token> tokenize( const char* p1, std::size_t p2);
};

class TokenizerImpl
		:public RpcInterfaceStub
		,public strus::TokenizerInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_concatBeforeTokenize,
		Method_createInstance
	};

	virtual ~TokenizerImpl();

	explicit TokenizerImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Tokenizer, endpoint_){}

	TokenizerImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_Tokenizer, objId_, endpoint_){}

	virtual bool concatBeforeTokenize( ) const;
	virtual TokenizerInstanceInterface* createInstance( ) const;
};

class WeightingClosureImpl
		:public RpcInterfaceStub
		,public strus::WeightingClosureInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_call
	};

	virtual ~WeightingClosureImpl();

	explicit WeightingClosureImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingClosure, endpoint_){}

	WeightingClosureImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingClosure, objId_, endpoint_){}

	virtual float call( const Index& p1);
};

class WeightingFunctionImpl
		:public RpcInterfaceStub
		,public strus::WeightingFunctionInterface
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_numericParameterNames,
		Method_createClosure
	};

	virtual ~WeightingFunctionImpl();

	explicit WeightingFunctionImpl( const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingFunction, endpoint_){}

	WeightingFunctionImpl( unsigned int objId_, const RpcRemoteEndPoint* endpoint_)
		:RpcInterfaceStub( (unsigned char)ClassId_WeightingFunction, objId_, endpoint_){}

	virtual const char** numericParameterNames( ) const;
	virtual WeightingClosureInterface* createClosure( const StorageClientInterface* p1, PostingIteratorInterface* p2, MetaDataReaderInterface* p3, const std::vector<ArithmeticVariant>& p4) const;
};
} //namespace
#endif
