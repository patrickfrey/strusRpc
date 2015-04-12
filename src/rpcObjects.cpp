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
#include "rpcMessage.hpp"

using namespace strus;

AttributeReaderImpl::~AttributeReaderImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index AttributeReaderImpl::elementHandle( const char* p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packCharp( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

void AttributeReaderImpl::skipDoc( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string AttributeReaderImpl::getValue( const Index& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::string p0 = answer.unpackString();;
	return p0;
}

DatabaseBackupCursorImpl::~DatabaseBackupCursorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DatabaseBackupCursorImpl::fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	answer.unpackBuffer( p1, p2);
	answer.unpackBuffer( p3, p4);
	return p0;
}

DatabaseClientImpl::~DatabaseClientImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseClientImpl::close( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseTransactionInterface* DatabaseClientImpl::createTransaction( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DatabaseTransaction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DatabaseTransactionImpl* p0 = new DatabaseTransactionImpl( objId_p0, endpoint());
	return p0;
}

DatabaseCursorInterface* DatabaseClientImpl::createCursor( const DatabaseOptions& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DatabaseCursor) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DatabaseCursorImpl* p0 = new DatabaseCursorImpl( objId_p0, endpoint());
	return p0;
}

DatabaseBackupCursorInterface* DatabaseClientImpl::createBackupCursor( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBackupCursor);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DatabaseBackupCursor) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DatabaseBackupCursorImpl* p0 = new DatabaseBackupCursorImpl( objId_p0, endpoint());
	return p0;
}

void DatabaseClientImpl::writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_writeImm);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseClientImpl::removeImm( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeImm);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DatabaseClientImpl::readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_readValue);
	msg.packBuffer( p1, p2);
	msg.packDatabaseOptions( p4);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	p3 = answer.unpackString();
	return p0;
}

DatabaseCursorImpl::~DatabaseCursorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBound( const char* p1, std::size_t p2, std::size_t p3)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBound);
	msg.packBuffer( p1, p2);
	msg.packSize( p3);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekFirst( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekFirst);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekLast( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekLast);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekNext( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekPrev( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekPrev);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::key( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_key);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::value( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_value);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	DatabaseCursorInterface::Slice p0 = answer.unpackSlice();;
	return p0;
}

DatabaseImpl::~DatabaseImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseClientInterface* DatabaseImpl::createClient( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DatabaseClientImpl* p0 = new DatabaseClientImpl( objId_p0, endpoint());
	return p0;
}

void DatabaseImpl::createDatabase( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDatabase);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseImpl::restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_destroyDatabase);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char* DatabaseImpl::getConfigDescription( DatabaseInterface::ConfigType p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char* p0 = answer.unpackConstCharp();;
	return p0;
}

