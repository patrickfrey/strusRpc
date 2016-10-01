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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AggregatorFunctionInstanceImpl::evaluate");
	return NumericVariant();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AggregatorFunctionInstanceImpl::evaluate", err.what());
	return NumericVariant();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AggregatorFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AggregatorFunctionImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AggregatorFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AggregatorFunctionImpl::getDescription", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::getTextProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::getTextProcessor", err.what());
	return 0;
}
}

const SegmenterInterface* AnalyzerObjectBuilderImpl::getSegmenter( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSegmenter);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::getSegmenter");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::getSegmenter", err.what());
	return 0;
}
}

const SegmenterInterface* AnalyzerObjectBuilderImpl::findMimeTypeSegmenter( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_findMimeTypeSegmenter);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::findMimeTypeSegmenter");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::findMimeTypeSegmenter", err.what());
	return 0;
}
}

DocumentAnalyzerInterface* AnalyzerObjectBuilderImpl::createDocumentAnalyzer( const SegmenterInterface* p1, const analyzer::SegmenterOptions& p2) const
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
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInterface* p0 = new DocumentAnalyzerImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createDocumentAnalyzer", err.what());
	return 0;
}
}

QueryAnalyzerInterface* AnalyzerObjectBuilderImpl::createQueryAnalyzer( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryAnalyzer);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryAnalyzer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryAnalyzerInterface* p0 = new QueryAnalyzerImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AnalyzerObjectBuilderImpl::createQueryAnalyzer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AnalyzerObjectBuilderImpl::createQueryAnalyzer", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AttributeReaderImpl::elementHandle");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AttributeReaderImpl::elementHandle", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AttributeReaderImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AttributeReaderImpl::skipDoc", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AttributeReaderImpl::getValue");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AttributeReaderImpl::getValue", err.what());
	return std::string();
}
}

std::vector<std::string> AttributeReaderImpl::getAttributeNames( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getAttributeNames);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "AttributeReaderImpl::getAttributeNames");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "AttributeReaderImpl::getAttributeNames", err.what());
	return std::vector<std::string>();
}
}

CharRegexMatchContextImpl::~CharRegexMatchContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<analyzer::IdToken> CharRegexMatchContextImpl::match( const char* p1, std::size_t p2)
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
	std::vector<analyzer::IdToken> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::IdToken elem_p0 = serializedMsg.unpackAnalyzerIdToken();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchContextImpl::match");
	return std::vector<analyzer::IdToken>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchContextImpl::match", err.what());
	return std::vector<analyzer::IdToken>();
}
}

CharRegexMatchInstanceImpl::~CharRegexMatchInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void CharRegexMatchInstanceImpl::definePattern( unsigned int p1, const std::string& p2, unsigned int p3, unsigned int p4, analyzer::PositionBind p5)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePattern);
	msg.packUint( p1);
	msg.packString( p2);
	msg.packUint( p3);
	msg.packUint( p4);
	msg.packByte( p5);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchInstanceImpl::definePattern");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchInstanceImpl::definePattern", err.what());
	return void();
}
}

void CharRegexMatchInstanceImpl::defineSymbol( unsigned int p1, unsigned int p2, const std::string& p3)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchInstanceImpl::defineSymbol");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchInstanceImpl::defineSymbol", err.what());
	return void();
}
}

unsigned int CharRegexMatchInstanceImpl::getSymbol( unsigned int p1, const std::string& p2) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchInstanceImpl::getSymbol");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchInstanceImpl::getSymbol", err.what());
	return 0;
}
}

bool CharRegexMatchInstanceImpl::compile( const analyzer::CharRegexMatchOptions& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compile);
	msg.packAnalyzerCharRegexMatchOptions( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchInstanceImpl::compile", err.what());
	return false;
}
}

CharRegexMatchContextInterface* CharRegexMatchInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_CharRegexMatchContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	CharRegexMatchContextInterface* p0 = new CharRegexMatchContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchInstanceImpl::createContext", err.what());
	return 0;
}
}

CharRegexMatchImpl::~CharRegexMatchImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<std::string> CharRegexMatchImpl::getCompileOptions( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getCompileOptions);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchImpl::getCompileOptions");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchImpl::getCompileOptions", err.what());
	return std::vector<std::string>();
}
}

