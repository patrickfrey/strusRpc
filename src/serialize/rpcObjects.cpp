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
#include "rpcObjects.hpp"
#include "rpcSerializer.hpp"

using namespace strus;

AnalyzerObjectBuilderImpl::~AnalyzerObjectBuilderImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const TextProcessorInterface* AnalyzerObjectBuilderImpl::getTextProcessor( ) const
{
	throw std::runtime_error("the method 'getTextProcessor' is not implemented for RPC");
}

SegmenterInterface* AnalyzerObjectBuilderImpl::createSegmenter( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createSegmenter);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_Segmenter) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	SegmenterInterface* p0 = new SegmenterImpl( objId_0, messaging());
	return p0;
}

DocumentAnalyzerInterface* AnalyzerObjectBuilderImpl::createDocumentAnalyzer( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentAnalyzer);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DocumentAnalyzer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DocumentAnalyzerInterface* p0 = new DocumentAnalyzerImpl( objId_0, messaging());
	return p0;
}

QueryAnalyzerInterface* AnalyzerObjectBuilderImpl::createQueryAnalyzer( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryAnalyzer);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_QueryAnalyzer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	QueryAnalyzerInterface* p0 = new QueryAnalyzerImpl( objId_0, messaging());
	return p0;
}

AttributeReaderImpl::~AttributeReaderImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index AttributeReaderImpl::elementHandle( const char* p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packCharp( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

void AttributeReaderImpl::skipDoc( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string AttributeReaderImpl::getValue( const Index& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

DatabaseBackupCursorImpl::~DatabaseBackupCursorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DatabaseBackupCursorImpl::fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*)constConstructor()->get( bp1, p2);
	const char* bp3;
	serializedMsg.unpackBuffer( bp3, p4);
	p3 = (const char*)constConstructor()->get( bp3, p4);
	return p0;
}

DatabaseClientImpl::~DatabaseClientImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseClientImpl::close( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseTransactionInterface* DatabaseClientImpl::createTransaction( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DatabaseTransaction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DatabaseTransactionInterface* p0 = new DatabaseTransactionImpl( objId_0, messaging());
	return p0;
}

DatabaseCursorInterface* DatabaseClientImpl::createCursor( const DatabaseOptions& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DatabaseCursor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, messaging());
	return p0;
}

DatabaseBackupCursorInterface* DatabaseClientImpl::createBackupCursor( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBackupCursor);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DatabaseBackupCursor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DatabaseBackupCursorInterface* p0 = new DatabaseBackupCursorImpl( objId_0, messaging());
	return p0;
}

void DatabaseClientImpl::writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_writeImm);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseClientImpl::removeImm( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeImm);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DatabaseClientImpl::readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_readValue);
	msg.packBuffer( p1, p2);
	msg.packDatabaseOptions( p4);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p3 = serializedMsg.unpackString();
	return p0;
}

DatabaseCursorImpl::~DatabaseCursorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBound( const char* p1, std::size_t p2, std::size_t p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBound);
	msg.packBuffer( p1, p2);
	msg.packSize( p3);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekFirst( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekFirst);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekLast( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekLast);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekNext( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekPrev( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekPrev);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::key( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_key);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::value( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_value);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	DatabaseCursorInterface::Slice slice0 = serializedMsg.unpackSlice();
	DatabaseCursorInterface::Slice p0 = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice0.ptr(), slice0.size()), slice0.size());;
	return p0;
}

DatabaseImpl::~DatabaseImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseClientInterface* DatabaseImpl::createClient( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DatabaseClientInterface* p0 = new DatabaseClientImpl( objId_0, messaging());
	return p0;
}

