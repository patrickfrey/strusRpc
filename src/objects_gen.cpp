/*
 * Copyright (c) 2015 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "objects_gen.hpp"
#include "rpcSerializer.hpp"
#include "strus/errorBufferInterface.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"
#include <iostream>
using namespace strus;

AclReaderImpl::~AclReaderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void AclReaderImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AclReaderImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AclReaderImpl::skipDoc", err.what());
	return void();
}
}

std::vector<std::string> AclReaderImpl::getReadAccessList( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getReadAccessList);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AclReaderImpl::getReadAccessList");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AclReaderImpl::getReadAccessList", err.what());
	return std::vector<std::string>();
}
}

AggregatorFunctionInstanceImpl::~AggregatorFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

NumericVariant AggregatorFunctionInstanceImpl::evaluate( const analyzer::Document& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packAnalyzerDocument( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	NumericVariant p0 = serializedMsg.unpackNumericVariant();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AggregatorFunctionInstanceImpl::evaluate");
	return NumericVariant();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AggregatorFunctionInstanceImpl::evaluate", err.what());
	return NumericVariant();
}
}

analyzer::FunctionView AggregatorFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AggregatorFunctionInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AggregatorFunctionInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

AggregatorFunctionImpl::~AggregatorFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

AggregatorFunctionInstanceInterface* AggregatorFunctionImpl::createInstance( const std::vector<std::string>& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_AggregatorFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	AggregatorFunctionInstanceInterface* p0 = new AggregatorFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AggregatorFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AggregatorFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* AggregatorFunctionImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AggregatorFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AggregatorFunctionImpl::getDescription", err.what());
	return 0;
}
}

AnalyzerObjectBuilderImpl::~AnalyzerObjectBuilderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const TextProcessorInterface* AnalyzerObjectBuilderImpl::getTextProcessor( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTextProcessor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TextProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TextProcessorImpl const_0( objId_0, ctx(), true, errorhnd());
	const TextProcessorInterface* p0 = (const TextProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::getTextProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::getTextProcessor", err.what());
	return 0;
}
}

DocumentAnalyzerInstanceInterface* AnalyzerObjectBuilderImpl::createDocumentAnalyzer( const SegmenterInterface* p1, const analyzer::SegmenterOptions& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentAnalyzer);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Segmenter");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packSegmenterOptions( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInstanceInterface* p0 = new DocumentAnalyzerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzer", err.what());
	return 0;
}
}

PosTaggerInstanceInterface* AnalyzerObjectBuilderImpl::createPosTaggerInstance( const SegmenterInterface* p1, const analyzer::SegmenterOptions& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPosTaggerInstance);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Segmenter");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packSegmenterOptions( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PosTaggerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PosTaggerInstanceInterface* p0 = new PosTaggerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createPosTaggerInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createPosTaggerInstance", err.what());
	return 0;
}
}

QueryAnalyzerInstanceInterface* AnalyzerObjectBuilderImpl::createQueryAnalyzer( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryAnalyzer);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryAnalyzerInstanceInterface* p0 = new QueryAnalyzerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createQueryAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createQueryAnalyzer", err.what());
	return 0;
}
}

DocumentAnalyzerMapInterface* AnalyzerObjectBuilderImpl::createDocumentAnalyzerMap( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentAnalyzerMap);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerMap;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerMapInterface* p0 = new DocumentAnalyzerMapImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzerMap");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzerMap", err.what());
	return 0;
}
}

DocumentClassDetectorInterface* AnalyzerObjectBuilderImpl::createDocumentClassDetector( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentClassDetector);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentClassDetector;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentClassDetectorInterface* p0 = new DocumentClassDetectorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createDocumentClassDetector");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createDocumentClassDetector", err.what());
	return 0;
}
}

ContentStatisticsInterface* AnalyzerObjectBuilderImpl::createContentStatistics( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContentStatistics);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ContentStatistics;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ContentStatisticsInterface* p0 = new ContentStatisticsImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createContentStatistics");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createContentStatistics", err.what());
	return 0;
}
}

AttributeReaderImpl::~AttributeReaderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index AttributeReaderImpl::elementHandle( const char* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packCharp( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AttributeReaderImpl::elementHandle");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AttributeReaderImpl::elementHandle", err.what());
	return 0;
}
}

void AttributeReaderImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AttributeReaderImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AttributeReaderImpl::skipDoc", err.what());
	return void();
}
}

std::string AttributeReaderImpl::getValue( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AttributeReaderImpl::getValue");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AttributeReaderImpl::getValue", err.what());
	return std::string();
}
}

std::vector<std::string> AttributeReaderImpl::getNames( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNames);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "AttributeReaderImpl::getNames");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "AttributeReaderImpl::getNames", err.what());
	return std::vector<std::string>();
}
}

ContentIteratorImpl::~ContentIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool ContentIteratorImpl::getNext( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	const char* bp3;
	serializedMsg.unpackBuffer( bp3, p4);
	p3 = (const char*) ctx()->constConstructor()->get( bp3, p4);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentIteratorImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentIteratorImpl::getNext", err.what());
	return false;
}
}

ContentStatisticsContextImpl::~ContentStatisticsContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ContentStatisticsContextImpl::putContent( const std::string& p1, const std::string& p2, const analyzer::DocumentClass& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putContent);
	msg.packString( p1);
	msg.packString( p2);
	msg.packDocumentClass( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsContextImpl::putContent");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsContextImpl::putContent", err.what());
	return void();
}
}

analyzer::ContentStatisticsResult ContentStatisticsContextImpl::statistics( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_statistics);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::ContentStatisticsResult p0 = serializedMsg.unpackAnalyzerContentStatisticsResult();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsContextImpl::statistics");
	return analyzer::ContentStatisticsResult();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsContextImpl::statistics", err.what());
	return analyzer::ContentStatisticsResult();
}
}

int ContentStatisticsContextImpl::nofDocuments( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofDocuments);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsContextImpl::nofDocuments");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsContextImpl::nofDocuments", err.what());
	return 0;
}
}

ContentStatisticsImpl::~ContentStatisticsImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ContentStatisticsImpl::addLibraryElement( const std::string& p1, const std::string& p2, int p3, int p4, int p5, TokenizerFunctionInstanceInterface* p6, const std::vector<NormalizerFunctionInstanceInterface*>& p7)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addLibraryElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packInt( p3);
	msg.packInt( p4);
	msg.packInt( p5);
	const RpcInterfaceStub* impl_6 = dynamic_cast<const RpcInterfaceStub*>(p6);
	if (!impl_6) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_6->classId(), impl_6->objId());
	msg.packSize( p7.size());
	for (unsigned int ii=0; ii < p7.size(); ++ii) {
		const RpcInterfaceStub* impl_7 = dynamic_cast<const RpcInterfaceStub*>(p7[ii]);
		if (!impl_7) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_7->classId(), impl_7->objId());
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsImpl::addLibraryElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsImpl::addLibraryElement", err.what());
	return void();
}
}

void ContentStatisticsImpl::addVisibleAttribute( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addVisibleAttribute);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsImpl::addVisibleAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsImpl::addVisibleAttribute", err.what());
	return void();
}
}

void ContentStatisticsImpl::addSelectorExpression( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectorExpression);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsImpl::addSelectorExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsImpl::addSelectorExpression", err.what());
	return void();
}
}

ContentStatisticsContextInterface* ContentStatisticsImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ContentStatisticsContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ContentStatisticsContextInterface* p0 = new ContentStatisticsContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsImpl::createContext", err.what());
	return 0;
}
}

analyzer::ContentStatisticsView ContentStatisticsImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::ContentStatisticsView p0 = serializedMsg.unpackAnalyzerContentStatisticsView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ContentStatisticsImpl::view");
	return analyzer::ContentStatisticsView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ContentStatisticsImpl::view", err.what());
	return analyzer::ContentStatisticsView();
}
}

DatabaseBackupCursorImpl::~DatabaseBackupCursorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool DatabaseBackupCursorImpl::fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	const char* bp3;
	serializedMsg.unpackBuffer( bp3, p4);
	p3 = (const char*) ctx()->constConstructor()->get( bp3, p4);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseBackupCursorImpl::fetch");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseBackupCursorImpl::fetch", err.what());
	return false;
}
}

DatabaseClientImpl::~DatabaseClientImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseTransactionInterface* DatabaseClientImpl::createTransaction( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseTransactionInterface* p0 = new DatabaseTransactionImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createTransaction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::createTransaction", err.what());
	return 0;
}
}

DatabaseCursorInterface* DatabaseClientImpl::createCursor( const DatabaseOptions& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::createCursor", err.what());
	return 0;
}
}

DatabaseBackupCursorInterface* DatabaseClientImpl::createBackupCursor( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBackupCursor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseBackupCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseBackupCursorInterface* p0 = new DatabaseBackupCursorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createBackupCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::createBackupCursor", err.what());
	return 0;
}
}

void DatabaseClientImpl::writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_writeImm);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::writeImm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::writeImm", err.what());
	return void();
}
}

void DatabaseClientImpl::removeImm( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeImm);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::removeImm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::removeImm", err.what());
	return void();
}
}

bool DatabaseClientImpl::readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_readValue);
	msg.packBuffer( p1, p2);
	msg.packDatabaseOptions( p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p3 = serializedMsg.unpackString();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::readValue");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::readValue", err.what());
	return false;
}
}

std::string DatabaseClientImpl::config( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_config);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::config");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::config", err.what());
	return std::string();
}
}

bool DatabaseClientImpl::compactDatabase( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compactDatabase);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::compactDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::compactDatabase", err.what());
	return false;
}
}

void DatabaseClientImpl::close( )
{
try
{
	if (objId() == 0) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseClientImpl::close");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseClientImpl::close", err.what());
	return void();
}
}

DatabaseCursorImpl::~DatabaseCursorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBound( const char* p1, std::size_t p2, std::size_t p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBound);
	msg.packBuffer( p1, p2);
	msg.packSize( p3);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekUpperBound");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekUpperBound", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBoundRestricted( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBoundRestricted);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekUpperBoundRestricted");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekUpperBoundRestricted", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekFirst( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekFirst);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekFirst");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekFirst", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekLast( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekLast);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekLast");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekLast", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekNext( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekNext);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekNext");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekNext", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekPrev( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekPrev);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekPrev");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekPrev", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::key( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_key);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::key");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::key", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::value( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_value);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::value");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseCursorImpl::value", err.what());
	return DatabaseCursorInterface::Slice();
}
}

DatabaseImpl::~DatabaseImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool DatabaseImpl::exists( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_exists);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::exists");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::exists", err.what());
	return false;
}
}

DatabaseClientInterface* DatabaseImpl::createClient( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseClientInterface* p0 = new DatabaseClientImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::createClient");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::createClient", err.what());
	return 0;
}
}

bool DatabaseImpl::createDatabase( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDatabase);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::createDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::createDatabase", err.what());
	return false;
}
}

bool DatabaseImpl::restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_restoreDatabase);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DatabaseBackupCursor");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::restoreDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::restoreDatabase", err.what());
	return false;
}
}

bool DatabaseImpl::destroyDatabase( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_destroyDatabase);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::destroyDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::destroyDatabase", err.what());
	return false;
}
}

const char* DatabaseImpl::getConfigDescription( const DatabaseInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::getConfigDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::getConfigDescription", err.what());
	return 0;
}
}

const char** DatabaseImpl::getConfigParameters( const DatabaseInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char** p0 =  ctx()->constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseImpl::getConfigParameters");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseImpl::getConfigParameters", err.what());
	return 0;
}
}

DatabaseTransactionImpl::~DatabaseTransactionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseCursorInterface* DatabaseTransactionImpl::createCursor( const DatabaseOptions& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::createCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::createCursor", err.what());
	return 0;
}
}

void DatabaseTransactionImpl::write( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_write);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::write");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::write", err.what());
	return void();
}
}

void DatabaseTransactionImpl::remove( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_remove);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::remove");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::remove", err.what());
	return void();
}
}

void DatabaseTransactionImpl::removeSubTree( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeSubTree);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::removeSubTree");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::removeSubTree", err.what());
	return void();
}
}

bool DatabaseTransactionImpl::commit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::commit", err.what());
	return false;
}
}

void DatabaseTransactionImpl::rollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::rollback", err.what());
	return void();
}
}

DocumentAnalyzerContextImpl::~DocumentAnalyzerContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentAnalyzerContextImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerContextImpl::putInput", err.what());
	return void();
}
}

bool DocumentAnalyzerContextImpl::analyzeNext( analyzer::Document& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeNext);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackAnalyzerDocument();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerContextImpl::analyzeNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerContextImpl::analyzeNext", err.what());
	return false;
}
}

DocumentAnalyzerInstanceImpl::~DocumentAnalyzerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentAnalyzerInstanceImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, int p5, const analyzer::FeatureOptions& p6)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packInt( p5);
	msg.packFeatureOptions( p6);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::addSearchIndexFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::addSearchIndexFeature", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::addForwardIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, int p5, const analyzer::FeatureOptions& p6)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packInt( p5);
	msg.packFeatureOptions( p6);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::addForwardIndexFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::addForwardIndexFeature", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineMetaData( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaData);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineMetaData", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineAggregatedMetaData( const std::string& p1, AggregatorFunctionInstanceInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAggregatedMetaData);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "AggregatorFunctionInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineAggregatedMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineAggregatedMetaData", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineAttribute( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAttribute);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineAttribute", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineSubDocument( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubDocument);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineSubDocument");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineSubDocument", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineSubContent( const std::string& p1, const analyzer::DocumentClass& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubContent);
	msg.packString( p1);
	msg.packDocumentClass( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineSubContent");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineSubContent", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::addPatternLexem( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, int p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addPatternLexem);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packInt( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::addPatternLexem");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::addPatternLexem", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineTokenPatternMatcher( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternTermFeederInstanceInterface* p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenPatternMatcher);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternMatcherInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternTermFeederInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineTokenPatternMatcher");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineTokenPatternMatcher", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineContentPatternMatcher( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternLexerInstanceInterface* p3, const std::vector<std::string>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineContentPatternMatcher);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternMatcherInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternLexerInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packString( p4[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineContentPatternMatcher");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineContentPatternMatcher", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::addSearchIndexFeatureFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3, int p4, const analyzer::FeatureOptions& p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexFeatureFromPatternMatch);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3[ii]);
		if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_3->classId(), impl_3->objId());
	}
	msg.packInt( p4);
	msg.packFeatureOptions( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	for (std::size_t ai_3=0; ai_3 < p3.size(); ++ai_3) {
		RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3[ai_3]);
		done_3->release();
		delete p3[ai_3];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::addSearchIndexFeatureFromPatternMatch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::addSearchIndexFeatureFromPatternMatch", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::addForwardIndexFeatureFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3, int p4, const analyzer::FeatureOptions& p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexFeatureFromPatternMatch);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3[ii]);
		if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_3->classId(), impl_3->objId());
	}
	msg.packInt( p4);
	msg.packFeatureOptions( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	for (std::size_t ai_3=0; ai_3 < p3.size(); ++ai_3) {
		RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3[ai_3]);
		done_3->release();
		delete p3[ai_3];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::addForwardIndexFeatureFromPatternMatch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::addForwardIndexFeatureFromPatternMatch", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineMetaDataFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaDataFromPatternMatch);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3[ii]);
		if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_3->classId(), impl_3->objId());
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	for (std::size_t ai_3=0; ai_3 < p3.size(); ++ai_3) {
		RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3[ai_3]);
		done_3->release();
		delete p3[ai_3];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineMetaDataFromPatternMatch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineMetaDataFromPatternMatch", err.what());
	return void();
}
}

void DocumentAnalyzerInstanceImpl::defineAttributeFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAttributeFromPatternMatch);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3[ii]);
		if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_3->classId(), impl_3->objId());
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	for (std::size_t ai_3=0; ai_3 < p3.size(); ++ai_3) {
		RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3[ai_3]);
		done_3->release();
		delete p3[ai_3];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::defineAttributeFromPatternMatch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::defineAttributeFromPatternMatch", err.what());
	return void();
}
}

analyzer::Document DocumentAnalyzerInstanceImpl::analyze( const std::string& p1, const analyzer::DocumentClass& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packDocumentClass( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::Document p0 = serializedMsg.unpackAnalyzerDocument();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::analyze");
	return analyzer::Document();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::analyze", err.what());
	return analyzer::Document();
}
}

DocumentAnalyzerContextInterface* DocumentAnalyzerInstanceImpl::createContext( const analyzer::DocumentClass& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	msg.packDocumentClass( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerContextInterface* p0 = new DocumentAnalyzerContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::createContext", err.what());
	return 0;
}
}

analyzer::DocumentAnalyzerView DocumentAnalyzerInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::DocumentAnalyzerView p0 = serializedMsg.unpackAnalyzerDocumentAnalyzerView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerInstanceImpl::view");
	return analyzer::DocumentAnalyzerView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerInstanceImpl::view", err.what());
	return analyzer::DocumentAnalyzerView();
}
}

DocumentAnalyzerMapImpl::~DocumentAnalyzerMapImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DocumentAnalyzerInstanceInterface* DocumentAnalyzerMapImpl::createAnalyzer( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAnalyzer);
	msg.packString( p1);
	msg.packString( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInstanceInterface* p0 = new DocumentAnalyzerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::createAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::createAnalyzer", err.what());
	return 0;
}
}

void DocumentAnalyzerMapImpl::addAnalyzer( const std::string& p1, const std::string& p2, DocumentAnalyzerInstanceInterface* p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addAnalyzer);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DocumentAnalyzerInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::addAnalyzer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::addAnalyzer", err.what());
	return void();
}
}

const DocumentAnalyzerInstanceInterface* DocumentAnalyzerMapImpl::getAnalyzer( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getAnalyzer);
	msg.packString( p1);
	msg.packString( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInstanceImpl const_0( objId_0, ctx(), true, errorhnd());
	const DocumentAnalyzerInstanceInterface* p0 = (const DocumentAnalyzerInstanceImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::getAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::getAnalyzer", err.what());
	return 0;
}
}

analyzer::Document DocumentAnalyzerMapImpl::analyze( const std::string& p1, const analyzer::DocumentClass& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packDocumentClass( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::Document p0 = serializedMsg.unpackAnalyzerDocument();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::analyze");
	return analyzer::Document();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::analyze", err.what());
	return analyzer::Document();
}
}

DocumentAnalyzerContextInterface* DocumentAnalyzerMapImpl::createContext( const analyzer::DocumentClass& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	msg.packDocumentClass( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerContextInterface* p0 = new DocumentAnalyzerContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::createContext", err.what());
	return 0;
}
}

analyzer::DocumentAnalyzerMapView DocumentAnalyzerMapImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::DocumentAnalyzerMapView p0 = serializedMsg.unpackAnalyzerDocumentAnalyzerMapView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentAnalyzerMapImpl::view");
	return analyzer::DocumentAnalyzerMapView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentAnalyzerMapImpl::view", err.what());
	return analyzer::DocumentAnalyzerMapView();
}
}

DocumentClassDetectorImpl::~DocumentClassDetectorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentClassDetectorImpl::defineDocumentSchemaDetector( const std::string& p1, const std::string& p2, const std::vector<std::string>& p3, const std::vector<std::string>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineDocumentSchemaDetector);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packString( p3[ii]);
	}
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packString( p4[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentClassDetectorImpl::defineDocumentSchemaDetector");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentClassDetectorImpl::defineDocumentSchemaDetector", err.what());
	return void();
}
}

bool DocumentClassDetectorImpl::detect( analyzer::DocumentClass& p1, const char* p2, std::size_t p3, bool p4) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_detect);
	msg.packBuffer( p2, p3);
	msg.packBool( p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackDocumentClass();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentClassDetectorImpl::detect");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentClassDetectorImpl::detect", err.what());
	return false;
}
}

DocumentTermIteratorImpl::~DocumentTermIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index DocumentTermIteratorImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::skipDoc", err.what());
	return 0;
}
}

bool DocumentTermIteratorImpl::nextTerm( DocumentTermIteratorInterface::Term& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextTerm);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackDocumentTermIteratorTerm();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::nextTerm");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::nextTerm", err.what());
	return false;
}
}

unsigned int DocumentTermIteratorImpl::termDocumentFrequency( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_termDocumentFrequency);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::termDocumentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::termDocumentFrequency", err.what());
	return 0;
}
}

std::string DocumentTermIteratorImpl::termValue( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_termValue);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::termValue");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::termValue", err.what());
	return std::string();
}
}

FileLocatorImpl::~FileLocatorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void FileLocatorImpl::addResourcePath( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "FileLocatorImpl::addResourcePath");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "FileLocatorImpl::addResourcePath", err.what());
	return void();
}
}

std::string FileLocatorImpl::getResourceFilePath( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourceFilePath);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "FileLocatorImpl::getResourceFilePath");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "FileLocatorImpl::getResourceFilePath", err.what());
	return std::string();
}
}

void FileLocatorImpl::defineWorkingDirectory( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWorkingDirectory);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "FileLocatorImpl::defineWorkingDirectory");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "FileLocatorImpl::defineWorkingDirectory", err.what());
	return void();
}
}

std::string FileLocatorImpl::getWorkingDirectory( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWorkingDirectory);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "FileLocatorImpl::getWorkingDirectory");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "FileLocatorImpl::getWorkingDirectory", err.what());
	return std::string();
}
}

std::vector<std::string> FileLocatorImpl::getResourcePaths( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePaths);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "FileLocatorImpl::getResourcePaths");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "FileLocatorImpl::getResourcePaths", err.what());
	return std::vector<std::string>();
}
}

ForwardIteratorImpl::~ForwardIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ForwardIteratorImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ForwardIteratorImpl::skipDoc", err.what());
	return void();
}
}

Index ForwardIteratorImpl::skipPos( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::skipPos");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ForwardIteratorImpl::skipPos", err.what());
	return 0;
}
}

std::string ForwardIteratorImpl::fetch( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::fetch");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ForwardIteratorImpl::fetch", err.what());
	return std::string();
}
}

InvAclIteratorImpl::~InvAclIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index InvAclIteratorImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "InvAclIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "InvAclIteratorImpl::skipDoc", err.what());
	return 0;
}
}

MetaDataReaderImpl::~MetaDataReaderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index MetaDataReaderImpl::elementHandle( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::elementHandle");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::elementHandle", err.what());
	return 0;
}
}

Index MetaDataReaderImpl::nofElements( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofElements);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::nofElements");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::nofElements", err.what());
	return 0;
}
}

void MetaDataReaderImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::skipDoc", err.what());
	return void();
}
}

NumericVariant MetaDataReaderImpl::getValue( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	NumericVariant p0 = serializedMsg.unpackNumericVariant();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getValue");
	return NumericVariant();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getValue", err.what());
	return NumericVariant();
}
}

const char* MetaDataReaderImpl::getType( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getType);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getType");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getType", err.what());
	return 0;
}
}

const char* MetaDataReaderImpl::getName( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getName);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getName");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getName", err.what());
	return 0;
}
}

std::vector<std::string> MetaDataReaderImpl::getNames( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNames);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getNames");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getNames", err.what());
	return std::vector<std::string>();
}
}

MetaDataRestrictionInstanceImpl::~MetaDataRestrictionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool MetaDataRestrictionInstanceImpl::match( const Index& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_match);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataRestrictionInstanceImpl::match");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataRestrictionInstanceImpl::match", err.what());
	return false;
}
}

MetaDataRestrictionImpl::~MetaDataRestrictionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void MetaDataRestrictionImpl::addCondition( const MetaDataRestrictionInterface::CompareOperator& p1, const std::string& p2, const NumericVariant& p3, bool p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addCondition);
	msg.packMetaDataRestrictionCompareOperator( p1);
	msg.packString( p2);
	msg.packNumericVariant( p3);
	msg.packBool( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::addCondition");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::addCondition", err.what());
	return void();
}
}

MetaDataRestrictionInstanceInterface* MetaDataRestrictionImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_MetaDataRestrictionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	MetaDataRestrictionInstanceInterface* p0 = new MetaDataRestrictionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::createInstance", err.what());
	return 0;
}
}

std::string MetaDataRestrictionImpl::tostring( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tostring);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::tostring", err.what());
	return std::string();
}
}

NormalizerFunctionInstanceImpl::~NormalizerFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string NormalizerFunctionInstanceImpl::normalize( const char* p1, std::size_t p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "NormalizerFunctionInstanceImpl::normalize");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "NormalizerFunctionInstanceImpl::normalize", err.what());
	return std::string();
}
}

analyzer::FunctionView NormalizerFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "NormalizerFunctionInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "NormalizerFunctionInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

NormalizerFunctionImpl::~NormalizerFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

NormalizerFunctionInstanceInterface* NormalizerFunctionImpl::createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TextProcessor");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerFunctionInstanceInterface* p0 = new NormalizerFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "NormalizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "NormalizerFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* NormalizerFunctionImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "NormalizerFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "NormalizerFunctionImpl::getDescription", err.what());
	return 0;
}
}

PatternLexerContextImpl::~PatternLexerContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<analyzer::PatternLexem> PatternLexerContextImpl::match( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_match);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<analyzer::PatternLexem> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::PatternLexem elem_p0 = serializedMsg.unpackAnalyzerPatternLexem();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerContextImpl::match");
	return std::vector<analyzer::PatternLexem>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerContextImpl::match", err.what());
	return std::vector<analyzer::PatternLexem>();
}
}

void PatternLexerContextImpl::reset( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_reset);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerContextImpl::reset");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerContextImpl::reset", err.what());
	return void();
}
}

PatternLexerInstanceImpl::~PatternLexerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PatternLexerInstanceImpl::defineOption( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineOption);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::defineOption");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::defineOption", err.what());
	return void();
}
}

void PatternLexerInstanceImpl::defineLexemName( unsigned int p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineLexemName);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::defineLexemName");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::defineLexemName", err.what());
	return void();
}
}

void PatternLexerInstanceImpl::defineLexem( unsigned int p1, const std::string& p2, unsigned int p3, unsigned int p4, analyzer::PositionBind p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineLexem);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packUint( p3);
	msg.packUint( p4);
	msg.packByte( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::defineLexem");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::defineLexem", err.what());
	return void();
}
}

void PatternLexerInstanceImpl::defineSymbol( unsigned int p1, unsigned int p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSymbol);
	msg.packUint( p1);
	msg.packUint( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::defineSymbol");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::defineSymbol", err.what());
	return void();
}
}

unsigned int PatternLexerInstanceImpl::getSymbol( unsigned int p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSymbol);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::getSymbol");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::getSymbol", err.what());
	return 0;
}
}

const char* PatternLexerInstanceImpl::getLexemName( unsigned int p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getLexemName);
	msg.packUint( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::getLexemName");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::getLexemName", err.what());
	return 0;
}
}

bool PatternLexerInstanceImpl::compile( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compile);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::compile", err.what());
	return false;
}
}

PatternLexerContextInterface* PatternLexerInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternLexerContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternLexerContextInterface* p0 = new PatternLexerContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::createContext", err.what());
	return 0;
}
}

analyzer::FunctionView PatternLexerInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

PatternLexerImpl::~PatternLexerImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<std::string> PatternLexerImpl::getCompileOptionNames( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getCompileOptionNames);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerImpl::getCompileOptionNames");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerImpl::getCompileOptionNames", err.what());
	return std::vector<std::string>();
}
}

PatternLexerInstanceInterface* PatternLexerImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternLexerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternLexerInstanceInterface* p0 = new PatternLexerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerImpl::createInstance", err.what());
	return 0;
}
}

const char* PatternLexerImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternLexerImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternLexerImpl::getDescription", err.what());
	return 0;
}
}

PatternMatcherContextImpl::~PatternMatcherContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PatternMatcherContextImpl::putInput( const analyzer::PatternLexem& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packAnalyzerPatternLexem( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherContextImpl::putInput", err.what());
	return void();
}
}

std::vector<analyzer::PatternMatcherResult> PatternMatcherContextImpl::fetchResults( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetchResults);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<analyzer::PatternMatcherResult> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::PatternMatcherResult elem_p0 = serializedMsg.unpackAnalyzerPatternMatcherResult();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherContextImpl::fetchResults");
	return std::vector<analyzer::PatternMatcherResult>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherContextImpl::fetchResults", err.what());
	return std::vector<analyzer::PatternMatcherResult>();
}
}

analyzer::PatternMatcherStatistics PatternMatcherContextImpl::getStatistics( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getStatistics);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::PatternMatcherStatistics p0 = serializedMsg.unpackAnalyzerPatternMatcherStatistics();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherContextImpl::getStatistics");
	return analyzer::PatternMatcherStatistics();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherContextImpl::getStatistics", err.what());
	return analyzer::PatternMatcherStatistics();
}
}

void PatternMatcherContextImpl::reset( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_reset);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherContextImpl::reset");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherContextImpl::reset", err.what());
	return void();
}
}

PatternMatcherInstanceImpl::~PatternMatcherInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PatternMatcherInstanceImpl::defineOption( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineOption);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::defineOption");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::defineOption", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::defineTermFrequency( unsigned int p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTermFrequency);
	msg.packUint( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::defineTermFrequency");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::defineTermFrequency", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::pushTerm( unsigned int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packUint( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::pushTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::pushTerm", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::pushExpression( PatternMatcherInstanceInterface::JoinOperation p1, std::size_t p2, unsigned int p3, unsigned int p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	msg.packByte( p1);
	msg.packSize( p2);
	msg.packUint( p3);
	msg.packUint( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::pushExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::pushExpression", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::pushPattern( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushPattern);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::pushPattern");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::pushPattern", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::attachVariable( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::attachVariable");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::attachVariable", err.what());
	return void();
}
}

void PatternMatcherInstanceImpl::definePattern( const std::string& p1, const std::string& p2, bool p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePattern);
	msg.packString( p1);
	msg.packString( p2);
	msg.packBool( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::definePattern");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::definePattern", err.what());
	return void();
}
}

bool PatternMatcherInstanceImpl::compile( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compile);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::compile", err.what());
	return false;
}
}

PatternMatcherContextInterface* PatternMatcherInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternMatcherContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternMatcherContextInterface* p0 = new PatternMatcherContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::createContext", err.what());
	return 0;
}
}

analyzer::FunctionView PatternMatcherInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

PatternMatcherImpl::~PatternMatcherImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<std::string> PatternMatcherImpl::getCompileOptionNames( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getCompileOptionNames);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherImpl::getCompileOptionNames");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherImpl::getCompileOptionNames", err.what());
	return std::vector<std::string>();
}
}

PatternMatcherInstanceInterface* PatternMatcherImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternMatcherInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternMatcherInstanceInterface* p0 = new PatternMatcherInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherImpl::createInstance", err.what());
	return 0;
}
}

const char* PatternMatcherImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternMatcherImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternMatcherImpl::getDescription", err.what());
	return 0;
}
}

PatternTermFeederInstanceImpl::~PatternTermFeederInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PatternTermFeederInstanceImpl::defineLexem( unsigned int p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineLexem);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::defineLexem");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::defineLexem", err.what());
	return void();
}
}

void PatternTermFeederInstanceImpl::defineSymbol( unsigned int p1, unsigned int p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSymbol);
	msg.packUint( p1);
	msg.packUint( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::defineSymbol");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::defineSymbol", err.what());
	return void();
}
}

unsigned int PatternTermFeederInstanceImpl::getLexem( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getLexem);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::getLexem");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::getLexem", err.what());
	return 0;
}
}

std::vector<std::string> PatternTermFeederInstanceImpl::lexemTypes( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_lexemTypes);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::lexemTypes");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::lexemTypes", err.what());
	return std::vector<std::string>();
}
}

unsigned int PatternTermFeederInstanceImpl::getSymbol( unsigned int p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSymbol);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::getSymbol");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::getSymbol", err.what());
	return 0;
}
}

analyzer::FunctionView PatternTermFeederInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

PatternTermFeederImpl::~PatternTermFeederImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PatternTermFeederInstanceInterface* PatternTermFeederImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternTermFeederInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternTermFeederInstanceInterface* p0 = new PatternTermFeederInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PatternTermFeederImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PatternTermFeederImpl::createInstance", err.what());
	return 0;
}
}

PosTaggerContextImpl::~PosTaggerContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string PosTaggerContextImpl::markupDocument( int p1, const analyzer::DocumentClass& p2, const std::string& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_markupDocument);
	msg.packInt( p1);
	msg.packDocumentClass( p2);
	msg.packString( p3);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerContextImpl::markupDocument");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerContextImpl::markupDocument", err.what());
	return std::string();
}
}

PosTaggerDataImpl::~PosTaggerDataImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PosTaggerDataImpl::declareIgnoredToken( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_declareIgnoredToken);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerDataImpl::declareIgnoredToken");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerDataImpl::declareIgnoredToken", err.what());
	return void();
}
}

void PosTaggerDataImpl::insert( int p1, const std::vector<PosTaggerDataInterface::Element>& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_insert);
	msg.packInt( p1);
	msg.packSize( p2.size());
	for (unsigned int ii=0; ii < p2.size(); ++ii) {
		msg.packPosTaggerDataElement( p2[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerDataImpl::insert");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerDataImpl::insert", err.what());
	return void();
}
}

void PosTaggerDataImpl::markupSegment( TokenMarkupContextInterface* p1, int p2, int& p3, const SegmenterPosition& p4, const char* p5, std::size_t p6) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_markupSegment);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenMarkupContext");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packInt( p2);
	msg.packGlobalCounter( p4);
	msg.packBuffer( p5, p6);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	p3 = serializedMsg.unpackInt();
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerDataImpl::markupSegment");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerDataImpl::markupSegment", err.what());
	return void();
}
}

PosTaggerInstanceImpl::~PosTaggerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PosTaggerInstanceImpl::addContentExpression( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addContentExpression);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerInstanceImpl::addContentExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerInstanceImpl::addContentExpression", err.what());
	return void();
}
}

void PosTaggerInstanceImpl::addPosTaggerInputPunctuation( const std::string& p1, const std::string& p2, int p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addPosTaggerInputPunctuation);
	msg.packString( p1);
	msg.packString( p2);
	msg.packInt( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerInstanceImpl::addPosTaggerInputPunctuation");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerInstanceImpl::addPosTaggerInputPunctuation", err.what());
	return void();
}
}

std::string PosTaggerInstanceImpl::getPosTaggerInput( const analyzer::DocumentClass& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPosTaggerInput);
	msg.packDocumentClass( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerInstanceImpl::getPosTaggerInput");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerInstanceImpl::getPosTaggerInput", err.what());
	return std::string();
}
}

std::string PosTaggerInstanceImpl::markupDocument( const PosTaggerDataInterface* p1, int p2, const analyzer::DocumentClass& p3, const std::string& p4) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_markupDocument);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PosTaggerData");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packInt( p2);
	msg.packDocumentClass( p3);
	msg.packString( p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerInstanceImpl::markupDocument");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerInstanceImpl::markupDocument", err.what());
	return std::string();
}
}

PosTaggerImpl::~PosTaggerImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PosTaggerInstanceInterface* PosTaggerImpl::createInstance( const SegmenterInterface* p1, const analyzer::SegmenterOptions& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Segmenter");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packSegmenterOptions( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PosTaggerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PosTaggerInstanceInterface* p0 = new PosTaggerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PosTaggerImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PosTaggerImpl::createInstance", err.what());
	return 0;
}
}

PostingIteratorImpl::~PostingIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index PostingIteratorImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipDoc", err.what());
	return 0;
}
}

Index PostingIteratorImpl::skipDocCandidate( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDocCandidate);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipDocCandidate");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipDocCandidate", err.what());
	return 0;
}
}

Index PostingIteratorImpl::skipPos( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipPos");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipPos", err.what());
	return 0;
}
}

const char* PostingIteratorImpl::featureid( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureid);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::featureid");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::featureid", err.what());
	return 0;
}
}

Index PostingIteratorImpl::documentFrequency( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::documentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::documentFrequency", err.what());
	return 0;
}
}

unsigned int PostingIteratorImpl::frequency( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_frequency);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::frequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::frequency", err.what());
	return 0;
}
}

Index PostingIteratorImpl::docno( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_docno);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::docno");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::docno", err.what());
	return 0;
}
}

Index PostingIteratorImpl::posno( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_posno);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::posno");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::posno", err.what());
	return 0;
}
}

Index PostingIteratorImpl::length( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_length);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingIteratorImpl::length");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingIteratorImpl::length", err.what());
	return 0;
}
}

PostingJoinOperatorImpl::~PostingJoinOperatorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PostingIteratorInterface* PostingJoinOperatorImpl::createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2, unsigned int p3) const
{
	errorhnd()->report( ErrorCodeNotImplemented, _TXT("the method '%s' is not implemented for RPC"),"createResultIterator");
	return 0;
}

const char* PostingJoinOperatorImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingJoinOperatorImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingJoinOperatorImpl::name", err.what());
	return 0;
}
}

StructView PostingJoinOperatorImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "PostingJoinOperatorImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "PostingJoinOperatorImpl::view", err.what());
	return StructView();
}
}

QueryAnalyzerContextImpl::~QueryAnalyzerContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryAnalyzerContextImpl::putField( int p1, const std::string& p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putField);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerContextImpl::putField");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerContextImpl::putField", err.what());
	return void();
}
}

void QueryAnalyzerContextImpl::groupElements( int p1, const std::vector<int>& p2, const QueryAnalyzerContextInterface::GroupBy& p3, bool p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_groupElements);
	msg.packInt( p1);
	msg.packSize( p2.size());
	for (unsigned int ii=0; ii < p2.size(); ++ii) {
		msg.packInt( p2[ii]);
	}
	msg.packAnalyzerGroupBy( p3);
	msg.packBool( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerContextImpl::groupElements");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerContextImpl::groupElements", err.what());
	return void();
}
}

analyzer::QueryTermExpression QueryAnalyzerContextImpl::analyze( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::QueryTermExpression p0 = serializedMsg.unpackAnalyzerQueryTermExpression();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerContextImpl::analyze");
	return analyzer::QueryTermExpression();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerContextImpl::analyze", err.what());
	return analyzer::QueryTermExpression();
}
}

QueryAnalyzerInstanceImpl::~QueryAnalyzerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryAnalyzerInstanceImpl::addElement( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, int p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packInt( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::addElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::addElement", err.what());
	return void();
}
}

void QueryAnalyzerInstanceImpl::addPatternLexem( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, int p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addPatternLexem);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_4->classId(), impl_4->objId());
	}
	msg.packInt( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3);
	done_3->release();
	delete p3;
	for (std::size_t ai_4=0; ai_4 < p4.size(); ++ai_4) {
		RpcInterfaceStub* done_4 = dynamic_cast<RpcInterfaceStub*>(p4[ai_4]);
		done_4->release();
		delete p4[ai_4];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::addPatternLexem");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::addPatternLexem", err.what());
	return void();
}
}

void QueryAnalyzerInstanceImpl::defineTokenPatternMatcher( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternTermFeederInstanceInterface* p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenPatternMatcher);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternMatcherInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternTermFeederInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::defineTokenPatternMatcher");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::defineTokenPatternMatcher", err.what());
	return void();
}
}

void QueryAnalyzerInstanceImpl::defineContentPatternMatcher( const std::string& p1, PatternMatcherInstanceInterface* p2, PatternLexerInstanceInterface* p3, const std::vector<std::string>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineContentPatternMatcher);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternMatcherInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternLexerInstance");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packString( p4[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::defineContentPatternMatcher");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::defineContentPatternMatcher", err.what());
	return void();
}
}

void QueryAnalyzerInstanceImpl::addElementFromPatternMatch( const std::string& p1, const std::string& p2, const std::vector<NormalizerFunctionInstanceInterface*>& p3, int p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElementFromPatternMatch);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3[ii]);
		if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunctionInstance");
		msg.packObject( impl_3->classId(), impl_3->objId());
	}
	msg.packInt( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	for (std::size_t ai_3=0; ai_3 < p3.size(); ++ai_3) {
		RpcInterfaceStub* done_3 = dynamic_cast<RpcInterfaceStub*>(p3[ai_3]);
		done_3->release();
		delete p3[ai_3];
	}
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::addElementFromPatternMatch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::addElementFromPatternMatch", err.what());
	return void();
}
}

std::vector<std::string> QueryAnalyzerInstanceImpl::queryTermTypes( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_queryTermTypes);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::queryTermTypes");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::queryTermTypes", err.what());
	return std::vector<std::string>();
}
}

std::vector<std::string> QueryAnalyzerInstanceImpl::queryFieldTypes( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_queryFieldTypes);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::queryFieldTypes");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::queryFieldTypes", err.what());
	return std::vector<std::string>();
}
}

QueryAnalyzerContextInterface* QueryAnalyzerInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryAnalyzerContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryAnalyzerContextInterface* p0 = new QueryAnalyzerContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::createContext", err.what());
	return 0;
}
}

analyzer::QueryAnalyzerView QueryAnalyzerInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::QueryAnalyzerView p0 = serializedMsg.unpackAnalyzerQueryAnalyzerView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryAnalyzerInstanceImpl::view");
	return analyzer::QueryAnalyzerView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryAnalyzerInstanceImpl::view", err.what());
	return analyzer::QueryAnalyzerView();
}
}

QueryEvalImpl::~QueryEvalImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryEvalImpl::addTerm( const std::string& p1, const std::string& p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addTerm", err.what());
	return void();
}
}

void QueryEvalImpl::addSelectionFeature( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectionFeature);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addSelectionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addSelectionFeature", err.what());
	return void();
}
}

void QueryEvalImpl::addRestrictionFeature( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addRestrictionFeature);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addRestrictionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addRestrictionFeature", err.what());
	return void();
}
}

void QueryEvalImpl::addExclusionFeature( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addExclusionFeature);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addExclusionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addExclusionFeature", err.what());
	return void();
}
}

std::vector<std::string> QueryEvalImpl::getWeightingFeatureSets( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWeightingFeatureSets);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::getWeightingFeatureSets");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::getWeightingFeatureSets", err.what());
	return std::vector<std::string>();
}
}

std::vector<std::string> QueryEvalImpl::getSelectionFeatureSets( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSelectionFeatureSets);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::getSelectionFeatureSets");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::getSelectionFeatureSets", err.what());
	return std::vector<std::string>();
}
}

std::vector<std::string> QueryEvalImpl::getRestrictionFeatureSets( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getRestrictionFeatureSets);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::getRestrictionFeatureSets");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::getRestrictionFeatureSets", err.what());
	return std::vector<std::string>();
}
}

std::vector<std::string> QueryEvalImpl::getExclusionFeatureSets( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getExclusionFeatureSets);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::getExclusionFeatureSets");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::getExclusionFeatureSets", err.what());
	return std::vector<std::string>();
}
}

void QueryEvalImpl::addSummarizerFunction( const std::string& p1, SummarizerFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3, const std::string& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizerFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "SummarizerFunctionInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packFeatureParameter( p3[ii]);
	}
	msg.packString( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addSummarizerFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addSummarizerFunction", err.what());
	return void();
}
}

void QueryEvalImpl::addWeightingFunction( const std::string& p1, WeightingFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3, const std::string& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addWeightingFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "WeightingFunctionInstance");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packFeatureParameter( p3[ii]);
	}
	msg.packString( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::addWeightingFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::addWeightingFunction", err.what());
	return void();
}
}

void QueryEvalImpl::defineWeightingFormula( ScalarFunctionInterface* p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWeightingFormula);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "ScalarFunction");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_1 = dynamic_cast<RpcInterfaceStub*>(p1);
	done_1->release();
	delete p1;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::defineWeightingFormula");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::defineWeightingFormula", err.what());
	return void();
}
}

QueryInterface* QueryEvalImpl::createQuery( const StorageClientInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQuery);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "StorageClient");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Query;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryInterface* p0 = new QueryImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::createQuery");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::createQuery", err.what());
	return 0;
}
}

StructView QueryEvalImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryEvalImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryEvalImpl::view", err.what());
	return StructView();
}
}

QueryImpl::~QueryImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::pushTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::pushTerm", err.what());
	return void();
}
}

void QueryImpl::pushDocField( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushDocField);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::pushDocField");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::pushDocField", err.what());
	return void();
}
}

void QueryImpl::pushExpression( const PostingJoinOperatorInterface* p1, unsigned int p2, int p3, unsigned int p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PostingJoinOperator");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packUint( p2);
	msg.packInt( p3);
	msg.packUint( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::pushExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::pushExpression", err.what());
	return void();
}
}

void QueryImpl::attachVariable( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::attachVariable");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::attachVariable", err.what());
	return void();
}
}

void QueryImpl::defineFeature( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::defineFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::defineFeature", err.what());
	return void();
}
}

void QueryImpl::defineTermStatistics( const std::string& p1, const std::string& p2, const TermStatistics& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTermStatistics);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTermStatistics( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::defineTermStatistics");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::defineTermStatistics", err.what());
	return void();
}
}

void QueryImpl::defineGlobalStatistics( const GlobalStatistics& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineGlobalStatistics);
	msg.packGlobalStatistics( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::defineGlobalStatistics");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::defineGlobalStatistics", err.what());
	return void();
}
}

void QueryImpl::addMetaDataRestrictionCondition( const MetaDataRestrictionInterface::CompareOperator& p1, const std::string& p2, const NumericVariant& p3, bool p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addMetaDataRestrictionCondition);
	msg.packMetaDataRestrictionCompareOperator( p1);
	msg.packString( p2);
	msg.packNumericVariant( p3);
	msg.packBool( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::addMetaDataRestrictionCondition");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::addMetaDataRestrictionCondition", err.what());
	return void();
}
}

void QueryImpl::addDocumentEvaluationSet( const std::vector<Index>& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addDocumentEvaluationSet);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packIndex( p1[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::addDocumentEvaluationSet");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::addDocumentEvaluationSet", err.what());
	return void();
}
}

void QueryImpl::addAccess( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addAccess);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::addAccess");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::addAccess", err.what());
	return void();
}
}

void QueryImpl::setMaxNofRanks( std::size_t p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMaxNofRanks);
	msg.packSize( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::setMaxNofRanks");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::setMaxNofRanks", err.what());
	return void();
}
}

void QueryImpl::setMinRank( std::size_t p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMinRank);
	msg.packSize( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::setMinRank");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::setMinRank", err.what());
	return void();
}
}

void QueryImpl::setWeightingVariableValue( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setWeightingVariableValue);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::setWeightingVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::setWeightingVariableValue", err.what());
	return void();
}
}

void QueryImpl::setDebugMode( bool p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setDebugMode);
	msg.packBool( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::setDebugMode");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::setDebugMode", err.what());
	return void();
}
}

QueryResult QueryImpl::evaluate( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	QueryResult p0 = serializedMsg.unpackQueryResult();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::evaluate");
	return QueryResult();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::evaluate", err.what());
	return QueryResult();
}
}

StructView QueryImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryImpl::view", err.what());
	return StructView();
}
}

QueryProcessorImpl::~QueryProcessorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string QueryProcessorImpl::getResourceFilePath( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourceFilePath);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getResourceFilePath");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getResourceFilePath", err.what());
	return std::string();
}
}

void QueryProcessorImpl::definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePostingJoinOperator);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PostingJoinOperator");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::definePostingJoinOperator");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::definePostingJoinOperator", err.what());
	return void();
}
}

const PostingJoinOperatorInterface* QueryProcessorImpl::getPostingJoinOperator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPostingJoinOperator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PostingJoinOperator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PostingJoinOperatorImpl const_0( objId_0, ctx(), true, errorhnd());
	const PostingJoinOperatorInterface* p0 = (const PostingJoinOperatorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getPostingJoinOperator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getPostingJoinOperator", err.what());
	return 0;
}
}

void QueryProcessorImpl::defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWeightingFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "WeightingFunction");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineWeightingFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineWeightingFunction", err.what());
	return void();
}
}

const WeightingFunctionInterface* QueryProcessorImpl::getWeightingFunction( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWeightingFunction);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingFunctionImpl const_0( objId_0, ctx(), true, errorhnd());
	const WeightingFunctionInterface* p0 = (const WeightingFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getWeightingFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getWeightingFunction", err.what());
	return 0;
}
}

void QueryProcessorImpl::defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSummarizerFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "SummarizerFunction");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineSummarizerFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineSummarizerFunction", err.what());
	return void();
}
}

const SummarizerFunctionInterface* QueryProcessorImpl::getSummarizerFunction( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummarizerFunction);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerFunctionImpl const_0( objId_0, ctx(), true, errorhnd());
	const SummarizerFunctionInterface* p0 = (const SummarizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getSummarizerFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getSummarizerFunction", err.what());
	return 0;
}
}

std::vector<std::string> QueryProcessorImpl::getFunctionList( const QueryProcessorInterface::FunctionType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getFunctionList);
	msg.packQueryProcessorFunctionType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getFunctionList");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getFunctionList", err.what());
	return std::vector<std::string>();
}
}

void QueryProcessorImpl::defineScalarFunctionParser( const std::string& p1, ScalarFunctionParserInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineScalarFunctionParser);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "ScalarFunctionParser");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineScalarFunctionParser");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineScalarFunctionParser", err.what());
	return void();
}
}

const ScalarFunctionParserInterface* QueryProcessorImpl::getScalarFunctionParser( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getScalarFunctionParser);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ScalarFunctionParser;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ScalarFunctionParserImpl const_0( objId_0, ctx(), true, errorhnd());
	const ScalarFunctionParserInterface* p0 = (const ScalarFunctionParserImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getScalarFunctionParser");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "QueryProcessorImpl::getScalarFunctionParser", err.what());
	return 0;
}
}

ScalarFunctionInstanceImpl::~ScalarFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ScalarFunctionInstanceImpl::setVariableValue( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setVariableValue);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::setVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::setVariableValue", err.what());
	return void();
}
}

double ScalarFunctionInstanceImpl::call( const double* p1, unsigned int p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packBufferFloat( p1, p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	double p0 = serializedMsg.unpackDouble();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::call");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::call", err.what());
	return 0;
}
}

const char* ScalarFunctionInstanceImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::name", err.what());
	return 0;
}
}

StructView ScalarFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::view", err.what());
	return StructView();
}
}

ScalarFunctionImpl::~ScalarFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<std::string> ScalarFunctionImpl::getVariables( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getVariables);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::getVariables");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::getVariables", err.what());
	return std::vector<std::string>();
}
}

unsigned int ScalarFunctionImpl::getNofArguments( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNofArguments);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::getNofArguments");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::getNofArguments", err.what());
	return 0;
}
}

void ScalarFunctionImpl::setDefaultVariableValue( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setDefaultVariableValue);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::setDefaultVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::setDefaultVariableValue", err.what());
	return void();
}
}

ScalarFunctionInstanceInterface* ScalarFunctionImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ScalarFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ScalarFunctionInstanceInterface* p0 = new ScalarFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* ScalarFunctionImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::name", err.what());
	return 0;
}
}

StructView ScalarFunctionImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionImpl::view", err.what());
	return StructView();
}
}

ScalarFunctionParserImpl::~ScalarFunctionParserImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

ScalarFunctionInterface* ScalarFunctionParserImpl::createFunction( const std::string& p1, const std::vector<std::string>& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFunction);
	msg.packString( p1);
	msg.packSize( p2.size());
	for (unsigned int ii=0; ii < p2.size(); ++ii) {
		msg.packString( p2[ii]);
	}
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ScalarFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ScalarFunctionInterface* p0 = new ScalarFunctionImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionParserImpl::createFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionParserImpl::createFunction", err.what());
	return 0;
}
}

const char* ScalarFunctionParserImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ScalarFunctionParserImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ScalarFunctionParserImpl::getDescription", err.what());
	return 0;
}
}

SegmenterContextImpl::~SegmenterContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SegmenterContextImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterContextImpl::putInput", err.what());
	return void();
}
}

bool SegmenterContextImpl::getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackInt();
	p2 = serializedMsg.unpackGlobalCounter();
	const char* bp3;
	serializedMsg.unpackBuffer( bp3, p4);
	p3 = (const char*) ctx()->constConstructor()->get( bp3, p4);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterContextImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterContextImpl::getNext", err.what());
	return false;
}
}

SegmenterInstanceImpl::~SegmenterInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SegmenterInstanceImpl::defineSelectorExpression( int p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSelectorExpression);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::defineSelectorExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::defineSelectorExpression", err.what());
	return void();
}
}

void SegmenterInstanceImpl::defineSubSection( int p1, int p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubSection);
	msg.packInt( p1);
	msg.packInt( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::defineSubSection");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::defineSubSection", err.what());
	return void();
}
}

SegmenterContextInterface* SegmenterInstanceImpl::createContext( const analyzer::DocumentClass& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	msg.packDocumentClass( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SegmenterContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterContextInterface* p0 = new SegmenterContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::createContext", err.what());
	return 0;
}
}

SegmenterMarkupContextInterface* SegmenterInstanceImpl::createMarkupContext( const analyzer::DocumentClass& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMarkupContext);
	msg.packDocumentClass( p1);
	msg.packString( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SegmenterMarkupContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterMarkupContextInterface* p0 = new SegmenterMarkupContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::createMarkupContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::createMarkupContext", err.what());
	return 0;
}
}

analyzer::FunctionView SegmenterInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

SegmenterImpl::~SegmenterImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const char* SegmenterImpl::mimeType( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_mimeType);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterImpl::mimeType");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterImpl::mimeType", err.what());
	return 0;
}
}

SegmenterInstanceInterface* SegmenterImpl::createInstance( const analyzer::SegmenterOptions& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSegmenterOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SegmenterInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterInstanceInterface* p0 = new SegmenterInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterImpl::createInstance", err.what());
	return 0;
}
}

ContentIteratorInterface* SegmenterImpl::createContentIterator( const char* p1, std::size_t p2, const std::vector<std::string>& p3, const std::vector<std::string>& p4, const analyzer::DocumentClass& p5, const analyzer::SegmenterOptions& p6) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContentIterator);
	msg.packBuffer( p1, p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packString( p3[ii]);
	}
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packString( p4[ii]);
	}
	msg.packDocumentClass( p5);
	msg.packSegmenterOptions( p6);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ContentIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ContentIteratorInterface* p0 = new ContentIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterImpl::createContentIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterImpl::createContentIterator", err.what());
	return 0;
}
}

const char* SegmenterImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterImpl::getDescription", err.what());
	return 0;
}
}

SegmenterMarkupContextImpl::~SegmenterMarkupContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool SegmenterMarkupContextImpl::getNext( SegmenterPosition& p1, const char*& p2, std::size_t& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackGlobalCounter();
	const char* bp2;
	serializedMsg.unpackBuffer( bp2, p3);
	p2 = (const char*) ctx()->constConstructor()->get( bp2, p3);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::getNext", err.what());
	return false;
}
}

unsigned int SegmenterMarkupContextImpl::segmentSize( const SegmenterPosition& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_segmentSize);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::segmentSize");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::segmentSize", err.what());
	return 0;
}
}

std::string SegmenterMarkupContextImpl::tagName( const SegmenterPosition& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tagName);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::tagName");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::tagName", err.what());
	return std::string();
}
}

int SegmenterMarkupContextImpl::tagLevel( const SegmenterPosition& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tagLevel);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::tagLevel");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::tagLevel", err.what());
	return 0;
}
}

void SegmenterMarkupContextImpl::putOpenTag( const SegmenterPosition& p1, std::size_t p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putOpenTag);
	msg.packGlobalCounter( p1);
	msg.packSize( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putOpenTag");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putOpenTag", err.what());
	return void();
}
}

void SegmenterMarkupContextImpl::putAttribute( const SegmenterPosition& p1, std::size_t p2, const std::string& p3, const std::string& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putAttribute);
	msg.packGlobalCounter( p1);
	msg.packSize( p2);
	msg.packString( p3);
	msg.packString( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putAttribute", err.what());
	return void();
}
}

void SegmenterMarkupContextImpl::putCloseTag( const SegmenterPosition& p1, std::size_t p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putCloseTag);
	msg.packGlobalCounter( p1);
	msg.packSize( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putCloseTag");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putCloseTag", err.what());
	return void();
}
}

std::string SegmenterMarkupContextImpl::getContent( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getContent);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::getContent");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::getContent", err.what());
	return std::string();
}
}

SentenceAnalyzerInstanceImpl::~SentenceAnalyzerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SentenceAnalyzerInstanceImpl::pushTerm( const std::string& p1, const std::string& p2, float p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packFloat( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::pushTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::pushTerm", err.what());
	return void();
}
}

void SentenceAnalyzerInstanceImpl::pushNone( float p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushNone);
	msg.packFloat( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::pushNone");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::pushNone", err.what());
	return void();
}
}

void SentenceAnalyzerInstanceImpl::pushAlt( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushAlt);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::pushAlt");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::pushAlt", err.what());
	return void();
}
}

void SentenceAnalyzerInstanceImpl::pushSequenceImm( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushSequenceImm);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::pushSequenceImm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::pushSequenceImm", err.what());
	return void();
}
}

void SentenceAnalyzerInstanceImpl::pushRepeat( int p1, int p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushRepeat);
	msg.packInt( p1);
	msg.packInt( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::pushRepeat");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::pushRepeat", err.what());
	return void();
}
}

void SentenceAnalyzerInstanceImpl::defineSentence( const std::string& p1, float p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSentence);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::defineSentence");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::defineSentence", err.what());
	return void();
}
}

bool SentenceAnalyzerInstanceImpl::compile( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compile);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::compile", err.what());
	return false;
}
}

std::vector<SentenceGuess> SentenceAnalyzerInstanceImpl::analyzeSentence( const SentenceLexerInstanceInterface* p1, const std::string& p2, int p3, double p4) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeSentence);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "SentenceLexerInstance");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packString( p2);
	msg.packInt( p3);
	msg.packDouble( p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<SentenceGuess> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		SentenceGuess elem_p0 = serializedMsg.unpackSentenceGuess();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceAnalyzerInstanceImpl::analyzeSentence");
	return std::vector<SentenceGuess>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceAnalyzerInstanceImpl::analyzeSentence", err.what());
	return std::vector<SentenceGuess>();
}
}

SentenceLexerContextImpl::~SentenceLexerContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool SentenceLexerContextImpl::fetchFirstSplit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetchFirstSplit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::fetchFirstSplit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::fetchFirstSplit", err.what());
	return false;
}
}

bool SentenceLexerContextImpl::fetchNextSplit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetchNextSplit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::fetchNextSplit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::fetchNextSplit", err.what());
	return false;
}
}

int SentenceLexerContextImpl::nofTokens( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofTokens);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::nofTokens");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::nofTokens", err.what());
	return 0;
}
}

std::string SentenceLexerContextImpl::featureValue( int p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureValue);
	msg.packInt( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::featureValue");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::featureValue", err.what());
	return std::string();
}
}

std::vector<std::string> SentenceLexerContextImpl::featureTypes( int p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureTypes);
	msg.packInt( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::featureTypes");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::featureTypes", err.what());
	return std::vector<std::string>();
}
}

std::vector<SentenceGuess> SentenceLexerContextImpl::rankSentences( const std::vector<SentenceGuess>& p1, int p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rankSentences);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packSentenceGuess( p1[ii]);
	}
	msg.packInt( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<SentenceGuess> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		SentenceGuess elem_p0 = serializedMsg.unpackSentenceGuess();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerContextImpl::rankSentences");
	return std::vector<SentenceGuess>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerContextImpl::rankSentences", err.what());
	return std::vector<SentenceGuess>();
}
}

SentenceLexerInstanceImpl::~SentenceLexerInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SentenceLexerInstanceImpl::addSeparator( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSeparator);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerInstanceImpl::addSeparator");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerInstanceImpl::addSeparator", err.what());
	return void();
}
}

void SentenceLexerInstanceImpl::addSpace( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSpace);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerInstanceImpl::addSpace");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerInstanceImpl::addSpace", err.what());
	return void();
}
}

void SentenceLexerInstanceImpl::addLink( int p1, char p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addLink);
	msg.packInt( p1);
	msg.packByte( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerInstanceImpl::addLink");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerInstanceImpl::addLink", err.what());
	return void();
}
}

void SentenceLexerInstanceImpl::defineGroupSimilarityDistance( double p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineGroupSimilarityDistance);
	msg.packDouble( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerInstanceImpl::defineGroupSimilarityDistance");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerInstanceImpl::defineGroupSimilarityDistance", err.what());
	return void();
}
}

SentenceLexerContextInterface* SentenceLexerInstanceImpl::createContext( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SentenceLexerContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SentenceLexerContextInterface* p0 = new SentenceLexerContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SentenceLexerInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SentenceLexerInstanceImpl::createContext", err.what());
	return 0;
}
}

StatisticsBuilderImpl::~StatisticsBuilderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StatisticsBuilderImpl::addNofDocumentsInsertedChange( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::addNofDocumentsInsertedChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::addNofDocumentsInsertedChange", err.what());
	return void();
}
}

void StatisticsBuilderImpl::addDfChange( const char* p1, const char* p2, int p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addDfChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packInt( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::addDfChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::addDfChange", err.what());
	return void();
}
}

StatisticsIteratorInterface* StatisticsBuilderImpl::createIteratorAndRollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createIteratorAndRollback);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::createIteratorAndRollback");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::createIteratorAndRollback", err.what());
	return 0;
}
}

bool StatisticsBuilderImpl::commit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::commit", err.what());
	return false;
}
}

void StatisticsBuilderImpl::rollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::rollback", err.what());
	return void();
}
}

void StatisticsBuilderImpl::releaseStatistics( const TimeStamp& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_releaseStatistics);
	msg.packTimeStamp( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::releaseStatistics");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::releaseStatistics", err.what());
	return void();
}
}

StatisticsIteratorImpl::~StatisticsIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StatisticsMessage StatisticsIteratorImpl::getNext( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StatisticsMessage p0 = serializedMsg.unpackStatisticsMessage();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsIteratorImpl::getNext");
	return StatisticsMessage();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsIteratorImpl::getNext", err.what());
	return StatisticsMessage();
}
}

StatisticsMapImpl::~StatisticsMapImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StatisticsMapImpl::addNofDocumentsInsertedChange( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsMapImpl::addNofDocumentsInsertedChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsMapImpl::addNofDocumentsInsertedChange", err.what());
	return void();
}
}

void StatisticsMapImpl::addDfChange( const char* p1, const char* p2, int p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addDfChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packInt( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsMapImpl::addDfChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsMapImpl::addDfChange", err.what());
	return void();
}
}

bool StatisticsMapImpl::processStatisticsMessage( const void* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_processStatisticsMessage);
	msg.packBuffer( (const char*)p1, p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsMapImpl::processStatisticsMessage");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsMapImpl::processStatisticsMessage", err.what());
	return false;
}
}

GlobalCounter StatisticsMapImpl::nofDocuments( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofDocuments);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsMapImpl::nofDocuments");
	return GlobalCounter();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsMapImpl::nofDocuments", err.what());
	return GlobalCounter();
}
}

GlobalCounter StatisticsMapImpl::df( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_df);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsMapImpl::df");
	return GlobalCounter();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsMapImpl::df", err.what());
	return GlobalCounter();
}
}

StatisticsProcessorImpl::~StatisticsProcessorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StatisticsViewerInterface* StatisticsProcessorImpl::createViewer( const void* p1, std::size_t p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createViewer);
	msg.packBuffer( (const char*)p1, p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsViewer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsViewerInterface* p0 = new StatisticsViewerImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createViewer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createViewer", err.what());
	return 0;
}
}

StatisticsIteratorInterface* StatisticsProcessorImpl::createIterator( const std::string& p1, const TimeStamp& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createIterator);
	msg.packString( p1);
	msg.packTimeStamp( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createIterator", err.what());
	return 0;
}
}

std::vector<TimeStamp> StatisticsProcessorImpl::getChangeTimeStamps( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getChangeTimeStamps);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<TimeStamp> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		TimeStamp elem_p0 = serializedMsg.unpackTimeStamp();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::getChangeTimeStamps");
	return std::vector<TimeStamp>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::getChangeTimeStamps", err.what());
	return std::vector<TimeStamp>();
}
}

StatisticsMessage StatisticsProcessorImpl::loadChangeMessage( const std::string& p1, const TimeStamp& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_loadChangeMessage);
	msg.packString( p1);
	msg.packTimeStamp( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StatisticsMessage p0 = serializedMsg.unpackStatisticsMessage();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::loadChangeMessage");
	return StatisticsMessage();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::loadChangeMessage", err.what());
	return StatisticsMessage();
}
}

StatisticsBuilderInterface* StatisticsProcessorImpl::createBuilder( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBuilder);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsBuilder;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsBuilderInterface* p0 = new StatisticsBuilderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createBuilder");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createBuilder", err.what());
	return 0;
}
}

StatisticsMapInterface* StatisticsProcessorImpl::createMap( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMap);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsMap;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsMapInterface* p0 = new StatisticsMapImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createMap");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createMap", err.what());
	return 0;
}
}

StatisticsViewerImpl::~StatisticsViewerImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

int StatisticsViewerImpl::nofDocumentsInsertedChange( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofDocumentsInsertedChange);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsViewerImpl::nofDocumentsInsertedChange");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsViewerImpl::nofDocumentsInsertedChange", err.what());
	return 0;
}
}

bool StatisticsViewerImpl::nextDfChange( TermStatisticsChange& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextDfChange);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackTermStatisticsChange();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StatisticsViewerImpl::nextDfChange");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StatisticsViewerImpl::nextDfChange", err.what());
	return false;
}
}

StorageAlterMetaDataTableImpl::~StorageAlterMetaDataTableImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::addElement( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::addElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::addElement", err.what());
	return void();
}
}

void StorageAlterMetaDataTableImpl::alterElement( const std::string& p1, const std::string& p2, const std::string& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_alterElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::alterElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::alterElement", err.what());
	return void();
}
}

void StorageAlterMetaDataTableImpl::renameElement( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_renameElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::renameElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::renameElement", err.what());
	return void();
}
}

void StorageAlterMetaDataTableImpl::deleteElement( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteElement);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::deleteElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::deleteElement", err.what());
	return void();
}
}

void StorageAlterMetaDataTableImpl::clearElement( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearElement);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::clearElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::clearElement", err.what());
	return void();
}
}

bool StorageAlterMetaDataTableImpl::commit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::commit", err.what());
	return false;
}
}

void StorageAlterMetaDataTableImpl::rollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::rollback", err.what());
	return void();
}
}

StorageClientImpl::~StorageClientImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string StorageClientImpl::config( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_config);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::config");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::config", err.what());
	return std::string();
}
}

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2, const Index& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermPostingIterator);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PostingIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermPostingIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createTermPostingIterator", err.what());
	return 0;
}
}

StructIteratorInterface* StorageClientImpl::createStructIterator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStructIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StructIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StructIteratorInterface* p0 = new StructIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createStructIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createStructIterator", err.what());
	return 0;
}
}

PostingIteratorInterface* StorageClientImpl::createBrowsePostingIterator( const MetaDataRestrictionInterface* p1, const Index& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBrowsePostingIterator);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "MetaDataRestriction");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packIndex( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PostingIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createBrowsePostingIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createBrowsePostingIterator", err.what());
	return 0;
}
}

PostingIteratorInterface* StorageClientImpl::createFieldPostingIterator( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFieldPostingIterator);
	msg.packString( p1);
	msg.packString( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PostingIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createFieldPostingIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createFieldPostingIterator", err.what());
	return 0;
}
}

ForwardIteratorInterface* StorageClientImpl::createForwardIterator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createForwardIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ForwardIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ForwardIteratorInterface* p0 = new ForwardIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createForwardIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createForwardIterator", err.what());
	return 0;
}
}

DocumentTermIteratorInterface* StorageClientImpl::createDocumentTermIterator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentTermIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentTermIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentTermIteratorInterface* p0 = new DocumentTermIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocumentTermIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createDocumentTermIterator", err.what());
	return 0;
}
}

InvAclIteratorInterface* StorageClientImpl::createInvAclIterator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInvAclIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_InvAclIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	InvAclIteratorInterface* p0 = new InvAclIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createInvAclIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createInvAclIterator", err.what());
	return 0;
}
}

AclReaderInterface* StorageClientImpl::createAclReader( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAclReader);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_AclReader;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	AclReaderInterface* p0 = new AclReaderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createAclReader");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createAclReader", err.what());
	return 0;
}
}

Index StorageClientImpl::nofDocumentsInserted( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofDocumentsInserted);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::nofDocumentsInserted");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::nofDocumentsInserted", err.what());
	return 0;
}
}

Index StorageClientImpl::documentFrequency( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::documentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::documentFrequency", err.what());
	return 0;
}
}

Index StorageClientImpl::maxDocumentNumber( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_maxDocumentNumber);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::maxDocumentNumber");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::maxDocumentNumber", err.what());
	return 0;
}
}

Index StorageClientImpl::documentNumber( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentNumber);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::documentNumber");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::documentNumber", err.what());
	return 0;
}
}

Index StorageClientImpl::termTypeNumber( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_termTypeNumber);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::termTypeNumber");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::termTypeNumber", err.what());
	return 0;
}
}

bool StorageClientImpl::isForwardIndexTerm( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_isForwardIndexTerm);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::isForwardIndexTerm");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::isForwardIndexTerm", err.what());
	return false;
}
}

ValueIteratorInterface* StorageClientImpl::createTermTypeIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermTypeIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermTypeIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createTermTypeIterator", err.what());
	return 0;
}
}

ValueIteratorInterface* StorageClientImpl::createStructTypeIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStructTypeIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createStructTypeIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createStructTypeIterator", err.what());
	return 0;
}
}

ValueIteratorInterface* StorageClientImpl::createTermValueIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermValueIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermValueIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createTermValueIterator", err.what());
	return 0;
}
}

ValueIteratorInterface* StorageClientImpl::createDocIdIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocIdIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocIdIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createDocIdIterator", err.what());
	return 0;
}
}

ValueIteratorInterface* StorageClientImpl::createUserNameIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createUserNameIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createUserNameIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createUserNameIterator", err.what());
	return 0;
}
}

Index StorageClientImpl::documentStatistics( const Index& p1, const StorageClientInterface::DocumentStatisticsType& p2, const std::string& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentStatistics);
	msg.packIndex( p1);
	msg.packDocumentStatisticsType( p2);
	msg.packString( p3);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::documentStatistics");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::documentStatistics", err.what());
	return 0;
}
}

MetaDataReaderInterface* StorageClientImpl::createMetaDataReader( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataReader);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_MetaDataReader;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	MetaDataReaderInterface* p0 = new MetaDataReaderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createMetaDataReader");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createMetaDataReader", err.what());
	return 0;
}
}

MetaDataRestrictionInterface* StorageClientImpl::createMetaDataRestriction( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataRestriction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_MetaDataRestriction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	MetaDataRestrictionInterface* p0 = new MetaDataRestrictionImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createMetaDataRestriction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createMetaDataRestriction", err.what());
	return 0;
}
}

AttributeReaderInterface* StorageClientImpl::createAttributeReader( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAttributeReader);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_AttributeReader;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	AttributeReaderInterface* p0 = new AttributeReaderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createAttributeReader");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createAttributeReader", err.what());
	return 0;
}
}

StorageTransactionInterface* StorageClientImpl::createTransaction( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageTransactionInterface* p0 = new StorageTransactionImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createTransaction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createTransaction", err.what());
	return 0;
}
}

StatisticsIteratorInterface* StorageClientImpl::createAllStatisticsIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAllStatisticsIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createAllStatisticsIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createAllStatisticsIterator", err.what());
	return 0;
}
}

StatisticsIteratorInterface* StorageClientImpl::createChangeStatisticsIterator( const TimeStamp& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createChangeStatisticsIterator);
	msg.packTimeStamp( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createChangeStatisticsIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createChangeStatisticsIterator", err.what());
	return 0;
}
}

std::vector<TimeStamp> StorageClientImpl::getChangeStatisticTimeStamps( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getChangeStatisticTimeStamps);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<TimeStamp> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		TimeStamp elem_p0 = serializedMsg.unpackTimeStamp();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::getChangeStatisticTimeStamps");
	return std::vector<TimeStamp>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::getChangeStatisticTimeStamps", err.what());
	return std::vector<TimeStamp>();
}
}

StatisticsMessage StorageClientImpl::loadChangeStatisticsMessage( const TimeStamp& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_loadChangeStatisticsMessage);
	msg.packTimeStamp( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StatisticsMessage p0 = serializedMsg.unpackStatisticsMessage();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::loadChangeStatisticsMessage");
	return StatisticsMessage();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::loadChangeStatisticsMessage", err.what());
	return StatisticsMessage();
}
}

const StatisticsProcessorInterface* StorageClientImpl::getStatisticsProcessor( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getStatisticsProcessor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsProcessorImpl const_0( objId_0, ctx(), true, errorhnd());
	const StatisticsProcessorInterface* p0 = (const StatisticsProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::getStatisticsProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::getStatisticsProcessor", err.what());
	return 0;
}
}

StorageDocumentInterface* StorageClientImpl::createDocumentChecker( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentChecker);
	msg.packString( p1);
	msg.packString( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDocument;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocumentChecker");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::createDocumentChecker", err.what());
	return 0;
}
}

bool StorageClientImpl::checkStorage( std::ostream& p1) const
{
	errorhnd()->report( ErrorCodeNotImplemented, _TXT("the method '%s' is not implemented for RPC"),"checkStorage");
	return false;
}

void StorageClientImpl::close( )
{
try
{
	if (objId() == 0) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::close");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::close", err.what());
	return void();
}
}

void StorageClientImpl::compaction( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compaction);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageClientImpl::compaction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageClientImpl::compaction", err.what());
	return void();
}
}

StorageDocumentImpl::~StorageDocumentImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::addSearchIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::addSearchIndexTerm", err.what());
	return void();
}
}

void StorageDocumentImpl::addSearchIndexStructure( const std::string& p1, const IndexRange& p2, const IndexRange& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexStructure);
	msg.packString( p1);
	msg.packIndexRange( p2);
	msg.packIndexRange( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::addSearchIndexStructure");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::addSearchIndexStructure", err.what());
	return void();
}
}

void StorageDocumentImpl::addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::addForwardIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::addForwardIndexTerm", err.what());
	return void();
}
}

void StorageDocumentImpl::setMetaData( const std::string& p1, const NumericVariant& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packNumericVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::setMetaData", err.what());
	return void();
}
}

void StorageDocumentImpl::setAttribute( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::setAttribute", err.what());
	return void();
}
}

void StorageDocumentImpl::setUserAccessRight( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::setUserAccessRight", err.what());
	return void();
}
}

void StorageDocumentImpl::done( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentImpl::done");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentImpl::done", err.what());
	return void();
}
}

StorageDocumentUpdateImpl::~StorageDocumentUpdateImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentUpdateImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::addSearchIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::addSearchIndexTerm", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::addSearchIndexStructure( const std::string& p1, const IndexRange& p2, const IndexRange& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexStructure);
	msg.packString( p1);
	msg.packIndexRange( p2);
	msg.packIndexRange( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::addSearchIndexStructure");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::addSearchIndexStructure", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::addForwardIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::addForwardIndexTerm", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearSearchIndexTerm( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearSearchIndexTerm);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearSearchIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearSearchIndexTerm", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearSearchIndexStructure( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearSearchIndexStructure);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearSearchIndexStructure");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearSearchIndexStructure", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearForwardIndexTerm( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearForwardIndexTerm);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearForwardIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearForwardIndexTerm", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::setMetaData( const std::string& p1, const NumericVariant& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packNumericVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setMetaData", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::setAttribute( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setAttribute", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearAttribute( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearAttribute);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearAttribute", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::setUserAccessRight( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setUserAccessRight", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearUserAccessRight( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearUserAccessRight", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::clearUserAccessRights( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearUserAccessRights);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearUserAccessRights");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearUserAccessRights", err.what());
	return void();
}
}

void StorageDocumentUpdateImpl::done( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::done");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::done", err.what());
	return void();
}
}

StorageDumpImpl::~StorageDumpImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool StorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageDumpImpl::nextChunk");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageDumpImpl::nextChunk", err.what());
	return false;
}
}

StorageImpl::~StorageImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageClientInterface* StorageImpl::createClient( const std::string& p1, const DatabaseInterface* p2, const StatisticsProcessorInterface* p3) const
{
try
{
	if (p1.empty()) return new StorageClientImpl( 0, ctx(), false, errorhnd());
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "StatisticsProcessor");
	msg.packObject( impl_3->classId(), impl_3->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageClientInterface* p0 = new StorageClientImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::createClient");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::createClient", err.what());
	return 0;
}
}

bool StorageImpl::createStorage( const std::string& p1, const DatabaseInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::createStorage");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::createStorage", err.what());
	return false;
}
}

StorageAlterMetaDataTableInterface* StorageImpl::createAlterMetaDataTable( const std::string& p1, const DatabaseInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::createAlterMetaDataTable");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::createAlterMetaDataTable", err.what());
	return 0;
}
}

const char* StorageImpl::getConfigDescription( const StorageInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::getConfigDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::getConfigDescription", err.what());
	return 0;
}
}

const char** StorageImpl::getConfigParameters( const StorageInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char** p0 =  ctx()->constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::getConfigParameters");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::getConfigParameters", err.what());
	return 0;
}
}

StorageDumpInterface* StorageImpl::createDump( const std::string& p1, const DatabaseInterface* p2, const std::string& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packString( p3);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDump;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDumpInterface* p0 = new StorageDumpImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageImpl::createDump");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageImpl::createDump", err.what());
	return 0;
}
}

StorageObjectBuilderImpl::~StorageObjectBuilderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const StorageInterface* StorageObjectBuilderImpl::getStorage( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getStorage);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Storage;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageImpl const_0( objId_0, ctx(), true, errorhnd());
	const StorageInterface* p0 = (const StorageImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getStorage");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getStorage", err.what());
	return 0;
}
}

const DatabaseInterface* StorageObjectBuilderImpl::getDatabase( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDatabase);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Database;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseImpl const_0( objId_0, ctx(), true, errorhnd());
	const DatabaseInterface* p0 = (const DatabaseImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getDatabase");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getDatabase", err.what());
	return 0;
}
}

const QueryProcessorInterface* StorageObjectBuilderImpl::getQueryProcessor( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getQueryProcessor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryProcessorImpl const_0( objId_0, ctx(), true, errorhnd());
	const QueryProcessorInterface* p0 = (const QueryProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getQueryProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getQueryProcessor", err.what());
	return 0;
}
}

const StatisticsProcessorInterface* StorageObjectBuilderImpl::getStatisticsProcessor( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getStatisticsProcessor);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsProcessorImpl const_0( objId_0, ctx(), true, errorhnd());
	const StatisticsProcessorInterface* p0 = (const StatisticsProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getStatisticsProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getStatisticsProcessor", err.what());
	return 0;
}
}

const VectorStorageInterface* StorageObjectBuilderImpl::getVectorStorage( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getVectorStorage);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorStorage;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorStorageImpl const_0( objId_0, ctx(), true, errorhnd());
	const VectorStorageInterface* p0 = (const VectorStorageImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getVectorStorage");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getVectorStorage", err.what());
	return 0;
}
}

QueryEvalInterface* StorageObjectBuilderImpl::createQueryEval( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryEval);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryEval;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryEvalInterface* p0 = new QueryEvalImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::createQueryEval");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::createQueryEval", err.what());
	return 0;
}
}

SentenceAnalyzerInstanceInterface* StorageObjectBuilderImpl::createSentenceAnalyzer( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createSentenceAnalyzer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SentenceAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SentenceAnalyzerInstanceInterface* p0 = new SentenceAnalyzerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::createSentenceAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::createSentenceAnalyzer", err.what());
	return 0;
}
}

StorageTransactionImpl::~StorageTransactionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageDocumentInterface* StorageTransactionImpl::createDocument( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocument);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDocument;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::createDocument");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::createDocument", err.what());
	return 0;
}
}

StorageDocumentUpdateInterface* StorageTransactionImpl::createDocumentUpdate( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentUpdate);
	msg.packIndex( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDocumentUpdate;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDocumentUpdateInterface* p0 = new StorageDocumentUpdateImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::createDocumentUpdate");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::createDocumentUpdate", err.what());
	return 0;
}
}

void StorageTransactionImpl::deleteDocument( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteDocument);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::deleteDocument");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::deleteDocument", err.what());
	return void();
}
}

void StorageTransactionImpl::deleteUserAccessRights( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteUserAccessRights);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::deleteUserAccessRights");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::deleteUserAccessRights", err.what());
	return void();
}
}

void StorageTransactionImpl::updateMetaData( const Index& p1, const std::string& p2, const NumericVariant& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateMetaData);
	msg.packIndex( p1);
	msg.packString( p2);
	msg.packNumericVariant( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::updateMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::updateMetaData", err.what());
	return void();
}
}

void StorageTransactionImpl::updateDocumentFrequency( const std::string& p1, const std::string& p2, int p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packInt( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::updateDocumentFrequency");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::updateDocumentFrequency", err.what());
	return void();
}
}

bool StorageTransactionImpl::commit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::commit", err.what());
	return false;
}
}

void StorageTransactionImpl::rollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::rollback", err.what());
	return void();
}
}

unsigned int StorageTransactionImpl::nofDocumentsAffected( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofDocumentsAffected);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StorageTransactionImpl::nofDocumentsAffected");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StorageTransactionImpl::nofDocumentsAffected", err.what());
	return 0;
}
}

StructIteratorImpl::~StructIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index StructIteratorImpl::skipDoc( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StructIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StructIteratorImpl::skipDoc", err.what());
	return 0;
}
}

IndexRange StructIteratorImpl::skipPosSource( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPosSource);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	IndexRange p0 = serializedMsg.unpackIndexRange();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StructIteratorImpl::skipPosSource");
	return IndexRange();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StructIteratorImpl::skipPosSource", err.what());
	return IndexRange();
}
}

IndexRange StructIteratorImpl::skipPosSink( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPosSink);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	IndexRange p0 = serializedMsg.unpackIndexRange();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StructIteratorImpl::skipPosSink");
	return IndexRange();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StructIteratorImpl::skipPosSink", err.what());
	return IndexRange();
}
}

IndexRange StructIteratorImpl::source( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_source);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	IndexRange p0 = serializedMsg.unpackIndexRange();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StructIteratorImpl::source");
	return IndexRange();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StructIteratorImpl::source", err.what());
	return IndexRange();
}
}

IndexRange StructIteratorImpl::sink( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_sink);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	IndexRange p0 = serializedMsg.unpackIndexRange();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "StructIteratorImpl::sink");
	return IndexRange();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "StructIteratorImpl::sink", err.what());
	return IndexRange();
}
}

SummarizerFunctionContextImpl::~SummarizerFunctionContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SummarizerFunctionContextImpl::addSummarizationFeature( const std::string& p1, PostingIteratorInterface* p2, const std::vector<SummarizationVariable>& p3, double p4, const TermStatistics& p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizationFeature);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PostingIterator");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packSummarizationVariable( p3[ii]);
	}
	msg.packDouble( p4);
	msg.packTermStatistics( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::addSummarizationFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::addSummarizationFeature", err.what());
	return void();
}
}

void SummarizerFunctionContextImpl::setVariableValue( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setVariableValue);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::setVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::setVariableValue", err.what());
	return void();
}
}

std::vector<SummaryElement> SummarizerFunctionContextImpl::getSummary( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummary);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<SummaryElement> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		SummaryElement elem_p0 = serializedMsg.unpackSummaryElement();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::getSummary");
	return std::vector<SummaryElement>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::getSummary", err.what());
	return std::vector<SummaryElement>();
}
}

std::string SummarizerFunctionContextImpl::debugCall( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_debugCall);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::debugCall");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::debugCall", err.what());
	return std::string();
}
}

SummarizerFunctionInstanceImpl::~SummarizerFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SummarizerFunctionInstanceImpl::addStringParameter( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addStringParameter);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::addStringParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::addStringParameter", err.what());
	return void();
}
}

void SummarizerFunctionInstanceImpl::addNumericParameter( const std::string& p1, const NumericVariant& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNumericParameter);
	msg.packString( p1);
	msg.packNumericVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::addNumericParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::addNumericParameter", err.what());
	return void();
}
}

void SummarizerFunctionInstanceImpl::defineResultName( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineResultName);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::defineResultName");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::defineResultName", err.what());
	return void();
}
}

std::vector<std::string> SummarizerFunctionInstanceImpl::getVariables( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getVariables);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::getVariables");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::getVariables", err.what());
	return std::vector<std::string>();
}
}

SummarizerFunctionContextInterface* SummarizerFunctionInstanceImpl::createFunctionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2, const GlobalStatistics& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFunctionContext);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "StorageClient");
	msg.packObject( impl_1->classId(), impl_1->objId());
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "MetaDataReader");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packGlobalStatistics( p3);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerFunctionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerFunctionContextInterface* p0 = new SummarizerFunctionContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
}
}

const char* SummarizerFunctionInstanceImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::name", err.what());
	return 0;
}
}

StructView SummarizerFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::view", err.what());
	return StructView();
}
}

SummarizerFunctionImpl::~SummarizerFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

SummarizerFunctionInstanceInterface* SummarizerFunctionImpl::createInstance( const QueryProcessorInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "QueryProcessor");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerFunctionInstanceInterface* p0 = new SummarizerFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* SummarizerFunctionImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionImpl::name", err.what());
	return 0;
}
}

StructView SummarizerFunctionImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "SummarizerFunctionImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "SummarizerFunctionImpl::view", err.what());
	return StructView();
}
}

TextProcessorImpl::~TextProcessorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string TextProcessorImpl::getResourceFilePath( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourceFilePath);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getResourceFilePath");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getResourceFilePath", err.what());
	return std::string();
}
}

const SegmenterInterface* TextProcessorImpl::getSegmenterByName( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSegmenterByName);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Segmenter;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterImpl const_0( objId_0, ctx(), true, errorhnd());
	const SegmenterInterface* p0 = (const SegmenterImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getSegmenterByName");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getSegmenterByName", err.what());
	return 0;
}
}

const SegmenterInterface* TextProcessorImpl::getSegmenterByMimeType( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSegmenterByMimeType);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Segmenter;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterImpl const_0( objId_0, ctx(), true, errorhnd());
	const SegmenterInterface* p0 = (const SegmenterImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getSegmenterByMimeType");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getSegmenterByMimeType", err.what());
	return 0;
}
}

analyzer::SegmenterOptions TextProcessorImpl::getSegmenterOptions( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSegmenterOptions);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::SegmenterOptions p0 = serializedMsg.unpackSegmenterOptions();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getSegmenterOptions");
	return analyzer::SegmenterOptions();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getSegmenterOptions", err.what());
	return analyzer::SegmenterOptions();
}
}

const TokenizerFunctionInterface* TextProcessorImpl::getTokenizer( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTokenizer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerFunctionImpl const_0( objId_0, ctx(), true, errorhnd());
	const TokenizerFunctionInterface* p0 = (const TokenizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getTokenizer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getTokenizer", err.what());
	return 0;
}
}

const NormalizerFunctionInterface* TextProcessorImpl::getNormalizer( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNormalizer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerFunctionImpl const_0( objId_0, ctx(), true, errorhnd());
	const NormalizerFunctionInterface* p0 = (const NormalizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getNormalizer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getNormalizer", err.what());
	return 0;
}
}

const AggregatorFunctionInterface* TextProcessorImpl::getAggregator( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getAggregator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_AggregatorFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	AggregatorFunctionImpl const_0( objId_0, ctx(), true, errorhnd());
	const AggregatorFunctionInterface* p0 = (const AggregatorFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getAggregator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getAggregator", err.what());
	return 0;
}
}

const PatternLexerInterface* TextProcessorImpl::getPatternLexer( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPatternLexer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternLexer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternLexerImpl const_0( objId_0, ctx(), true, errorhnd());
	const PatternLexerInterface* p0 = (const PatternLexerImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getPatternLexer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getPatternLexer", err.what());
	return 0;
}
}

const PatternMatcherInterface* TextProcessorImpl::getPatternMatcher( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPatternMatcher);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternMatcher;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternMatcherImpl const_0( objId_0, ctx(), true, errorhnd());
	const PatternMatcherInterface* p0 = (const PatternMatcherImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getPatternMatcher");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getPatternMatcher", err.what());
	return 0;
}
}

const PatternTermFeederInterface* TextProcessorImpl::getPatternTermFeeder( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPatternTermFeeder);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternTermFeeder;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternTermFeederImpl const_0( objId_0, ctx(), true, errorhnd());
	const PatternTermFeederInterface* p0 = (const PatternTermFeederImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getPatternTermFeeder");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getPatternTermFeeder", err.what());
	return 0;
}
}

PosTaggerDataInterface* TextProcessorImpl::createPosTaggerData( TokenizerFunctionInstanceInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPosTaggerData);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunctionInstance");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PosTaggerData;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PosTaggerDataInterface* p0 = new PosTaggerDataImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::createPosTaggerData");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::createPosTaggerData", err.what());
	return 0;
}
}

const PosTaggerInterface* TextProcessorImpl::getPosTagger( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPosTagger);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PosTagger;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PosTaggerImpl const_0( objId_0, ctx(), true, errorhnd());
	const PosTaggerInterface* p0 = (const PosTaggerImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getPosTagger");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getPosTagger", err.what());
	return 0;
}
}

TokenMarkupInstanceInterface* TextProcessorImpl::createTokenMarkupInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTokenMarkupInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenMarkupInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenMarkupInstanceInterface* p0 = new TokenMarkupInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::createTokenMarkupInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::createTokenMarkupInstance", err.what());
	return 0;
}
}

bool TextProcessorImpl::detectDocumentClass( analyzer::DocumentClass& p1, const char* p2, std::size_t p3, bool p4) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_detectDocumentClass);
	msg.packBuffer( p2, p3);
	msg.packBool( p4);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackDocumentClass();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::detectDocumentClass");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::detectDocumentClass", err.what());
	return false;
}
}

void TextProcessorImpl::defineDocumentClassDetector( DocumentClassDetectorInterface* p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineDocumentClassDetector);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DocumentClassDetector");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_1 = dynamic_cast<RpcInterfaceStub*>(p1);
	done_1->release();
	delete p1;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineDocumentClassDetector");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineDocumentClassDetector", err.what());
	return void();
}
}

void TextProcessorImpl::defineSegmenter( const std::string& p1, SegmenterInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSegmenter);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Segmenter");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineSegmenter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineSegmenter", err.what());
	return void();
}
}

void TextProcessorImpl::defineSegmenterOptions( const std::string& p1, const analyzer::SegmenterOptions& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSegmenterOptions);
	msg.packString( p1);
	msg.packSegmenterOptions( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineSegmenterOptions");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineSegmenterOptions", err.what());
	return void();
}
}

void TextProcessorImpl::defineTokenizer( const std::string& p1, TokenizerFunctionInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenizer);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TokenizerFunction");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineTokenizer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineTokenizer", err.what());
	return void();
}
}

void TextProcessorImpl::defineNormalizer( const std::string& p1, NormalizerFunctionInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineNormalizer);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "NormalizerFunction");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineNormalizer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineNormalizer", err.what());
	return void();
}
}

void TextProcessorImpl::defineAggregator( const std::string& p1, AggregatorFunctionInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAggregator);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "AggregatorFunction");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineAggregator");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::defineAggregator", err.what());
	return void();
}
}

void TextProcessorImpl::definePatternLexer( const std::string& p1, PatternLexerInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePatternLexer);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternLexer");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::definePatternLexer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::definePatternLexer", err.what());
	return void();
}
}

void TextProcessorImpl::definePatternMatcher( const std::string& p1, PatternMatcherInterface* p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePatternMatcher);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PatternMatcher");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::definePatternMatcher");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::definePatternMatcher", err.what());
	return void();
}
}

std::vector<std::string> TextProcessorImpl::getFunctionList( const TextProcessorInterface::FunctionType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getFunctionList);
	msg.packTextProcessorFunctionType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TextProcessorImpl::getFunctionList");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TextProcessorImpl::getFunctionList", err.what());
	return std::vector<std::string>();
}
}

TokenMarkupContextImpl::~TokenMarkupContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void TokenMarkupContextImpl::putMarkup( const analyzer::Position& p1, const analyzer::Position& p2, const analyzer::TokenMarkup& p3, unsigned int p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putMarkup);
	msg.packAnalyzerPosition( p1);
	msg.packAnalyzerPosition( p2);
	msg.packAnalyzerTokenMarkup( p3);
	msg.packUint( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenMarkupContextImpl::putMarkup");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenMarkupContextImpl::putMarkup", err.what());
	return void();
}
}

std::string TokenMarkupContextImpl::markupDocument( const analyzer::DocumentClass& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_markupDocument);
	msg.packDocumentClass( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenMarkupContextImpl::markupDocument");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenMarkupContextImpl::markupDocument", err.what());
	return std::string();
}
}

TokenMarkupInstanceImpl::~TokenMarkupInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

TokenMarkupContextInterface* TokenMarkupInstanceImpl::createContext( const SegmenterInstanceInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "SegmenterInstance");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenMarkupContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenMarkupContextInterface* p0 = new TokenMarkupContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenMarkupInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenMarkupInstanceImpl::createContext", err.what());
	return 0;
}
}

analyzer::FunctionView TokenMarkupInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenMarkupInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenMarkupInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

TokenizerFunctionInstanceImpl::~TokenizerFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool TokenizerFunctionInstanceImpl::concatBeforeTokenize( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_concatBeforeTokenize);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenizerFunctionInstanceImpl::concatBeforeTokenize");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenizerFunctionInstanceImpl::concatBeforeTokenize", err.what());
	return false;
}
}

std::vector<analyzer::Token> TokenizerFunctionInstanceImpl::tokenize( const char* p1, std::size_t p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<analyzer::Token> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::Token elem_p0 = serializedMsg.unpackAnalyzerToken();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenizerFunctionInstanceImpl::tokenize");
	return std::vector<analyzer::Token>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenizerFunctionInstanceImpl::tokenize", err.what());
	return std::vector<analyzer::Token>();
}
}

analyzer::FunctionView TokenizerFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::FunctionView p0 = serializedMsg.unpackAnalyzerFunctionView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenizerFunctionInstanceImpl::view");
	return analyzer::FunctionView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenizerFunctionInstanceImpl::view", err.what());
	return analyzer::FunctionView();
}
}

TokenizerFunctionImpl::~TokenizerFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

TokenizerFunctionInstanceInterface* TokenizerFunctionImpl::createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "TextProcessor");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerFunctionInstanceInterface* p0 = new TokenizerFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenizerFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* TokenizerFunctionImpl::getDescription( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDescription);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "TokenizerFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "TokenizerFunctionImpl::getDescription", err.what());
	return 0;
}
}

ValueIteratorImpl::~ValueIteratorImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ValueIteratorImpl::skip( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skip);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ValueIteratorImpl::skip");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ValueIteratorImpl::skip", err.what());
	return void();
}
}

void ValueIteratorImpl::skipPrefix( const char* p1, std::size_t p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPrefix);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ValueIteratorImpl::skipPrefix");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ValueIteratorImpl::skipPrefix", err.what());
	return void();
}
}

std::vector<std::string> ValueIteratorImpl::fetchValues( std::size_t p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetchValues);
	msg.packSize( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "ValueIteratorImpl::fetchValues");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "ValueIteratorImpl::fetchValues", err.what());
	return std::vector<std::string>();
}
}

VectorStorageClientImpl::~VectorStorageClientImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void VectorStorageClientImpl::prepareSearch( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_prepareSearch);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::prepareSearch");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::prepareSearch", err.what());
	return void();
}
}

std::vector<VectorQueryResult> VectorStorageClientImpl::findSimilar( const std::string& p1, const WordVector& p2, int p3, double p4, double p5, bool p6) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_findSimilar);
	msg.packString( p1);
	msg.packWordVector( p2);
	msg.packInt( p3);
	msg.packDouble( p4);
	msg.packDouble( p5);
	msg.packBool( p6);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<VectorQueryResult> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		VectorQueryResult elem_p0 = serializedMsg.unpackVectorQueryResult();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::findSimilar");
	return std::vector<VectorQueryResult>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::findSimilar", err.what());
	return std::vector<VectorQueryResult>();
}
}

VectorStorageTransactionInterface* VectorStorageClientImpl::createTransaction( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorStorageTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorStorageTransactionInterface* p0 = new VectorStorageTransactionImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::createTransaction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::createTransaction", err.what());
	return 0;
}
}

std::vector<std::string> VectorStorageClientImpl::types( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_types);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::types");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::types", err.what());
	return std::vector<std::string>();
}
}

ValueIteratorInterface* VectorStorageClientImpl::createFeatureValueIterator( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFeatureValueIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ValueIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ValueIteratorInterface* p0 = new ValueIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::createFeatureValueIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::createFeatureValueIterator", err.what());
	return 0;
}
}

std::vector<std::string> VectorStorageClientImpl::featureTypes( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureTypes);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::featureTypes");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::featureTypes", err.what());
	return std::vector<std::string>();
}
}

int VectorStorageClientImpl::nofTypes( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofTypes);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::nofTypes");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::nofTypes", err.what());
	return 0;
}
}

int VectorStorageClientImpl::nofFeatures( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofFeatures);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::nofFeatures");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::nofFeatures", err.what());
	return 0;
}
}

int VectorStorageClientImpl::nofVectors( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofVectors);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	int p0 = serializedMsg.unpackInt();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::nofVectors");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::nofVectors", err.what());
	return 0;
}
}

WordVector VectorStorageClientImpl::featureVector( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureVector);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	WordVector p0 = serializedMsg.unpackWordVector();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::featureVector");
	return WordVector();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::featureVector", err.what());
	return WordVector();
}
}

double VectorStorageClientImpl::vectorSimilarity( const WordVector& p1, const WordVector& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_vectorSimilarity);
	msg.packWordVector( p1);
	msg.packWordVector( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	double p0 = serializedMsg.unpackDouble();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::vectorSimilarity");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::vectorSimilarity", err.what());
	return 0;
}
}

WordVector VectorStorageClientImpl::normalize( const WordVector& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packWordVector( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	WordVector p0 = serializedMsg.unpackWordVector();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::normalize");
	return WordVector();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::normalize", err.what());
	return WordVector();
}
}

SentenceLexerInstanceInterface* VectorStorageClientImpl::createSentenceLexer( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createSentenceLexer);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SentenceLexerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SentenceLexerInstanceInterface* p0 = new SentenceLexerInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::createSentenceLexer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::createSentenceLexer", err.what());
	return 0;
}
}

std::string VectorStorageClientImpl::config( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_config);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::config");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::config", err.what());
	return std::string();
}
}

void VectorStorageClientImpl::close( )
{
try
{
	if (objId() == 0) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::close");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::close", err.what());
	return void();
}
}

void VectorStorageClientImpl::compaction( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compaction);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageClientImpl::compaction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageClientImpl::compaction", err.what());
	return void();
}
}

VectorStorageDumpImpl::~VectorStorageDumpImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool VectorStorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
	ctx()->constConstructor()->reset();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageDumpImpl::nextChunk");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageDumpImpl::nextChunk", err.what());
	return false;
}
}

VectorStorageImpl::~VectorStorageImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool VectorStorageImpl::createStorage( const std::string& p1, const DatabaseInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageImpl::createStorage");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageImpl::createStorage", err.what());
	return false;
}
}

VectorStorageClientInterface* VectorStorageImpl::createClient( const std::string& p1, const DatabaseInterface* p2) const
{
try
{
	if (p1.empty()) return new VectorStorageClientImpl( 0, ctx(), false, errorhnd());
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorStorageClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorStorageClientInterface* p0 = new VectorStorageClientImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageImpl::createClient");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageImpl::createClient", err.what());
	return 0;
}
}

VectorStorageDumpInterface* VectorStorageImpl::createDump( const std::string& p1, const DatabaseInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "Database");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorStorageDump;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorStorageDumpInterface* p0 = new VectorStorageDumpImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageImpl::createDump");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageImpl::createDump", err.what());
	return 0;
}
}

const char* VectorStorageImpl::getConfigDescription( const VectorStorageInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packVectorStorageConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageImpl::getConfigDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageImpl::getConfigDescription", err.what());
	return 0;
}
}

const char** VectorStorageImpl::getConfigParameters( const VectorStorageInterface::ConfigType& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packVectorStorageConfigType( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char** p0 =  ctx()->constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageImpl::getConfigParameters");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageImpl::getConfigParameters", err.what());
	return 0;
}
}

VectorStorageTransactionImpl::~VectorStorageTransactionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void VectorStorageTransactionImpl::defineVector( const std::string& p1, const std::string& p2, const WordVector& p3)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineVector);
	msg.packString( p1);
	msg.packString( p2);
	msg.packWordVector( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageTransactionImpl::defineVector");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageTransactionImpl::defineVector", err.what());
	return void();
}
}

void VectorStorageTransactionImpl::defineFeature( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageTransactionImpl::defineFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageTransactionImpl::defineFeature", err.what());
	return void();
}
}

void VectorStorageTransactionImpl::clear( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clear);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageTransactionImpl::clear");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageTransactionImpl::clear", err.what());
	return void();
}
}

bool VectorStorageTransactionImpl::commit( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageTransactionImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageTransactionImpl::commit", err.what());
	return false;
}
}

void VectorStorageTransactionImpl::rollback( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "VectorStorageTransactionImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "VectorStorageTransactionImpl::rollback", err.what());
	return void();
}
}

WeightingFunctionContextImpl::~WeightingFunctionContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void WeightingFunctionContextImpl::addWeightingFeature( const std::string& p1, PostingIteratorInterface* p2, double p3, const TermStatistics& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addWeightingFeature);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PostingIterator");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packDouble( p3);
	msg.packTermStatistics( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::addWeightingFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::addWeightingFeature", err.what());
	return void();
}
}

void WeightingFunctionContextImpl::setVariableValue( const std::string& p1, double p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setVariableValue);
	msg.packString( p1);
	msg.packDouble( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::setVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::setVariableValue", err.what());
	return void();
}
}

double WeightingFunctionContextImpl::call( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	double p0 = serializedMsg.unpackDouble();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::call");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::call", err.what());
	return 0;
}
}

std::string WeightingFunctionContextImpl::debugCall( const Index& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_debugCall);
	msg.packIndex( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::debugCall");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::debugCall", err.what());
	return std::string();
}
}

WeightingFunctionInstanceImpl::~WeightingFunctionInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void WeightingFunctionInstanceImpl::addStringParameter( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addStringParameter);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::addStringParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::addStringParameter", err.what());
	return void();
}
}

void WeightingFunctionInstanceImpl::addNumericParameter( const std::string& p1, const NumericVariant& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNumericParameter);
	msg.packString( p1);
	msg.packNumericVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::addNumericParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::addNumericParameter", err.what());
	return void();
}
}

WeightingFunctionContextInterface* WeightingFunctionInstanceImpl::createFunctionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2, const GlobalStatistics& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFunctionContext);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "StorageClient");
	msg.packObject( impl_1->classId(), impl_1->objId());
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "MetaDataReader");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packGlobalStatistics( p3);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingFunctionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingFunctionContextInterface* p0 = new WeightingFunctionContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
}
}

std::vector<std::string> WeightingFunctionInstanceImpl::getVariables( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getVariables);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<std::string> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		std::string elem_p0 = serializedMsg.unpackString();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::getVariables");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::getVariables", err.what());
	return std::vector<std::string>();
}
}

const char* WeightingFunctionInstanceImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::name", err.what());
	return 0;
}
}

StructView WeightingFunctionInstanceImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::view", err.what());
	return StructView();
}
}

WeightingFunctionImpl::~WeightingFunctionImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

WeightingFunctionInstanceInterface* WeightingFunctionImpl::createInstance( const QueryProcessorInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "QueryProcessor");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingFunctionInstanceInterface* p0 = new WeightingFunctionInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionImpl::createInstance", err.what());
	return 0;
}
}

const char* WeightingFunctionImpl::name( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_name);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionImpl::name");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionImpl::name", err.what());
	return 0;
}
}

StructView WeightingFunctionImpl::view( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_view);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	StructView p0 = serializedMsg.unpackStructView();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report( ErrorCodeOutOfMem, _TXT("out of memory calling method '%s'"), "WeightingFunctionImpl::view");
	return StructView();
} catch (const std::exception& err) {
	errorhnd()->report( ErrorCodeRuntimeError, _TXT("error calling method '%s': %s"), "WeightingFunctionImpl::view", err.what());
	return StructView();
}
}

