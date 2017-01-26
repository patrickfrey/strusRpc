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
	ClassId_NormalizerFunctionInstance,
	ClassId_NormalizerFunction,
	ClassId_PatternLexerContext,
	ClassId_PatternLexerInstance,
	ClassId_PatternLexer,
	ClassId_PatternMatcherContext,
	ClassId_PatternMatcherInstance,
	ClassId_PatternMatcher,
	ClassId_PatternTermFeederInstance,
	ClassId_PatternTermFeeder,
	ClassId_PostingIterator,
	ClassId_PostingJoinOperator,
	ClassId_QueryAnalyzerContext,
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
	ClassId_TokenizerFunctionInstance,
	ClassId_TokenizerFunction,
	ClassId_ValueIterator,
	ClassId_VectorStorageClient,
	ClassId_VectorStorageDump,
	ClassId_VectorStorage,
	ClassId_VectorStorageSearch,
	ClassId_VectorStorageTransaction,
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
		Method_readValue,
		Method_config
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
		Method_addPatternLexem,
		Method_definePatternMatcherPostProc,
		Method_definePatternMatcherPreProc,
		Method_addSearchIndexFeatureFromPatternMatch,
		Method_addForwardIndexFeatureFromPatternMatch,
		Method_defineMetaDataFromPatternMatch,
		Method_defineAttributeFromPatternMatch,
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

class NormalizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_normalize
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
		Method_match,
		Method_reset
	};
};

class PatternLexerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineOption,
		Method_defineLexem,
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
		Method_getCompileOptionNames,
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
		Method_getStatistics,
		Method_reset
	};
};

class PatternMatcherInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineOption,
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
		Method_getCompileOptionNames,
		Method_createInstance,
		Method_getDescription
	};
};

class PatternTermFeederInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineLexem,
		Method_defineSymbol,
		Method_getLexem,
		Method_lexemTypes,
		Method_getSymbol
	};
};

class PatternTermFeederConst
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

class QueryAnalyzerContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putField,
		Method_groupElements,
		Method_analyze
	};
};

class QueryAnalyzerConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSearchIndexElement,
		Method_addMetaDataElement,
		Method_addPatternLexem,
		Method_definePatternMatcherPostProc,
		Method_definePatternMatcherPreProc,
		Method_addSearchIndexElementFromPatternMatch,
		Method_addMetaDataElementFromPatternMatch,
		Method_createContext
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
		Method_pushDocField,
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
		Method_config,
		Method_createTermPostingIterator,
		Method_createBrowsePostingIterator,
		Method_createFieldPostingIterator,
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
		Method_checkStorage
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
		Method_getConfigParameters,
		Method_createDump
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
		Method_getVectorStorage,
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
		Method_rollback,
		Method_nofDocumentsAffected
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
		Method_defineResultName,
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
		Method_getPatternTermFeeder,
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

class TokenizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_concatBeforeTokenize,
		Method_tokenize
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

class VectorStorageClientConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createSearcher,
		Method_createTransaction,
		Method_conceptClassNames,
		Method_conceptFeatures,
		Method_nofConcepts,
		Method_featureConcepts,
		Method_featureVector,
		Method_featureName,
		Method_featureIndex,
		Method_nofFeatures,
		Method_config
	};
};

class VectorStorageDumpConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_nextChunk
	};
};

class VectorStorageConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createStorage,
		Method_createClient,
		Method_createDump,
		Method_runBuild
	};
};

class VectorStorageSearchConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_findSimilar,
		Method_findSimilarFromSelection,
		Method_close
	};
};

class VectorStorageTransactionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addFeature,
		Method_defineFeatureConceptRelation,
		Method_commit,
		Method_rollback
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