void DatabaseImpl::createDatabase( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDatabase);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseImpl::restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_restoreDatabase);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseImpl::destroyDatabase( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_destroyDatabase);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char* DatabaseImpl::getConfigDescription( DatabaseInterface::ConfigType p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char* p0 = constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char** DatabaseImpl::getConfigParameters( DatabaseInterface::ConfigType p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

DatabaseTransactionImpl::~DatabaseTransactionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseCursorInterface* DatabaseTransactionImpl::createCursor( const DatabaseOptions& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DatabaseCursor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DatabaseCursorInterface* p0 = new DatabaseCursorImpl( objId_0, messaging());
	return p0;
}

void DatabaseTransactionImpl::write( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_write);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::remove( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_remove);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::removeSubTree( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeSubTree);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void DatabaseTransactionImpl::rollback( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

DocnoRangeAllocatorImpl::~DocnoRangeAllocatorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index DocnoRangeAllocatorImpl::allocDocnoRange( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_allocDocnoRange);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

bool DocnoRangeAllocatorImpl::deallocDocnoRange( const Index& p1, const Index& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deallocDocnoRange);
	msg.packIndex( p1);
	msg.packIndex( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

DocumentAnalyzerInstanceImpl::~DocumentAnalyzerInstanceImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DocumentAnalyzerInstanceImpl::analyzeNext( analyzer::Document& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackAnalyzerDocument();
	return p0;
}

DocumentAnalyzerImpl::~DocumentAnalyzerImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTokenizerConfig( p3);
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packNormalizerConfig( p4[ii]);
	}
	msg.packFeatureOptions( p5);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::addForwardIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTokenizerConfig( p3);
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packNormalizerConfig( p4[ii]);
	}
	msg.packFeatureOptions( p5);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::defineMetaData( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaData);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTokenizerConfig( p3);
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packNormalizerConfig( p4[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::defineAttribute( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTokenizerConfig( p3);
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packNormalizerConfig( p4[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::defineSubDocument( const std::string& p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubDocument);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

analyzer::Document DocumentAnalyzerImpl::analyze( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	analyzer::Document p0 = serializedMsg.unpackAnalyzerDocument();;
	return p0;
}

DocumentAnalyzerInstanceInterface* DocumentAnalyzerImpl::createInstance( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DocumentAnalyzerInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DocumentAnalyzerInstanceInterface* p0 = new DocumentAnalyzerInstanceImpl( objId_0, messaging());
	return p0;
}

ForwardIteratorImpl::~ForwardIteratorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void ForwardIteratorImpl::skipDoc( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index ForwardIteratorImpl::skipPos( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

std::string ForwardIteratorImpl::fetch( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

InvAclIteratorImpl::~InvAclIteratorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index InvAclIteratorImpl::skipDoc( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

MetaDataReaderImpl::~MetaDataReaderImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool MetaDataReaderImpl::hasElement( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_hasElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

Index MetaDataReaderImpl::elementHandle( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index MetaDataReaderImpl::nofElements( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofElements);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

void MetaDataReaderImpl::skipDoc( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

ArithmeticVariant MetaDataReaderImpl::getValue( const Index& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	ArithmeticVariant p0 = serializedMsg.unpackArithmeticVariant();;
	return p0;
}

const char* MetaDataReaderImpl::getType( const Index& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getType);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char* p0 = constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char* MetaDataReaderImpl::getName( const Index& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getName);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char* p0 = constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

NormalizerConstructorImpl::~NormalizerConstructorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

NormalizerInterface* NormalizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_create);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_Normalizer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	NormalizerInterface* p0 = new NormalizerImpl( objId_0, messaging());
	return p0;
}

NormalizerInstanceImpl::~NormalizerInstanceImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string NormalizerInstanceImpl::normalize( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

NormalizerImpl::~NormalizerImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

NormalizerInstanceInterface* NormalizerImpl::createInstance( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_NormalizerInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	NormalizerInstanceInterface* p0 = new NormalizerInstanceImpl( objId_0, messaging());
	return p0;
}

PeerStorageTransactionImpl::~PeerStorageTransactionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void PeerStorageTransactionImpl::updateNofDocumentsInsertedChange( const GlobalCounter& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateNofDocumentsInsertedChange);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void PeerStorageTransactionImpl::updateDocumentFrequencyChange( const char* p1, const char* p2, const GlobalCounter& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packGlobalCounter( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void PeerStorageTransactionImpl::commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void PeerStorageTransactionImpl::rollback( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorImpl::~PostingIteratorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index PostingIteratorImpl::skipDoc( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::skipPos( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

const char* PostingIteratorImpl::featureid( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureid);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char* p0 = constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

std::vector<const PostingIteratorInterface*> PostingIteratorImpl::subExpressions( bool p1) const
{
	throw std::runtime_error("the method 'subExpressions' is not implemented for RPC");
}

GlobalCounter PostingIteratorImpl::documentFrequency( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

unsigned int PostingIteratorImpl::frequency( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_frequency);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned int p0 = serializedMsg.unpackUint();;
	return p0;
}

Index PostingIteratorImpl::docno( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_docno);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::posno( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_posno);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

PostingJoinOperatorImpl::~PostingJoinOperatorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorInterface* PostingJoinOperatorImpl::createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createResultIterator);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
			const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1[ii].get());
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	}
	msg.packInt( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, messaging());
	return p0;
}

QueryAnalyzerImpl::~QueryAnalyzerImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryAnalyzerImpl::definePhraseType( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePhraseType);
	msg.packString( p1);
	msg.packString( p2);
	msg.packTokenizerConfig( p3);
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packNormalizerConfig( p4[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<analyzer::Term> QueryAnalyzerImpl::analyzePhrase( const std::string& p1, const std::string& p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhrase);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
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
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addTerm( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addSelectionFeature( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectionFeature);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addRestrictionFeature( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addRestrictionFeature);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addSummarizer( const std::string& p1, const std::string& p2, const SummarizerConfig& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizer);
	msg.packString( p1);
	msg.packString( p2);
	msg.packSummarizerConfig( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addWeightingFunction( const std::string& p1, const WeightingConfig& p2, const std::vector<std::string>& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addWeightingFunction);
	msg.packString( p1);
	msg.packWeightingConfig( p2);
	msg.packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packString( p3[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
}

QueryInterface* QueryEvalImpl::createQuery( const StorageClientInterface* p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQuery);
		const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_Query) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	QueryInterface* p0 = new QueryImpl( objId_0, messaging());
	return p0;
}

QueryImpl::~QueryImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::pushExpression( const std::string& p1, std::size_t p2, int p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	msg.packString( p1);
	msg.packSize( p2);
	msg.packInt( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::pushDuplicate( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushDuplicate);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::attachVariable( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::defineFeature( const std::string& p1, float p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaDataRestriction);
	msg.packCompareOperator( p1);
	msg.packString( p2);
	msg.packArithmeticVariant( p3);
	msg.packBool( p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::setMaxNofRanks( std::size_t p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMaxNofRanks);
	msg.packSize( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::setMinRank( std::size_t p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMinRank);
	msg.packSize( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::setUserName( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserName);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<ResultDocument> QueryImpl::evaluate( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
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
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryProcessorImpl::definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePostingJoinOperator);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

const PostingJoinOperatorInterface* QueryProcessorImpl::getPostingJoinOperator( const std::string& p1) const
{
	throw std::runtime_error("the method 'getPostingJoinOperator' is not implemented for RPC");
}

void QueryProcessorImpl::defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWeightingFunction);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

const WeightingFunctionInterface* QueryProcessorImpl::getWeightingFunction( const std::string& p1) const
{
	throw std::runtime_error("the method 'getWeightingFunction' is not implemented for RPC");
}

void QueryProcessorImpl::defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSummarizerFunction);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

const SummarizerFunctionInterface* QueryProcessorImpl::getSummarizerFunction( const std::string& p1) const
{
	throw std::runtime_error("the method 'getSummarizerFunction' is not implemented for RPC");
}

SegmenterInstanceImpl::~SegmenterInstanceImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool SegmenterInstanceImpl::getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	p1 = serializedMsg.unpackInt();
	p2 = serializedMsg.unpackGlobalCounter();
	const char* bp3;
	serializedMsg.unpackBuffer( bp3, p4);
	p3 = (const char*)constConstructor()->get( bp3, p4);
	return p0;
}

SegmenterImpl::~SegmenterImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterImpl::defineSelectorExpression( int p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSelectorExpression);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterImpl::defineSubSection( int p1, int p2, const std::string& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubSection);
	msg.packInt( p1);
	msg.packInt( p2);
	msg.packString( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

SegmenterInstanceInterface* SegmenterImpl::createInstance( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_SegmenterInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	SegmenterInstanceInterface* p0 = new SegmenterInstanceImpl( objId_0, messaging());
	return p0;
}

StorageAlterMetaDataTableImpl::~StorageAlterMetaDataTableImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::addElement( const std::string& p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::alterElement( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_alterElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::renameElement( const std::string& p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_renameElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::deleteElement( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::clearElement( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void StorageAlterMetaDataTableImpl::rollback( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageClientImpl::~StorageClientImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageClientImpl::close( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermPostingIterator);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	PostingIteratorInterface* p0 = new PostingIteratorImpl( objId_0, messaging());
	return p0;
}

ForwardIteratorInterface* StorageClientImpl::createForwardIterator( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createForwardIterator);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_ForwardIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	ForwardIteratorInterface* p0 = new ForwardIteratorImpl( objId_0, messaging());
	return p0;
}

InvAclIteratorInterface* StorageClientImpl::createInvAclIterator( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInvAclIterator);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_InvAclIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	InvAclIteratorInterface* p0 = new InvAclIteratorImpl( objId_0, messaging());
	return p0;
}

GlobalCounter StorageClientImpl::globalNofDocumentsInserted( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalNofDocumentsInserted);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localNofDocumentsInserted( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localNofDocumentsInserted);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

GlobalCounter StorageClientImpl::globalDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	GlobalCounter p0 = serializedMsg.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index StorageClientImpl::maxDocumentNumber( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_maxDocumentNumber);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

Index StorageClientImpl::documentNumber( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentNumber);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	Index p0 = serializedMsg.unpackIndex();;
	return p0;
}

MetaDataReaderInterface* StorageClientImpl::createMetaDataReader( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataReader);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	MetaDataReaderInterface* p0 = new MetaDataReaderImpl( objId_0, messaging());
	return p0;
}

AttributeReaderInterface* StorageClientImpl::createAttributeReader( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAttributeReader);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_AttributeReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	AttributeReaderInterface* p0 = new AttributeReaderImpl( objId_0, messaging());
	return p0;
}

DocnoRangeAllocatorInterface* StorageClientImpl::createDocnoRangeAllocator( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocnoRangeAllocator);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_DocnoRangeAllocator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	DocnoRangeAllocatorInterface* p0 = new DocnoRangeAllocatorImpl( objId_0, messaging());
	return p0;
}

StorageTransactionInterface* StorageClientImpl::createTransaction( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageTransaction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageTransactionInterface* p0 = new StorageTransactionImpl( objId_0, messaging());
	return p0;
}

PeerStorageTransactionInterface* StorageClientImpl::createPeerStorageTransaction( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPeerStorageTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_PeerStorageTransaction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	PeerStorageTransactionInterface* p0 = new PeerStorageTransactionImpl( objId_0, messaging());
	return p0;
}

void StorageClientImpl::defineStoragePeerInterface( const StoragePeerInterface* p1, bool p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineStoragePeerInterface);
		const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packBool( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageDocumentInterface* StorageClientImpl::createDocumentChecker( const std::string& p1, const std::string& p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentChecker);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageDocument) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, messaging());
	return p0;
}

void StorageClientImpl::checkStorage( std::ostream& p1) const
{
	throw std::runtime_error("the method 'checkStorage' is not implemented for RPC");
}

StorageDumpInterface* StorageClientImpl::createDump( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageDump) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageDumpInterface* p0 = new StorageDumpImpl( objId_0, messaging());
	return p0;
}

StorageDocumentImpl::~StorageDocumentImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::setMetaData( const std::string& p1, const ArithmeticVariant& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::setAttribute( const std::string& p1, const std::string& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::setUserAccessRight( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::done( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

StorageDumpImpl::~StorageDumpImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool StorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	const char* bp1;
	serializedMsg.unpackBuffer( bp1, p2);
	p1 = (const char*)constConstructor()->get( bp1, p2);
	return p0;
}

StorageImpl::~StorageImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageClientInterface* StorageImpl::createClient( const std::string& p1, DatabaseClientInterface* p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageClientInterface* p0 = new StorageClientImpl( objId_0, messaging());
	return p0;
}

void StorageImpl::createStorage( const std::string& p1, DatabaseClientInterface* p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageAlterMetaDataTableInterface* StorageImpl::createAlterMetaDataTable( DatabaseClientInterface* p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
		const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageAlterMetaDataTable) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, messaging());
	return p0;
}

const char* StorageImpl::getConfigDescription( StorageInterface::ConfigType p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char* p0 = constConstructor()->getCharp( serializedMsg.unpackConstCharp());;
	return p0;
}

const char** StorageImpl::getConfigParameters( StorageInterface::ConfigType p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

StorageObjectBuilderImpl::~StorageObjectBuilderImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const StorageInterface* StorageObjectBuilderImpl::getStorage( ) const
{
	throw std::runtime_error("the method 'getStorage' is not implemented for RPC");
}

const DatabaseInterface* StorageObjectBuilderImpl::getDatabase( const std::string& p1) const
{
	throw std::runtime_error("the method 'getDatabase' is not implemented for RPC");
}

const QueryProcessorInterface* StorageObjectBuilderImpl::getQueryProcessor( ) const
{
	throw std::runtime_error("the method 'getQueryProcessor' is not implemented for RPC");
}

StorageClientInterface* StorageObjectBuilderImpl::createStorageClient( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorageClient);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageClientInterface* p0 = new StorageClientImpl( objId_0, messaging());
	return p0;
}

StorageAlterMetaDataTableInterface* StorageObjectBuilderImpl::createAlterMetaDataTable( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageAlterMetaDataTable) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageAlterMetaDataTableInterface* p0 = new StorageAlterMetaDataTableImpl( objId_0, messaging());
	return p0;
}

QueryEvalInterface* StorageObjectBuilderImpl::createQueryEval( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQueryEval);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_QueryEval) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	QueryEvalInterface* p0 = new QueryEvalImpl( objId_0, messaging());
	return p0;
}

StoragePeerImpl::~StoragePeerImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StoragePeerTransactionInterface* StoragePeerImpl::createTransaction( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StoragePeerTransaction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StoragePeerTransactionInterface* p0 = new StoragePeerTransactionImpl( objId_0, messaging());
	return p0;
}

StoragePeerTransactionImpl::~StoragePeerTransactionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::populateNofDocumentsInsertedChange( int p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::populateDocumentFrequencyChange( const char* p1, const char* p2, int p3, bool p4)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packInt( p3);
	msg.packBool( p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::try_commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_try_commit);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::final_commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_final_commit);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::rollback( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageTransactionImpl::~StorageTransactionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageDocumentInterface* StorageTransactionImpl::createDocument( const std::string& p1, const Index& p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocument);
	msg.packString( p1);
	msg.packIndex( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_StorageDocument) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	StorageDocumentInterface* p0 = new StorageDocumentImpl( objId_0, messaging());
	return p0;
}

void StorageTransactionImpl::deleteDocument( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteDocument);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageTransactionImpl::deleteUserAccessRights( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteUserAccessRights);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageTransactionImpl::commit( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void StorageTransactionImpl::rollback( )
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

SummarizerClosureImpl::~SummarizerClosureImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<SummarizerClosureInterface::SummaryElement> SummarizerClosureImpl::getSummary( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummary);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::vector<SummarizerClosureInterface::SummaryElement> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		SummarizerClosureInterface::SummaryElement elem_p0 = serializedMsg.unpackSummaryElement();
		p0.push_back( elem_p0);
	}
	return p0;
}

SummarizerFunctionImpl::~SummarizerFunctionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char** SummarizerFunctionImpl::numericParameterNames( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

const char** SummarizerFunctionImpl::textualParameterNames( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_textualParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

const char** SummarizerFunctionImpl::featureParameterClassNames( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureParameterClassNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

SummarizerClosureInterface* SummarizerFunctionImpl::createClosure( const StorageClientInterface* p1, const QueryProcessorInterface* p2, MetaDataReaderInterface* p3, const std::vector<SummarizerFunctionInterface::FeatureParameter>& p4, const std::vector<std::string>& p5, const std::vector<ArithmeticVariant>& p6) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClosure);
		const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packFeatureParameter( p4[ii]);
	}
	msg.packSize( p5.size());
	for (unsigned int ii=0; ii < p5.size(); ++ii) {
		msg.packString( p5[ii]);
	}
	msg.packSize( p6.size());
	for (unsigned int ii=0; ii < p6.size(); ++ii) {
		msg.packArithmeticVariant( p6[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_SummarizerClosure) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	SummarizerClosureInterface* p0 = new SummarizerClosureImpl( objId_0, messaging());
	return p0;
}

TextProcessorImpl::~TextProcessorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void TextProcessorImpl::addResourcePath( const std::string& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string TextProcessorImpl::getResourcePath( const std::string& p1) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::string p0 = serializedMsg.unpackString();;
	return p0;
}

const TokenizerConstructorInterface* TextProcessorImpl::getTokenizer( const std::string& p1) const
{
	throw std::runtime_error("the method 'getTokenizer' is not implemented for RPC");
}

const NormalizerConstructorInterface* TextProcessorImpl::getNormalizer( const std::string& p1) const
{
	throw std::runtime_error("the method 'getNormalizer' is not implemented for RPC");
}

void TextProcessorImpl::defineTokenizer( const std::string& p1, const TokenizerConstructorInterface* p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenizer);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

void TextProcessorImpl::defineNormalizer( const std::string& p1, const NormalizerConstructorInterface* p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineNormalizer);
	msg.packString( p1);
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
}

TokenizerConstructorImpl::~TokenizerConstructorImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

TokenizerInterface* TokenizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_create);
	msg.packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_Tokenizer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	TokenizerInterface* p0 = new TokenizerImpl( objId_0, messaging());
	return p0;
}

TokenizerInstanceImpl::~TokenizerInstanceImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<analyzer::Token> TokenizerInstanceImpl::tokenize( const char* p1, std::size_t p2)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	std::vector<analyzer::Token> p0;
	std::size_t n0 = serializedMsg.unpackSize();
	for (std::size_t ii=0; ii < n0; ++ii) {
		analyzer::Token elem_p0 = serializedMsg.unpackAnalyzerToken();
		p0.push_back( elem_p0);
	}
	return p0;
}

TokenizerImpl::~TokenizerImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool TokenizerImpl::concatBeforeTokenize( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_concatBeforeTokenize);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	bool p0 = serializedMsg.unpackBool();;
	return p0;
}

TokenizerInstanceInterface* TokenizerImpl::createInstance( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_TokenizerInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	TokenizerInstanceInterface* p0 = new TokenizerInstanceImpl( objId_0, messaging());
	return p0;
}

WeightingClosureImpl::~WeightingClosureImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

float WeightingClosureImpl::call( const Index& p1)
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	float p0 = serializedMsg.unpackFloat();;
	return p0;
}

WeightingFunctionImpl::~WeightingFunctionImpl()
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char** WeightingFunctionImpl::numericParameterNames( ) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	const char** p0 = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());;
	return p0;
}

WeightingClosureInterface* WeightingFunctionImpl::createClosure( const StorageClientInterface* p1, PostingIteratorInterface* p2, MetaDataReaderInterface* p3, const std::vector<ArithmeticVariant>& p4) const
{
	RpcSerializer msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClosure);
		const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
		const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
		const RpcInterfaceStub* impl_3 = dynamic_cast<const RpcInterfaceStub*>(p3);
	if (!impl_3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_3->classId(), impl_3->objId());
	msg.packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packArithmeticVariant( p4[ii]);
	}
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcDeserializer serializedMsg( rpc_recv());
	serializedMsg.unpackByte();
	unsigned char classId_0; unsigned int objId_0;
	serializedMsg.unpackObject( classId_0, objId_0);
	if (classId_0 != ClassId_WeightingClosure) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
	WeightingClosureInterface* p0 = new WeightingClosureImpl( objId_0, messaging());
	return p0;
}