CharRegexMatchInstanceInterface* CharRegexMatchImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_CharRegexMatchInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	CharRegexMatchInstanceInterface* p0 = new CharRegexMatchInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "CharRegexMatchImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "CharRegexMatchImpl::createInstance", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseBackupCursorImpl::fetch");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseBackupCursorImpl::fetch", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createTransaction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::createTransaction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::createCursor", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::createBackupCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::createBackupCursor", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::writeImm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::writeImm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::removeImm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::removeImm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseClientImpl::readValue");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseClientImpl::readValue", err.what());
	return false;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekUpperBound");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekUpperBound", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekUpperBoundRestricted");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekUpperBoundRestricted", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekFirst");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekFirst", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekLast");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekLast", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekNext");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekNext", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::seekPrev");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::seekPrev", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::key");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::key", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseCursorImpl::value");
	return DatabaseCursorInterface::Slice();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseCursorImpl::value", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::exists");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::exists", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::createClient");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::createClient", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::createDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::createDatabase", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::restoreDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::restoreDatabase", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::destroyDatabase");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::destroyDatabase", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::getConfigDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::getConfigDescription", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseImpl::getConfigParameters");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseImpl::getConfigParameters", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::createCursor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::createCursor", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::write");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::write", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::remove");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::remove", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::removeSubTree");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::removeSubTree", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::commit", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DatabaseTransactionImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DatabaseTransactionImpl::rollback", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerContextImpl::putInput", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerContextImpl::analyzeNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerContextImpl::analyzeNext", err.what());
	return false;
}
}

DocumentAnalyzerImpl::~DocumentAnalyzerImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentAnalyzerImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
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
	msg.packFeatureOptions( p5);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::addSearchIndexFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::addSearchIndexFeature", err.what());
	return void();
}
}

void DocumentAnalyzerImpl::addForwardIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
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
	msg.packFeatureOptions( p5);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::addForwardIndexFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::addForwardIndexFeature", err.what());
	return void();
}
}

void DocumentAnalyzerImpl::defineMetaData( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::defineMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::defineMetaData", err.what());
	return void();
}
}

void DocumentAnalyzerImpl::defineAggregatedMetaData( const std::string& p1, AggregatorFunctionInstanceInterface* p2)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::defineAggregatedMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::defineAggregatedMetaData", err.what());
	return void();
}
}

void DocumentAnalyzerImpl::defineAttribute( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::defineAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::defineAttribute", err.what());
	return void();
}
}

void DocumentAnalyzerImpl::defineSubDocument( const std::string& p1, const std::string& p2)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::defineSubDocument");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::defineSubDocument", err.what());
	return void();
}
}

analyzer::Document DocumentAnalyzerImpl::analyze( const std::string& p1, const analyzer::DocumentClass& p2) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::analyze");
	return analyzer::Document();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::analyze", err.what());
	return analyzer::Document();
}
}

DocumentAnalyzerContextInterface* DocumentAnalyzerImpl::createContext( const analyzer::DocumentClass& p1) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentAnalyzerImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentAnalyzerImpl::createContext", err.what());
	return 0;
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

bool DocumentClassDetectorImpl::detect( analyzer::DocumentClass& p1, const char* p2, std::size_t p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_detect);
	msg.packBuffer( p2, p3);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackDocumentClass();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentClassDetectorImpl::detect");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentClassDetectorImpl::detect", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::skipDoc", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::nextTerm");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::nextTerm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::termDocumentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::termDocumentFrequency", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "DocumentTermIteratorImpl::termValue");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "DocumentTermIteratorImpl::termValue", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ForwardIteratorImpl::skipDoc", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::skipPos");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ForwardIteratorImpl::skipPos", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ForwardIteratorImpl::fetch");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ForwardIteratorImpl::fetch", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "InvAclIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "InvAclIteratorImpl::skipDoc", err.what());
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

bool MetaDataReaderImpl::hasElement( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_hasElement);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::hasElement");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::hasElement", err.what());
	return false;
}
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::elementHandle");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::elementHandle", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::nofElements");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::nofElements", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::skipDoc");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::skipDoc", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getValue");
	return NumericVariant();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getValue", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getType");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getType", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataReaderImpl::getName");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataReaderImpl::getName", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataRestrictionInstanceImpl::match");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataRestrictionInstanceImpl::match", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::addCondition");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::addCondition", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "MetaDataRestrictionImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "MetaDataRestrictionImpl::tostring", err.what());
	return std::string();
}
}

NormalizerFunctionContextImpl::~NormalizerFunctionContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string NormalizerFunctionContextImpl::normalize( const char* p1, std::size_t p2)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "NormalizerFunctionContextImpl::normalize");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "NormalizerFunctionContextImpl::normalize", err.what());
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

