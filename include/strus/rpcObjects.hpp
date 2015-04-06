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

namespace strus {
namespace rpc {

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
	ClassId_Tokenizer,
	ClassId_WeightingClosure,
	ClassId_WeightingFunction
};

enum CallId
{
	CallId_AttributeReaderInterface_elementHandle = 101,
	CallId_AttributeReaderInterface_skipDoc = 102,
	CallId_AttributeReaderInterface_getValue = 103,
	CallId_DatabaseBackupCursorInterface_fetch = 201,
	CallId_DatabaseClientInterface_close = 301,
	CallId_DatabaseClientInterface_createTransaction = 302,
	CallId_DatabaseClientInterface_createCursor = 303,
	CallId_DatabaseClientInterface_createBackupCursor = 304,
	CallId_DatabaseClientInterface_writeImm = 305,
	CallId_DatabaseClientInterface_removeImm = 306,
	CallId_DatabaseClientInterface_readValue = 307,
	CallId_DatabaseCursorInterface_seekUpperBound = 401,
	CallId_DatabaseCursorInterface_seekFirst = 402,
	CallId_DatabaseCursorInterface_seekLast = 403,
	CallId_DatabaseCursorInterface_seekNext = 404,
	CallId_DatabaseCursorInterface_seekPrev = 405,
	CallId_DatabaseCursorInterface_key = 406,
	CallId_DatabaseCursorInterface_value = 407,
	CallId_DatabaseInterface_createClient = 501,
	CallId_DatabaseInterface_createDatabase = 502,
	CallId_DatabaseInterface_restoreDatabase = 503,
	CallId_DatabaseInterface_destroyDatabase = 504,
	CallId_DatabaseInterface_getConfigDescription = 505,
	CallId_DatabaseInterface_getConfigParameters = 506,
	CallId_DatabaseTransactionInterface_createCursor = 601,
	CallId_DatabaseTransactionInterface_write = 602,
	CallId_DatabaseTransactionInterface_remove = 603,
	CallId_DatabaseTransactionInterface_removeSubTree = 604,
	CallId_DatabaseTransactionInterface_commit = 605,
	CallId_DatabaseTransactionInterface_rollback = 606,
	CallId_DocnoRangeAllocatorInterface_allocDocnoRange = 701,
	CallId_DocnoRangeAllocatorInterface_deallocDocnoRange = 702,
	CallId_DocumentAnalyzerInstanceInterface_putInput = 801,
	CallId_DocumentAnalyzerInstanceInterface_analyzeNext = 802,
	CallId_DocumentAnalyzerInterface_addSearchIndexFeature = 901,
	CallId_DocumentAnalyzerInterface_addForwardIndexFeature = 902,
	CallId_DocumentAnalyzerInterface_defineMetaData = 903,
	CallId_DocumentAnalyzerInterface_defineAttribute = 904,
	CallId_DocumentAnalyzerInterface_defineSubDocument = 905,
	CallId_DocumentAnalyzerInterface_analyze = 906,
	CallId_DocumentAnalyzerInterface_createInstance = 907,
	CallId_ForwardIteratorInterface_skipDoc = 1001,
	CallId_ForwardIteratorInterface_skipPos = 1002,
	CallId_ForwardIteratorInterface_fetch = 1003,
	CallId_InvAclIteratorInterface_skipDoc = 1101,
	CallId_MetaDataReaderInterface_hasElement = 1201,
	CallId_MetaDataReaderInterface_elementHandle = 1202,
	CallId_MetaDataReaderInterface_nofElements = 1203,
	CallId_MetaDataReaderInterface_skipDoc = 1204,
	CallId_MetaDataReaderInterface_getValue = 1205,
	CallId_MetaDataReaderInterface_getType = 1206,
	CallId_MetaDataReaderInterface_getName = 1207,
	CallId_NormalizerInterface_createArgument = 1301,
	CallId_NormalizerInterface_createContext = 1302,
	CallId_NormalizerInterface_normalize = 1303,
	CallId_PeerStorageTransactionInterface_updateNofDocumentsInsertedChange = 1401,
	CallId_PeerStorageTransactionInterface_updateDocumentFrequencyChange = 1402,
	CallId_PeerStorageTransactionInterface_commit = 1403,
	CallId_PeerStorageTransactionInterface_rollback = 1404,
	CallId_PostingIteratorInterface_skipDoc = 1501,
	CallId_PostingIteratorInterface_skipPos = 1502,
	CallId_PostingIteratorInterface_featureid = 1503,
	CallId_PostingIteratorInterface_subExpressions = 1504,
	CallId_PostingIteratorInterface_documentFrequency = 1505,
	CallId_PostingIteratorInterface_frequency = 1506,
	CallId_PostingIteratorInterface_docno = 1507,
	CallId_PostingIteratorInterface_posno = 1508,
	CallId_PostingJoinOperatorInterface_createResultIterator = 1601,
	CallId_QueryAnalyzerInterface_definePhraseType = 1701,
	CallId_QueryAnalyzerInterface_analyzePhrase = 1702,
	CallId_QueryEvalInterface_addTerm = 1801,
	CallId_QueryEvalInterface_addSelectionFeature = 1802,
	CallId_QueryEvalInterface_addRestrictionFeature = 1803,
	CallId_QueryEvalInterface_addSummarizer = 1804,
	CallId_QueryEvalInterface_addWeightingFunction = 1805,
	CallId_QueryEvalInterface_createQuery = 1806,
	CallId_QueryInterface_pushTerm = 1901,
	CallId_QueryInterface_pushExpression = 1902,
	CallId_QueryInterface_pushDuplicate = 1903,
	CallId_QueryInterface_attachVariable = 1904,
	CallId_QueryInterface_defineFeature = 1905,
	CallId_QueryInterface_defineMetaDataRestriction = 1906,
	CallId_QueryInterface_setMaxNofRanks = 1907,
	CallId_QueryInterface_setMinRank = 1908,
	CallId_QueryInterface_setUserName = 1909,
	CallId_QueryInterface_evaluate = 1910,
	CallId_QueryProcessorInterface_definePostingJoinOperator = 2001,
	CallId_QueryProcessorInterface_getPostingJoinOperator = 2002,
	CallId_QueryProcessorInterface_defineWeightingFunction = 2003,
	CallId_QueryProcessorInterface_getWeightingFunction = 2004,
	CallId_QueryProcessorInterface_defineSummarizerFunction = 2005,
	CallId_QueryProcessorInterface_getSummarizerFunction = 2006,
	CallId_SegmenterInstanceInterface_putInput = 2101,
	CallId_SegmenterInstanceInterface_getNext = 2102,
	CallId_SegmenterInterface_defineSelectorExpression = 2201,
	CallId_SegmenterInterface_defineSubSection = 2202,
	CallId_SegmenterInterface_createInstance = 2203,
	CallId_StorageAlterMetaDataTableInterface_addElement = 2301,
	CallId_StorageAlterMetaDataTableInterface_alterElement = 2302,
	CallId_StorageAlterMetaDataTableInterface_renameElement = 2303,
	CallId_StorageAlterMetaDataTableInterface_deleteElement = 2304,
	CallId_StorageAlterMetaDataTableInterface_clearElement = 2305,
	CallId_StorageAlterMetaDataTableInterface_commit = 2306,
	CallId_StorageAlterMetaDataTableInterface_rollback = 2307,
	CallId_StorageClientInterface_close = 2401,
	CallId_StorageClientInterface_createTermPostingIterator = 2402,
	CallId_StorageClientInterface_createForwardIterator = 2403,
	CallId_StorageClientInterface_createInvAclIterator = 2404,
	CallId_StorageClientInterface_globalNofDocumentsInserted = 2405,
	CallId_StorageClientInterface_localNofDocumentsInserted = 2406,
	CallId_StorageClientInterface_globalDocumentFrequency = 2407,
	CallId_StorageClientInterface_localDocumentFrequency = 2408,
	CallId_StorageClientInterface_maxDocumentNumber = 2409,
	CallId_StorageClientInterface_documentNumber = 2410,
	CallId_StorageClientInterface_createMetaDataReader = 2411,
	CallId_StorageClientInterface_createAttributeReader = 2412,
	CallId_StorageClientInterface_createDocnoRangeAllocator = 2413,
	CallId_StorageClientInterface_createTransaction = 2414,
	CallId_StorageClientInterface_createPeerStorageTransaction = 2415,
	CallId_StorageClientInterface_defineStoragePeerInterface = 2416,
	CallId_StorageClientInterface_createDocumentChecker = 2417,
	CallId_StorageClientInterface_checkStorage = 2418,
	CallId_StorageClientInterface_createDump = 2419,
	CallId_StorageDocumentInterface_addSearchIndexTerm = 2501,
	CallId_StorageDocumentInterface_addForwardIndexTerm = 2502,
	CallId_StorageDocumentInterface_setMetaData = 2503,
	CallId_StorageDocumentInterface_setAttribute = 2504,
	CallId_StorageDocumentInterface_setUserAccessRight = 2505,
	CallId_StorageDocumentInterface_done = 2506,
	CallId_StorageDumpInterface_nextChunk = 2601,
	CallId_StorageInterface_createClient = 2701,
	CallId_StorageInterface_createStorage = 2702,
	CallId_StorageInterface_createAlterMetaDataTable = 2703,
	CallId_StorageInterface_getConfigDescription = 2704,
	CallId_StorageInterface_getConfigParameters = 2705,
	CallId_StoragePeerInterface_createTransaction = 2801,
	CallId_StoragePeerTransactionInterface_populateNofDocumentsInsertedChange = 2901,
	CallId_StoragePeerTransactionInterface_populateDocumentFrequencyChange = 2902,
	CallId_StoragePeerTransactionInterface_try_commit = 2903,
	CallId_StoragePeerTransactionInterface_final_commit = 2904,
	CallId_StoragePeerTransactionInterface_rollback = 2905,
	CallId_StorageTransactionInterface_createDocument = 3001,
	CallId_StorageTransactionInterface_deleteDocument = 3002,
	CallId_StorageTransactionInterface_deleteUserAccessRights = 3003,
	CallId_StorageTransactionInterface_commit = 3004,
	CallId_StorageTransactionInterface_rollback = 3005,
	CallId_SummarizerClosureInterface_getSummary = 3101,
	CallId_SummarizerFunctionInterface_numericParameterNames = 3201,
	CallId_SummarizerFunctionInterface_textualParameterNames = 3202,
	CallId_SummarizerFunctionInterface_featureParameterClassNames = 3203,
	CallId_SummarizerFunctionInterface_createClosure = 3204,
	CallId_TextProcessorInterface_addResourcePath = 3301,
	CallId_TextProcessorInterface_getResourcePath = 3302,
	CallId_TextProcessorInterface_getTokenizer = 3303,
	CallId_TextProcessorInterface_getNormalizer = 3304,
	CallId_TextProcessorInterface_defineTokenizer = 3305,
	CallId_TextProcessorInterface_defineNormalizer = 3306,
	CallId_TokenizerInterface_createArgument = 3401,
	CallId_TokenizerInterface_createContext = 3402,
	CallId_TokenizerInterface_concatBeforeTokenize = 3403,
	CallId_TokenizerInterface_tokenize = 3404,
	CallId_WeightingClosureInterface_call = 3501,
	CallId_WeightingFunctionInterface_numericParameterNames = 3601,
	CallId_WeightingFunctionInterface_createClosure = 3602
};

class AttributeReaderImpl
		:public RcpInterfaceStub
		,public strus:AttributeReaderInterface
{
public:
	virtual ~AttributeReaderImpl(){}

	AttributeReaderImpl()
	:RcpInterfaceStub(ClassId_AttributeReader){}

	virtual Index elementHandle(const char* p0) const;
	virtual void skipDoc(const Index& p0);
	virtual std::string getValue(const Index& p0) const;
};

class DatabaseBackupCursorImpl
		:public RcpInterfaceStub
		,public strus:DatabaseBackupCursorInterface
{
public:
	virtual ~DatabaseBackupCursorImpl(){}

	DatabaseBackupCursorImpl()
	:RcpInterfaceStub(ClassId_DatabaseBackupCursor){}

	virtual bool fetch(const char*& p0, std::size_t& p0, const char*& p0, std::size_t& p0);
};

class DatabaseClientImpl
		:public RcpInterfaceStub
		,public strus:DatabaseClientInterface
{
public:
	virtual ~DatabaseClientImpl(){}

	DatabaseClientImpl()
	:RcpInterfaceStub(ClassId_DatabaseClient){}

	virtual void close();
	virtual DatabaseTransactionInterface* createTransaction();
	virtual DatabaseCursorInterface* createCursor(const DatabaseOptions& p0) const;
	virtual DatabaseBackupCursorInterface* createBackupCursor() const;
	virtual void writeImm(const char* p0, std::size_t p0, const char* p0, std::size_t p0);
	virtual void removeImm(const char* p0, std::size_t p0);
	virtual bool readValue(const char* p0, std::size_t p0, std::string& p0, const DatabaseOptions& p0) const;
};

class DatabaseCursorImpl
		:public RcpInterfaceStub
		,public strus:DatabaseCursorInterface
{
public:
	virtual ~DatabaseCursorImpl(){}

	DatabaseCursorImpl()
	:RcpInterfaceStub(ClassId_DatabaseCursor){}

	virtual Slice seekUpperBound(const char* p0, std::size_t p0, std::size_t p0);
	virtual Slice seekFirst(const char* p0, std::size_t p0);
	virtual Slice seekLast(const char* p0, std::size_t p0);
	virtual Slice seekNext();
	virtual Slice seekPrev();
	virtual Slice key() const;
	virtual Slice value() const;
};

class DatabaseImpl
		:public RcpInterfaceStub
		,public strus:DatabaseInterface
{
public:
	virtual ~DatabaseImpl(){}

	DatabaseImpl()
	:RcpInterfaceStub(ClassId_Database){}

	virtual DatabaseClientInterface* createClient(const std::string& p0) const;
	virtual void createDatabase(const std::string& p0) const;
	virtual void restoreDatabase(const std::string& p0, DatabaseBackupCursorInterface* p0) const;
	virtual void destroyDatabase(const std::string& p0) const;
	virtual const char* getConfigDescription(ConfigType p0) const;
	virtual const char** getConfigParameters(ConfigType p0) const;
};

class DatabaseTransactionImpl
		:public RcpInterfaceStub
		,public strus:DatabaseTransactionInterface
{
public:
	virtual ~DatabaseTransactionImpl(){}

	DatabaseTransactionImpl()
	:RcpInterfaceStub(ClassId_DatabaseTransaction){}

	virtual DatabaseCursorInterface* createCursor(const DatabaseOptions& p0) const;
	virtual void write(const char* p0, std::size_t p0, const char* p0, std::size_t p0);
	virtual void remove(const char* p0, std::size_t p0);
	virtual void removeSubTree(const char* p0, std::size_t p0);
	virtual void commit();
	virtual void rollback();
};

class DocnoRangeAllocatorImpl
		:public RcpInterfaceStub
		,public strus:DocnoRangeAllocatorInterface
{
public:
	virtual ~DocnoRangeAllocatorImpl(){}

	DocnoRangeAllocatorImpl()
	:RcpInterfaceStub(ClassId_DocnoRangeAllocator){}

	virtual Index allocDocnoRange(const Index& p0);
	virtual bool deallocDocnoRange(const Index& p0, const Index& p0);
};

class DocumentAnalyzerInstanceImpl
		:public RcpInterfaceStub
		,public strus:DocumentAnalyzerInstanceInterface
{
public:
	virtual ~DocumentAnalyzerInstanceImpl(){}

	DocumentAnalyzerInstanceImpl()
	:RcpInterfaceStub(ClassId_DocumentAnalyzerInstance){}

	virtual void putInput(const char* p0, std::size_t p0, bool p0);
	virtual bool analyzeNext(analyzer::Document& p0);
};

class DocumentAnalyzerImpl
		:public RcpInterfaceStub
		,public strus:DocumentAnalyzerInterface
{
public:
	virtual ~DocumentAnalyzerImpl(){}

	DocumentAnalyzerImpl()
	:RcpInterfaceStub(ClassId_DocumentAnalyzer){}

	virtual void addSearchIndexFeature(const std::string& p0, const std::string& p0, const TokenizerConfig& p0, const std::vector<NormalizerConfig>& p0, const FeatureOptions& p0);
	virtual void addForwardIndexFeature(const std::string& p0, const std::string& p0, const TokenizerConfig& p0, const std::vector<NormalizerConfig>& p0, const FeatureOptions& p0);
	virtual void defineMetaData(const std::string& p0, const std::string& p0, const TokenizerConfig& p0, const std::vector<NormalizerConfig>& p0);
	virtual void defineAttribute(const std::string& p0, const std::string& p0, const TokenizerConfig& p0, const std::vector<NormalizerConfig>& p0);
	virtual void defineSubDocument(const std::string& p0, const std::string& p0);
	virtual analyzer::Document analyze(const std::string& p0) const;
	virtual DocumentAnalyzerInstanceInterface* createInstance() const;
};

class ForwardIteratorImpl
		:public RcpInterfaceStub
		,public strus:ForwardIteratorInterface
{
public:
	virtual ~ForwardIteratorImpl(){}

	ForwardIteratorImpl()
	:RcpInterfaceStub(ClassId_ForwardIterator){}

	virtual void skipDoc(const Index& p0);
	virtual Index skipPos(const Index& p0);
	virtual std::string fetch();
};

class InvAclIteratorImpl
		:public RcpInterfaceStub
		,public strus:InvAclIteratorInterface
{
public:
	virtual ~InvAclIteratorImpl(){}

	InvAclIteratorImpl()
	:RcpInterfaceStub(ClassId_InvAclIterator){}

	virtual Index skipDoc(const Index& p0);
};

class MetaDataReaderImpl
		:public RcpInterfaceStub
		,public strus:MetaDataReaderInterface
{
public:
	virtual ~MetaDataReaderImpl(){}

	MetaDataReaderImpl()
	:RcpInterfaceStub(ClassId_MetaDataReader){}

	virtual bool hasElement(const std::string& p0) const;
	virtual Index elementHandle(const std::string& p0) const;
	virtual Index nofElements() const;
	virtual void skipDoc(const Index& p0);
	virtual ArithmeticVariant getValue(const Index& p0) const;
	virtual const char* getType(const Index& p0) const;
	virtual const char* getName(const Index& p0) const;
};

class NormalizerImpl
		:public RcpInterfaceStub
		,public strus:NormalizerInterface
{
public:
	virtual ~NormalizerImpl(){}

	NormalizerImpl()
	:RcpInterfaceStub(ClassId_Normalizer){}

	virtual Argument* createArgument(const TextProcessorInterface* p0, const std::vector<std::string>& p0) const;
	virtual Context* createContext(const Argument* p0) const;
	virtual std::string normalize(Context* p0, const char* p0, std::size_t p0) const;
};

class PeerStorageTransactionImpl
		:public RcpInterfaceStub
		,public strus:PeerStorageTransactionInterface
{
public:
	virtual ~PeerStorageTransactionImpl(){}

	PeerStorageTransactionImpl()
	:RcpInterfaceStub(ClassId_PeerStorageTransaction){}

	virtual void updateNofDocumentsInsertedChange(const GlobalCounter& p0);
	virtual void updateDocumentFrequencyChange(const char* p0, const char* p0, const GlobalCounter& p0);
	virtual void commit();
	virtual void rollback();
};

class PostingIteratorImpl
		:public RcpInterfaceStub
		,public strus:PostingIteratorInterface
{
public:
	virtual ~PostingIteratorImpl(){}

	PostingIteratorImpl()
	:RcpInterfaceStub(ClassId_PostingIterator){}

	virtual Index skipDoc(const Index& p0);
	virtual Index skipPos(const Index& p0);
	virtual const char* featureid() const;
	virtual const std::vector<PostingIteratorInterface<*> > subExpressions(bool p0) const;
	virtual GlobalCounter documentFrequency() const;
	virtual unsigned<int>  frequency();
	virtual Index docno() const;
	virtual Index posno() const;
};

class PostingJoinOperatorImpl
		:public RcpInterfaceStub
		,public strus:PostingJoinOperatorInterface
{
public:
	virtual ~PostingJoinOperatorImpl(){}

	PostingJoinOperatorImpl()
	:RcpInterfaceStub(ClassId_PostingJoinOperator){}

	virtual PostingIteratorInterface* createResultIterator(const std::vector<Reference<PostingIteratorInterface> >& p0, int p0) const;
};

class QueryAnalyzerImpl
		:public RcpInterfaceStub
		,public strus:QueryAnalyzerInterface
{
public:
	virtual ~QueryAnalyzerImpl(){}

	QueryAnalyzerImpl()
	:RcpInterfaceStub(ClassId_QueryAnalyzer){}

	virtual void definePhraseType(const std::string& p0, const std::string& p0, const TokenizerConfig& p0, const std::vector<NormalizerConfig>& p0);
	virtual std::vector<analyzer::Term> analyzePhrase(const std::string& p0, const std::string& p0) const;
};

class QueryEvalImpl
		:public RcpInterfaceStub
		,public strus:QueryEvalInterface
{
public:
	virtual ~QueryEvalImpl(){}

	QueryEvalImpl()
	:RcpInterfaceStub(ClassId_QueryEval){}

	virtual void addTerm(const std::string& p0, const std::string& p0, const std::string& p0);
	virtual void addSelectionFeature(const std::string& p0);
	virtual void addRestrictionFeature(const std::string& p0);
	virtual void addSummarizer(const std::string& p0, const std::string& p0, const SummarizerConfig& p0);
	virtual void addWeightingFunction(const std::string& p0, const WeightingConfig& p0, const std::vector<std::string>& p0);
	virtual QueryInterface* createQuery(const StorageClientInterface* p0) const;
};

class QueryImpl
		:public RcpInterfaceStub
		,public strus:QueryInterface
{
public:
	virtual ~QueryImpl(){}

	QueryImpl()
	:RcpInterfaceStub(ClassId_Query){}

	virtual void pushTerm(const std::string& p0, const std::string& p0);
	virtual void pushExpression(const std::string& p0, std::size_t p0, int p0);
	virtual void pushDuplicate();
	virtual void attachVariable(const std::string& p0);
	virtual void defineFeature(const std::string& p0, float p0);
	virtual void defineMetaDataRestriction(CompareOperator p0, const std::string& p0, const ArithmeticVariant& p0, bool p0);
	virtual void setMaxNofRanks(std::size_t p0);
	virtual void setMinRank(std::size_t p0);
	virtual void setUserName(const std::string& p0);
	virtual std::vector<ResultDocument> evaluate();
};

class QueryProcessorImpl
		:public RcpInterfaceStub
		,public strus:QueryProcessorInterface
{
public:
	virtual ~QueryProcessorImpl(){}

	QueryProcessorImpl()
	:RcpInterfaceStub(ClassId_QueryProcessor){}

	virtual void definePostingJoinOperator(const std::string& p0, PostingJoinOperatorInterface* p0);
	virtual const PostingJoinOperatorInterface* getPostingJoinOperator(const std::string& p0) const;
	virtual void defineWeightingFunction(const std::string& p0, WeightingFunctionInterface* p0);
	virtual const WeightingFunctionInterface* getWeightingFunction(const std::string& p0) const;
	virtual void defineSummarizerFunction(const std::string& p0, SummarizerFunctionInterface* p0);
	virtual const SummarizerFunctionInterface* getSummarizerFunction(const std::string& p0) const;
};

class SegmenterInstanceImpl
		:public RcpInterfaceStub
		,public strus:SegmenterInstanceInterface
{
public:
	virtual ~SegmenterInstanceImpl(){}

	SegmenterInstanceImpl()
	:RcpInterfaceStub(ClassId_SegmenterInstance){}

	virtual void putInput(const char* p0, std::size_t p0, bool p0);
	virtual bool getNext(int& p0, SegmenterPosition& p0, const char*& p0, std::size_t& p0);
};

class SegmenterImpl
		:public RcpInterfaceStub
		,public strus:SegmenterInterface
{
public:
	virtual ~SegmenterImpl(){}

	SegmenterImpl()
	:RcpInterfaceStub(ClassId_Segmenter){}

	virtual void defineSelectorExpression(int p0, const std::string& p0);
	virtual void defineSubSection(int p0, int p0, const std::string& p0);
	virtual SegmenterInstanceInterface* createInstance() const;
};

class StorageAlterMetaDataTableImpl
		:public RcpInterfaceStub
		,public strus:StorageAlterMetaDataTableInterface
{
public:
	virtual ~StorageAlterMetaDataTableImpl(){}

	StorageAlterMetaDataTableImpl()
	:RcpInterfaceStub(ClassId_StorageAlterMetaDataTable){}

	virtual void addElement(const std::string& p0, const std::string& p0);
	virtual void alterElement(const std::string& p0, const std::string& p0, const std::string& p0);
	virtual void renameElement(const std::string& p0, const std::string& p0);
	virtual void deleteElement(const std::string& p0);
	virtual void clearElement(const std::string& p0);
	virtual void commit();
	virtual void rollback();
};

class StorageClientImpl
		:public RcpInterfaceStub
		,public strus:StorageClientInterface
{
public:
	virtual ~StorageClientImpl(){}

	StorageClientImpl()
	:RcpInterfaceStub(ClassId_StorageClient){}

	virtual void close();
	virtual PostingIteratorInterface* createTermPostingIterator(const std::string& p0, const std::string& p0) const;
	virtual ForwardIteratorInterface* createForwardIterator(const std::string& p0) const;
	virtual InvAclIteratorInterface* createInvAclIterator(const std::string& p0) const;
	virtual GlobalCounter globalNofDocumentsInserted() const;
	virtual Index localNofDocumentsInserted() const;
	virtual GlobalCounter globalDocumentFrequency(const std::string& p0, const std::string& p0) const;
	virtual Index localDocumentFrequency(const std::string& p0, const std::string& p0) const;
	virtual Index maxDocumentNumber() const;
	virtual Index documentNumber(const std::string& p0) const;
	virtual MetaDataReaderInterface* createMetaDataReader() const;
	virtual AttributeReaderInterface* createAttributeReader() const;
	virtual DocnoRangeAllocatorInterface* createDocnoRangeAllocator();
	virtual StorageTransactionInterface* createTransaction();
	virtual PeerStorageTransactionInterface* createPeerStorageTransaction();
	virtual void defineStoragePeerInterface(const StoragePeerInterface* p0, bool p0);
	virtual StorageDocumentInterface* createDocumentChecker(const std::string& p0, const std::string& p0) const;
	virtual void checkStorage() const;
	virtual StorageDumpInterface* createDump() const;
};

class StorageDocumentImpl
		:public RcpInterfaceStub
		,public strus:StorageDocumentInterface
{
public:
	virtual ~StorageDocumentImpl(){}

	StorageDocumentImpl()
	:RcpInterfaceStub(ClassId_StorageDocument){}

	virtual void addSearchIndexTerm(const std::string& p0, const std::string& p0, const Index& p0);
	virtual void addForwardIndexTerm(const std::string& p0, const std::string& p0, const Index& p0);
	virtual void setMetaData(const std::string& p0, const ArithmeticVariant& p0);
	virtual void setAttribute(const std::string& p0, const std::string& p0);
	virtual void setUserAccessRight(const std::string& p0);
	virtual void done();
};

class StorageDumpImpl
		:public RcpInterfaceStub
		,public strus:StorageDumpInterface
{
public:
	virtual ~StorageDumpImpl(){}

	StorageDumpImpl()
	:RcpInterfaceStub(ClassId_StorageDump){}

	virtual bool nextChunk(const char*& p0, std::size_t& p0);
};

class StorageImpl
		:public RcpInterfaceStub
		,public strus:StorageInterface
{
public:
	virtual ~StorageImpl(){}

	StorageImpl()
	:RcpInterfaceStub(ClassId_Storage){}

	virtual StorageClientInterface* createClient(const std::string& p0, DatabaseClientInterface* p0) const;
	virtual void createStorage(const std::string& p0, DatabaseClientInterface* p0) const;
	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable(DatabaseClientInterface* p0) const;
	virtual const char* getConfigDescription(ConfigType p0) const;
	virtual const char** getConfigParameters(ConfigType p0) const;
};

class StoragePeerImpl
		:public RcpInterfaceStub
		,public strus:StoragePeerInterface
{
public:
	virtual ~StoragePeerImpl(){}

	StoragePeerImpl()
	:RcpInterfaceStub(ClassId_StoragePeer){}

	virtual StoragePeerTransactionInterface* createTransaction() const;
};

class StoragePeerTransactionImpl
		:public RcpInterfaceStub
		,public strus:StoragePeerTransactionInterface
{
public:
	virtual ~StoragePeerTransactionImpl(){}

	StoragePeerTransactionImpl()
	:RcpInterfaceStub(ClassId_StoragePeerTransaction){}

	virtual void populateNofDocumentsInsertedChange(int p0);
	virtual void populateDocumentFrequencyChange(const char* p0, const char* p0, int p0, bool p0);
	virtual void try_commit();
	virtual void final_commit();
	virtual void rollback();
};

class StorageTransactionImpl
		:public RcpInterfaceStub
		,public strus:StorageTransactionInterface
{
public:
	virtual ~StorageTransactionImpl(){}

	StorageTransactionImpl()
	:RcpInterfaceStub(ClassId_StorageTransaction){}

	virtual StorageDocumentInterface* createDocument(const std::string& p0, const Index& p0);
	virtual void deleteDocument(const std::string& p0);
	virtual void deleteUserAccessRights(const std::string& p0);
	virtual void commit();
	virtual void rollback();
};

class SummarizerClosureImpl
		:public RcpInterfaceStub
		,public strus:SummarizerClosureInterface
{
public:
	virtual ~SummarizerClosureImpl(){}

	SummarizerClosureImpl()
	:RcpInterfaceStub(ClassId_SummarizerClosure){}

	virtual std::vector<SummaryElement> getSummary(const Index& p0);
};

class SummarizerFunctionImpl
		:public RcpInterfaceStub
		,public strus:SummarizerFunctionInterface
{
public:
	virtual ~SummarizerFunctionImpl(){}

	SummarizerFunctionImpl()
	:RcpInterfaceStub(ClassId_SummarizerFunction){}

	virtual const char** numericParameterNames() const;
	virtual const char** textualParameterNames() const;
	virtual const char** featureParameterClassNames() const;
	virtual SummarizerClosureInterface* createClosure(const StorageClientInterface* p0, const QueryProcessorInterface* p0, MetaDataReaderInterface* p0, const std::vector<FeatureParameter>& p0, const std::vector<std::string>& p0, const std::vector<ArithmeticVariant>& p0) const;
};

class TextProcessorImpl
		:public RcpInterfaceStub
		,public strus:TextProcessorInterface
{
public:
	virtual ~TextProcessorImpl(){}

	TextProcessorImpl()
	:RcpInterfaceStub(ClassId_TextProcessor){}

	virtual void addResourcePath(const std::string& p0);
	virtual std::string getResourcePath(const std::string& p0) const;
	virtual const TokenizerInterface* getTokenizer(const std::string& p0) const;
	virtual const NormalizerInterface* getNormalizer(const std::string& p0) const;
	virtual void defineTokenizer(const std::string& p0, const TokenizerInterface* p0);
	virtual void defineNormalizer(const std::string& p0, const NormalizerInterface* p0);
};

class TokenizerImpl
		:public RcpInterfaceStub
		,public strus:TokenizerInterface
{
public:
	virtual ~TokenizerImpl(){}

	TokenizerImpl()
	:RcpInterfaceStub(ClassId_Tokenizer){}

	virtual Argument* createArgument(const std::vector<std::string>& p0) const;
	virtual Context* createContext(const Argument* p0) const;
	virtual bool concatBeforeTokenize() const;
	virtual std::vector<analyzer::Token> tokenize(Context* p0, const char* p0, std::size_t p0) const;
};

class WeightingClosureImpl
		:public RcpInterfaceStub
		,public strus:WeightingClosureInterface
{
public:
	virtual ~WeightingClosureImpl(){}

	WeightingClosureImpl()
	:RcpInterfaceStub(ClassId_WeightingClosure){}

	virtual float call(const Index& p0);
};

class WeightingFunctionImpl
		:public RcpInterfaceStub
		,public strus:WeightingFunctionInterface
{
public:
	virtual ~WeightingFunctionImpl(){}

	WeightingFunctionImpl()
	:RcpInterfaceStub(ClassId_WeightingFunction){}

	virtual const char** numericParameterNames() const;
	virtual WeightingClosureInterface* createClosure(const StorageClientInterface* p0, PostingIteratorInterface* p0, MetaDataReaderInterface* p0, const std::vector<ArithmeticVariant>& p0) const;
};

};
}} //namespace
#endif
