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
	ClassId_AclReader,
	ClassId_AggregatorFunctionInstance,
	ClassId_AggregatorFunction,
	ClassId_AnalyzerObjectBuilder,
	ClassId_AttributeReader,
	ClassId_ContentIterator,
	ClassId_ContentStatisticsContext,
	ClassId_ContentStatistics,
	ClassId_DatabaseBackupCursor,
	ClassId_DatabaseClient,
	ClassId_DatabaseCursor,
	ClassId_Database,
	ClassId_DatabaseTransaction,
	ClassId_DocumentAnalyzerContext,
	ClassId_DocumentAnalyzerInstance,
	ClassId_DocumentAnalyzerMap,
	ClassId_DocumentClassDetector,
	ClassId_DocumentTermIterator,
	ClassId_FileLocator,
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
	ClassId_PosTaggerContext,
	ClassId_PosTaggerData,
	ClassId_PosTaggerInstance,
	ClassId_PosTagger,
	ClassId_PostingIterator,
	ClassId_PostingJoinOperator,
	ClassId_QueryAnalyzerContext,
	ClassId_QueryAnalyzerInstance,
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
	ClassId_SentenceAnalyzerInstance,
	ClassId_SentenceLexerContext,
	ClassId_SentenceLexerInstance,
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
	ClassId_StructIterator,
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
	ClassId_VectorStorageTransaction,
	ClassId_WeightingFunctionContext,
	ClassId_WeightingFunctionInstance,
	ClassId_WeightingFunction
};

class AclReaderConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_getReadAccessList
	};
};

class AggregatorFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_evaluate,
		Method_view
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
		Method_createDocumentAnalyzer,
		Method_createPosTaggerInstance,
		Method_createQueryAnalyzer,
		Method_createDocumentAnalyzerMap,
		Method_createDocumentClassDetector,
		Method_createContentStatistics
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
		Method_getNames
	};
};

class ContentIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_getNext
	};
};

class ContentStatisticsContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_putContent,
		Method_statistics,
		Method_nofDocuments
	};
};

class ContentStatisticsConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addLibraryElement,
		Method_addVisibleAttribute,
		Method_addSelectorExpression,
		Method_createContext,
		Method_view
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
		Method_config,
		Method_compactDatabase,
		Method_close
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

class DocumentAnalyzerInstanceConst
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
		Method_defineSubContent,
		Method_addPatternLexem,
		Method_defineTokenPatternMatcher,
		Method_defineContentPatternMatcher,
		Method_addSearchIndexFeatureFromPatternMatch,
		Method_addForwardIndexFeatureFromPatternMatch,
		Method_defineMetaDataFromPatternMatch,
		Method_defineAttributeFromPatternMatch,
		Method_analyze,
		Method_createContext,
		Method_view
	};
};

class DocumentAnalyzerMapConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_createAnalyzer,
		Method_addAnalyzer,
		Method_getAnalyzer,
		Method_analyze,
		Method_createContext,
		Method_view
	};
};

class DocumentClassDetectorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineDocumentSchemeDetector,
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

class FileLocatorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addResourcePath,
		Method_getResourceFilePath,
		Method_defineWorkingDirectory,
		Method_getWorkingDirectory,
		Method_getResourcePaths
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
		Method_elementHandle,
		Method_nofElements,
		Method_skipDoc,
		Method_getValue,
		Method_getType,
		Method_getName,
		Method_getNames
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
		Method_normalize,
		Method_view
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
		Method_defineLexemName,
		Method_defineLexem,
		Method_defineSymbol,
		Method_getSymbol,
		Method_getLexemName,
		Method_compile,
		Method_createContext,
		Method_view
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
		Method_createContext,
		Method_view
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
		Method_getSymbol,
		Method_view
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

class PosTaggerContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_markupDocument
	};
};

class PosTaggerDataConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_declareIgnoredToken,
		Method_insert,
		Method_markupSegment
	};
};

class PosTaggerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addContentExpression,
		Method_addPosTaggerInputPunctuation,
		Method_getPosTaggerInput,
		Method_markupDocument
	};
};

class PosTaggerConst
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
		Method_posno,
		Method_length
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

class QueryAnalyzerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addElement,
		Method_addPatternLexem,
		Method_defineTokenPatternMatcher,
		Method_defineContentPatternMatcher,
		Method_addElementFromPatternMatch,
		Method_queryTermTypes,
		Method_queryFieldTypes,
		Method_createContext,
		Method_view
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
		Method_getWeightingFeatureSets,
		Method_getSelectionFeatureSets,
		Method_getRestrictionFeatureSets,
		Method_getExclusionFeatureSets,
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
		Method_addAccess,
		Method_setMaxNofRanks,
		Method_setMinRank,
		Method_setWeightingVariableValue,
		Method_setDebugMode,
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
		Method_getResourceFilePath,
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
		Method_createFunction,
		Method_getDescription
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
		Method_createMarkupContext,
		Method_view
	};
};

class SegmenterConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_mimeType,
		Method_createInstance,
		Method_createContentIterator,
		Method_getDescription
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

class SentenceAnalyzerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_pushTerm,
		Method_pushAlt,
		Method_pushSequenceImm,
		Method_pushRepeat,
		Method_defineSentence,
		Method_analyzeSentence
	};
};

class SentenceLexerContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_fetchFirstSplit,
		Method_fetchNextSplit,
		Method_nofTokens,
		Method_featureValue,
		Method_featureTypes
	};
};

class SentenceLexerInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSeparator,
		Method_addLink,
		Method_createContext,
		Method_getSimilarity
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
		Method_createStructIterator,
		Method_createBrowsePostingIterator,
		Method_createFieldPostingIterator,
		Method_createForwardIterator,
		Method_createDocumentTermIterator,
		Method_createInvAclIterator,
		Method_createAclReader,
		Method_nofDocumentsInserted,
		Method_documentFrequency,
		Method_maxDocumentNumber,
		Method_documentNumber,
		Method_termTypeNumber,
		Method_isForwardIndexTerm,
		Method_createTermTypeIterator,
		Method_createStructTypeIterator,
		Method_createTermValueIterator,
		Method_createDocIdIterator,
		Method_createUserNameIterator,
		Method_documentStatistics,
		Method_createMetaDataReader,
		Method_createMetaDataRestriction,
		Method_createAttributeReader,
		Method_createTransaction,
		Method_createAllStatisticsIterator,
		Method_createChangeStatisticsIterator,
		Method_getStatisticsProcessor,
		Method_createDocumentChecker,
		Method_checkStorage,
		Method_close
	};
};

class StorageDocumentConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSearchIndexTerm,
		Method_addSearchIndexStructure,
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
		Method_addSearchIndexTerm,
		Method_addSearchIndexStructure,
		Method_addForwardIndexTerm,
		Method_clearSearchIndexTerm,
		Method_clearSearchIndexStructure,
		Method_clearForwardIndexTerm,
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
		Method_createQueryEval,
		Method_createSentenceAnalyzer
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
		Method_updateDocumentFrequency,
		Method_commit,
		Method_rollback,
		Method_nofDocumentsAffected
	};
};

class StructIteratorConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_skipDoc,
		Method_skipPosSource,
		Method_skipPosSink,
		Method_source,
		Method_sink
	};
};

class SummarizerFunctionContextConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_addSummarizationFeature,
		Method_setVariableValue,
		Method_getSummary,
		Method_debugCall
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
		Method_getVariables,
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
		Method_getResourceFilePath,
		Method_getSegmenterByName,
		Method_getSegmenterByMimeType,
		Method_getSegmenterOptions,
		Method_getTokenizer,
		Method_getNormalizer,
		Method_getAggregator,
		Method_getPatternLexer,
		Method_getPatternMatcher,
		Method_getPatternTermFeeder,
		Method_createPosTaggerData,
		Method_getPosTagger,
		Method_createTokenMarkupInstance,
		Method_detectDocumentClass,
		Method_defineDocumentClassDetector,
		Method_defineSegmenter,
		Method_defineSegmenterOptions,
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
		Method_createContext,
		Method_view
	};
};

class TokenizerFunctionInstanceConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_concatBeforeTokenize,
		Method_tokenize,
		Method_view
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
		Method_skipPrefix,
		Method_fetchValues
	};
};

class VectorStorageClientConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_prepareSearch,
		Method_findSimilar,
		Method_createTransaction,
		Method_types,
		Method_createFeatureValueIterator,
		Method_featureTypes,
		Method_nofVectors,
		Method_featureVector,
		Method_vectorSimilarity,
		Method_normalize,
		Method_createSentenceLexer,
		Method_config,
		Method_close
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
		Method_createDump
	};
};

class VectorStorageTransactionConst
{
public:
	enum MethodId
	{
		Method_Destructor,
		Method_defineVector,
		Method_defineFeature,
		Method_defineScalar,
		Method_clear,
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
		Method_setVariableValue,
		Method_call,
		Method_debugCall
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
		Method_getVariables,
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