NormalizerFunctionContextInterface* NormalizerFunctionInstanceImpl::createFunctionContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFunctionContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerFunctionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerFunctionContextInterface* p0 = new NormalizerFunctionContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "NormalizerFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "NormalizerFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "NormalizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "NormalizerFunctionImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "NormalizerFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "NormalizerFunctionImpl::getDescription", err.what());
	return 0;
}
}

PatternMatchProgramInstanceImpl::~PatternMatchProgramInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool PatternMatchProgramInstanceImpl::load( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_load);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramInstanceImpl::load");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramInstanceImpl::load", err.what());
	return false;
}
}

bool PatternMatchProgramInstanceImpl::compile( )
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramInstanceImpl::compile", err.what());
	return false;
}
}

const CharRegexMatchInstanceInterface* PatternMatchProgramInstanceImpl::getCharRegexMatchInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getCharRegexMatchInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_CharRegexMatchInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	CharRegexMatchInstanceImpl const_0( objId_0, ctx(), true, errorhnd());
	const CharRegexMatchInstanceInterface* p0 = (const CharRegexMatchInstanceImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramInstanceImpl::getCharRegexMatchInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramInstanceImpl::getCharRegexMatchInstance", err.what());
	return 0;
}
}

const TokenPatternMatchInstanceInterface* PatternMatchProgramInstanceImpl::getTokenPatternMatchInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTokenPatternMatchInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenPatternMatchInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenPatternMatchInstanceImpl const_0( objId_0, ctx(), true, errorhnd());
	const TokenPatternMatchInstanceInterface* p0 = (const TokenPatternMatchInstanceImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramInstanceImpl::getTokenPatternMatchInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramInstanceImpl::getTokenPatternMatchInstance", err.what());
	return 0;
}
}

const char* PatternMatchProgramInstanceImpl::tokenName( unsigned int p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenName);
	msg.packUint( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramInstanceImpl::tokenName");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramInstanceImpl::tokenName", err.what());
	return 0;
}
}

PatternMatchProgramImpl::~PatternMatchProgramImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PatternMatchProgramInstanceInterface* PatternMatchProgramImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PatternMatchProgramInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PatternMatchProgramInstanceInterface* p0 = new PatternMatchProgramInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PatternMatchProgramImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PatternMatchProgramImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipDoc");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipDoc", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipDocCandidate");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipDocCandidate", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::skipPos");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::skipPos", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::featureid");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::featureid", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::documentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::documentFrequency", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::frequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::frequency", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::docno");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::docno", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingIteratorImpl::posno");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingIteratorImpl::posno", err.what());
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
	errorhnd()->report(_TXT("the method '%s' is not implemented for RPC"),"createResultIterator");
	return 0;
}

PostingJoinOperatorInterface::Description PostingJoinOperatorImpl::getDescription( ) const
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
	PostingJoinOperatorInterface::Description p0 = serializedMsg.unpackPostingJoinOperatorDescription();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "PostingJoinOperatorImpl::getDescription");
	return PostingJoinOperatorInterface::Description();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "PostingJoinOperatorImpl::getDescription", err.what());
	return PostingJoinOperatorInterface::Description();
}
}

QueryAnalyzerImpl::~QueryAnalyzerImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryAnalyzerImpl::definePhraseType( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePhraseType);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryAnalyzerImpl::definePhraseType");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryAnalyzerImpl::definePhraseType", err.what());
	return void();
}
}

std::vector<analyzer::Term> QueryAnalyzerImpl::analyzePhrase( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhrase);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<analyzer::Term> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::Term elem_p0 = serializedMsg.unpackAnalyzerTerm();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryAnalyzerImpl::analyzePhrase");
	return std::vector<analyzer::Term>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryAnalyzerImpl::analyzePhrase", err.what());
	return std::vector<analyzer::Term>();
}
}

std::vector<analyzer::TermVector> QueryAnalyzerImpl::analyzePhraseBulk( const std::vector<QueryAnalyzerInterface::Phrase>& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhraseBulk);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packPhrase( p1[ii]);
	}
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<analyzer::TermVector> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::TermVector elem_p0 = serializedMsg.unpackAnalyzerTermVector();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryAnalyzerImpl::analyzePhraseBulk");
	return std::vector<analyzer::TermVector>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryAnalyzerImpl::analyzePhraseBulk", err.what());
	return std::vector<analyzer::TermVector>();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addTerm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addSelectionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addSelectionFeature", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addRestrictionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addRestrictionFeature", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addExclusionFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addExclusionFeature", err.what());
	return void();
}
}