const char** DatabaseImpl::getConfigParameters( DatabaseInterface::ConfigType p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packDatabaseConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

DatabaseTransactionImpl::~DatabaseTransactionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

DatabaseCursorInterface* DatabaseTransactionImpl::createCursor( const DatabaseOptions& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	msg.packDatabaseOptions( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DatabaseCursor) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DatabaseCursorImpl* p0 = new DatabaseCursorImpl( objId_p0, endpoint());
	return p0;
}

void DatabaseTransactionImpl::write( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_write);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::remove( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_remove);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::removeSubTree( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeSubTree);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DatabaseTransactionImpl::commit( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void DatabaseTransactionImpl::rollback( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

DocnoRangeAllocatorImpl::~DocnoRangeAllocatorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index DocnoRangeAllocatorImpl::allocDocnoRange( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_allocDocnoRange);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

bool DocnoRangeAllocatorImpl::deallocDocnoRange( const Index& p1, const Index& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deallocDocnoRange);
	msg.packIndex( p1);
	msg.packIndex( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	return p0;
}

DocumentAnalyzerInstanceImpl::~DocumentAnalyzerInstanceImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool DocumentAnalyzerInstanceImpl::analyzeNext( analyzer::Document& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	p1 = answer.unpackAnalyzerDocument();
	return p0;
}

DocumentAnalyzerImpl::~DocumentAnalyzerImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void DocumentAnalyzerImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubDocument);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

analyzer::Document DocumentAnalyzerImpl::analyze( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	analyzer::Document p0 = answer.unpackAnalyzerDocument();;
	return p0;
}

DocumentAnalyzerInstanceInterface* DocumentAnalyzerImpl::createInstance( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DocumentAnalyzerInstance) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DocumentAnalyzerInstanceImpl* p0 = new DocumentAnalyzerInstanceImpl( objId_p0, endpoint());
	return p0;
}

ForwardIteratorImpl::~ForwardIteratorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void ForwardIteratorImpl::skipDoc( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index ForwardIteratorImpl::skipPos( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

std::string ForwardIteratorImpl::fetch( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::string p0 = answer.unpackString();;
	return p0;
}

InvAclIteratorImpl::~InvAclIteratorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index InvAclIteratorImpl::skipDoc( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

MetaDataReaderImpl::~MetaDataReaderImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool MetaDataReaderImpl::hasElement( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_hasElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	return p0;
}

Index MetaDataReaderImpl::elementHandle( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

Index MetaDataReaderImpl::nofElements( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofElements);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

void MetaDataReaderImpl::skipDoc( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

ArithmeticVariant MetaDataReaderImpl::getValue( const Index& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	ArithmeticVariant p0 = answer.unpackArithmeticVariant();;
	return p0;
}

const char* MetaDataReaderImpl::getType( const Index& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getType);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char* p0 = answer.unpackConstCharp();;
	return p0;
}

const char* MetaDataReaderImpl::getName( const Index& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getName);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char* p0 = answer.unpackConstCharp();;
	return p0;
}

NormalizerConstructorImpl::~NormalizerConstructorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

NormalizerInterface* NormalizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RpcMessage msg;
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
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_Normalizer) throw std::runtime_error("error in RPC answer: return object type mismatch");
	NormalizerImpl* p0 = new NormalizerImpl( objId_p0, endpoint());
	return p0;
}

NormalizerInstanceImpl::~NormalizerInstanceImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string NormalizerInstanceImpl::normalize( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::string p0 = answer.unpackString();;
	return p0;
}

NormalizerImpl::~NormalizerImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

NormalizerInstanceInterface* NormalizerImpl::createInstance( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_NormalizerInstance) throw std::runtime_error("error in RPC answer: return object type mismatch");
	NormalizerInstanceImpl* p0 = new NormalizerInstanceImpl( objId_p0, endpoint());
	return p0;
}

PeerStorageTransactionImpl::~PeerStorageTransactionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void PeerStorageTransactionImpl::updateNofDocumentsInsertedChange( const GlobalCounter& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateNofDocumentsInsertedChange);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void PeerStorageTransactionImpl::updateDocumentFrequencyChange( const char* p1, const char* p2, const GlobalCounter& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void PeerStorageTransactionImpl::rollback( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorImpl::~PostingIteratorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

Index PostingIteratorImpl::skipDoc( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::skipPos( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

const char* PostingIteratorImpl::featureid( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureid);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char* p0 = answer.unpackConstCharp();;
	return p0;
}

std::vector<const PostingIteratorInterface*> PostingIteratorImpl::subExpressions( bool p1) const
{
	throw std::runtime_error("the method 'subExpressions' is not implemented for RPC");
}

GlobalCounter PostingIteratorImpl::documentFrequency( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	GlobalCounter p0 = answer.unpackGlobalCounter();;
	return p0;
}

unsigned int PostingIteratorImpl::frequency( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_frequency);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned int p0 = answer.unpackUint();;
	return p0;
}

Index PostingIteratorImpl::docno( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_docno);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

Index PostingIteratorImpl::posno( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_posno);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

PostingJoinOperatorImpl::~PostingJoinOperatorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorInterface* PostingJoinOperatorImpl::createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2) const
{
	RpcMessage msg;
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
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_PostingIterator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	PostingIteratorImpl* p0 = new PostingIteratorImpl( objId_p0, endpoint());
	return p0;
}

QueryAnalyzerImpl::~QueryAnalyzerImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryAnalyzerImpl::definePhraseType( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhrase);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::vector<analyzer::Term> p0;
	std::size_t n0 = answer.unpackSize();
	for (unsigned int ii=0; ii < n0; ++ii) {
		analyzer::Term elem_p0 = answer.unpackAnalyzerTerm();
		p0.push_back( elem_p0);
	}
	return p0;
}

QueryEvalImpl::~QueryEvalImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addTerm( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectionFeature);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addRestrictionFeature( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addRestrictionFeature);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryEvalImpl::addSummarizer( const std::string& p1, const std::string& p2, const SummarizerConfig& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQuery);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_Query) throw std::runtime_error("error in RPC answer: return object type mismatch");
	QueryImpl* p0 = new QueryImpl( objId_p0, endpoint());
	return p0;
}

