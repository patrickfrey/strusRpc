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
#ifndef _STRUS_RPC_OBJECT_IDS_HPP_INCLUDED
#define _STRUS_RPC_OBJECT_IDS_HPP_INCLUDED

namespace strus {

enum ClassId
{
	ClassId_AggregatorFunctionInstance,
	ClassId_AggregatorFunction,
	ClassId_AnalyzerObjectBuilder,
	ClassId_AttributeReader,
	ClassId_DatabaseBackupCursor,
	ClassId_DatabaseClient,
	ClassId_DatabaseCursor,
	ClassId_Database,
	ClassId_DatabaseTransaction,
	ClassId_DocumentAnalyzerContext,
	ClassId_DocumentAnalyzer,
	ClassId_DocumentClassDetector,
	ClassId_ForwardIterator,
	ClassId_InvAclIterator,
	ClassId_MetaDataReader,
	ClassId_NormalizerFunctionContext,
	ClassId_NormalizerFunctionInstance,
	ClassId_NormalizerFunction,
	ClassId_PostingIterator,
	ClassId_PostingJoinOperator,
	ClassId_QueryAnalyzer,
	ClassId_QueryEval,
	ClassId_Query,
	ClassId_QueryProcessor,
	ClassId_SegmenterContext,
	ClassId_SegmenterInstance,
	ClassId_Segmenter,
	ClassId_StatisticsBuilder,
	ClassId_StatisticsIterator,
	ClassId_StatisticsProcessor,
	ClassId_StatisticsViewer,
	ClassId_StorageAlterMetaDataTable,
	ClassId_StorageClient,
	ClassId_StorageDocument,
	ClassId_StorageDocumentUpdate,
	ClassId_StorageDump,
	ClassId_Storage,
	ClassId_StorageObjectBuilder,
	ClassId_StorageTransaction,
	ClassId_SummarizerFunctionContext,
	ClassId_SummarizerFunctionInstance,
	ClassId_SummarizerFunction,
	ClassId_TextProcessor,
	ClassId_TokenizerFunctionContext,
	ClassId_TokenizerFunctionInstance,
	ClassId_TokenizerFunction,
	ClassId_ValueIterator,
	ClassId_WeightingFunctionContext,
	ClassId_WeightingFunctionInstance,
	ClassId_WeightingFunction
};

class AggregatorFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_evaluate
	};
};

class AggregatorFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_getDescription
	};
};

class AnalyzerObjectBuilderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getTextProcessor,
		Method_createSegmenter,
		Method_createDocumentAnalyzer,
		Method_createQueryAnalyzer
	};
};

class AttributeReaderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_elementHandle,
		Method_skipDoc,
		Method_getValue,
		Method_getAttributeNames
	};
};

class DatabaseBackupCursorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_fetch
	};
};

class DatabaseClientConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createTransaction,
		Method_createCursor,
		Method_createBackupCursor,
		Method_writeImm,
		Method_removeImm,
		Method_readValue
	};
};

class DatabaseCursorConst
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
};

class DatabaseConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_exists,
		Method_createClient,
		Method_createDatabase,
		Method_restoreDatabase,
		Method_destroyDatabase,
		Method_getConfigDescription,
		Method_getConfigParameters
	};
};

class DatabaseTransactionConst
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
};

class DocumentAnalyzerContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putInput,
		Method_analyzeNext
	};
};

class DocumentAnalyzerConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSearchIndexFeature,
		Method_addForwardIndexFeature,
		Method_defineMetaData,
		Method_defineAggregatedMetaData,
		Method_defineAttribute,
		Method_defineSubDocument,
		Method_analyze,
		Method_createContext
	};
};

class DocumentClassDetectorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_detect
	};
};

class ForwardIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_skipPos,
		Method_fetch
	};
};

class InvAclIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc
	};
};

class MetaDataReaderConst
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
};

class NormalizerFunctionContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_normalize
	};
};

class NormalizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createFunctionContext
	};
};

class NormalizerFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_getDescription
	};
};

class PostingIteratorConst
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
};

class PostingJoinOperatorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createResultIterator,
		Method_getDescription
	};
};

class QueryAnalyzerConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_definePhraseType,
		Method_analyzePhrase,
		Method_analyzePhraseBulk
	};
};

class QueryEvalConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addTerm,
		Method_addSelectionFeature,
		Method_addRestrictionFeature,
		Method_addExclusionFeature,
		Method_addSummarizerFunction,
		Method_addWeightingFunction,
		Method_createQuery
	};
};

class QueryConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_pushTerm,
		Method_pushExpression,
		Method_attachVariable,
		Method_defineFeature,
		Method_defineTermStatistics,
		Method_defineGlobalStatistics,
		Method_defineMetaDataRestriction,
		Method_addDocumentEvaluationSet,
		Method_setMaxNofRanks,
		Method_setMinRank,
		Method_addUserName,
		Method_evaluate
	};
};

class QueryProcessorConst
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
		Method_getSummarizerFunction,
		Method_getFunctionList
	};
};

class SegmenterContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putInput,
		Method_getNext
	};
};

class SegmenterInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineSelectorExpression,
		Method_defineSubSection,
		Method_createContext
	};
};

class SegmenterConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_mimeType,
		Method_createInstance
	};
};

class StatisticsBuilderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_setNofDocumentsInsertedChange,
		Method_addDfChange,
		Method_start,
		Method_rollback,
		Method_fetchMessage
	};
};

class StatisticsIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getNext
	};
};

class StatisticsProcessorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createViewer,
		Method_createBuilder
	};
};

class StatisticsViewerConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_nofDocumentsInsertedChange,
		Method_nextDfChange
	};
};

class StorageAlterMetaDataTableConst
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
};

class StorageClientConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createTermPostingIterator,
		Method_createForwardIterator,
		Method_createInvAclIterator,
		Method_nofDocumentsInserted,
		Method_documentFrequency,
		Method_maxDocumentNumber,
		Method_documentNumber,
		Method_createTermTypeIterator,
		Method_createTermValueIterator,
		Method_createDocIdIterator,
		Method_createUserNameIterator,
		Method_documentStatistics,
		Method_createMetaDataReader,
		Method_createAttributeReader,
		Method_createTransaction,
		Method_createInitStatisticsIterator,
		Method_createUpdateStatisticsIterator,
		Method_getStatisticsProcessor,
		Method_createDocumentChecker,
		Method_checkStorage,
		Method_createDump
	};
};

class StorageDocumentConst
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
};

class StorageDocumentUpdateConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_setMetaData,
		Method_setAttribute,
		Method_clearAttribute,
		Method_setUserAccessRight,
		Method_clearUserAccessRight,
		Method_clearUserAccessRights,
		Method_done
	};
};

class StorageDumpConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_nextChunk
	};
};

class StorageConst
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
};

class StorageObjectBuilderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getStorage,
		Method_getDatabase,
		Method_getQueryProcessor,
		Method_getStatisticsProcessor,
		Method_createStorageClient,
		Method_createAlterMetaDataTable,
		Method_createQueryEval
	};
};

class StorageTransactionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createDocument,
		Method_createDocumentUpdate,
		Method_deleteDocument,
		Method_deleteUserAccessRights,
		Method_updateMetaData,
		Method_commit,
		Method_rollback
	};
};

class SummarizerFunctionContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSummarizationFeature,
		Method_getSummary
	};
};

class SummarizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addStringParameter,
		Method_addNumericParameter,
		Method_createFunctionContext,
		Method_tostring
	};
};

class SummarizerFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_getDescription
	};
};

class TextProcessorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addResourcePath,
		Method_getResourcePath,
		Method_getTokenizer,
		Method_getNormalizer,
		Method_getAggregator,
		Method_detectDocumentClass,
		Method_defineDocumentClassDetector,
		Method_defineTokenizer,
		Method_defineNormalizer,
		Method_defineAggregator,
		Method_getFunctionList
	};
};

class TokenizerFunctionContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_tokenize
	};
};

class TokenizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_concatBeforeTokenize,
		Method_createFunctionContext
	};
};

class TokenizerFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_getDescription
	};
};

class ValueIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skip,
		Method_fetchValues
	};
};

class WeightingFunctionContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addWeightingFeature,
		Method_call
	};
};

class WeightingFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addStringParameter,
		Method_addNumericParameter,
		Method_createFunctionContext,
		Method_tostring
	};
};

class WeightingFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_getDescription
	};
};
} //namespace
#endif