void QueryEvalImpl::addSummarizerFunction( const std::string& p1, SummarizerFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3)
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
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addSummarizerFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addSummarizerFunction", err.what());
	return void();
}
}

void QueryEvalImpl::addWeightingFunction( const std::string& p1, WeightingFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::FeatureParameter>& p3)
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
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::addWeightingFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::addWeightingFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::defineWeightingFormula");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::defineWeightingFormula", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryEvalImpl::createQuery");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryEvalImpl::createQuery", err.what());
	return 0;
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

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::pushTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::pushTerm", err.what());
	return void();
}
}

void QueryImpl::pushExpression( const PostingJoinOperatorInterface* p1, std::size_t p2, int p3, unsigned int p4)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "PostingJoinOperator");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packSize( p2);
	msg.packInt( p3);
	msg.packUint( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::pushExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::pushExpression", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::attachVariable");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::attachVariable", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::defineFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::defineFeature", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::defineTermStatistics");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::defineTermStatistics", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::defineGlobalStatistics");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::defineGlobalStatistics", err.what());
	return void();
}
}

void QueryImpl::addMetaDataRestrictionCondition( MetaDataRestrictionInterface::CompareOperator p1, const std::string& p2, const NumericVariant& p3, bool p4)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::addMetaDataRestrictionCondition");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::addMetaDataRestrictionCondition", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::addDocumentEvaluationSet");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::addDocumentEvaluationSet", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::setMaxNofRanks");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::setMaxNofRanks", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::setMinRank");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::setMinRank", err.what());
	return void();
}
}

void QueryImpl::addUserName( const std::string& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addUserName);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::addUserName");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::addUserName", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::setWeightingVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::setWeightingVariableValue", err.what());
	return void();
}
}

QueryResult QueryImpl::evaluate( )
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::evaluate");
	return QueryResult();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::evaluate", err.what());
	return QueryResult();
}
}

std::string QueryImpl::tostring( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryImpl::tostring", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::definePostingJoinOperator");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::definePostingJoinOperator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getPostingJoinOperator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::getPostingJoinOperator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineWeightingFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineWeightingFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getWeightingFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::getWeightingFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineSummarizerFunction");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineSummarizerFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getSummarizerFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::getSummarizerFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getFunctionList");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::getFunctionList", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::defineScalarFunctionParser");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::defineScalarFunctionParser", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "QueryProcessorImpl::getScalarFunctionParser");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "QueryProcessorImpl::getScalarFunctionParser", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::setVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::setVariableValue", err.what());
	return void();
}
}

double ScalarFunctionInstanceImpl::call( const double* p1, std::size_t p2) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::call");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::call", err.what());
	return 0;
}
}

std::string ScalarFunctionInstanceImpl::tostring( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionInstanceImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionInstanceImpl::tostring", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::getVariables");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionImpl::getVariables", err.what());
	return std::vector<std::string>();
}
}

std::size_t ScalarFunctionImpl::getNofArguments( ) const
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
	std::size_t p0 = serializedMsg.unpackSize();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::getNofArguments");
	return std::size_t();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionImpl::getNofArguments", err.what());
	return std::size_t();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::setDefaultVariableValue");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionImpl::setDefaultVariableValue", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionImpl::createInstance", err.what());
	return 0;
}
}

std::string ScalarFunctionImpl::tostring( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionImpl::tostring", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ScalarFunctionParserImpl::createFunction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ScalarFunctionParserImpl::createFunction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterContextImpl::putInput", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterContextImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterContextImpl::getNext", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::defineSelectorExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::defineSelectorExpression", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::defineSubSection");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::defineSubSection", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::createContext", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterInstanceImpl::createMarkupContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterInstanceImpl::createMarkupContext", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterImpl::mimeType");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterImpl::mimeType", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::getNext", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::segmentSize");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::segmentSize", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::tagName");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::tagName", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::tagLevel");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::tagLevel", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putOpenTag");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putOpenTag", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putAttribute", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::putCloseTag");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::putCloseTag", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SegmenterMarkupContextImpl::getContent");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SegmenterMarkupContextImpl::getContent", err.what());
	return std::string();
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

void StatisticsBuilderImpl::setNofDocumentsInsertedChange( int p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::setNofDocumentsInsertedChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::setNofDocumentsInsertedChange", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::addDfChange");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::addDfChange", err.what());
	return void();
}
}

