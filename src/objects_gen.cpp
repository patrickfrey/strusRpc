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
#include "objects_gen.hpp"
#include "rpcSerializer.hpp"
#include <iostream>
using namespace strus;

AnalyzerObjectBuilderImpl::~AnalyzerObjectBuilderImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of AnalyzerObjectBuilderImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const TextProcessorInterface* AnalyzerObjectBuilderImpl::getTextProcessor( ) const
{
	std::cerr << "calling method AnalyzerObjectBuilderImpl::getTextProcessor" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTextProcessor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TextProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TextProcessorImpl const_0( objId_0, ctx(), true);
	const TextProcessorInterface* p0 = (const TextProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

SegmenterInterface* AnalyzerObjectBuilderImpl::createSegmenter( const std::string& p1) const
{
	std::cerr << "calling method AnalyzerObjectBuilderImpl::createSegmenter" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createSegmenter);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Segmenter;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterInterface* p0 = new SegmenterImpl( objId_0, ctx());
	return p0;
}

DocumentAnalyzerInterface* AnalyzerObjectBuilderImpl::createDocumentAnalyzer( const std::string& p1) const
{
	std::cerr << "calling method AnalyzerObjectBuilderImpl::createDocumentAnalyzer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentAnalyzer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInterface* p0 = new DocumentAnalyzerImpl( objId_0, ctx());
	return p0;
}

QueryAnalyzerInterface* AnalyzerObjectBuilderImpl::createQueryAnalyzer( ) const
{
	std::cerr << "calling method AnalyzerObjectBuilderImpl::createQueryAnalyzer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryAnalyzer);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryAnalyzer;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryAnalyzerInterface* p0 = new QueryAnalyzerImpl( objId_0, ctx());
	return p0;
}

AttributeReaderImpl::~AttributeReaderImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of AttributeReaderImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index AttributeReaderImpl::elementHandle( const char* p1) const
{
	std::cerr << "calling method AttributeReaderImpl::elementHandle" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packCharp( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

void AttributeReaderImpl::skipDoc( const Index& p1)
{
	std::cerr << "calling method AttributeReaderImpl::skipDoc" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string AttributeReaderImpl::getValue( const Index& p1) const
{
	std::cerr << "calling method AttributeReaderImpl::getValue" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

DatabaseBackupCursorImpl::~DatabaseBackupCursorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DatabaseBackupCursorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool DatabaseBackupCursorImpl::fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
	std::cerr << "calling method DatabaseBackupCursorImpl::fetch" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	enter();
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
}

DatabaseClientImpl::~DatabaseClientImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DatabaseClientImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseClientImpl::close( )
{
	std::cerr << "calling method DatabaseClientImpl::close" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseTransactionInterface* DatabaseClientImpl::createTransaction( )
{
	std::cerr << "calling method DatabaseClientImpl::createTransaction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseTransactionInterface* p0 = new DatabaseTransactionImpl( objId_0, ctx());
	return p0;
}

DatabaseCursorInterface* DatabaseClientImpl::createCursor( const DatabaseOptions& p1) const
{
	std::cerr << "calling method DatabaseClientImpl::createCursor" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, ctx());
	return p0;
}

DatabaseBackupCursorInterface* DatabaseClientImpl::createBackupCursor( ) const
{
	std::cerr << "calling method DatabaseClientImpl::createBackupCursor" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBackupCursor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseBackupCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseBackupCursorInterface* p0 = new DatabaseBackupCursorImpl( objId_0, ctx());
	return p0;
}

void DatabaseClientImpl::writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	std::cerr << "calling method DatabaseClientImpl::writeImm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_writeImm);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseClientImpl::removeImm( const char* p1, std::size_t p2)
{
	std::cerr << "calling method DatabaseClientImpl::removeImm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeImm);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool DatabaseClientImpl::readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const
{
	std::cerr << "calling method DatabaseClientImpl::readValue" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_readValue);
	msg.packBuffer( p1, p2);
	msg.packDatabaseOptions( p4);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p3 = serializedMsg.unpackString();
	return p0;
}

DatabaseCursorImpl::~DatabaseCursorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DatabaseCursorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBound( const char* p1, std::size_t p2, std::size_t p3)
{
	std::cerr << "calling method DatabaseCursorImpl::seekUpperBound" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBound);
	msg.packBuffer( p1, p2);
	msg.packSize( p3);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekFirst( const char* p1, std::size_t p2)
{
	std::cerr << "calling method DatabaseCursorImpl::seekFirst" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekFirst);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekLast( const char* p1, std::size_t p2)
{
	std::cerr << "calling method DatabaseCursorImpl::seekLast" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekLast);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekNext( )
{
	std::cerr << "calling method DatabaseCursorImpl::seekNext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekNext);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekPrev( )
{
	std::cerr << "calling method DatabaseCursorImpl::seekPrev" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekPrev);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::key( ) const
{
	std::cerr << "calling method DatabaseCursorImpl::key" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_key);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::value( ) const
{
	std::cerr << "calling method DatabaseCursorImpl::value" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_value);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*) ctx()->constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseImpl::~DatabaseImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DatabaseImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseClientInterface* DatabaseImpl::createClient( const std::string& p1) const
{
	std::cerr << "calling method DatabaseImpl::createClient" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseClientInterface* p0 = new DatabaseClientImpl( objId_0, ctx());
	return p0;
}

void DatabaseImpl::createDatabase( const std::string& p1) const
{
	std::cerr << "calling method DatabaseImpl::createDatabase" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDatabase);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseImpl::restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const
{
	std::cerr << "calling method DatabaseImpl::restoreDatabase" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_restoreDatabase);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseImpl::destroyDatabase( const std::string& p1) const
{
	std::cerr << "calling method DatabaseImpl::destroyDatabase" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_destroyDatabase);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const char* DatabaseImpl::getConfigDescription( DatabaseInterface::ConfigType p1) const
{
	std::cerr << "calling method DatabaseImpl::getConfigDescription" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char** DatabaseImpl::getConfigParameters( DatabaseInterface::ConfigType p1) const
{
	std::cerr << "calling method DatabaseImpl::getConfigParameters" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char** p0 =  ctx()->constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

DatabaseTransactionImpl::~DatabaseTransactionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DatabaseTransactionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DatabaseCursorInterface* DatabaseTransactionImpl::createCursor( const DatabaseOptions& p1) const
{
	std::cerr << "calling method DatabaseTransactionImpl::createCursor" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, ctx());
	return p0;
}

void DatabaseTransactionImpl::write( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	std::cerr << "calling method DatabaseTransactionImpl::write" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_write);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseTransactionImpl::remove( const char* p1, std::size_t p2)
{
	std::cerr << "calling method DatabaseTransactionImpl::remove" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_remove);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseTransactionImpl::removeSubTree( const char* p1, std::size_t p2)
{
	std::cerr << "calling method DatabaseTransactionImpl::removeSubTree" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeSubTree);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DatabaseTransactionImpl::commit( )
{
	std::cerr << "calling method DatabaseTransactionImpl::commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
}

void DatabaseTransactionImpl::rollback( )
{
	std::cerr << "calling method DatabaseTransactionImpl::rollback" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

DocnoRangeAllocatorImpl::~DocnoRangeAllocatorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DocnoRangeAllocatorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index DocnoRangeAllocatorImpl::allocDocnoRange( const Index& p1)
{
	std::cerr << "calling method DocnoRangeAllocatorImpl::allocDocnoRange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_allocDocnoRange);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

bool DocnoRangeAllocatorImpl::deallocDocnoRange( const Index& p1, const Index& p2)
{
	std::cerr << "calling method DocnoRangeAllocatorImpl::deallocDocnoRange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deallocDocnoRange);
	msg.packIndex( p1);
	msg.packIndex( p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

DocumentAnalyzerInstanceImpl::~DocumentAnalyzerInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DocumentAnalyzerInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentAnalyzerInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	std::cerr << "calling method DocumentAnalyzerInstanceImpl::putInput" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool DocumentAnalyzerInstanceImpl::analyzeNext( analyzer::Document& p1)
{
	std::cerr << "calling method DocumentAnalyzerInstanceImpl::analyzeNext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeNext);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackAnalyzerDocument();
	return p0;
}

DocumentAnalyzerImpl::~DocumentAnalyzerImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of DocumentAnalyzerImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void DocumentAnalyzerImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	std::cerr << "calling method DocumentAnalyzerImpl::addSearchIndexFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw std::runtime_error( "passing non RPC interface object in RPC call");
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
}

void DocumentAnalyzerImpl::addForwardIndexFeature( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	std::cerr << "calling method DocumentAnalyzerImpl::addForwardIndexFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw std::runtime_error( "passing non RPC interface object in RPC call");
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
}

void DocumentAnalyzerImpl::defineMetaData( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
	std::cerr << "calling method DocumentAnalyzerImpl::defineMetaData" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaData);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw std::runtime_error( "passing non RPC interface object in RPC call");
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
}

void DocumentAnalyzerImpl::defineAttribute( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
	std::cerr << "calling method DocumentAnalyzerImpl::defineAttribute" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAttribute);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw std::runtime_error( "passing non RPC interface object in RPC call");
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
}

void DocumentAnalyzerImpl::defineSubDocument( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method DocumentAnalyzerImpl::defineSubDocument" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubDocument);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

analyzer::Document DocumentAnalyzerImpl::analyze( const std::string& p1) const
{
	std::cerr << "calling method DocumentAnalyzerImpl::analyze" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	analyzer::Document p0 = serializedMsg.unpackAnalyzerDocument();;
	return p0;
}

DocumentAnalyzerInstanceInterface* DocumentAnalyzerImpl::createInstance( ) const
{
	std::cerr << "calling method DocumentAnalyzerImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocumentAnalyzerInstanceInterface* p0 = new DocumentAnalyzerInstanceImpl( objId_0, ctx());
	return p0;
}

ForwardIteratorImpl::~ForwardIteratorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of ForwardIteratorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void ForwardIteratorImpl::skipDoc( const Index& p1)
{
	std::cerr << "calling method ForwardIteratorImpl::skipDoc" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index ForwardIteratorImpl::skipPos( const Index& p1)
{
	std::cerr << "calling method ForwardIteratorImpl::skipPos" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

std::string ForwardIteratorImpl::fetch( )
{
	std::cerr << "calling method ForwardIteratorImpl::fetch" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

InvAclIteratorImpl::~InvAclIteratorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of InvAclIteratorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index InvAclIteratorImpl::skipDoc( const Index& p1)
{
	std::cerr << "calling method InvAclIteratorImpl::skipDoc" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

MetaDataReaderImpl::~MetaDataReaderImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of MetaDataReaderImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool MetaDataReaderImpl::hasElement( const std::string& p1) const
{
	std::cerr << "calling method MetaDataReaderImpl::hasElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_hasElement);
	msg.packString( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

Index MetaDataReaderImpl::elementHandle( const std::string& p1) const
{
	std::cerr << "calling method MetaDataReaderImpl::elementHandle" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packString( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index MetaDataReaderImpl::nofElements( ) const
{
	std::cerr << "calling method MetaDataReaderImpl::nofElements" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofElements);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

void MetaDataReaderImpl::skipDoc( const Index& p1)
{
	std::cerr << "calling method MetaDataReaderImpl::skipDoc" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

ArithmeticVariant MetaDataReaderImpl::getValue( const Index& p1) const
{
	std::cerr << "calling method MetaDataReaderImpl::getValue" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	ArithmeticVariant p0 = serializedMsg.unpackArithmeticVariant();;
	return p0;
}

const char* MetaDataReaderImpl::getType( const Index& p1) const
{
	std::cerr << "calling method MetaDataReaderImpl::getType" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getType);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char* MetaDataReaderImpl::getName( const Index& p1) const
{
	std::cerr << "calling method MetaDataReaderImpl::getName" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getName);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

NormalizerExecutionContextImpl::~NormalizerExecutionContextImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of NormalizerExecutionContextImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string NormalizerExecutionContextImpl::normalize( const char* p1, std::size_t p2)
{
	std::cerr << "calling method NormalizerExecutionContextImpl::normalize" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

NormalizerFunctionInstanceImpl::~NormalizerFunctionInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of NormalizerFunctionInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

NormalizerExecutionContextInterface* NormalizerFunctionInstanceImpl::createExecutionContext( ) const
{
	std::cerr << "calling method NormalizerFunctionInstanceImpl::createExecutionContext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createExecutionContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerExecutionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerExecutionContextInterface* p0 = new NormalizerExecutionContextImpl( objId_0, ctx());
	return p0;
}

NormalizerFunctionImpl::~NormalizerFunctionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of NormalizerFunctionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

NormalizerFunctionInstanceInterface* NormalizerFunctionImpl::createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	std::cerr << "calling method NormalizerFunctionImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerFunctionInstanceInterface* p0 = new NormalizerFunctionInstanceImpl( objId_0, ctx());
	return p0;
}

PeerStorageTransactionImpl::~PeerStorageTransactionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of PeerStorageTransactionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PeerStorageTransactionImpl::updateNofDocumentsInsertedChange( const GlobalCounter& p1)
{
	std::cerr << "calling method PeerStorageTransactionImpl::updateNofDocumentsInsertedChange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateNofDocumentsInsertedChange);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PeerStorageTransactionImpl::updateDocumentFrequencyChange( const char* p1, const char* p2, const GlobalCounter& p3)
{
	std::cerr << "calling method PeerStorageTransactionImpl::updateDocumentFrequencyChange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packGlobalCounter( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void PeerStorageTransactionImpl::commit( )
{
	std::cerr << "calling method PeerStorageTransactionImpl::commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
}

void PeerStorageTransactionImpl::rollback( )
{
	std::cerr << "calling method PeerStorageTransactionImpl::rollback" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PostingIteratorImpl::~PostingIteratorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of PostingIteratorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

Index PostingIteratorImpl::skipDoc( const Index& p1)
{
	std::cerr << "calling method PostingIteratorImpl::skipDoc" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::skipPos( const Index& p1)
{
	std::cerr << "calling method PostingIteratorImpl::skipPos" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

const char* PostingIteratorImpl::featureid( ) const
{
	std::cerr << "calling method PostingIteratorImpl::featureid" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureid);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

std::vector<const PostingIteratorInterface*> PostingIteratorImpl::subExpressions( bool p1) const
{
	throw std::runtime_error("the method 'subExpressions' is not implemented for RPC");
}

GlobalCounter PostingIteratorImpl::documentFrequency( ) const
{
	std::cerr << "calling method PostingIteratorImpl::documentFrequency" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

unsigned int PostingIteratorImpl::frequency( )
{
	std::cerr << "calling method PostingIteratorImpl::frequency" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_frequency);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
}

Index PostingIteratorImpl::docno( ) const
{
	std::cerr << "calling method PostingIteratorImpl::docno" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_docno);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::posno( ) const
{
	std::cerr << "calling method PostingIteratorImpl::posno" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_posno);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

PostingJoinOperatorImpl::~PostingJoinOperatorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of PostingJoinOperatorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PostingIteratorInterface* PostingJoinOperatorImpl::createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2) const
{
	throw std::runtime_error("the method 'createResultIterator' is not implemented for RPC");
}

QueryAnalyzerImpl::~QueryAnalyzerImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of QueryAnalyzerImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryAnalyzerImpl::definePhraseType( const std::string& p1, const std::string& p2, TokenizerFunctionInstanceInterface* p3, const std::vector<NormalizerFunctionInstanceInterface*>& p4)
{
	std::cerr << "calling method QueryAnalyzerImpl::definePhraseType" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePhraseType);
	msg.packString( p1);
	msg.packString( p2);
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		const RpcInterfaceStub* impl_4 = dynamic_cast<const RpcInterfaceStub*>(p4[ii]);
		if (!impl_4) throw std::runtime_error( "passing non RPC interface object in RPC call");
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
}

std::vector<analyzer::Term> QueryAnalyzerImpl::analyzePhrase( const std::string& p1, const std::string& p2) const
{
	std::cerr << "calling method QueryAnalyzerImpl::analyzePhrase" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhrase);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	enter();
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
}

QueryEvalImpl::~QueryEvalImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of QueryEvalImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryEvalImpl::addTerm( const std::string& p1, const std::string& p2, const std::string& p3)
{
	std::cerr << "calling method QueryEvalImpl::addTerm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryEvalImpl::addSelectionFeature( const std::string& p1)
{
	std::cerr << "calling method QueryEvalImpl::addSelectionFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectionFeature);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryEvalImpl::addRestrictionFeature( const std::string& p1)
{
	std::cerr << "calling method QueryEvalImpl::addRestrictionFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addRestrictionFeature);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryEvalImpl::addSummarizerFunction( const std::string& p1, SummarizerFunctionInstanceInterface* p2, const std::vector<QueryEvalInterface::SummarizerFeatureParameter>& p3, const std::string& p4)
{
	std::cerr << "calling method QueryEvalImpl::addSummarizerFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizerFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packSummarizerFeatureParameter( p3[ii]);
	}
	msg.packString( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
}

void QueryEvalImpl::addWeightingFunction( const std::string& p1, WeightingFunctionInstanceInterface* p2, const std::vector<std::string>& p3)
{
	std::cerr << "calling method QueryEvalImpl::addWeightingFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addWeightingFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packString( p3[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
}

QueryInterface* QueryEvalImpl::createQuery( const StorageClientInterface* p1) const
{
	std::cerr << "calling method QueryEvalImpl::createQuery" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQuery);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Query;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryInterface* p0 = new QueryImpl( objId_0, ctx());
	return p0;
}

QueryImpl::~QueryImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of QueryImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method QueryImpl::pushTerm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::pushExpression( const PostingJoinOperatorInterface* p1, std::size_t p2, int p3)
{
	std::cerr << "calling method QueryImpl::pushExpression" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packSize( p2);
	msg.packInt( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::pushDuplicate( )
{
	std::cerr << "calling method QueryImpl::pushDuplicate" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushDuplicate);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::attachVariable( const std::string& p1)
{
	std::cerr << "calling method QueryImpl::attachVariable" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::defineFeature( const std::string& p1, float p2)
{
	std::cerr << "calling method QueryImpl::defineFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4)
{
	std::cerr << "calling method QueryImpl::defineMetaDataRestriction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaDataRestriction);
	msg.packCompareOperator( p1);
	msg.packString( p2);
	msg.packArithmeticVariant( p3);
	msg.packBool( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::setMaxNofRanks( std::size_t p1)
{
	std::cerr << "calling method QueryImpl::setMaxNofRanks" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMaxNofRanks);
	msg.packSize( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::setMinRank( std::size_t p1)
{
	std::cerr << "calling method QueryImpl::setMinRank" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMinRank);
	msg.packSize( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryImpl::setUserName( const std::string& p1)
{
	std::cerr << "calling method QueryImpl::setUserName" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserName);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<ResultDocument> QueryImpl::evaluate( )
{
	std::cerr << "calling method QueryImpl::evaluate" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<ResultDocument> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		ResultDocument elem_p0 = serializedMsg.unpackResultDocument();
		p0.push_back( elem_p0);
	}
	return p0;
}

QueryProcessorImpl::~QueryProcessorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of QueryProcessorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void QueryProcessorImpl::definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2)
{
	std::cerr << "calling method QueryProcessorImpl::definePostingJoinOperator" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePostingJoinOperator);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
}

const PostingJoinOperatorInterface* QueryProcessorImpl::getPostingJoinOperator( const std::string& p1) const
{
	std::cerr << "calling method QueryProcessorImpl::getPostingJoinOperator" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPostingJoinOperator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PostingJoinOperator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PostingJoinOperatorImpl const_0( objId_0, ctx(), true);
	const PostingJoinOperatorInterface* p0 = (const PostingJoinOperatorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

void QueryProcessorImpl::defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2)
{
	std::cerr << "calling method QueryProcessorImpl::defineWeightingFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWeightingFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
}

const WeightingFunctionInterface* QueryProcessorImpl::getWeightingFunction( const std::string& p1) const
{
	std::cerr << "calling method QueryProcessorImpl::getWeightingFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWeightingFunction);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingFunctionImpl const_0( objId_0, ctx(), true);
	const WeightingFunctionInterface* p0 = (const WeightingFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

void QueryProcessorImpl::defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2)
{
	std::cerr << "calling method QueryProcessorImpl::defineSummarizerFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSummarizerFunction);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
}

const SummarizerFunctionInterface* QueryProcessorImpl::getSummarizerFunction( const std::string& p1) const
{
	std::cerr << "calling method QueryProcessorImpl::getSummarizerFunction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummarizerFunction);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerFunctionImpl const_0( objId_0, ctx(), true);
	const SummarizerFunctionInterface* p0 = (const SummarizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

SegmenterInstanceImpl::~SegmenterInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of SegmenterInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SegmenterInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	std::cerr << "calling method SegmenterInstanceImpl::putInput" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool SegmenterInstanceImpl::getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4)
{
	std::cerr << "calling method SegmenterInstanceImpl::getNext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	enter();
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
}

SegmenterImpl::~SegmenterImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of SegmenterImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SegmenterImpl::defineSelectorExpression( int p1, const std::string& p2)
{
	std::cerr << "calling method SegmenterImpl::defineSelectorExpression" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSelectorExpression);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SegmenterImpl::defineSubSection( int p1, int p2, const std::string& p3)
{
	std::cerr << "calling method SegmenterImpl::defineSubSection" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubSection);
	msg.packInt( p1);
	msg.packInt( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

SegmenterInstanceInterface* SegmenterImpl::createInstance( ) const
{
	std::cerr << "calling method SegmenterImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SegmenterInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SegmenterInstanceInterface* p0 = new SegmenterInstanceImpl( objId_0, ctx());
	return p0;
}

StorageAlterMetaDataTableImpl::~StorageAlterMetaDataTableImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageAlterMetaDataTableImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::addElement( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::addElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::alterElement( const std::string& p1, const std::string& p2, const std::string& p3)
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::alterElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_alterElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::renameElement( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::renameElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_renameElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::deleteElement( const std::string& p1)
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::deleteElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteElement);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::clearElement( const std::string& p1)
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::clearElement" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearElement);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageAlterMetaDataTableImpl::commit( )
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
}

void StorageAlterMetaDataTableImpl::rollback( )
{
	std::cerr << "calling method StorageAlterMetaDataTableImpl::rollback" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageClientImpl::~StorageClientImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageClientImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageClientImpl::close( )
{
	std::cerr << "calling method StorageClientImpl::close" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2) const
{
	std::cerr << "calling method StorageClientImpl::createTermPostingIterator" << std::endl;
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
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, ctx());
	return p0;
}

ForwardIteratorInterface* StorageClientImpl::createForwardIterator( const std::string& p1) const
{
	std::cerr << "calling method StorageClientImpl::createForwardIterator" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createForwardIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_ForwardIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ForwardIteratorInterface* p0 = new ForwardIteratorImpl( objId_0, ctx());
	return p0;
}

InvAclIteratorInterface* StorageClientImpl::createInvAclIterator( const std::string& p1) const
{
	std::cerr << "calling method StorageClientImpl::createInvAclIterator" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInvAclIterator);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_InvAclIterator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	InvAclIteratorInterface* p0 = new InvAclIteratorImpl( objId_0, ctx());
	return p0;
}

GlobalCounter StorageClientImpl::globalNofDocumentsInserted( ) const
{
	std::cerr << "calling method StorageClientImpl::globalNofDocumentsInserted" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalNofDocumentsInserted);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localNofDocumentsInserted( ) const
{
	std::cerr << "calling method StorageClientImpl::localNofDocumentsInserted" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localNofDocumentsInserted);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

GlobalCounter StorageClientImpl::globalDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	std::cerr << "calling method StorageClientImpl::globalDocumentFrequency" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	std::cerr << "calling method StorageClientImpl::localDocumentFrequency" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index StorageClientImpl::maxDocumentNumber( ) const
{
	std::cerr << "calling method StorageClientImpl::maxDocumentNumber" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_maxDocumentNumber);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index StorageClientImpl::documentNumber( const std::string& p1) const
{
	std::cerr << "calling method StorageClientImpl::documentNumber" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentNumber);
	msg.packString( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

MetaDataReaderInterface* StorageClientImpl::createMetaDataReader( ) const
{
	std::cerr << "calling method StorageClientImpl::createMetaDataReader" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataReader);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_MetaDataReader;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	MetaDataReaderInterface* p0 = new MetaDataReaderImpl( objId_0, ctx());
	return p0;
}

AttributeReaderInterface* StorageClientImpl::createAttributeReader( ) const
{
	std::cerr << "calling method StorageClientImpl::createAttributeReader" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAttributeReader);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_AttributeReader;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	AttributeReaderInterface* p0 = new AttributeReaderImpl( objId_0, ctx());
	return p0;
}

DocnoRangeAllocatorInterface* StorageClientImpl::createDocnoRangeAllocator( )
{
	std::cerr << "calling method StorageClientImpl::createDocnoRangeAllocator" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocnoRangeAllocator);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_DocnoRangeAllocator;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DocnoRangeAllocatorInterface* p0 = new DocnoRangeAllocatorImpl( objId_0, ctx());
	return p0;
}

StorageTransactionInterface* StorageClientImpl::createTransaction( )
{
	std::cerr << "calling method StorageClientImpl::createTransaction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageTransactionInterface* p0 = new StorageTransactionImpl( objId_0, ctx());
	return p0;
}

PeerStorageTransactionInterface* StorageClientImpl::createPeerStorageTransaction( )
{
	std::cerr << "calling method StorageClientImpl::createPeerStorageTransaction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPeerStorageTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_PeerStorageTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	PeerStorageTransactionInterface* p0 = new PeerStorageTransactionImpl( objId_0, ctx());
	return p0;
}

void StorageClientImpl::defineStoragePeerInterface( const StoragePeerInterface* p1, bool p2)
{
	std::cerr << "calling method StorageClientImpl::defineStoragePeerInterface" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineStoragePeerInterface);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packBool( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageDocumentInterface* StorageClientImpl::createDocumentChecker( const std::string& p1, const std::string& p2) const
{
	std::cerr << "calling method StorageClientImpl::createDocumentChecker" << std::endl;
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
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, ctx());
	return p0;
}

void StorageClientImpl::checkStorage( std::ostream& p1) const
{
	throw std::runtime_error("the method 'checkStorage' is not implemented for RPC");
}

StorageDumpInterface* StorageClientImpl::createDump( ) const
{
	std::cerr << "calling method StorageClientImpl::createDump" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDump;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDumpInterface* p0 = new StorageDumpImpl( objId_0, ctx());
	return p0;
}

StorageDocumentImpl::~StorageDocumentImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageDocumentImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	std::cerr << "calling method StorageDocumentImpl::addSearchIndexTerm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	std::cerr << "calling method StorageDocumentImpl::addForwardIndexTerm" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::setMetaData( const std::string& p1, const ArithmeticVariant& p2)
{
	std::cerr << "calling method StorageDocumentImpl::setMetaData" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::setAttribute( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method StorageDocumentImpl::setAttribute" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::setUserAccessRight( const std::string& p1)
{
	std::cerr << "calling method StorageDocumentImpl::setUserAccessRight" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageDocumentImpl::done( )
{
	std::cerr << "calling method StorageDocumentImpl::done" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
}

StorageDumpImpl::~StorageDumpImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageDumpImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool StorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
	std::cerr << "calling method StorageDumpImpl::nextChunk" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*) ctx()->constConstructor()->get( bp1, p2);
	return p0;
}

StorageImpl::~StorageImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageClientInterface* StorageImpl::createClient( const std::string& p1, DatabaseClientInterface* p2) const
{
	std::cerr << "calling method StorageImpl::createClient" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageClientInterface* p0 = new StorageClientImpl( objId_0, ctx());
	RpcInterfaceStub* done_2 = dynamic_cast<RpcInterfaceStub*>(p2);
	done_2->release();
	delete p2;
	return p0;
}

void StorageImpl::createStorage( const std::string& p1, DatabaseClientInterface* p2) const
{
	std::cerr << "calling method StorageImpl::createStorage" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageAlterMetaDataTableInterface* StorageImpl::createAlterMetaDataTable( DatabaseClientInterface* p1) const
{
	std::cerr << "calling method StorageImpl::createAlterMetaDataTable" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, ctx());
	RpcInterfaceStub* done_1 = dynamic_cast<RpcInterfaceStub*>(p1);
	done_1->release();
	delete p1;
	return p0;
}

const char* StorageImpl::getConfigDescription( StorageInterface::ConfigType p1) const
{
	std::cerr << "calling method StorageImpl::getConfigDescription" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char* p0 =  ctx()->constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char** StorageImpl::getConfigParameters( StorageInterface::ConfigType p1) const
{
	std::cerr << "calling method StorageImpl::getConfigParameters" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	const char** p0 =  ctx()->constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

StorageObjectBuilderImpl::~StorageObjectBuilderImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageObjectBuilderImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

const StorageInterface* StorageObjectBuilderImpl::getStorage( ) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::getStorage" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getStorage);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Storage;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageImpl const_0( objId_0, ctx(), true);
	const StorageInterface* p0 = (const StorageImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

const DatabaseInterface* StorageObjectBuilderImpl::getDatabase( const std::string& p1) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::getDatabase" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getDatabase);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_Database;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	DatabaseImpl const_0( objId_0, ctx(), true);
	const DatabaseInterface* p0 = (const DatabaseImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

const QueryProcessorInterface* StorageObjectBuilderImpl::getQueryProcessor( ) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::getQueryProcessor" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getQueryProcessor);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryProcessor;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryProcessorImpl const_0( objId_0, ctx(), true);
	const QueryProcessorInterface* p0 = (const QueryProcessorImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

StorageClientInterface* StorageObjectBuilderImpl::createStorageClient( const std::string& p1) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::createStorageClient" << std::endl;
	if (p1.empty()) return new StorageClientImpl( 0, ctx());
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorageClient);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageClient;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageClientInterface* p0 = new StorageClientImpl( objId_0, ctx());
	return p0;
}

StorageAlterMetaDataTableInterface* StorageObjectBuilderImpl::createAlterMetaDataTable( const std::string& p1) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::createAlterMetaDataTable" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, ctx());
	return p0;
}

QueryEvalInterface* StorageObjectBuilderImpl::createQueryEval( ) const
{
	std::cerr << "calling method StorageObjectBuilderImpl::createQueryEval" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryEval);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_QueryEval;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	QueryEvalInterface* p0 = new QueryEvalImpl( objId_0, ctx());
	return p0;
}

StoragePeerImpl::~StoragePeerImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StoragePeerImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StoragePeerTransactionInterface* StoragePeerImpl::createTransaction( ) const
{
	std::cerr << "calling method StoragePeerImpl::createTransaction" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StoragePeerTransaction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StoragePeerTransactionInterface* p0 = new StoragePeerTransactionImpl( objId_0, ctx());
	return p0;
}

StoragePeerTransactionImpl::~StoragePeerTransactionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StoragePeerTransactionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StoragePeerTransactionImpl::populateNofDocumentsInsertedChange( int p1)
{
	std::cerr << "calling method StoragePeerTransactionImpl::populateNofDocumentsInsertedChange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StoragePeerTransactionImpl::populateDocumentFrequencyChange( const char* p1, const char* p2, int p3, bool p4)
{
	std::cerr << "calling method StoragePeerTransactionImpl::populateDocumentFrequencyChange" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packInt( p3);
	msg.packBool( p4);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StoragePeerTransactionImpl::try_commit( )
{
	std::cerr << "calling method StoragePeerTransactionImpl::try_commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_try_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StoragePeerTransactionImpl::final_commit( )
{
	std::cerr << "calling method StoragePeerTransactionImpl::final_commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_final_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StoragePeerTransactionImpl::rollback( )
{
	std::cerr << "calling method StoragePeerTransactionImpl::rollback" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageTransactionImpl::~StorageTransactionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of StorageTransactionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

StorageDocumentInterface* StorageTransactionImpl::createDocument( const std::string& p1, const Index& p2)
{
	std::cerr << "calling method StorageTransactionImpl::createDocument" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocument);
	msg.packString( p1);
	msg.packIndex( p2);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_StorageDocument;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, ctx());
	return p0;
}

void StorageTransactionImpl::deleteDocument( const std::string& p1)
{
	std::cerr << "calling method StorageTransactionImpl::deleteDocument" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteDocument);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageTransactionImpl::deleteUserAccessRights( const std::string& p1)
{
	std::cerr << "calling method StorageTransactionImpl::deleteUserAccessRights" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteUserAccessRights);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void StorageTransactionImpl::commit( )
{
	std::cerr << "calling method StorageTransactionImpl::commit" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	ctx()->rpc_synchronize();
}

void StorageTransactionImpl::rollback( )
{
	std::cerr << "calling method StorageTransactionImpl::rollback" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

SummarizerExecutionContextImpl::~SummarizerExecutionContextImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of SummarizerExecutionContextImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SummarizerExecutionContextImpl::addSummarizationFeature( const std::string& p1, PostingIteratorInterface* p2, const std::vector<SummarizationVariable>& p3)
{
	std::cerr << "calling method SummarizerExecutionContextImpl::addSummarizationFeature" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizationFeature);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packSummarizationVariable( p3[ii]);
	}
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<SummarizerExecutionContextInterface::SummaryElement> SummarizerExecutionContextImpl::getSummary( const Index& p1)
{
	std::cerr << "calling method SummarizerExecutionContextImpl::getSummary" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummary);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::vector<SummarizerExecutionContextInterface::SummaryElement> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		SummarizerExecutionContextInterface::SummaryElement elem_p0 = serializedMsg.unpackSummaryElement();
		p0.push_back( elem_p0);
	}
	return p0;
}

SummarizerFunctionInstanceImpl::~SummarizerFunctionInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of SummarizerFunctionInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SummarizerFunctionInstanceImpl::addStringParameter( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method SummarizerFunctionInstanceImpl::addStringParameter" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addStringParameter);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void SummarizerFunctionInstanceImpl::addNumericParameter( const std::string& p1, const ArithmeticVariant& p2)
{
	std::cerr << "calling method SummarizerFunctionInstanceImpl::addNumericParameter" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNumericParameter);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

SummarizerExecutionContextInterface* SummarizerFunctionInstanceImpl::createExecutionContext( const StorageClientInterface* p1, MetaDataReaderInterface* p2) const
{
	std::cerr << "calling method SummarizerFunctionInstanceImpl::createExecutionContext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createExecutionContext);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerExecutionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerExecutionContextInterface* p0 = new SummarizerExecutionContextImpl( objId_0, ctx());
	return p0;
}

std::string SummarizerFunctionInstanceImpl::tostring( ) const
{
	std::cerr << "calling method SummarizerFunctionInstanceImpl::tostring" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tostring);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

SummarizerFunctionImpl::~SummarizerFunctionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of SummarizerFunctionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

SummarizerFunctionInstanceInterface* SummarizerFunctionImpl::createInstance( const QueryProcessorInterface* p1) const
{
	std::cerr << "calling method SummarizerFunctionImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_SummarizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	SummarizerFunctionInstanceInterface* p0 = new SummarizerFunctionInstanceImpl( objId_0, ctx());
	return p0;
}

TextProcessorImpl::~TextProcessorImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of TextProcessorImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void TextProcessorImpl::addResourcePath( const std::string& p1)
{
	std::cerr << "calling method TextProcessorImpl::addResourcePath" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::string TextProcessorImpl::getResourcePath( const std::string& p1) const
{
	std::cerr << "calling method TextProcessorImpl::getResourcePath" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

const TokenizerFunctionInterface* TextProcessorImpl::getTokenizer( const std::string& p1) const
{
	std::cerr << "calling method TextProcessorImpl::getTokenizer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTokenizer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerFunctionImpl const_0( objId_0, ctx(), true);
	const TokenizerFunctionInterface* p0 = (const TokenizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

const NormalizerFunctionInterface* TextProcessorImpl::getNormalizer( const std::string& p1) const
{
	std::cerr << "calling method TextProcessorImpl::getNormalizer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNormalizer);
	msg.packString( p1);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_NormalizerFunction;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	NormalizerFunctionImpl const_0( objId_0, ctx(), true);
	const NormalizerFunctionInterface* p0 = (const NormalizerFunctionImpl*)ctx()->constConstructor()->getLongLiving( &const_0, sizeof(const_0));
	return p0;
}

void TextProcessorImpl::defineTokenizer( const std::string& p1, const TokenizerFunctionInterface* p2)
{
	std::cerr << "calling method TextProcessorImpl::defineTokenizer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenizer);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void TextProcessorImpl::defineNormalizer( const std::string& p1, const NormalizerFunctionInterface* p2)
{
	std::cerr << "calling method TextProcessorImpl::defineNormalizer" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineNormalizer);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

TokenizerExecutionContextImpl::~TokenizerExecutionContextImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of TokenizerExecutionContextImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

std::vector<analyzer::Token> TokenizerExecutionContextImpl::tokenize( const char* p1, std::size_t p2)
{
	std::cerr << "calling method TokenizerExecutionContextImpl::tokenize" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	enter();
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
}

TokenizerFunctionInstanceImpl::~TokenizerFunctionInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of TokenizerFunctionInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

bool TokenizerFunctionInstanceImpl::concatBeforeTokenize( ) const
{
	std::cerr << "calling method TokenizerFunctionInstanceImpl::concatBeforeTokenize" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_concatBeforeTokenize);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

TokenizerExecutionContextInterface* TokenizerFunctionInstanceImpl::createExecutionContext( ) const
{
	std::cerr << "calling method TokenizerFunctionInstanceImpl::createExecutionContext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createExecutionContext);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerExecutionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerExecutionContextInterface* p0 = new TokenizerExecutionContextImpl( objId_0, ctx());
	return p0;
}

TokenizerFunctionImpl::~TokenizerFunctionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of TokenizerFunctionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

TokenizerFunctionInstanceInterface* TokenizerFunctionImpl::createInstance( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	std::cerr << "calling method TokenizerFunctionImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_TokenizerFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	TokenizerFunctionInstanceInterface* p0 = new TokenizerFunctionInstanceImpl( objId_0, ctx());
	return p0;
}

WeightingExecutionContextImpl::~WeightingExecutionContextImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of WeightingExecutionContextImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

float WeightingExecutionContextImpl::call( const Index& p1)
{
	std::cerr << "calling method WeightingExecutionContextImpl::call" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packIndex( p1);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	float p0 = serializedMsg.unpackFloat();;
	return p0;
}

WeightingFunctionInstanceImpl::~WeightingFunctionInstanceImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of WeightingFunctionInstanceImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void WeightingFunctionInstanceImpl::addStringParameter( const std::string& p1, const std::string& p2)
{
	std::cerr << "calling method WeightingFunctionInstanceImpl::addStringParameter" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addStringParameter);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

void WeightingFunctionInstanceImpl::addNumericParameter( const std::string& p1, const ArithmeticVariant& p2)
{
	std::cerr << "calling method WeightingFunctionInstanceImpl::addNumericParameter" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addNumericParameter);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

WeightingExecutionContextInterface* WeightingFunctionInstanceImpl::createExecutionContext( const StorageClientInterface* p1, PostingIteratorInterface* p2, MetaDataReaderInterface* p3) const
{
	std::cerr << "calling method WeightingFunctionInstanceImpl::createExecutionContext" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createExecutionContext);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingExecutionContext;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingExecutionContextInterface* p0 = new WeightingExecutionContextImpl( objId_0, ctx());
	return p0;
}

std::string WeightingFunctionInstanceImpl::tostring( ) const
{
	std::cerr << "calling method WeightingFunctionInstanceImpl::tostring" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tostring);
	msg.packCrc32();
	enter();
	std::string answer = ctx()->rpc_sendRequest( msg.content());
	RpcDeserializer serializedMsg( answer.c_str(), answer.size());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

WeightingFunctionImpl::~WeightingFunctionImpl()
{
	if (isConst()) return;
	std::cerr << "calling destructor of WeightingFunctionImpl" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
}

WeightingFunctionInstanceInterface* WeightingFunctionImpl::createInstance( ) const
{
	std::cerr << "calling method WeightingFunctionImpl::createInstance" << std::endl;
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	unsigned int objId_0 = ctx()->newObjId();
	unsigned char classId_0 = (unsigned char)ClassId_WeightingFunctionInstance;
	msg.packObject( classId_0, objId_0);
	msg.packCrc32();
	ctx()->rpc_sendMessage( msg.content());
	WeightingFunctionInstanceInterface* p0 = new WeightingFunctionInstanceImpl( objId_0, ctx());
	return p0;
}

