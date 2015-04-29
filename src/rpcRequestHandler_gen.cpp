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
#include "rpcRequestHandler.hpp"
#include "rpcSerializer.hpp"
#include "objectIds_gen.hpp"
#include "private/dll_tags.hpp"
#include <string>

using namespace strus;
std::string RpcRequestHandler::handleRequest( const char* src, std::size_t srcsize)
{
	RpcDeserializer serializedMsg( src, srcsize);
	if (!serializedMsg.unpackCrc32()) throw std::runtime_error("message CRC32 check failed");
	unsigned char classId; unsigned int objId; unsigned char methodId;
	serializedMsg.unpackObject( classId, objId);
	methodId = serializedMsg.unpackByte();
	switch( (ClassId)classId)
	{
	case ClassId_AnalyzerObjectBuilder:
	{
	AnalyzerObjectBuilderInterface* obj = getObject<AnalyzerObjectBuilderInterface>( classId, objId);
	switch( (AnalyzerObjectBuilderConst::MethodId)methodId)
	{
		case AnalyzerObjectBuilderConst::Method_Destructor:
		{
			std::cerr << "called destructor of AnalyzerObjectBuilderImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_getTextProcessor:
		{
			std::cerr << "called method AnalyzerObjectBuilderImpl::getTextProcessor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const TextProcessorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getTextProcessor();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_createSegmenter:
		{
			std::cerr << "called method AnalyzerObjectBuilderImpl::createSegmenter [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			SegmenterInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createSegmenter(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_createDocumentAnalyzer:
		{
			std::cerr << "called method AnalyzerObjectBuilderImpl::createDocumentAnalyzer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DocumentAnalyzerInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDocumentAnalyzer(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_createQueryAnalyzer:
		{
			std::cerr << "called method AnalyzerObjectBuilderImpl::createQueryAnalyzer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			QueryAnalyzerInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createQueryAnalyzer();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_AttributeReader:
	{
	AttributeReaderInterface* obj = getObject<AttributeReaderInterface>( classId, objId);
	switch( (AttributeReaderConst::MethodId)methodId)
	{
		case AttributeReaderConst::Method_Destructor:
		{
			std::cerr << "called destructor of AttributeReaderImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case AttributeReaderConst::Method_elementHandle:
		{
			std::cerr << "called method AttributeReaderImpl::elementHandle [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			const char* p1;
			p1 = serializedMsg.unpackConstCharp();
			try {
				p0 = obj->elementHandle(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case AttributeReaderConst::Method_skipDoc:
		{
			std::cerr << "called method AttributeReaderImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				obj->skipDoc(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case AttributeReaderConst::Method_getValue:
		{
			std::cerr << "called method AttributeReaderImpl::getValue [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->getValue(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DatabaseBackupCursor:
	{
	DatabaseBackupCursorInterface* obj = getObject<DatabaseBackupCursorInterface>( classId, objId);
	switch( (DatabaseBackupCursorConst::MethodId)methodId)
	{
		case DatabaseBackupCursorConst::Method_Destructor:
		{
			std::cerr << "called destructor of DatabaseBackupCursorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseBackupCursorConst::Method_fetch:
		{
			std::cerr << "called method DatabaseBackupCursorImpl::fetch [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			const char* p3;
			std::size_t p4;
			try {
				p0 = obj->fetch(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packBuffer( p1, p2);
			msg.packBuffer( p3, p4);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DatabaseClient:
	{
	DatabaseClientInterface* obj = getObject<DatabaseClientInterface>( classId, objId);
	switch( (DatabaseClientConst::MethodId)methodId)
	{
		case DatabaseClientConst::Method_Destructor:
		{
			std::cerr << "called destructor of DatabaseClientImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseClientConst::Method_close:
		{
			std::cerr << "called method DatabaseClientImpl::close [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->close();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseClientConst::Method_createTransaction:
		{
			std::cerr << "called method DatabaseClientImpl::createTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createTransaction();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseClientConst::Method_createCursor:
		{
			std::cerr << "called method DatabaseClientImpl::createCursor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface* p0;
			DatabaseOptions p1;
			p1 = serializedMsg.unpackDatabaseOptions();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createCursor(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseClientConst::Method_createBackupCursor:
		{
			std::cerr << "called method DatabaseClientImpl::createBackupCursor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseBackupCursorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createBackupCursor();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseClientConst::Method_writeImm:
		{
			std::cerr << "called method DatabaseClientImpl::writeImm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			const char* p3;
			std::size_t p4;
			serializedMsg.unpackBuffer( p1, p2);
			serializedMsg.unpackBuffer( p3, p4);
			try {
				obj->writeImm(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseClientConst::Method_removeImm:
		{
			std::cerr << "called method DatabaseClientImpl::removeImm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				obj->removeImm(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseClientConst::Method_readValue:
		{
			std::cerr << "called method DatabaseClientImpl::readValue [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			std::string p3;
			DatabaseOptions p4;
			serializedMsg.unpackBuffer( p1, p2);
			p4 = serializedMsg.unpackDatabaseOptions();
			try {
				p0 = obj->readValue(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packString( p3);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DatabaseCursor:
	{
	DatabaseCursorInterface* obj = getObject<DatabaseCursorInterface>( classId, objId);
	switch( (DatabaseCursorConst::MethodId)methodId)
	{
		case DatabaseCursorConst::Method_Destructor:
		{
			std::cerr << "called destructor of DatabaseCursorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseCursorConst::Method_seekUpperBound:
		{
			std::cerr << "called method DatabaseCursorImpl::seekUpperBound [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			const char* p1;
			std::size_t p2;
			std::size_t p3;
			serializedMsg.unpackBuffer( p1, p2);
			p3 = serializedMsg.unpackSize();
			try {
				p0 = obj->seekUpperBound(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekFirst:
		{
			std::cerr << "called method DatabaseCursorImpl::seekFirst [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				p0 = obj->seekFirst(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekLast:
		{
			std::cerr << "called method DatabaseCursorImpl::seekLast [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				p0 = obj->seekLast(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekNext:
		{
			std::cerr << "called method DatabaseCursorImpl::seekNext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			try {
				p0 = obj->seekNext();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekPrev:
		{
			std::cerr << "called method DatabaseCursorImpl::seekPrev [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			try {
				p0 = obj->seekPrev();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_key:
		{
			std::cerr << "called method DatabaseCursorImpl::key [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			try {
				p0 = obj->key();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_value:
		{
			std::cerr << "called method DatabaseCursorImpl::value [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			try {
				p0 = obj->value();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_Database:
	{
	DatabaseInterface* obj = getObject<DatabaseInterface>( classId, objId);
	switch( (DatabaseConst::MethodId)methodId)
	{
		case DatabaseConst::Method_Destructor:
		{
			std::cerr << "called destructor of DatabaseImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseConst::Method_createClient:
		{
			std::cerr << "called method DatabaseImpl::createClient [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseClientInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createClient(p1);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseConst::Method_createDatabase:
		{
			std::cerr << "called method DatabaseImpl::createDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->createDatabase(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseConst::Method_restoreDatabase:
		{
			std::cerr << "called method DatabaseImpl::restoreDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			DatabaseBackupCursorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseBackupCursor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<DatabaseBackupCursorInterface>( classId_2, objId_2);
			try {
				obj->restoreDatabase(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseConst::Method_destroyDatabase:
		{
			std::cerr << "called method DatabaseImpl::destroyDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->destroyDatabase(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseConst::Method_getConfigDescription:
		{
			std::cerr << "called method DatabaseImpl::getConfigDescription [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p0;
			DatabaseInterface::ConfigType p1;
			p1 = serializedMsg.unpackDatabaseConfigType();
			try {
				p0 = obj->getConfigDescription(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseConst::Method_getConfigParameters:
		{
			std::cerr << "called method DatabaseImpl::getConfigParameters [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char** p0;
			DatabaseInterface::ConfigType p1;
			p1 = serializedMsg.unpackDatabaseConfigType();
			try {
				p0 = obj->getConfigParameters(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharpp( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DatabaseTransaction:
	{
	DatabaseTransactionInterface* obj = getObject<DatabaseTransactionInterface>( classId, objId);
	switch( (DatabaseTransactionConst::MethodId)methodId)
	{
		case DatabaseTransactionConst::Method_Destructor:
		{
			std::cerr << "called destructor of DatabaseTransactionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseTransactionConst::Method_createCursor:
		{
			std::cerr << "called method DatabaseTransactionImpl::createCursor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DatabaseCursorInterface* p0;
			DatabaseOptions p1;
			p1 = serializedMsg.unpackDatabaseOptions();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createCursor(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseTransactionConst::Method_write:
		{
			std::cerr << "called method DatabaseTransactionImpl::write [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			const char* p3;
			std::size_t p4;
			serializedMsg.unpackBuffer( p1, p2);
			serializedMsg.unpackBuffer( p3, p4);
			try {
				obj->write(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseTransactionConst::Method_remove:
		{
			std::cerr << "called method DatabaseTransactionImpl::remove [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				obj->remove(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseTransactionConst::Method_removeSubTree:
		{
			std::cerr << "called method DatabaseTransactionImpl::removeSubTree [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				obj->removeSubTree(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DatabaseTransactionConst::Method_commit:
		{
			std::cerr << "called method DatabaseTransactionImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseTransactionConst::Method_rollback:
		{
			std::cerr << "called method DatabaseTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->rollback();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_DocnoRangeAllocator:
	{
	DocnoRangeAllocatorInterface* obj = getObject<DocnoRangeAllocatorInterface>( classId, objId);
	switch( (DocnoRangeAllocatorConst::MethodId)methodId)
	{
		case DocnoRangeAllocatorConst::Method_Destructor:
		{
			std::cerr << "called destructor of DocnoRangeAllocatorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DocnoRangeAllocatorConst::Method_allocDocnoRange:
		{
			std::cerr << "called method DocnoRangeAllocatorImpl::allocDocnoRange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->allocDocnoRange(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DocnoRangeAllocatorConst::Method_deallocDocnoRange:
		{
			std::cerr << "called method DocnoRangeAllocatorImpl::deallocDocnoRange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			Index p1;
			Index p2;
			p1 = serializedMsg.unpackIndex();
			p2 = serializedMsg.unpackIndex();
			try {
				p0 = obj->deallocDocnoRange(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DocumentAnalyzerInstance:
	{
	DocumentAnalyzerInstanceInterface* obj = getObject<DocumentAnalyzerInstanceInterface>( classId, objId);
	switch( (DocumentAnalyzerInstanceConst::MethodId)methodId)
	{
		case DocumentAnalyzerInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of DocumentAnalyzerInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentAnalyzerInstanceConst::Method_putInput:
		{
			std::cerr << "called method DocumentAnalyzerInstanceImpl::putInput [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			bool p3;
			serializedMsg.unpackBuffer( p1, p2);
			p3 = serializedMsg.unpackBool();
			try {
				obj->putInput(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerInstanceConst::Method_analyzeNext:
		{
			std::cerr << "called method DocumentAnalyzerInstanceImpl::analyzeNext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			analyzer::Document p1;
			try {
				p0 = obj->analyzeNext(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packAnalyzerDocument( p1);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_DocumentAnalyzer:
	{
	DocumentAnalyzerInterface* obj = getObject<DocumentAnalyzerInterface>( classId, objId);
	switch( (DocumentAnalyzerConst::MethodId)methodId)
	{
		case DocumentAnalyzerConst::Method_Destructor:
		{
			std::cerr << "called destructor of DocumentAnalyzerImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentAnalyzerConst::Method_addSearchIndexFeature:
		{
			std::cerr << "called method DocumentAnalyzerImpl::addSearchIndexFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerFunctionInstanceInterface* p3;
			std::vector<NormalizerFunctionInstanceInterface*> p4;
			DocumentAnalyzerInterface::FeatureOptions p5;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			try {
				obj->addSearchIndexFeature(p1,p2,p3,p4,p5);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerConst::Method_addForwardIndexFeature:
		{
			std::cerr << "called method DocumentAnalyzerImpl::addForwardIndexFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerFunctionInstanceInterface* p3;
			std::vector<NormalizerFunctionInstanceInterface*> p4;
			DocumentAnalyzerInterface::FeatureOptions p5;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			try {
				obj->addForwardIndexFeature(p1,p2,p3,p4,p5);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerConst::Method_defineMetaData:
		{
			std::cerr << "called method DocumentAnalyzerImpl::defineMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerFunctionInstanceInterface* p3;
			std::vector<NormalizerFunctionInstanceInterface*> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			try {
				obj->defineMetaData(p1,p2,p3,p4);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerConst::Method_defineAttribute:
		{
			std::cerr << "called method DocumentAnalyzerImpl::defineAttribute [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerFunctionInstanceInterface* p3;
			std::vector<NormalizerFunctionInstanceInterface*> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			try {
				obj->defineAttribute(p1,p2,p3,p4);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerConst::Method_defineSubDocument:
		{
			std::cerr << "called method DocumentAnalyzerImpl::defineSubDocument [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->defineSubDocument(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case DocumentAnalyzerConst::Method_analyze:
		{
			std::cerr << "called method DocumentAnalyzerImpl::analyze [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			analyzer::Document p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->analyze(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packAnalyzerDocument( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DocumentAnalyzerConst::Method_createInstance:
		{
			std::cerr << "called method DocumentAnalyzerImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DocumentAnalyzerInstanceInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_ForwardIterator:
	{
	ForwardIteratorInterface* obj = getObject<ForwardIteratorInterface>( classId, objId);
	switch( (ForwardIteratorConst::MethodId)methodId)
	{
		case ForwardIteratorConst::Method_Destructor:
		{
			std::cerr << "called destructor of ForwardIteratorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case ForwardIteratorConst::Method_skipDoc:
		{
			std::cerr << "called method ForwardIteratorImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				obj->skipDoc(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case ForwardIteratorConst::Method_skipPos:
		{
			std::cerr << "called method ForwardIteratorImpl::skipPos [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->skipPos(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case ForwardIteratorConst::Method_fetch:
		{
			std::cerr << "called method ForwardIteratorImpl::fetch [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			try {
				p0 = obj->fetch();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_InvAclIterator:
	{
	InvAclIteratorInterface* obj = getObject<InvAclIteratorInterface>( classId, objId);
	switch( (InvAclIteratorConst::MethodId)methodId)
	{
		case InvAclIteratorConst::Method_Destructor:
		{
			std::cerr << "called destructor of InvAclIteratorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case InvAclIteratorConst::Method_skipDoc:
		{
			std::cerr << "called method InvAclIteratorImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->skipDoc(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_MetaDataReader:
	{
	MetaDataReaderInterface* obj = getObject<MetaDataReaderInterface>( classId, objId);
	switch( (MetaDataReaderConst::MethodId)methodId)
	{
		case MetaDataReaderConst::Method_Destructor:
		{
			std::cerr << "called destructor of MetaDataReaderImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case MetaDataReaderConst::Method_hasElement:
		{
			std::cerr << "called method MetaDataReaderImpl::hasElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->hasElement(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_elementHandle:
		{
			std::cerr << "called method MetaDataReaderImpl::elementHandle [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->elementHandle(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_nofElements:
		{
			std::cerr << "called method MetaDataReaderImpl::nofElements [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			try {
				p0 = obj->nofElements();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_skipDoc:
		{
			std::cerr << "called method MetaDataReaderImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				obj->skipDoc(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case MetaDataReaderConst::Method_getValue:
		{
			std::cerr << "called method MetaDataReaderImpl::getValue [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			ArithmeticVariant p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->getValue(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packArithmeticVariant( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_getType:
		{
			std::cerr << "called method MetaDataReaderImpl::getType [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->getType(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_getName:
		{
			std::cerr << "called method MetaDataReaderImpl::getName [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->getName(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_NormalizerExecutionContext:
	{
	NormalizerExecutionContextInterface* obj = getObject<NormalizerExecutionContextInterface>( classId, objId);
	switch( (NormalizerExecutionContextConst::MethodId)methodId)
	{
		case NormalizerExecutionContextConst::Method_Destructor:
		{
			std::cerr << "called destructor of NormalizerExecutionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerExecutionContextConst::Method_normalize:
		{
			std::cerr << "called method NormalizerExecutionContextImpl::normalize [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				p0 = obj->normalize(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_NormalizerFunctionInstance:
	{
	NormalizerFunctionInstanceInterface* obj = getObject<NormalizerFunctionInstanceInterface>( classId, objId);
	switch( (NormalizerFunctionInstanceConst::MethodId)methodId)
	{
		case NormalizerFunctionInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of NormalizerFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionInstanceConst::Method_createExecutionContext:
		{
			std::cerr << "called method NormalizerFunctionInstanceImpl::createExecutionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			NormalizerExecutionContextInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createExecutionContext();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_NormalizerFunction:
	{
	NormalizerFunctionInterface* obj = getObject<NormalizerFunctionInterface>( classId, objId);
	switch( (NormalizerFunctionConst::MethodId)methodId)
	{
		case NormalizerFunctionConst::Method_Destructor:
		{
			std::cerr << "called destructor of NormalizerFunctionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionConst::Method_createInstance:
		{
			std::cerr << "called method NormalizerFunctionImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			NormalizerFunctionInstanceInterface* p0;
			std::vector<std::string> p1;
			const TextProcessorInterface* p2;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p1.push_back( ee);
			}
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_TextProcessor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getConstObject<TextProcessorInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_PeerStorageTransaction:
	{
	PeerStorageTransactionInterface* obj = getObject<PeerStorageTransactionInterface>( classId, objId);
	switch( (PeerStorageTransactionConst::MethodId)methodId)
	{
		case PeerStorageTransactionConst::Method_Destructor:
		{
			std::cerr << "called destructor of PeerStorageTransactionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PeerStorageTransactionConst::Method_updateNofDocumentsInsertedChange:
		{
			std::cerr << "called method PeerStorageTransactionImpl::updateNofDocumentsInsertedChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p1;
			p1 = serializedMsg.unpackGlobalCounter();
			try {
				obj->updateNofDocumentsInsertedChange(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case PeerStorageTransactionConst::Method_updateDocumentFrequencyChange:
		{
			std::cerr << "called method PeerStorageTransactionImpl::updateDocumentFrequencyChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			const char* p2;
			GlobalCounter p3;
			p1 = serializedMsg.unpackConstCharp();
			p2 = serializedMsg.unpackConstCharp();
			p3 = serializedMsg.unpackGlobalCounter();
			try {
				obj->updateDocumentFrequencyChange(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case PeerStorageTransactionConst::Method_commit:
		{
			std::cerr << "called method PeerStorageTransactionImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCrc32();
			return msg.content();
		}
		case PeerStorageTransactionConst::Method_rollback:
		{
			std::cerr << "called method PeerStorageTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->rollback();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_PostingIterator:
	{
	PostingIteratorInterface* obj = getObject<PostingIteratorInterface>( classId, objId);
	switch( (PostingIteratorConst::MethodId)methodId)
	{
		case PostingIteratorConst::Method_Destructor:
		{
			std::cerr << "called destructor of PostingIteratorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PostingIteratorConst::Method_skipDoc:
		{
			std::cerr << "called method PostingIteratorImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->skipDoc(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_skipPos:
		{
			std::cerr << "called method PostingIteratorImpl::skipPos [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->skipPos(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_featureid:
		{
			std::cerr << "called method PostingIteratorImpl::featureid [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p0;
			try {
				p0 = obj->featureid();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_subExpressions:
		{
			std::cerr << "called method PostingIteratorImpl::subExpressions [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'subExpressions' is not implemented for RPC");
			return msg.content();
		}
		case PostingIteratorConst::Method_documentFrequency:
		{
			std::cerr << "called method PostingIteratorImpl::documentFrequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			try {
				p0 = obj->documentFrequency();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packGlobalCounter( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_frequency:
		{
			std::cerr << "called method PostingIteratorImpl::frequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			unsigned int p0;
			try {
				p0 = obj->frequency();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packUint( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_docno:
		{
			std::cerr << "called method PostingIteratorImpl::docno [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			try {
				p0 = obj->docno();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_posno:
		{
			std::cerr << "called method PostingIteratorImpl::posno [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			try {
				p0 = obj->posno();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_PostingJoinOperator:
	{
	PostingJoinOperatorInterface* obj = getObject<PostingJoinOperatorInterface>( classId, objId);
	switch( (PostingJoinOperatorConst::MethodId)methodId)
	{
		case PostingJoinOperatorConst::Method_Destructor:
		{
			std::cerr << "called destructor of PostingJoinOperatorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PostingJoinOperatorConst::Method_createResultIterator:
		{
			std::cerr << "called method PostingJoinOperatorImpl::createResultIterator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'createResultIterator' is not implemented for RPC");
			return msg.content();
		}
	}
	break;
	}
	case ClassId_QueryAnalyzer:
	{
	QueryAnalyzerInterface* obj = getObject<QueryAnalyzerInterface>( classId, objId);
	switch( (QueryAnalyzerConst::MethodId)methodId)
	{
		case QueryAnalyzerConst::Method_Destructor:
		{
			std::cerr << "called destructor of QueryAnalyzerImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case QueryAnalyzerConst::Method_definePhraseType:
		{
			std::cerr << "called method QueryAnalyzerImpl::definePhraseType [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerFunctionInstanceInterface* p3;
			std::vector<NormalizerFunctionInstanceInterface*> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			try {
				obj->definePhraseType(p1,p2,p3,p4);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryAnalyzerConst::Method_analyzePhrase:
		{
			std::cerr << "called method QueryAnalyzerImpl::analyzePhrase [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::vector<analyzer::Term> p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				p0 = obj->analyzePhrase(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packAnalyzerTerm( p0[ii]);
			}
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_QueryEval:
	{
	QueryEvalInterface* obj = getObject<QueryEvalInterface>( classId, objId);
	switch( (QueryEvalConst::MethodId)methodId)
	{
		case QueryEvalConst::Method_Destructor:
		{
			std::cerr << "called destructor of QueryEvalImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case QueryEvalConst::Method_addTerm:
		{
			std::cerr << "called method QueryEvalImpl::addTerm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			std::string p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackString();
			try {
				obj->addTerm(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryEvalConst::Method_addSelectionFeature:
		{
			std::cerr << "called method QueryEvalImpl::addSelectionFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->addSelectionFeature(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryEvalConst::Method_addRestrictionFeature:
		{
			std::cerr << "called method QueryEvalImpl::addRestrictionFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->addRestrictionFeature(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryEvalConst::Method_addSummarizerFunction:
		{
			std::cerr << "called method QueryEvalImpl::addSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			SummarizerFunctionInstanceInterface* p2;
			std::vector<QueryEvalInterface::SummarizerFeatureParameter> p3;
			std::string p4;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_SummarizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<SummarizerFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				QueryEvalInterface::SummarizerFeatureParameter ee = serializedMsg.unpackSummarizerFeatureParameter();
				p3.push_back( ee);
			}
			p4 = serializedMsg.unpackString();
			try {
				obj->addSummarizerFunction(p1,p2,p3,p4);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryEvalConst::Method_addWeightingFunction:
		{
			std::cerr << "called method QueryEvalImpl::addWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			WeightingFunctionInstanceInterface* p2;
			std::vector<std::string> p3;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_WeightingFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<WeightingFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p3.push_back( ee);
			}
			try {
				obj->addWeightingFunction(p1,p2,p3);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryEvalConst::Method_createQuery:
		{
			std::cerr << "called method QueryEvalImpl::createQuery [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			QueryInterface* p0;
			const StorageClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createQuery(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_Query:
	{
	QueryInterface* obj = getObject<QueryInterface>( classId, objId);
	switch( (QueryConst::MethodId)methodId)
	{
		case QueryConst::Method_Destructor:
		{
			std::cerr << "called destructor of QueryImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case QueryConst::Method_pushTerm:
		{
			std::cerr << "called method QueryImpl::pushTerm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->pushTerm(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_pushExpression:
		{
			std::cerr << "called method QueryImpl::pushExpression [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const PostingJoinOperatorInterface* p1;
			std::size_t p2;
			int p3;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_PostingJoinOperator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<PostingJoinOperatorInterface>( classId_1, objId_1);
			p2 = serializedMsg.unpackSize();
			p3 = serializedMsg.unpackInt();
			try {
				obj->pushExpression(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_pushDuplicate:
		{
			std::cerr << "called method QueryImpl::pushDuplicate [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->pushDuplicate();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_attachVariable:
		{
			std::cerr << "called method QueryImpl::attachVariable [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->attachVariable(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_defineFeature:
		{
			std::cerr << "called method QueryImpl::defineFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			float p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackFloat();
			try {
				obj->defineFeature(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_defineMetaDataRestriction:
		{
			std::cerr << "called method QueryImpl::defineMetaDataRestriction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			QueryInterface::CompareOperator p1;
			std::string p2;
			ArithmeticVariant p3;
			bool p4;
			p1 = serializedMsg.unpackCompareOperator();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackArithmeticVariant();
			p4 = serializedMsg.unpackBool();
			try {
				obj->defineMetaDataRestriction(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_setMaxNofRanks:
		{
			std::cerr << "called method QueryImpl::setMaxNofRanks [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::size_t p1;
			p1 = serializedMsg.unpackSize();
			try {
				obj->setMaxNofRanks(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_setMinRank:
		{
			std::cerr << "called method QueryImpl::setMinRank [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::size_t p1;
			p1 = serializedMsg.unpackSize();
			try {
				obj->setMinRank(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_setUserName:
		{
			std::cerr << "called method QueryImpl::setUserName [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->setUserName(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryConst::Method_evaluate:
		{
			std::cerr << "called method QueryImpl::evaluate [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::vector<ResultDocument> p0;
			try {
				p0 = obj->evaluate();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packResultDocument( p0[ii]);
			}
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_QueryProcessor:
	{
	QueryProcessorInterface* obj = getObject<QueryProcessorInterface>( classId, objId);
	switch( (QueryProcessorConst::MethodId)methodId)
	{
		case QueryProcessorConst::Method_Destructor:
		{
			std::cerr << "called destructor of QueryProcessorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case QueryProcessorConst::Method_definePostingJoinOperator:
		{
			std::cerr << "called method QueryProcessorImpl::definePostingJoinOperator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			PostingJoinOperatorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingJoinOperator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingJoinOperatorInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			try {
				obj->definePostingJoinOperator(p1,p2);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryProcessorConst::Method_getPostingJoinOperator:
		{
			std::cerr << "called method QueryProcessorImpl::getPostingJoinOperator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const PostingJoinOperatorInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getPostingJoinOperator(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case QueryProcessorConst::Method_defineWeightingFunction:
		{
			std::cerr << "called method QueryProcessorImpl::defineWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			WeightingFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_WeightingFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<WeightingFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			try {
				obj->defineWeightingFunction(p1,p2);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryProcessorConst::Method_getWeightingFunction:
		{
			std::cerr << "called method QueryProcessorImpl::getWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const WeightingFunctionInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getWeightingFunction(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case QueryProcessorConst::Method_defineSummarizerFunction:
		{
			std::cerr << "called method QueryProcessorImpl::defineSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			SummarizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_SummarizerFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<SummarizerFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			try {
				obj->defineSummarizerFunction(p1,p2);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case QueryProcessorConst::Method_getSummarizerFunction:
		{
			std::cerr << "called method QueryProcessorImpl::getSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const SummarizerFunctionInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getSummarizerFunction(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_SegmenterInstance:
	{
	SegmenterInstanceInterface* obj = getObject<SegmenterInstanceInterface>( classId, objId);
	switch( (SegmenterInstanceConst::MethodId)methodId)
	{
		case SegmenterInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of SegmenterInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterInstanceConst::Method_putInput:
		{
			std::cerr << "called method SegmenterInstanceImpl::putInput [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			bool p3;
			serializedMsg.unpackBuffer( p1, p2);
			p3 = serializedMsg.unpackBool();
			try {
				obj->putInput(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SegmenterInstanceConst::Method_getNext:
		{
			std::cerr << "called method SegmenterInstanceImpl::getNext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			int p1;
			SegmenterPosition p2;
			const char* p3;
			std::size_t p4;
			try {
				p0 = obj->getNext(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packInt( p1);
			msg.packGlobalCounter( p2);
			msg.packBuffer( p3, p4);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_Segmenter:
	{
	SegmenterInterface* obj = getObject<SegmenterInterface>( classId, objId);
	switch( (SegmenterConst::MethodId)methodId)
	{
		case SegmenterConst::Method_Destructor:
		{
			std::cerr << "called destructor of SegmenterImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterConst::Method_defineSelectorExpression:
		{
			std::cerr << "called method SegmenterImpl::defineSelectorExpression [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			int p1;
			std::string p2;
			p1 = serializedMsg.unpackInt();
			p2 = serializedMsg.unpackString();
			try {
				obj->defineSelectorExpression(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SegmenterConst::Method_defineSubSection:
		{
			std::cerr << "called method SegmenterImpl::defineSubSection [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			int p1;
			int p2;
			std::string p3;
			p1 = serializedMsg.unpackInt();
			p2 = serializedMsg.unpackInt();
			p3 = serializedMsg.unpackString();
			try {
				obj->defineSubSection(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SegmenterConst::Method_createInstance:
		{
			std::cerr << "called method SegmenterImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			SegmenterInstanceInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StorageAlterMetaDataTable:
	{
	StorageAlterMetaDataTableInterface* obj = getObject<StorageAlterMetaDataTableInterface>( classId, objId);
	switch( (StorageAlterMetaDataTableConst::MethodId)methodId)
	{
		case StorageAlterMetaDataTableConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageAlterMetaDataTableImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_addElement:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::addElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->addElement(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_alterElement:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::alterElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			std::string p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackString();
			try {
				obj->alterElement(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_renameElement:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::renameElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->renameElement(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_deleteElement:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::deleteElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->deleteElement(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_clearElement:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::clearElement [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->clearElement(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_commit:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCrc32();
			return msg.content();
		}
		case StorageAlterMetaDataTableConst::Method_rollback:
		{
			std::cerr << "called method StorageAlterMetaDataTableImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->rollback();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_StorageClient:
	{
	StorageClientInterface* obj = getObject<StorageClientInterface>( classId, objId);
	switch( (StorageClientConst::MethodId)methodId)
	{
		case StorageClientConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageClientImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageClientConst::Method_close:
		{
			std::cerr << "called method StorageClientImpl::close [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->close();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageClientConst::Method_createTermPostingIterator:
		{
			std::cerr << "called method StorageClientImpl::createTermPostingIterator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			PostingIteratorInterface* p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createTermPostingIterator(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createForwardIterator:
		{
			std::cerr << "called method StorageClientImpl::createForwardIterator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			ForwardIteratorInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createForwardIterator(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createInvAclIterator:
		{
			std::cerr << "called method StorageClientImpl::createInvAclIterator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			InvAclIteratorInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInvAclIterator(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_globalNofDocumentsInserted:
		{
			std::cerr << "called method StorageClientImpl::globalNofDocumentsInserted [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			try {
				p0 = obj->globalNofDocumentsInserted();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packGlobalCounter( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_localNofDocumentsInserted:
		{
			std::cerr << "called method StorageClientImpl::localNofDocumentsInserted [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			try {
				p0 = obj->localNofDocumentsInserted();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_globalDocumentFrequency:
		{
			std::cerr << "called method StorageClientImpl::globalDocumentFrequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				p0 = obj->globalDocumentFrequency(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packGlobalCounter( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_localDocumentFrequency:
		{
			std::cerr << "called method StorageClientImpl::localDocumentFrequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				p0 = obj->localDocumentFrequency(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_maxDocumentNumber:
		{
			std::cerr << "called method StorageClientImpl::maxDocumentNumber [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			try {
				p0 = obj->maxDocumentNumber();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_documentNumber:
		{
			std::cerr << "called method StorageClientImpl::documentNumber [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->documentNumber(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_createMetaDataReader:
		{
			std::cerr << "called method StorageClientImpl::createMetaDataReader [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			MetaDataReaderInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createMetaDataReader();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createAttributeReader:
		{
			std::cerr << "called method StorageClientImpl::createAttributeReader [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			AttributeReaderInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createAttributeReader();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createDocnoRangeAllocator:
		{
			std::cerr << "called method StorageClientImpl::createDocnoRangeAllocator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DocnoRangeAllocatorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDocnoRangeAllocator();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createTransaction:
		{
			std::cerr << "called method StorageClientImpl::createTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createTransaction();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createPeerStorageTransaction:
		{
			std::cerr << "called method StorageClientImpl::createPeerStorageTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			PeerStorageTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createPeerStorageTransaction();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_defineStoragePeerInterface:
		{
			std::cerr << "called method StorageClientImpl::defineStoragePeerInterface [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const StoragePeerInterface* p1;
			bool p2;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StoragePeer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<StoragePeerInterface>( classId_1, objId_1);
			p2 = serializedMsg.unpackBool();
			try {
				obj->defineStoragePeerInterface(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageClientConst::Method_createDocumentChecker:
		{
			std::cerr << "called method StorageClientImpl::createDocumentChecker [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageDocumentInterface* p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDocumentChecker(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_checkStorage:
		{
			std::cerr << "called method StorageClientImpl::checkStorage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'checkStorage' is not implemented for RPC");
			return msg.content();
		}
		case StorageClientConst::Method_createDump:
		{
			std::cerr << "called method StorageClientImpl::createDump [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageDumpInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDump();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StorageDocument:
	{
	StorageDocumentInterface* obj = getObject<StorageDocumentInterface>( classId, objId);
	switch( (StorageDocumentConst::MethodId)methodId)
	{
		case StorageDocumentConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageDocumentImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageDocumentConst::Method_addSearchIndexTerm:
		{
			std::cerr << "called method StorageDocumentImpl::addSearchIndexTerm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			Index p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackIndex();
			try {
				obj->addSearchIndexTerm(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageDocumentConst::Method_addForwardIndexTerm:
		{
			std::cerr << "called method StorageDocumentImpl::addForwardIndexTerm [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			Index p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackIndex();
			try {
				obj->addForwardIndexTerm(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageDocumentConst::Method_setMetaData:
		{
			std::cerr << "called method StorageDocumentImpl::setMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			try {
				obj->setMetaData(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageDocumentConst::Method_setAttribute:
		{
			std::cerr << "called method StorageDocumentImpl::setAttribute [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->setAttribute(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageDocumentConst::Method_setUserAccessRight:
		{
			std::cerr << "called method StorageDocumentImpl::setUserAccessRight [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->setUserAccessRight(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageDocumentConst::Method_done:
		{
			std::cerr << "called method StorageDocumentImpl::done [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->done();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_StorageDump:
	{
	StorageDumpInterface* obj = getObject<StorageDumpInterface>( classId, objId);
	switch( (StorageDumpConst::MethodId)methodId)
	{
		case StorageDumpConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageDumpImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageDumpConst::Method_nextChunk:
		{
			std::cerr << "called method StorageDumpImpl::nextChunk [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			try {
				p0 = obj->nextChunk(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packBuffer( p1, p2);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_Storage:
	{
	StorageInterface* obj = getObject<StorageInterface>( classId, objId);
	switch( (StorageConst::MethodId)methodId)
	{
		case StorageConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageConst::Method_createClient:
		{
			std::cerr << "called method StorageImpl::createClient [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageClientInterface* p0;
			std::string p1;
			DatabaseClientInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createClient(p1,p2);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageConst::Method_createStorage:
		{
			std::cerr << "called method StorageImpl::createStorage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			DatabaseClientInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			try {
				obj->createStorage(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageConst::Method_createAlterMetaDataTable:
		{
			std::cerr << "called method StorageImpl::createAlterMetaDataTable [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageAlterMetaDataTableInterface* p0;
			DatabaseClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<DatabaseClientInterface>( classId_1, objId_1);
			markObjectToRelease( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createAlterMetaDataTable(p1);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageConst::Method_getConfigDescription:
		{
			std::cerr << "called method StorageImpl::getConfigDescription [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p0;
			StorageInterface::ConfigType p1;
			p1 = serializedMsg.unpackStorageConfigType();
			try {
				p0 = obj->getConfigDescription(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageConst::Method_getConfigParameters:
		{
			std::cerr << "called method StorageImpl::getConfigParameters [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char** p0;
			StorageInterface::ConfigType p1;
			p1 = serializedMsg.unpackStorageConfigType();
			try {
				p0 = obj->getConfigParameters(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCharpp( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_StorageObjectBuilder:
	{
	StorageObjectBuilderInterface* obj = getObject<StorageObjectBuilderInterface>( classId, objId);
	switch( (StorageObjectBuilderConst::MethodId)methodId)
	{
		case StorageObjectBuilderConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageObjectBuilderImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getStorage:
		{
			std::cerr << "called method StorageObjectBuilderImpl::getStorage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const StorageInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getStorage();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getDatabase:
		{
			std::cerr << "called method StorageObjectBuilderImpl::getDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const DatabaseInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getDatabase(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getQueryProcessor:
		{
			std::cerr << "called method StorageObjectBuilderImpl::getQueryProcessor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const QueryProcessorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getQueryProcessor();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_createStorageClient:
		{
			std::cerr << "called method StorageObjectBuilderImpl::createStorageClient [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageClientInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createStorageClient(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_createAlterMetaDataTable:
		{
			std::cerr << "called method StorageObjectBuilderImpl::createAlterMetaDataTable [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageAlterMetaDataTableInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createAlterMetaDataTable(p1);
				releaseObjectsMarked();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_createQueryEval:
		{
			std::cerr << "called method StorageObjectBuilderImpl::createQueryEval [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			QueryEvalInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createQueryEval();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StoragePeer:
	{
	StoragePeerInterface* obj = getObject<StoragePeerInterface>( classId, objId);
	switch( (StoragePeerConst::MethodId)methodId)
	{
		case StoragePeerConst::Method_Destructor:
		{
			std::cerr << "called destructor of StoragePeerImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StoragePeerConst::Method_createTransaction:
		{
			std::cerr << "called method StoragePeerImpl::createTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StoragePeerTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createTransaction();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StoragePeerTransaction:
	{
	StoragePeerTransactionInterface* obj = getObject<StoragePeerTransactionInterface>( classId, objId);
	switch( (StoragePeerTransactionConst::MethodId)methodId)
	{
		case StoragePeerTransactionConst::Method_Destructor:
		{
			std::cerr << "called destructor of StoragePeerTransactionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StoragePeerTransactionConst::Method_populateNofDocumentsInsertedChange:
		{
			std::cerr << "called method StoragePeerTransactionImpl::populateNofDocumentsInsertedChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			int p1;
			p1 = serializedMsg.unpackInt();
			try {
				obj->populateNofDocumentsInsertedChange(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StoragePeerTransactionConst::Method_populateDocumentFrequencyChange:
		{
			std::cerr << "called method StoragePeerTransactionImpl::populateDocumentFrequencyChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			const char* p2;
			int p3;
			bool p4;
			p1 = serializedMsg.unpackConstCharp();
			p2 = serializedMsg.unpackConstCharp();
			p3 = serializedMsg.unpackInt();
			p4 = serializedMsg.unpackBool();
			try {
				obj->populateDocumentFrequencyChange(p1,p2,p3,p4);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StoragePeerTransactionConst::Method_try_commit:
		{
			std::cerr << "called method StoragePeerTransactionImpl::try_commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->try_commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StoragePeerTransactionConst::Method_final_commit:
		{
			std::cerr << "called method StoragePeerTransactionImpl::final_commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->final_commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StoragePeerTransactionConst::Method_rollback:
		{
			std::cerr << "called method StoragePeerTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->rollback();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_StorageTransaction:
	{
	StorageTransactionInterface* obj = getObject<StorageTransactionInterface>( classId, objId);
	switch( (StorageTransactionConst::MethodId)methodId)
	{
		case StorageTransactionConst::Method_Destructor:
		{
			std::cerr << "called destructor of StorageTransactionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageTransactionConst::Method_createDocument:
		{
			std::cerr << "called method StorageTransactionImpl::createDocument [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			StorageDocumentInterface* p0;
			std::string p1;
			Index p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackIndex();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDocument(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageTransactionConst::Method_deleteDocument:
		{
			std::cerr << "called method StorageTransactionImpl::deleteDocument [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->deleteDocument(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageTransactionConst::Method_deleteUserAccessRights:
		{
			std::cerr << "called method StorageTransactionImpl::deleteUserAccessRights [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->deleteUserAccessRights(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case StorageTransactionConst::Method_commit:
		{
			std::cerr << "called method StorageTransactionImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->commit();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packCrc32();
			return msg.content();
		}
		case StorageTransactionConst::Method_rollback:
		{
			std::cerr << "called method StorageTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			try {
				obj->rollback();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_SummarizerExecutionContext:
	{
	SummarizerExecutionContextInterface* obj = getObject<SummarizerExecutionContextInterface>( classId, objId);
	switch( (SummarizerExecutionContextConst::MethodId)methodId)
	{
		case SummarizerExecutionContextConst::Method_Destructor:
		{
			std::cerr << "called destructor of SummarizerExecutionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerExecutionContextConst::Method_addSummarizationFeature:
		{
			std::cerr << "called method SummarizerExecutionContextImpl::addSummarizationFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			PostingIteratorInterface* p2;
			std::vector<SummarizationVariable> p3;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				std::string varname_ = serializedMsg.unpackString();
				unsigned char viclassId_; unsigned int viobjId_;
				serializedMsg.unpackObject( viclassId_, viobjId_);
				PostingIteratorInterface* varpos_ = getObject<PostingIteratorInterface>( viclassId_, viobjId_);
				SummarizationVariable ee = SummarizationVariable( varname_, varpos_);
				
				p3.push_back( ee);
			}
			try {
				obj->addSummarizationFeature(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SummarizerExecutionContextConst::Method_getSummary:
		{
			std::cerr << "called method SummarizerExecutionContextImpl::getSummary [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::vector<SummarizerExecutionContextInterface::SummaryElement> p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->getSummary(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packSummaryElement( p0[ii]);
			}
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_SummarizerFunctionInstance:
	{
	SummarizerFunctionInstanceInterface* obj = getObject<SummarizerFunctionInstanceInterface>( classId, objId);
	switch( (SummarizerFunctionInstanceConst::MethodId)methodId)
	{
		case SummarizerFunctionInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of SummarizerFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_addStringParameter:
		{
			std::cerr << "called method SummarizerFunctionInstanceImpl::addStringParameter [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->addStringParameter(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_addNumericParameter:
		{
			std::cerr << "called method SummarizerFunctionInstanceImpl::addNumericParameter [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			try {
				obj->addNumericParameter(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_createExecutionContext:
		{
			std::cerr << "called method SummarizerFunctionInstanceImpl::createExecutionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			SummarizerExecutionContextInterface* p0;
			const StorageClientInterface* p1;
			MetaDataReaderInterface* p2;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<MetaDataReaderInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createExecutionContext(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_tostring:
		{
			std::cerr << "called method SummarizerFunctionInstanceImpl::tostring [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			try {
				p0 = obj->tostring();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_SummarizerFunction:
	{
	SummarizerFunctionInterface* obj = getObject<SummarizerFunctionInterface>( classId, objId);
	switch( (SummarizerFunctionConst::MethodId)methodId)
	{
		case SummarizerFunctionConst::Method_Destructor:
		{
			std::cerr << "called destructor of SummarizerFunctionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionConst::Method_createInstance:
		{
			std::cerr << "called method SummarizerFunctionImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			SummarizerFunctionInstanceInterface* p0;
			const QueryProcessorInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_QueryProcessor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<QueryProcessorInterface>( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_TextProcessor:
	{
	TextProcessorInterface* obj = getObject<TextProcessorInterface>( classId, objId);
	switch( (TextProcessorConst::MethodId)methodId)
	{
		case TextProcessorConst::Method_Destructor:
		{
			std::cerr << "called destructor of TextProcessorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TextProcessorConst::Method_addResourcePath:
		{
			std::cerr << "called method TextProcessorImpl::addResourcePath [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->addResourcePath(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case TextProcessorConst::Method_getResourcePath:
		{
			std::cerr << "called method TextProcessorImpl::getResourcePath [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->getResourcePath(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
		case TextProcessorConst::Method_getTokenizer:
		{
			std::cerr << "called method TextProcessorImpl::getTokenizer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const TokenizerFunctionInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getTokenizer(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case TextProcessorConst::Method_getNormalizer:
		{
			std::cerr << "called method TextProcessorImpl::getNormalizer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const NormalizerFunctionInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getNormalizer(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case TextProcessorConst::Method_defineTokenizer:
		{
			std::cerr << "called method TextProcessorImpl::defineTokenizer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			const TokenizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_TokenizerFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getConstObject<TokenizerFunctionInterface>( classId_2, objId_2);
			try {
				obj->defineTokenizer(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case TextProcessorConst::Method_defineNormalizer:
		{
			std::cerr << "called method TextProcessorImpl::defineNormalizer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			const NormalizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_NormalizerFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getConstObject<NormalizerFunctionInterface>( classId_2, objId_2);
			try {
				obj->defineNormalizer(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
	}
	break;
	}
	case ClassId_TokenizerExecutionContext:
	{
	TokenizerExecutionContextInterface* obj = getObject<TokenizerExecutionContextInterface>( classId, objId);
	switch( (TokenizerExecutionContextConst::MethodId)methodId)
	{
		case TokenizerExecutionContextConst::Method_Destructor:
		{
			std::cerr << "called destructor of TokenizerExecutionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerExecutionContextConst::Method_tokenize:
		{
			std::cerr << "called method TokenizerExecutionContextImpl::tokenize [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::vector<analyzer::Token> p0;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			try {
				p0 = obj->tokenize(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packAnalyzerToken( p0[ii]);
			}
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_TokenizerFunctionInstance:
	{
	TokenizerFunctionInstanceInterface* obj = getObject<TokenizerFunctionInstanceInterface>( classId, objId);
	switch( (TokenizerFunctionInstanceConst::MethodId)methodId)
	{
		case TokenizerFunctionInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of TokenizerFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionInstanceConst::Method_concatBeforeTokenize:
		{
			std::cerr << "called method TokenizerFunctionInstanceImpl::concatBeforeTokenize [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			try {
				p0 = obj->concatBeforeTokenize();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case TokenizerFunctionInstanceConst::Method_createExecutionContext:
		{
			std::cerr << "called method TokenizerFunctionInstanceImpl::createExecutionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			TokenizerExecutionContextInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createExecutionContext();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_TokenizerFunction:
	{
	TokenizerFunctionInterface* obj = getObject<TokenizerFunctionInterface>( classId, objId);
	switch( (TokenizerFunctionConst::MethodId)methodId)
	{
		case TokenizerFunctionConst::Method_Destructor:
		{
			std::cerr << "called destructor of TokenizerFunctionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionConst::Method_createInstance:
		{
			std::cerr << "called method TokenizerFunctionImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			TokenizerFunctionInstanceInterface* p0;
			std::vector<std::string> p1;
			const TextProcessorInterface* p2;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p1.push_back( ee);
			}
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_TextProcessor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getConstObject<TextProcessorInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_WeightingExecutionContext:
	{
	WeightingExecutionContextInterface* obj = getObject<WeightingExecutionContextInterface>( classId, objId);
	switch( (WeightingExecutionContextConst::MethodId)methodId)
	{
		case WeightingExecutionContextConst::Method_Destructor:
		{
			std::cerr << "called destructor of WeightingExecutionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingExecutionContextConst::Method_call:
		{
			std::cerr << "called method WeightingExecutionContextImpl::call [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			float p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			try {
				p0 = obj->call(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packFloat( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_WeightingFunctionInstance:
	{
	WeightingFunctionInstanceInterface* obj = getObject<WeightingFunctionInstanceInterface>( classId, objId);
	switch( (WeightingFunctionInstanceConst::MethodId)methodId)
	{
		case WeightingFunctionInstanceConst::Method_Destructor:
		{
			std::cerr << "called destructor of WeightingFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_addStringParameter:
		{
			std::cerr << "called method WeightingFunctionInstanceImpl::addStringParameter [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			try {
				obj->addStringParameter(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_addNumericParameter:
		{
			std::cerr << "called method WeightingFunctionInstanceImpl::addNumericParameter [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			try {
				obj->addNumericParameter(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_createExecutionContext:
		{
			std::cerr << "called method WeightingFunctionInstanceImpl::createExecutionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			WeightingExecutionContextInterface* p0;
			const StorageClientInterface* p1;
			PostingIteratorInterface* p2;
			MetaDataReaderInterface* p3;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<MetaDataReaderInterface>( classId_3, objId_3);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createExecutionContext(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_tostring:
		{
			std::cerr << "called method WeightingFunctionInstanceImpl::tostring [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p0;
			try {
				p0 = obj->tostring();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_WeightingFunction:
	{
	WeightingFunctionInterface* obj = getObject<WeightingFunctionInterface>( classId, objId);
	switch( (WeightingFunctionConst::MethodId)methodId)
	{
		case WeightingFunctionConst::Method_Destructor:
		{
			std::cerr << "called destructor of WeightingFunctionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionConst::Method_createInstance:
		{
			std::cerr << "called method WeightingFunctionImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			WeightingFunctionInstanceInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createInstance();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	}
	throw std::runtime_error("calling undefined request handler");
}