void StatisticsBuilderImpl::start( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_start);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::start");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::start", err.what());
	return void();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::rollback", err.what());
	return void();
}
}

bool StatisticsBuilderImpl::fetchMessage( const char*& p1, std::size_t& p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetchMessage);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsBuilderImpl::fetchMessage");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsBuilderImpl::fetchMessage", err.what());
	return false;
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

bool StatisticsIteratorImpl::getNext( const char*& p1, std::size_t& p2)
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
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsIteratorImpl::getNext");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsIteratorImpl::getNext", err.what());
	return false;
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

StatisticsViewerInterface* StatisticsProcessorImpl::createViewer( const char* p1, std::size_t p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createViewer);
	msg.packBuffer( p1, p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsViewer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsViewerInterface* p0 = new StatisticsViewerImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createViewer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createViewer", err.what());
	return 0;
}
}

StatisticsBuilderInterface* StatisticsProcessorImpl::createBuilder( const StatisticsProcessorInterface::BuilderOptions& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBuilder);
	msg.packStatisticsProcessorBuilderOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsBuilder;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsBuilderInterface* p0 = new StatisticsBuilderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsProcessorImpl::createBuilder");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsProcessorImpl::createBuilder", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsViewerImpl::nofDocumentsInsertedChange");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsViewerImpl::nofDocumentsInsertedChange", err.what());
	return 0;
}
}

bool StatisticsViewerImpl::nextDfChange( StatisticsViewerInterface::DocumentFrequencyChange& p1)
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
	p1 = serializedMsg.unpackStatisticsViewerDocumentFrequencyChange();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StatisticsViewerImpl::nextDfChange");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StatisticsViewerImpl::nextDfChange", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::addElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::addElement", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::alterElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::alterElement", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::renameElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::renameElement", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::deleteElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::deleteElement", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::clearElement");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::clearElement", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::commit", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageAlterMetaDataTableImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageAlterMetaDataTableImpl::rollback", err.what());
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

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermPostingIterator);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermPostingIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createTermPostingIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createBrowsePostingIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createBrowsePostingIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createForwardIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createForwardIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocumentTermIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createDocumentTermIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createInvAclIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createInvAclIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::nofDocumentsInserted");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::nofDocumentsInserted", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::documentFrequency");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::documentFrequency", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::maxDocumentNumber");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::maxDocumentNumber", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::documentNumber");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::documentNumber", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermTypeIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createTermTypeIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createTermValueIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createTermValueIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocIdIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createDocIdIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createUserNameIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createUserNameIterator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::documentStatistics");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::documentStatistics", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createMetaDataReader");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createMetaDataReader", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createMetaDataRestriction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createMetaDataRestriction", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createAttributeReader");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createAttributeReader", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createTransaction");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createTransaction", err.what());
	return 0;
}
}

StatisticsIteratorInterface* StorageClientImpl::createInitStatisticsIterator( bool p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInitStatisticsIterator);
	msg.packBool( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createInitStatisticsIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createInitStatisticsIterator", err.what());
	return 0;
}
}

StatisticsIteratorInterface* StorageClientImpl::createUpdateStatisticsIterator( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createUpdateStatisticsIterator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StatisticsIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StatisticsIteratorInterface* p0 = new StatisticsIteratorImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createUpdateStatisticsIterator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createUpdateStatisticsIterator", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::getStatisticsProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::getStatisticsProcessor", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createDocumentChecker");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createDocumentChecker", err.what());
	return 0;
}
}

bool StorageClientImpl::checkStorage( std::ostream& p1) const
{
	errorhnd()->report(_TXT("the method '%s' is not implemented for RPC"),"checkStorage");
	return false;
}

StorageDumpInterface* StorageClientImpl::createDump( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDump;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDumpInterface* p0 = new StorageDumpImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageClientImpl::createDump");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageClientImpl::createDump", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::addSearchIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::addSearchIndexTerm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::addForwardIndexTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::addForwardIndexTerm", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::setMetaData", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::setAttribute", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::setUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::setUserAccessRight", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentImpl::done");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentImpl::done", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setMetaData", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setAttribute", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearAttribute");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearAttribute", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::setUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::setUserAccessRight", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearUserAccessRight");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearUserAccessRight", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::clearUserAccessRights");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::clearUserAccessRights", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDocumentUpdateImpl::done");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDocumentUpdateImpl::done", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageDumpImpl::nextChunk");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageDumpImpl::nextChunk", err.what());
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