QueryImpl::~QueryImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::pushExpression( const std::string& p1, std::size_t p2, int p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushDuplicate);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::attachVariable( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::defineFeature( const std::string& p1, float p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMaxNofRanks);
	msg.packSize( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::setMinRank( std::size_t p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMinRank);
	msg.packSize( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryImpl::setUserName( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserName);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<ResultDocument> QueryImpl::evaluate( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::vector<ResultDocument> p0;
	std::size_t n0 = answer.unpackSize();
	for (unsigned int ii=0; ii < n0; ++ii) {
		ResultDocument elem_p0 = answer.unpackResultDocument();
		p0.push_back( elem_p0);
	}
	return p0;
}

QueryProcessorImpl::~QueryProcessorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void QueryProcessorImpl::definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPostingJoinOperator);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_PostingJoinOperator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	PostingJoinOperatorImpl* p0 = new PostingJoinOperatorImpl( objId_p0, endpoint());
	return p0;
}

void QueryProcessorImpl::defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWeightingFunction);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_WeightingFunction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	WeightingFunctionImpl* p0 = new WeightingFunctionImpl( objId_p0, endpoint());
	return p0;
}

void QueryProcessorImpl::defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummarizerFunction);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_SummarizerFunction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	SummarizerFunctionImpl* p0 = new SummarizerFunctionImpl( objId_p0, endpoint());
	return p0;
}

SegmenterInstanceImpl::~SegmenterInstanceImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool SegmenterInstanceImpl::getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	p1 = answer.unpackInt();
	p2 = answer.unpackGlobalCounter();
	answer.unpackBuffer( p3, p4);
	return p0;
}

SegmenterImpl::~SegmenterImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterImpl::defineSelectorExpression( int p1, const std::string& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSelectorExpression);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void SegmenterImpl::defineSubSection( int p1, int p2, const std::string& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_SegmenterInstance) throw std::runtime_error("error in RPC answer: return object type mismatch");
	SegmenterInstanceImpl* p0 = new SegmenterInstanceImpl( objId_p0, endpoint());
	return p0;
}

StorageAlterMetaDataTableImpl::~StorageAlterMetaDataTableImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::addElement( const std::string& p1, const std::string& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::alterElement( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_renameElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::deleteElement( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::clearElement( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearElement);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageAlterMetaDataTableImpl::commit( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void StorageAlterMetaDataTableImpl::rollback( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageClientImpl::~StorageClientImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageClientImpl::close( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
	rpc_send( msg.content());
}

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermPostingIterator);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_PostingIterator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	PostingIteratorImpl* p0 = new PostingIteratorImpl( objId_p0, endpoint());
	return p0;
}

ForwardIteratorInterface* StorageClientImpl::createForwardIterator( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createForwardIterator);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_ForwardIterator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	ForwardIteratorImpl* p0 = new ForwardIteratorImpl( objId_p0, endpoint());
	return p0;
}

InvAclIteratorInterface* StorageClientImpl::createInvAclIterator( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInvAclIterator);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_InvAclIterator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	InvAclIteratorImpl* p0 = new InvAclIteratorImpl( objId_p0, endpoint());
	return p0;
}

GlobalCounter StorageClientImpl::globalNofDocumentsInserted( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalNofDocumentsInserted);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	GlobalCounter p0 = answer.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localNofDocumentsInserted( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localNofDocumentsInserted);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

GlobalCounter StorageClientImpl::globalDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	GlobalCounter p0 = answer.unpackGlobalCounter();;
	return p0;
}

Index StorageClientImpl::localDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

Index StorageClientImpl::maxDocumentNumber( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_maxDocumentNumber);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

Index StorageClientImpl::documentNumber( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentNumber);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	Index p0 = answer.unpackIndex();;
	return p0;
}

MetaDataReaderInterface* StorageClientImpl::createMetaDataReader( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataReader);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC answer: return object type mismatch");
	MetaDataReaderImpl* p0 = new MetaDataReaderImpl( objId_p0, endpoint());
	return p0;
}

AttributeReaderInterface* StorageClientImpl::createAttributeReader( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAttributeReader);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_AttributeReader) throw std::runtime_error("error in RPC answer: return object type mismatch");
	AttributeReaderImpl* p0 = new AttributeReaderImpl( objId_p0, endpoint());
	return p0;
}

DocnoRangeAllocatorInterface* StorageClientImpl::createDocnoRangeAllocator( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocnoRangeAllocator);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_DocnoRangeAllocator) throw std::runtime_error("error in RPC answer: return object type mismatch");
	DocnoRangeAllocatorImpl* p0 = new DocnoRangeAllocatorImpl( objId_p0, endpoint());
	return p0;
}

