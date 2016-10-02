/*
 * Copyright (c) 2015 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
	ClassId_DocumentTermIterator,
	ClassId_ForwardIterator,
	ClassId_InvAclIterator,
	ClassId_MetaDataReader,
	ClassId_MetaDataRestrictionInstance,
	ClassId_MetaDataRestriction,
	ClassId_NormalizerFunctionContext,
	ClassId_NormalizerFunctionInstance,
	ClassId_NormalizerFunction,
	ClassId_PatternLexerContext,
	ClassId_PatternLexerInstance,
	ClassId_PatternLexer,
	ClassId_PatternMatcherContext,
	ClassId_PatternMatcherInstance,
	ClassId_PatternMatcher,
	ClassId_PatternMatcherProgramInstance,
	ClassId_PatternMatcherProgram,
	ClassId_PostingIterator,
	ClassId_PostingJoinOperator,
	ClassId_QueryAnalyzer,
	ClassId_QueryEval,
	ClassId_Query,
	ClassId_QueryProcessor,
	ClassId_ScalarFunctionInstance,
	ClassId_ScalarFunction,
	ClassId_ScalarFunctionParser,
	ClassId_SegmenterContext,
	ClassId_SegmenterInstance,
	ClassId_Segmenter,
	ClassId_SegmenterMarkupContext,
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
	ClassId_TokenMarkupContext,
	ClassId_TokenMarkupInstance,
	ClassId_TokenizerFunctionContext,
	ClassId_TokenizerFunctionInstance,
	ClassId_TokenizerFunction,
	ClassId_ValueIterator,
	ClassId_VectorSpaceModelBuilder,
	ClassId_VectorSpaceModelInstance,
	ClassId_VectorSpaceModel,
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
		Method_getSegmenter,
		Method_findMimeTypeSegmenter,
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
		Method_seekUpperBoundRestricted,
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

class DocumentTermIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_nextTerm,
		Method_termDocumentFrequency,
		Method_termValue
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

class MetaDataRestrictionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_match
	};
};

class MetaDataRestrictionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addCondition,
		Method_createInstance,
		Method_tostring
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

class PatternLexerContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_match
	};
};

class PatternLexerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_definePattern,
		Method_defineSymbol,
		Method_getSymbol,
		Method_compile,
		Method_createContext
	};
};

class PatternLexerConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getCompileOptions,
		Method_createInstance,
		Method_getDescription
	};
};

class PatternMatcherContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putInput,
		Method_fetchResults,
		Method_getStatistics
	};
};

class PatternMatcherInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineTermFrequency,
		Method_pushTerm,
		Method_pushExpression,
		Method_pushPattern,
		Method_attachVariable,
		Method_definePattern,
		Method_compile,
		Method_createContext
	};
};

class PatternMatcherConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getCompileOptions,
		Method_createInstance,
		Method_getDescription
	};
};

class PatternMatcherProgramInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_load,
		Method_compile,
		Method_getPatternLexerInstance,
		Method_getPatternMatcherInstance,
		Method_tokenName
	};
};

class PatternMatcherProgramConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance
	};
};

class PostingIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_skipDocCandidate,
		Method_skipPos,
		Method_featureid,
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
		Method_defineWeightingFormula,
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
		Method_addMetaDataRestrictionCondition,
		Method_addDocumentEvaluationSet,
		Method_setMaxNofRanks,
		Method_setMinRank,
		Method_addUserName,
		Method_setWeightingVariableValue,
		Method_evaluate,
		Method_tostring
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
		Method_getFunctionList,
		Method_defineScalarFunctionParser,
		Method_getScalarFunctionParser
	};
};

class ScalarFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_setVariableValue,
		Method_call,
		Method_tostring
	};
};

class ScalarFunctionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getVariables,
		Method_getNofArguments,
		Method_setDefaultVariableValue,
		Method_createInstance,
		Method_tostring
	};
};

class ScalarFunctionParserConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createFunction
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
		Method_createContext,
		Method_createMarkupContext
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

class SegmenterMarkupContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getNext,
		Method_segmentSize,
		Method_tagName,
		Method_tagLevel,
		Method_putOpenTag,
		Method_putAttribute,
		Method_putCloseTag,
		Method_getContent
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
		Method_createBrowsePostingIterator,
		Method_createForwardIterator,
		Method_createDocumentTermIterator,
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
		Method_createMetaDataRestriction,
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
		Method_getVectorSpaceModel,
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
		Method_getPatternLexer,
		Method_getPatternMatcher,
		Method_detectDocumentClass,
		Method_defineDocumentClassDetector,
		Method_defineTokenizer,
		Method_defineNormalizer,
		Method_defineAggregator,
		Method_definePatternLexer,
		Method_definePatternMatcher,
		Method_getFunctionList
	};
};

class TokenMarkupContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putMarkup,
		Method_markupDocument
	};
};

class TokenMarkupInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createContext
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

class VectorSpaceModelBuilderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSampleVector,
		Method_finalize,
		Method_store
	};
};

class VectorSpaceModelInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_mapVectorToFeatures,
		Method_nofFeatures,
		Method_config
	};
};

class VectorSpaceModelConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createInstance,
		Method_createBuilder
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