StorageClientInterface* StorageImpl::createClient( const std::string& p1, DatabaseClientInterface* p2, const StatisticsProcessorInterface* p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DatabaseClient");
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
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageImpl::createClient");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageImpl::createClient", err.what());
	return 0;
}
}

bool StorageImpl::createStorage( const std::string& p1, DatabaseClientInterface* p2) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DatabaseClient");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageImpl::createStorage");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageImpl::createStorage", err.what());
	return false;
}
}

StorageAlterMetaDataTableInterface* StorageImpl::createAlterMetaDataTable( DatabaseClientInterface* p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "DatabaseClient");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, ctx(), false, errorhnd());
	RpcInterfaceStub* done_1 = dynamic_cast<RpcInterfaceStub*>(p1);
	done_1->release();
	delete p1;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageImpl::createAlterMetaDataTable");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageImpl::createAlterMetaDataTable", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageImpl::getConfigDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageImpl::getConfigDescription", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageImpl::getConfigParameters");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageImpl::getConfigParameters", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getStorage");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getStorage", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getDatabase");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getDatabase", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getQueryProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getQueryProcessor", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getStatisticsProcessor");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getStatisticsProcessor", err.what());
	return 0;
}
}

const VectorSpaceModelInterface* StorageObjectBuilderImpl::getVectorSpaceModel( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getVectorSpaceModel);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorSpaceModel;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorSpaceModelImpl const_0( objId_0, ctx(), true, errorhnd());
	const VectorSpaceModelInterface* p0 = (const VectorSpaceModelImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::getVectorSpaceModel");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::getVectorSpaceModel", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageObjectBuilderImpl::createQueryEval");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageObjectBuilderImpl::createQueryEval", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::createDocument");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::createDocument", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::createDocumentUpdate");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::createDocumentUpdate", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::deleteDocument");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::deleteDocument", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::deleteUserAccessRights");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::deleteUserAccessRights", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::updateMetaData");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::updateMetaData", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::commit");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::commit", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "StorageTransactionImpl::rollback");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "StorageTransactionImpl::rollback", err.what());
	return void();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::addSummarizationFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::addSummarizationFeature", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionContextImpl::getSummary");
	return std::vector<SummaryElement>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionContextImpl::getSummary", err.what());
	return std::vector<SummaryElement>();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::addStringParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::addStringParameter", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::addNumericParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::addNumericParameter", err.what());
	return void();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
}
}

std::string SummarizerFunctionInstanceImpl::tostring( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionInstanceImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionInstanceImpl::tostring", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionImpl::createInstance", err.what());
	return 0;
}
}

FunctionDescription SummarizerFunctionImpl::getDescription( ) const
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
	FunctionDescription p0 = serializedMsg.unpackFunctionDescription();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "SummarizerFunctionImpl::getDescription");
	return FunctionDescription();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "SummarizerFunctionImpl::getDescription", err.what());
	return FunctionDescription();
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

void TextProcessorImpl::addResourcePath( const std::string& p1)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::addResourcePath");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::addResourcePath", err.what());
	return void();
}
}

std::string TextProcessorImpl::getResourcePath( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::getResourcePath");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::getResourcePath", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::getTokenizer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::getTokenizer", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::getNormalizer");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::getNormalizer", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::getAggregator");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::getAggregator", err.what());
	return 0;
}
}

bool TextProcessorImpl::detectDocumentClass( analyzer::DocumentClass& p1, const char* p2, std::size_t p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_detectDocumentClass);
	msg.packBuffer( p2, p3);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackDocumentClass();
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::detectDocumentClass");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::detectDocumentClass", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineDocumentClassDetector");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::defineDocumentClassDetector", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineTokenizer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::defineTokenizer", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineNormalizer");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::defineNormalizer", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::defineAggregator");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::defineAggregator", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TextProcessorImpl::getFunctionList");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TextProcessorImpl::getFunctionList", err.what());
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

void TokenMarkupContextImpl::putMarkup( const SegmenterPosition& p1, std::size_t p2, const SegmenterPosition& p3, std::size_t p4, const analyzer::TokenMarkup& p5, unsigned int p6)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putMarkup);
	msg.packGlobalCounter( p1);
	msg.packSize( p2);
	msg.packGlobalCounter( p3);
	msg.packSize( p4);
	msg.packAnalyzerTokenMarkup( p5);
	msg.packUint( p6);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenMarkupContextImpl::putMarkup");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenMarkupContextImpl::putMarkup", err.what());
	return void();
}
}