StorageTransactionInterface* StorageClientImpl::createTransaction( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageTransaction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageTransactionImpl* p0 = new StorageTransactionImpl( objId_p0, endpoint());
	return p0;
}

PeerStorageTransactionInterface* StorageClientImpl::createPeerStorageTransaction( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPeerStorageTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_PeerStorageTransaction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	PeerStorageTransactionImpl* p0 = new PeerStorageTransactionImpl( objId_p0, endpoint());
	return p0;
}

void StorageClientImpl::defineStoragePeerInterface( const StoragePeerInterface* p1, bool p2)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentChecker);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageDocument) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageDocumentImpl* p0 = new StorageDocumentImpl( objId_p0, endpoint());
	return p0;
}

void StorageClientImpl::checkStorage( std::ostream& p1) const
{
	throw std::runtime_error("the method 'checkStorage' is not implemented for RPC");
}

StorageDumpInterface* StorageClientImpl::createDump( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageDump) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageDumpImpl* p0 = new StorageDumpImpl( objId_p0, endpoint());
	return p0;
}

StorageDocumentImpl::~StorageDocumentImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::setAttribute( const std::string& p1, const std::string& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::setUserAccessRight( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageDocumentImpl::done( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

StorageDumpImpl::~StorageDumpImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool StorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	answer.unpackBuffer( p1, p2);
	return p0;
}

StorageImpl::~StorageImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageClientInterface* StorageImpl::createClient( const std::string& p1, DatabaseClientInterface* p2) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const RpcInterfaceStub* impl_2 = dynamic_cast<const RpcInterfaceStub*>(p2);
	if (!impl_2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_2->classId(), impl_2->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageClient) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageClientImpl* p0 = new StorageClientImpl( objId_p0, endpoint());
	return p0;
}

void StorageImpl::createStorage( const std::string& p1, DatabaseClientInterface* p2) const
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	const RpcInterfaceStub* impl_1 = dynamic_cast<const RpcInterfaceStub*>(p1);
	if (!impl_1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_1->classId(), impl_1->objId());
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageAlterMetaDataTable) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageAlterMetaDataTableImpl* p0 = new StorageAlterMetaDataTableImpl( objId_p0, endpoint());
	return p0;
}

const char* StorageImpl::getConfigDescription( StorageInterface::ConfigType p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char* p0 = answer.unpackConstCharp();;
	return p0;
}

const char** StorageImpl::getConfigParameters( StorageInterface::ConfigType p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	msg.packStorageConfigType( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

StoragePeerImpl::~StoragePeerImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StoragePeerTransactionInterface* StoragePeerImpl::createTransaction( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StoragePeerTransaction) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StoragePeerTransactionImpl* p0 = new StoragePeerTransactionImpl( objId_p0, endpoint());
	return p0;
}

StoragePeerTransactionImpl::~StoragePeerTransactionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::populateNofDocumentsInsertedChange( int p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::populateDocumentFrequencyChange( const char* p1, const char* p2, int p3, bool p4)
{
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_try_commit);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::final_commit( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_final_commit);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StoragePeerTransactionImpl::rollback( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageTransactionImpl::~StorageTransactionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

StorageDocumentInterface* StorageTransactionImpl::createDocument( const std::string& p1, const Index& p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocument);
	msg.packString( p1);
	msg.packIndex( p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_StorageDocument) throw std::runtime_error("error in RPC answer: return object type mismatch");
	StorageDocumentImpl* p0 = new StorageDocumentImpl( objId_p0, endpoint());
	return p0;
}

void StorageTransactionImpl::deleteDocument( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteDocument);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageTransactionImpl::deleteUserAccessRights( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteUserAccessRights);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

void StorageTransactionImpl::commit( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
	rpc_send( msg.content());
	rpc_waitAnswer();
}

void StorageTransactionImpl::rollback( )
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
	rpc_send( msg.content());
}

SummarizerClosureImpl::~SummarizerClosureImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<SummarizerClosureInterface::SummaryElement> SummarizerClosureImpl::getSummary( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummary);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::vector<SummarizerClosureInterface::SummaryElement> p0;
	std::size_t n0 = answer.unpackSize();
	for (unsigned int ii=0; ii < n0; ++ii) {
		SummarizerClosureInterface::SummaryElement elem_p0 = answer.unpackSummaryElement();
		p0.push_back( elem_p0);
	}
	return p0;
}

