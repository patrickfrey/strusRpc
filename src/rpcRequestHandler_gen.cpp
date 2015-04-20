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
#include "serializer.hpp"
#include "objectIds_gen.hpp"
#include "private/dll_tags.hpp"
#include <string>

using namespace strus;
DLL_PUBLIC std::string RpcRequestHandler::handleRequest( const char* src, std::size_t srcsize)
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
			deleteObject( classId, objId);
		}
		case AnalyzerObjectBuilderConst::Method_getTextProcessor:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getTextProcessor' is not implemented for RPC");
			return msg.content();
			break;
		}
		case AnalyzerObjectBuilderConst::Method_createSegmenter:
		{
			RpcSerializer msg;
			SegmenterInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_Segmenter;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case AnalyzerObjectBuilderConst::Method_createDocumentAnalyzer:
		{
			RpcSerializer msg;
			DocumentAnalyzerInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzer;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case AnalyzerObjectBuilderConst::Method_createQueryAnalyzer:
		{
			RpcSerializer msg;
			QueryAnalyzerInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_QueryAnalyzer;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case AttributeReaderConst::Method_elementHandle:
		{
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
			break;
		}
		case AttributeReaderConst::Method_skipDoc:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case AttributeReaderConst::Method_getValue:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DatabaseBackupCursorConst::Method_fetch:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DatabaseClientConst::Method_close:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_createTransaction:
		{
			RpcSerializer msg;
			DatabaseTransactionInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_DatabaseTransaction;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_createCursor:
		{
			RpcSerializer msg;
			DatabaseCursorInterface* p0;
			DatabaseOptions p1;
			p1 = serializedMsg.unpackDatabaseOptions();
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
			unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_createBackupCursor:
		{
			RpcSerializer msg;
			DatabaseBackupCursorInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_DatabaseBackupCursor;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_writeImm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_removeImm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseClientConst::Method_readValue:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DatabaseCursorConst::Method_seekUpperBound:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_seekFirst:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_seekLast:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_seekNext:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_seekPrev:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_key:
		{
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
			break;
		}
		case DatabaseCursorConst::Method_value:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DatabaseConst::Method_createClient:
		{
			RpcSerializer msg;
			DatabaseClientInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->createClient(p1);
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
			unsigned char classId_0 = (unsigned char)ClassId_DatabaseClient;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseConst::Method_createDatabase:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseConst::Method_restoreDatabase:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseConst::Method_destroyDatabase:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseConst::Method_getConfigDescription:
		{
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
			break;
		}
		case DatabaseConst::Method_getConfigParameters:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DatabaseTransactionConst::Method_createCursor:
		{
			RpcSerializer msg;
			DatabaseCursorInterface* p0;
			DatabaseOptions p1;
			p1 = serializedMsg.unpackDatabaseOptions();
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
			unsigned char classId_0 = (unsigned char)ClassId_DatabaseCursor;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseTransactionConst::Method_write:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseTransactionConst::Method_remove:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseTransactionConst::Method_removeSubTree:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DatabaseTransactionConst::Method_commit:
		{
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
			break;
		}
		case DatabaseTransactionConst::Method_rollback:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case DocnoRangeAllocatorConst::Method_allocDocnoRange:
		{
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
			break;
		}
		case DocnoRangeAllocatorConst::Method_deallocDocnoRange:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DocumentAnalyzerInstanceConst::Method_putInput:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DocumentAnalyzerInstanceConst::Method_analyzeNext:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case DocumentAnalyzerConst::Method_addSearchIndexFeature:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerConfig p3;
			std::vector<NormalizerConfig> p4;
			DocumentAnalyzerInterface::FeatureOptions p5;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTokenizerConfig();
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				NormalizerConfig ee = serializedMsg.unpackNormalizerConfig();
				p4.push_back( ee);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			try {
				obj->addSearchIndexFeature(p1,p2,p3,p4,p5);
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
			break;
		}
		case DocumentAnalyzerConst::Method_addForwardIndexFeature:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerConfig p3;
			std::vector<NormalizerConfig> p4;
			DocumentAnalyzerInterface::FeatureOptions p5;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTokenizerConfig();
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				NormalizerConfig ee = serializedMsg.unpackNormalizerConfig();
				p4.push_back( ee);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			try {
				obj->addForwardIndexFeature(p1,p2,p3,p4,p5);
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
			break;
		}
		case DocumentAnalyzerConst::Method_defineMetaData:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerConfig p3;
			std::vector<NormalizerConfig> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTokenizerConfig();
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				NormalizerConfig ee = serializedMsg.unpackNormalizerConfig();
				p4.push_back( ee);
			}
			try {
				obj->defineMetaData(p1,p2,p3,p4);
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
			break;
		}
		case DocumentAnalyzerConst::Method_defineAttribute:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerConfig p3;
			std::vector<NormalizerConfig> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTokenizerConfig();
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				NormalizerConfig ee = serializedMsg.unpackNormalizerConfig();
				p4.push_back( ee);
			}
			try {
				obj->defineAttribute(p1,p2,p3,p4);
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
			break;
		}
		case DocumentAnalyzerConst::Method_defineSubDocument:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case DocumentAnalyzerConst::Method_analyze:
		{
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
			break;
		}
		case DocumentAnalyzerConst::Method_createInstance:
		{
			RpcSerializer msg;
			DocumentAnalyzerInstanceInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_DocumentAnalyzerInstance;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case ForwardIteratorConst::Method_skipDoc:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case ForwardIteratorConst::Method_skipPos:
		{
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
			break;
		}
		case ForwardIteratorConst::Method_fetch:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case InvAclIteratorConst::Method_skipDoc:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case MetaDataReaderConst::Method_hasElement:
		{
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
			break;
		}
		case MetaDataReaderConst::Method_elementHandle:
		{
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
			break;
		}
		case MetaDataReaderConst::Method_nofElements:
		{
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
			break;
		}
		case MetaDataReaderConst::Method_skipDoc:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case MetaDataReaderConst::Method_getValue:
		{
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
			break;
		}
		case MetaDataReaderConst::Method_getType:
		{
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
			break;
		}
		case MetaDataReaderConst::Method_getName:
		{
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
			break;
		}
	}
	break;
	}
	case ClassId_NormalizerConstructor:
	{
	NormalizerConstructorInterface* obj = getObject<NormalizerConstructorInterface>( classId, objId);
	switch( (NormalizerConstructorConst::MethodId)methodId)
	{
		case NormalizerConstructorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case NormalizerConstructorConst::Method_create:
		{
			RpcSerializer msg;
			NormalizerInterface* p0;
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
			p2 = getObject<TextProcessorInterface>( classId_2, objId_2);
			try {
				p0 = obj->create(p1,p2);
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
			unsigned char classId_0 = (unsigned char)ClassId_Normalizer;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	case ClassId_NormalizerInstance:
	{
	NormalizerInstanceInterface* obj = getObject<NormalizerInstanceInterface>( classId, objId);
	switch( (NormalizerInstanceConst::MethodId)methodId)
	{
		case NormalizerInstanceConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case NormalizerInstanceConst::Method_normalize:
		{
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
			break;
		}
	}
	break;
	}
	case ClassId_Normalizer:
	{
	NormalizerInterface* obj = getObject<NormalizerInterface>( classId, objId);
	switch( (NormalizerConst::MethodId)methodId)
	{
		case NormalizerConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case NormalizerConst::Method_createInstance:
		{
			RpcSerializer msg;
			NormalizerInstanceInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_NormalizerInstance;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case PeerStorageTransactionConst::Method_updateNofDocumentsInsertedChange:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case PeerStorageTransactionConst::Method_updateDocumentFrequencyChange:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case PeerStorageTransactionConst::Method_commit:
		{
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
			break;
		}
		case PeerStorageTransactionConst::Method_rollback:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case PostingIteratorConst::Method_skipDoc:
		{
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
			break;
		}
		case PostingIteratorConst::Method_skipPos:
		{
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
			break;
		}
		case PostingIteratorConst::Method_featureid:
		{
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
			break;
		}
		case PostingIteratorConst::Method_subExpressions:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'subExpressions' is not implemented for RPC");
			return msg.content();
			break;
		}
		case PostingIteratorConst::Method_documentFrequency:
		{
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
			break;
		}
		case PostingIteratorConst::Method_frequency:
		{
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
			break;
		}
		case PostingIteratorConst::Method_docno:
		{
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
			break;
		}
		case PostingIteratorConst::Method_posno:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case PostingJoinOperatorConst::Method_createResultIterator:
		{
			RpcSerializer msg;
			PostingIteratorInterface* p0;
			std::vector<Reference<PostingIteratorInterface> > p1;
			int p2;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				unsigned char classId_; unsigned int objId_;
			serializedMsg.unpackObject( classId_, objId_);
			if (classId_ != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			PostingIteratorInterface* ee = getObject<PostingIteratorInterface>( classId_, objId_);
				p1.push_back( ee);
			}
			p2 = serializedMsg.unpackInt();
			try {
				p0 = obj->createResultIterator(p1,p2);
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
			unsigned char classId_0 = (unsigned char)ClassId_PostingIterator;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case QueryAnalyzerConst::Method_definePhraseType:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TokenizerConfig p3;
			std::vector<NormalizerConfig> p4;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTokenizerConfig();
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				NormalizerConfig ee = serializedMsg.unpackNormalizerConfig();
				p4.push_back( ee);
			}
			try {
				obj->definePhraseType(p1,p2,p3,p4);
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
			break;
		}
		case QueryAnalyzerConst::Method_analyzePhrase:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case QueryEvalConst::Method_addTerm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryEvalConst::Method_addSelectionFeature:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryEvalConst::Method_addRestrictionFeature:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryEvalConst::Method_addSummarizer:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			SummarizerConfig p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackSummarizerConfig();
			try {
				obj->addSummarizer(p1,p2,p3);
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
			break;
		}
		case QueryEvalConst::Method_addWeightingFunction:
		{
			RpcSerializer msg;
			std::string p1;
			WeightingConfig p2;
			std::vector<std::string> p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackWeightingConfig();
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p3.push_back( ee);
			}
			try {
				obj->addWeightingFunction(p1,p2,p3);
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
			break;
		}
		case QueryEvalConst::Method_createQuery:
		{
			RpcSerializer msg;
			QueryInterface* p0;
			const StorageClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<StorageClientInterface>( classId_1, objId_1);
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
			unsigned char classId_0 = (unsigned char)ClassId_Query;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case QueryConst::Method_pushTerm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_pushExpression:
		{
			RpcSerializer msg;
			std::string p1;
			std::size_t p2;
			int p3;
			p1 = serializedMsg.unpackString();
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_pushDuplicate:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_attachVariable:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_defineFeature:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_defineMetaDataRestriction:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_setMaxNofRanks:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_setMinRank:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_setUserName:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case QueryConst::Method_evaluate:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case QueryProcessorConst::Method_definePostingJoinOperator:
		{
			RpcSerializer msg;
			std::string p1;
			PostingJoinOperatorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingJoinOperator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingJoinOperatorInterface>( classId_2, objId_2);
			try {
				obj->definePostingJoinOperator(p1,p2);
				releaseObject( classId_2, objId_2);
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
			break;
		}
		case QueryProcessorConst::Method_getPostingJoinOperator:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getPostingJoinOperator' is not implemented for RPC");
			return msg.content();
			break;
		}
		case QueryProcessorConst::Method_defineWeightingFunction:
		{
			RpcSerializer msg;
			std::string p1;
			WeightingFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_WeightingFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<WeightingFunctionInterface>( classId_2, objId_2);
			try {
				obj->defineWeightingFunction(p1,p2);
				releaseObject( classId_2, objId_2);
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
			break;
		}
		case QueryProcessorConst::Method_getWeightingFunction:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getWeightingFunction' is not implemented for RPC");
			return msg.content();
			break;
		}
		case QueryProcessorConst::Method_defineSummarizerFunction:
		{
			RpcSerializer msg;
			std::string p1;
			SummarizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_SummarizerFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<SummarizerFunctionInterface>( classId_2, objId_2);
			try {
				obj->defineSummarizerFunction(p1,p2);
				releaseObject( classId_2, objId_2);
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
			break;
		}
		case QueryProcessorConst::Method_getSummarizerFunction:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getSummarizerFunction' is not implemented for RPC");
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case SegmenterInstanceConst::Method_putInput:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case SegmenterInstanceConst::Method_getNext:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case SegmenterConst::Method_defineSelectorExpression:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case SegmenterConst::Method_defineSubSection:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case SegmenterConst::Method_createInstance:
		{
			RpcSerializer msg;
			SegmenterInstanceInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_SegmenterInstance;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StorageAlterMetaDataTableConst::Method_addElement:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageAlterMetaDataTableConst::Method_alterElement:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageAlterMetaDataTableConst::Method_renameElement:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageAlterMetaDataTableConst::Method_deleteElement:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageAlterMetaDataTableConst::Method_clearElement:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageAlterMetaDataTableConst::Method_commit:
		{
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
			break;
		}
		case StorageAlterMetaDataTableConst::Method_rollback:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StorageClientConst::Method_close:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createTermPostingIterator:
		{
			RpcSerializer msg;
			PostingIteratorInterface* p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_PostingIterator;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createForwardIterator:
		{
			RpcSerializer msg;
			ForwardIteratorInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_ForwardIterator;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createInvAclIterator:
		{
			RpcSerializer msg;
			InvAclIteratorInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_InvAclIterator;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_globalNofDocumentsInserted:
		{
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
			break;
		}
		case StorageClientConst::Method_localNofDocumentsInserted:
		{
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
			break;
		}
		case StorageClientConst::Method_globalDocumentFrequency:
		{
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
			break;
		}
		case StorageClientConst::Method_localDocumentFrequency:
		{
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
			break;
		}
		case StorageClientConst::Method_maxDocumentNumber:
		{
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
			break;
		}
		case StorageClientConst::Method_documentNumber:
		{
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
			break;
		}
		case StorageClientConst::Method_createMetaDataReader:
		{
			RpcSerializer msg;
			MetaDataReaderInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_MetaDataReader;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createAttributeReader:
		{
			RpcSerializer msg;
			AttributeReaderInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_AttributeReader;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createDocnoRangeAllocator:
		{
			RpcSerializer msg;
			DocnoRangeAllocatorInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_DocnoRangeAllocator;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createTransaction:
		{
			RpcSerializer msg;
			StorageTransactionInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageTransaction;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createPeerStorageTransaction:
		{
			RpcSerializer msg;
			PeerStorageTransactionInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_PeerStorageTransaction;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_defineStoragePeerInterface:
		{
			RpcSerializer msg;
			const StoragePeerInterface* p1;
			bool p2;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StoragePeer) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<StoragePeerInterface>( classId_1, objId_1);
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createDocumentChecker:
		{
			RpcSerializer msg;
			StorageDocumentInterface* p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageDocument;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageClientConst::Method_checkStorage:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'checkStorage' is not implemented for RPC");
			return msg.content();
			break;
		}
		case StorageClientConst::Method_createDump:
		{
			RpcSerializer msg;
			StorageDumpInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageDump;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StorageDocumentConst::Method_addSearchIndexTerm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageDocumentConst::Method_addForwardIndexTerm:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageDocumentConst::Method_setMetaData:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageDocumentConst::Method_setAttribute:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageDocumentConst::Method_setUserAccessRight:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageDocumentConst::Method_done:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case StorageDumpConst::Method_nextChunk:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case StorageConst::Method_createClient:
		{
			RpcSerializer msg;
			StorageClientInterface* p0;
			std::string p1;
			DatabaseClientInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			try {
				p0 = obj->createClient(p1,p2);
				releaseObject( classId_2, objId_2);
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageClient;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageConst::Method_createStorage:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageConst::Method_createAlterMetaDataTable:
		{
			RpcSerializer msg;
			StorageAlterMetaDataTableInterface* p0;
			DatabaseClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_DatabaseClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<DatabaseClientInterface>( classId_1, objId_1);
			try {
				p0 = obj->createAlterMetaDataTable(p1);
				releaseObject( classId_1, objId_1);
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageConst::Method_getConfigDescription:
		{
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
			break;
		}
		case StorageConst::Method_getConfigParameters:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case StorageObjectBuilderConst::Method_getStorage:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getStorage' is not implemented for RPC");
			return msg.content();
			break;
		}
		case StorageObjectBuilderConst::Method_getDatabase:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getDatabase' is not implemented for RPC");
			return msg.content();
			break;
		}
		case StorageObjectBuilderConst::Method_getQueryProcessor:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getQueryProcessor' is not implemented for RPC");
			return msg.content();
			break;
		}
		case StorageObjectBuilderConst::Method_createStorageClient:
		{
			RpcSerializer msg;
			StorageClientInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageClient;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageObjectBuilderConst::Method_createAlterMetaDataTable:
		{
			RpcSerializer msg;
			StorageAlterMetaDataTableInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->createAlterMetaDataTable(p1);
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageAlterMetaDataTable;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageObjectBuilderConst::Method_createQueryEval:
		{
			RpcSerializer msg;
			QueryEvalInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_QueryEval;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StoragePeerConst::Method_createTransaction:
		{
			RpcSerializer msg;
			StoragePeerTransactionInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_StoragePeerTransaction;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StoragePeerTransactionConst::Method_populateNofDocumentsInsertedChange:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StoragePeerTransactionConst::Method_populateDocumentFrequencyChange:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StoragePeerTransactionConst::Method_try_commit:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StoragePeerTransactionConst::Method_final_commit:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StoragePeerTransactionConst::Method_rollback:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case StorageTransactionConst::Method_createDocument:
		{
			RpcSerializer msg;
			StorageDocumentInterface* p0;
			std::string p1;
			Index p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackIndex();
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
			unsigned char classId_0 = (unsigned char)ClassId_StorageDocument;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageTransactionConst::Method_deleteDocument:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageTransactionConst::Method_deleteUserAccessRights:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case StorageTransactionConst::Method_commit:
		{
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
			break;
		}
		case StorageTransactionConst::Method_rollback:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	case ClassId_SummarizerClosure:
	{
	SummarizerClosureInterface* obj = getObject<SummarizerClosureInterface>( classId, objId);
	switch( (SummarizerClosureConst::MethodId)methodId)
	{
		case SummarizerClosureConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case SummarizerClosureConst::Method_getSummary:
		{
			RpcSerializer msg;
			std::vector<SummarizerClosureInterface::SummaryElement> p0;
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
			break;
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
			deleteObject( classId, objId);
		}
		case SummarizerFunctionConst::Method_numericParameterNames:
		{
			RpcSerializer msg;
			const char** p0;
			try {
				p0 = obj->numericParameterNames();
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
			break;
		}
		case SummarizerFunctionConst::Method_textualParameterNames:
		{
			RpcSerializer msg;
			const char** p0;
			try {
				p0 = obj->textualParameterNames();
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
			break;
		}
		case SummarizerFunctionConst::Method_featureParameterClassNames:
		{
			RpcSerializer msg;
			const char** p0;
			try {
				p0 = obj->featureParameterClassNames();
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
			break;
		}
		case SummarizerFunctionConst::Method_createClosure:
		{
			RpcSerializer msg;
			SummarizerClosureInterface* p0;
			const StorageClientInterface* p1;
			const QueryProcessorInterface* p2;
			MetaDataReaderInterface* p3;
			std::vector<SummarizerFunctionInterface::FeatureParameter> p4;
			std::vector<std::string> p5;
			std::vector<ArithmeticVariant> p6;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_QueryProcessor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<QueryProcessorInterface>( classId_2, objId_2);
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<MetaDataReaderInterface>( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
					unsigned int featclass_ = serializedMsg.unpackUint();
			unsigned char piclassId_; unsigned int piobjId_;
			serializedMsg.unpackObject( piclassId_, piobjId_);
			PostingIteratorInterface* pos_ = getObject<PostingIteratorInterface>( piclassId_, piobjId_);
			std::size_t vi_=0,ve_ = serializedMsg.unpackSize();
			std::vector<SummarizationVariable> vars_;
			for (; vi_ != ve_; ++vi_)
			{
				std::string varname = serializedMsg.unpackString();
			unsigned char viclassId_; unsigned int viobjId_;
			serializedMsg.unpackObject( viclassId_, viobjId_);
				PostingIteratorInterface* varpos = getObject<PostingIteratorInterface>( viclassId_, viobjId_);
				vars_.push_back( SummarizationVariable( varname, varpos));
			}
			SummarizerFunctionInterface::FeatureParameter ee = SummarizerFunctionInterface::FeatureParameter( featclass_, SummarizationFeature( pos_, vars_));
		
				p4.push_back( ee);
			}
			std::size_t n5 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n5; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p5.push_back( ee);
			}
			std::size_t n6 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n6; ++ii) {
				ArithmeticVariant ee = serializedMsg.unpackArithmeticVariant();
				p6.push_back( ee);
			}
			try {
				p0 = obj->createClosure(p1,p2,p3,p4,p5,p6);
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
			unsigned char classId_0 = (unsigned char)ClassId_SummarizerClosure;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
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
			deleteObject( classId, objId);
		}
		case TextProcessorConst::Method_addResourcePath:
		{
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case TextProcessorConst::Method_getResourcePath:
		{
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
			break;
		}
		case TextProcessorConst::Method_getTokenizer:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getTokenizer' is not implemented for RPC");
			return msg.content();
			break;
		}
		case TextProcessorConst::Method_getNormalizer:
		{
			RpcSerializer msg;
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'getNormalizer' is not implemented for RPC");
			return msg.content();
			break;
		}
		case TextProcessorConst::Method_defineTokenizer:
		{
			RpcSerializer msg;
			std::string p1;
			const TokenizerConstructorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_TokenizerConstructor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<TokenizerConstructorInterface>( classId_2, objId_2);
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
			msg.packCrc32();
			return msg.content();
			break;
		}
		case TextProcessorConst::Method_defineNormalizer:
		{
			RpcSerializer msg;
			std::string p1;
			const NormalizerConstructorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_NormalizerConstructor) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<NormalizerConstructorInterface>( classId_2, objId_2);
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
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	case ClassId_TokenizerConstructor:
	{
	TokenizerConstructorInterface* obj = getObject<TokenizerConstructorInterface>( classId, objId);
	switch( (TokenizerConstructorConst::MethodId)methodId)
	{
		case TokenizerConstructorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case TokenizerConstructorConst::Method_create:
		{
			RpcSerializer msg;
			TokenizerInterface* p0;
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
			p2 = getObject<TextProcessorInterface>( classId_2, objId_2);
			try {
				p0 = obj->create(p1,p2);
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
			unsigned char classId_0 = (unsigned char)ClassId_Tokenizer;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	case ClassId_TokenizerInstance:
	{
	TokenizerInstanceInterface* obj = getObject<TokenizerInstanceInterface>( classId, objId);
	switch( (TokenizerInstanceConst::MethodId)methodId)
	{
		case TokenizerInstanceConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case TokenizerInstanceConst::Method_tokenize:
		{
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
			break;
		}
	}
	break;
	}
	case ClassId_Tokenizer:
	{
	TokenizerInterface* obj = getObject<TokenizerInterface>( classId, objId);
	switch( (TokenizerConst::MethodId)methodId)
	{
		case TokenizerConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case TokenizerConst::Method_concatBeforeTokenize:
		{
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
			break;
		}
		case TokenizerConst::Method_createInstance:
		{
			RpcSerializer msg;
			TokenizerInstanceInterface* p0;
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
			unsigned char classId_0 = (unsigned char)ClassId_TokenizerInstance;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	case ClassId_WeightingClosure:
	{
	WeightingClosureInterface* obj = getObject<WeightingClosureInterface>( classId, objId);
	switch( (WeightingClosureConst::MethodId)methodId)
	{
		case WeightingClosureConst::Method_Destructor:
		{
			deleteObject( classId, objId);
		}
		case WeightingClosureConst::Method_call:
		{
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
			break;
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
			deleteObject( classId, objId);
		}
		case WeightingFunctionConst::Method_numericParameterNames:
		{
			RpcSerializer msg;
			const char** p0;
			try {
				p0 = obj->numericParameterNames();
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
			break;
		}
		case WeightingFunctionConst::Method_createClosure:
		{
			RpcSerializer msg;
			WeightingClosureInterface* p0;
			const StorageClientInterface* p1;
			PostingIteratorInterface* p2;
			MetaDataReaderInterface* p3;
			std::vector<ArithmeticVariant> p4;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_MetaDataReader) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p3 = getObject<MetaDataReaderInterface>( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				ArithmeticVariant ee = serializedMsg.unpackArithmeticVariant();
				p4.push_back( ee);
			}
			try {
				p0 = obj->createClosure(p1,p2,p3,p4);
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
			unsigned char classId_0 = (unsigned char)ClassId_WeightingClosure;
			unsigned int objId_0 = createObject( classId_0, p0);
			msg.packObject( classId_0, objId_0);
			msg.packCrc32();
			return msg.content();
			break;
		}
	}
	break;
	}
	}
	throw std::runtime_error("calling undefined request handler");
}