std::string TokenMarkupContextImpl::markupDocument( const SegmenterInstanceInterface* p1, const analyzer::DocumentClass& p2, const std::string& p3) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_markupDocument);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (%s)"), "SegmenterInstance");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packDocumentClass( p2);
	msg.packString( p3);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenMarkupContextImpl::markupDocument");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenMarkupContextImpl::markupDocument", err.what());
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

TokenMarkupContextInterface* TokenMarkupInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenMarkupContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenMarkupContextInterface* p0 = new TokenMarkupContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenMarkupInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenMarkupInstanceImpl::createContext", err.what());
	return 0;
}
}

TokenPatternMatchContextImpl::~TokenPatternMatchContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void TokenPatternMatchContextImpl::putInput( const analyzer::IdToken& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packAnalyzerIdToken( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchContextImpl::putInput");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchContextImpl::putInput", err.what());
	return void();
}
}

std::vector<analyzer::TokenPatternMatchResult> TokenPatternMatchContextImpl::fetchResults( ) const
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
	std::vector<analyzer::TokenPatternMatchResult> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::TokenPatternMatchResult elem_p0 = serializedMsg.unpackAnalyzerTokenPatternMatchResult();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchContextImpl::fetchResults");
	return std::vector<analyzer::TokenPatternMatchResult>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchContextImpl::fetchResults", err.what());
	return std::vector<analyzer::TokenPatternMatchResult>();
}
}

analyzer::TokenPatternMatchStatistics TokenPatternMatchContextImpl::getStatistics( ) const
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
	analyzer::TokenPatternMatchStatistics p0 = serializedMsg.unpackAnalyzerTokenPatternMatchStatistics();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchContextImpl::getStatistics");
	return analyzer::TokenPatternMatchStatistics();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchContextImpl::getStatistics", err.what());
	return analyzer::TokenPatternMatchStatistics();
}
}

TokenPatternMatchInstanceImpl::~TokenPatternMatchInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void TokenPatternMatchInstanceImpl::defineTermFrequency( unsigned int p1, double p2)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::defineTermFrequency");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::defineTermFrequency", err.what());
	return void();
}
}

void TokenPatternMatchInstanceImpl::pushTerm( unsigned int p1)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::pushTerm");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::pushTerm", err.what());
	return void();
}
}

void TokenPatternMatchInstanceImpl::pushExpression( TokenPatternMatchInstanceInterface::JoinOperation p1, std::size_t p2, unsigned int p3, unsigned int p4)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::pushExpression");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::pushExpression", err.what());
	return void();
}
}

void TokenPatternMatchInstanceImpl::pushPattern( const std::string& p1)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::pushPattern");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::pushPattern", err.what());
	return void();
}
}

void TokenPatternMatchInstanceImpl::attachVariable( const std::string& p1, float p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::attachVariable");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::attachVariable", err.what());
	return void();
}
}

void TokenPatternMatchInstanceImpl::definePattern( const std::string& p1, bool p2)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePattern);
	msg.packString( p1);
	msg.packBool( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::definePattern");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::definePattern", err.what());
	return void();
}
}

bool TokenPatternMatchInstanceImpl::compile( const analyzer::TokenPatternMatchOptions& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_compile);
	msg.packAnalyzerTokenPatternMatchOptions( p1);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::compile");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::compile", err.what());
	return false;
}
}

TokenPatternMatchContextInterface* TokenPatternMatchInstanceImpl::createContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenPatternMatchContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenPatternMatchContextInterface* p0 = new TokenPatternMatchContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchInstanceImpl::createContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchInstanceImpl::createContext", err.what());
	return 0;
}
}

TokenPatternMatchImpl::~TokenPatternMatchImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<std::string> TokenPatternMatchImpl::getCompileOptions( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getCompileOptions);
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchImpl::getCompileOptions");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchImpl::getCompileOptions", err.what());
	return std::vector<std::string>();
}
}

TokenPatternMatchInstanceInterface* TokenPatternMatchImpl::createInstance( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenPatternMatchInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenPatternMatchInstanceInterface* p0 = new TokenPatternMatchInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenPatternMatchImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenPatternMatchImpl::createInstance", err.what());
	return 0;
}
}

TokenizerFunctionContextImpl::~TokenizerFunctionContextImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<analyzer::Token> TokenizerFunctionContextImpl::tokenize( const char* p1, std::size_t p2)
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenizerFunctionContextImpl::tokenize");
	return std::vector<analyzer::Token>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenizerFunctionContextImpl::tokenize", err.what());
	return std::vector<analyzer::Token>();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenizerFunctionInstanceImpl::concatBeforeTokenize");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenizerFunctionInstanceImpl::concatBeforeTokenize", err.what());
	return false;
}
}