SummarizerFunctionImpl::~SummarizerFunctionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char** SummarizerFunctionImpl::numericParameterNames( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

const char** SummarizerFunctionImpl::textualParameterNames( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_textualParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

const char** SummarizerFunctionImpl::featureParameterClassNames( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureParameterClassNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

SummarizerClosureInterface* SummarizerFunctionImpl::createClosure( const StorageClientInterface* p1, const QueryProcessorInterface* p2, MetaDataReaderInterface* p3, const std::vector<SummarizerFunctionInterface::FeatureParameter>& p4, const std::vector<std::string>& p5, const std::vector<ArithmeticVariant>& p6) const
{
	RpcMessage msg;
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
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_SummarizerClosure) throw std::runtime_error("error in RPC answer: return object type mismatch");
	SummarizerClosureImpl* p0 = new SummarizerClosureImpl( objId_p0, endpoint());
	return p0;
}

TextProcessorImpl::~TextProcessorImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

void TextProcessorImpl::addResourcePath( const std::string& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::string TextProcessorImpl::getResourcePath( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePath);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::string p0 = answer.unpackString();;
	return p0;
}

const TokenizerConstructorInterface* TextProcessorImpl::getTokenizer( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTokenizer);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_TokenizerConstructor) throw std::runtime_error("error in RPC answer: return object type mismatch");
	TokenizerConstructorImpl* p0 = new TokenizerConstructorImpl( objId_p0, endpoint());
	return p0;
}

const NormalizerConstructorInterface* TextProcessorImpl::getNormalizer( const std::string& p1) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNormalizer);
	msg.packString( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_NormalizerConstructor) throw std::runtime_error("error in RPC answer: return object type mismatch");
	NormalizerConstructorImpl* p0 = new NormalizerConstructorImpl( objId_p0, endpoint());
	return p0;
}

void TextProcessorImpl::defineTokenizer( const std::string& p1, const TokenizerConstructorInterface* p2)
{
	RpcMessage msg;
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
	RpcMessage msg;
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
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

TokenizerInterface* TokenizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RpcMessage msg;
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
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_Tokenizer) throw std::runtime_error("error in RPC answer: return object type mismatch");
	TokenizerImpl* p0 = new TokenizerImpl( objId_p0, endpoint());
	return p0;
}

TokenizerInstanceImpl::~TokenizerInstanceImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

std::vector<analyzer::Token> TokenizerInstanceImpl::tokenize( const char* p1, std::size_t p2)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	std::vector<analyzer::Token> p0;
	std::size_t n0 = answer.unpackSize();
	for (unsigned int ii=0; ii < n0; ++ii) {
		analyzer::Token elem_p0 = answer.unpackAnalyzerToken();
		p0.push_back( elem_p0);
	}
	return p0;
}

TokenizerImpl::~TokenizerImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

bool TokenizerImpl::concatBeforeTokenize( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_concatBeforeTokenize);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	bool p0 = answer.unpackBool();;
	return p0;
}

TokenizerInstanceInterface* TokenizerImpl::createInstance( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_TokenizerInstance) throw std::runtime_error("error in RPC answer: return object type mismatch");
	TokenizerInstanceImpl* p0 = new TokenizerInstanceImpl( objId_p0, endpoint());
	return p0;
}

WeightingClosureImpl::~WeightingClosureImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

float WeightingClosureImpl::call( const Index& p1)
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packIndex( p1);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	float p0 = answer.unpackFloat();;
	return p0;
}

WeightingFunctionImpl::~WeightingFunctionImpl()
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_Destructor);
	msg.packCrc32();
	rpc_send( msg.content());
}

const char** WeightingFunctionImpl::numericParameterNames( ) const
{
	RpcMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
	rpc_send( msg.content());
	enter();
	RpcAnswer answer( constConstructor(), rpc_recv());
	const char** p0 = answer.unpackConstCharpp();;
	return p0;
}

WeightingClosureInterface* WeightingFunctionImpl::createClosure( const StorageClientInterface* p1, PostingIteratorInterface* p2, MetaDataReaderInterface* p3, const std::vector<ArithmeticVariant>& p4) const
{
	RpcMessage msg;
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
	RpcAnswer answer( constConstructor(), rpc_recv());
	unsigned char classId_p0; unsigned int objId_p0;
	answer.unpackObject( classId_p0, objId_p0);
	if (classId_p0 != ClassId_WeightingClosure) throw std::runtime_error("error in RPC answer: return object type mismatch");
	WeightingClosureImpl* p0 = new WeightingClosureImpl( objId_p0, endpoint());
	return p0;
}