TokenizerFunctionContextInterface* TokenizerFunctionInstanceImpl::createFunctionContext( ) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createFunctionContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerFunctionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerFunctionContextInterface* p0 = new TokenizerFunctionContextImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenizerFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenizerFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenizerFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenizerFunctionImpl::createInstance", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "TokenizerFunctionImpl::getDescription");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "TokenizerFunctionImpl::getDescription", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ValueIteratorImpl::skip");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ValueIteratorImpl::skip", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "ValueIteratorImpl::fetchValues");
	return std::vector<std::string>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "ValueIteratorImpl::fetchValues", err.what());
	return std::vector<std::string>();
}
}

VectorSpaceModelBuilderImpl::~VectorSpaceModelBuilderImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void VectorSpaceModelBuilderImpl::addSampleVector( const std::vector<double>& p1)
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSampleVector);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packDouble( p1[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelBuilderImpl::addSampleVector");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelBuilderImpl::addSampleVector", err.what());
	return void();
}
}

void VectorSpaceModelBuilderImpl::finalize( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_finalize);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelBuilderImpl::finalize");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelBuilderImpl::finalize", err.what());
	return void();
}
}

bool VectorSpaceModelBuilderImpl::store( )
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_store);
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelBuilderImpl::store");
	return false;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelBuilderImpl::store", err.what());
	return false;
}
}

VectorSpaceModelInstanceImpl::~VectorSpaceModelInstanceImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<unsigned int> VectorSpaceModelInstanceImpl::mapVectorToFeatures( const std::vector<double>& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_mapVectorToFeatures);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packDouble( p1[ii]);
	}
	msg.packCrc32();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<unsigned int> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		unsigned int elem_p0 = serializedMsg.unpackUint();
		p0.push_back( elem_p0);
	}
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelInstanceImpl::mapVectorToFeatures");
	return std::vector<unsigned int>();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelInstanceImpl::mapVectorToFeatures", err.what());
	return std::vector<unsigned int>();
}
}

unsigned int VectorSpaceModelInstanceImpl::nofFeatures( ) const
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
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelInstanceImpl::nofFeatures");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelInstanceImpl::nofFeatures", err.what());
	return 0;
}
}

std::string VectorSpaceModelInstanceImpl::config( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelInstanceImpl::config");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelInstanceImpl::config", err.what());
	return std::string();
}
}

VectorSpaceModelImpl::~VectorSpaceModelImpl()
{
	if (isConst()) return;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

VectorSpaceModelInstanceInterface* VectorSpaceModelImpl::createInstance( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorSpaceModelInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorSpaceModelInstanceInterface* p0 = new VectorSpaceModelInstanceImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelImpl::createInstance", err.what());
	return 0;
}
}

VectorSpaceModelBuilderInterface* VectorSpaceModelImpl::createBuilder( const std::string& p1) const
{
try
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBuilder);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_VectorSpaceModelBuilder;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	VectorSpaceModelBuilderInterface* p0 = new VectorSpaceModelBuilderImpl( objId_0, ctx(), false, errorhnd());
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "VectorSpaceModelImpl::createBuilder");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "VectorSpaceModelImpl::createBuilder", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::addWeightingFeature");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::addWeightingFeature", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionContextImpl::call");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionContextImpl::call", err.what());
	return 0;
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::addStringParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::addStringParameter", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::addNumericParameter");
	return void();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::addNumericParameter", err.what());
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::createFunctionContext");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::createFunctionContext", err.what());
	return 0;
}
}

std::string WeightingFunctionInstanceImpl::tostring( ) const
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionInstanceImpl::tostring");
	return std::string();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionInstanceImpl::tostring", err.what());
	return std::string();
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
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionImpl::createInstance");
	return 0;
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionImpl::createInstance", err.what());
	return 0;
}
}

FunctionDescription WeightingFunctionImpl::getDescription( ) const
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
	FunctionDescription p0 = serializedMsg.unpackFunctionDescription();;
	return p0;
} catch (const std::bad_alloc&) {
	errorhnd()->report(_TXT("out of memory calling method '%s'"), "WeightingFunctionImpl::getDescription");
	return FunctionDescription();
} catch (const std::exception& err) {
	errorhnd()->report(_TXT("error calling method '%s': %s"), "WeightingFunctionImpl::getDescription", err.what());
	return FunctionDescription();
}
}

