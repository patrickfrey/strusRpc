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
	case ClassId_AggregatorFunctionInstance:
	{
	AggregatorFunctionInstanceInterface* obj = getObject<AggregatorFunctionInstanceInterface>( classId, objId);
	switch( (AggregatorFunctionInstanceConst::MethodId)methodId)
	{
		case AggregatorFunctionInstanceConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case AggregatorFunctionInstanceConst::Method_evaluate:
		{
			RpcSerializer msg;
			double p0;
			analyzer::Document p1;
			p1 = serializedMsg.unpackAnalyzerDocument();
			try {
				p0 = obj->evaluate(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
			} catch (const std::bad_alloc& err) {
				msg.packByte( MsgTypeException_BadAlloc);
				msg.packString( "memory allocation error");
				return msg.content();
			} catch (const std::logic_error& err) {
				msg.packByte( MsgTypeException_LogicError);
				msg.packString( err.what());
				return msg.content();
			}
			msg.packDouble( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_AggregatorFunction:
	{
	AggregatorFunctionInterface* obj = getObject<AggregatorFunctionInterface>( classId, objId);
	switch( (AggregatorFunctionConst::MethodId)methodId)
	{
		case AggregatorFunctionConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case AggregatorFunctionConst::Method_createInstance:
		{
			RpcSerializer msg;
			AggregatorFunctionInstanceInterface* p0;
			std::vector<std::string> p1;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				std::string ee = serializedMsg.unpackString();
				p1.push_back( ee);
			}
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
	case ClassId_AnalyzerObjectBuilder:
	{
	AnalyzerObjectBuilderInterface* obj = getObject<AnalyzerObjectBuilderInterface>( classId, objId);
	switch( (AnalyzerObjectBuilderConst::MethodId)methodId)
	{
		case AnalyzerObjectBuilderConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_getTextProcessor:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
		}
		case AttributeReaderConst::Method_getAttributeNames:
		{
			RpcSerializer msg;
			std::vector<std::string> p0;
			try {
				p0 = obj->getAttributeNames();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
				msg.packString( p0[ii]);
			}
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
		}
		case DatabaseClientConst::Method_createTransaction:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
		}
		case DatabaseConst::Method_exists:
		{
			RpcSerializer msg;
			bool p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				p0 = obj->exists(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case DatabaseConst::Method_createClient:
		{
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
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseTransactionConst::Method_createCursor:
		{
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
			return std::string();
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
			deleteObject( classId, objId);
			return std::string();
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
		}
	}
	break;
	}
	case ClassId_DocumentAnalyzerContext:
	{
	DocumentAnalyzerContextInterface* obj = getObject<DocumentAnalyzerContextInterface>( classId, objId);
	switch( (DocumentAnalyzerContextConst::MethodId)methodId)
	{
		case DocumentAnalyzerContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentAnalyzerContextConst::Method_putInput:
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
			return std::string();
		}
		case DocumentAnalyzerContextConst::Method_analyzeNext:
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
			return std::string();
		}
		case DocumentAnalyzerConst::Method_addSearchIndexFeature:
		{
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
		case DocumentAnalyzerConst::Method_defineAggregatedMetaData:
		{
			RpcSerializer msg;
			std::string p1;
			AggregatorFunctionInstanceInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_AggregatorFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<AggregatorFunctionInstanceInterface>( classId_2, objId_2);
			try {
				obj->defineAggregatedMetaData(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case DocumentAnalyzerConst::Method_defineAttribute:
		{
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
			RpcSerializer msg;
			analyzer::Document p0;
			std::string p1;
			DocumentClass p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackDocumentClass();
			try {
				p0 = obj->analyze(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case DocumentAnalyzerConst::Method_mimeType:
		{
			RpcSerializer msg;
			std::string p0;
			try {
				p0 = obj->mimeType();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case DocumentAnalyzerConst::Method_createContext:
		{
			RpcSerializer msg;
			DocumentAnalyzerContextInterface* p0;
			DocumentClass p1;
			p1 = serializedMsg.unpackDocumentClass();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createContext(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
	case ClassId_DocumentClassDetector:
	{
	DocumentClassDetectorInterface* obj = getObject<DocumentClassDetectorInterface>( classId, objId);
	switch( (DocumentClassDetectorConst::MethodId)methodId)
	{
		case DocumentClassDetectorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentClassDetectorConst::Method_detect:
		{
			RpcSerializer msg;
			bool p0;
			DocumentClass p1;
			const char* p2;
			std::size_t p3;
			serializedMsg.unpackBuffer( p2, p3);
			try {
				p0 = obj->detect(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			msg.packDocumentClass( p1);
			msg.packCrc32();
			return msg.content();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
		}
	}
	break;
	}
	case ClassId_NormalizerFunctionContext:
	{
	NormalizerFunctionContextInterface* obj = getObject<NormalizerFunctionContextInterface>( classId, objId);
	switch( (NormalizerFunctionContextConst::MethodId)methodId)
	{
		case NormalizerFunctionContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionContextConst::Method_normalize:
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
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			NormalizerFunctionContextInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createFunctionContext();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionConst::Method_createInstance:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			deleteObject( classId, objId);
			return std::string();
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
		}
		case PostingIteratorConst::Method_subExpressions:
		{
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'subExpressions' is not implemented for RPC");
			return msg.content();
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
			return std::string();
		}
		case PostingJoinOperatorConst::Method_createResultIterator:
		{
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
			deleteObject( classId, objId);
			return std::string();
		}
		case QueryAnalyzerConst::Method_definePhraseType:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
		}
		case QueryEvalConst::Method_addExclusionFeature:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->addExclusionFeature(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			RpcSerializer msg;
			std::string p1;
			SummarizerFunctionInstanceInterface* p2;
			std::vector<QueryEvalInterface::FeatureParameter> p3;
			std::string p4;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_SummarizerFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<SummarizerFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				QueryEvalInterface::FeatureParameter ee = serializedMsg.unpackFeatureParameter();
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
			RpcSerializer msg;
			std::string p1;
			WeightingFunctionInstanceInterface* p2;
			std::vector<QueryEvalInterface::FeatureParameter> p3;
			float p4;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_WeightingFunctionInstance) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<WeightingFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				QueryEvalInterface::FeatureParameter ee = serializedMsg.unpackFeatureParameter();
				p3.push_back( ee);
			}
			p4 = serializedMsg.unpackFloat();
			try {
				obj->addWeightingFunction(p1,p2,p3,p4);
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
		}
		case QueryConst::Method_pushExpression:
		{
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
		case QueryConst::Method_addUserName:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->addUserName(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
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
	case ClassId_SegmenterContext:
	{
	SegmenterContextInterface* obj = getObject<SegmenterContextInterface>( classId, objId);
	switch( (SegmenterContextConst::MethodId)methodId)
	{
		case SegmenterContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterContextConst::Method_putInput:
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
			return std::string();
		}
		case SegmenterContextConst::Method_getNext:
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
			return std::string();
		}
		case SegmenterConst::Method_mimeType:
		{
			RpcSerializer msg;
			std::string p0;
			try {
				p0 = obj->mimeType();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			return std::string();
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
			return std::string();
		}
		case SegmenterConst::Method_createContext:
		{
			RpcSerializer msg;
			SegmenterContextInterface* p0;
			DocumentClass p1;
			p1 = serializedMsg.unpackDocumentClass();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createContext(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
		}
		case StorageClientConst::Method_createTermPostingIterator:
		{
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
		case StorageClientConst::Method_documentStatistics:
		{
			RpcSerializer msg;
			Index p0;
			Index p1;
			StorageClientInterface::DocumentStatisticsType p2;
			std::string p3;
			p1 = serializedMsg.unpackIndex();
			p2 = serializedMsg.unpackDocumentStatisticsType();
			p3 = serializedMsg.unpackString();
			try {
				p0 = obj->documentStatistics(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeException_RuntimeError);
			msg.packString( "the method 'checkStorage' is not implemented for RPC");
			return msg.content();
		}
		case StorageClientConst::Method_createDump:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
		}
	}
	break;
	}
	case ClassId_StorageDocumentUpdate:
	{
	StorageDocumentUpdateInterface* obj = getObject<StorageDocumentUpdateInterface>( classId, objId);
	switch( (StorageDocumentUpdateConst::MethodId)methodId)
	{
		case StorageDocumentUpdateConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_setMetaData:
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
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_setAttribute:
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
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_clearAttribute:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->clearAttribute(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case StorageDocumentUpdateConst::Method_setUserAccessRight:
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
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_clearUserAccessRight:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			try {
				obj->clearUserAccessRight(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case StorageDocumentUpdateConst::Method_clearUserAccessRights:
		{
			RpcSerializer msg;
			try {
				obj->clearUserAccessRights();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case StorageDocumentUpdateConst::Method_done:
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getStorage:
		{
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
			deleteObject( classId, objId);
			return std::string();
		}
		case StoragePeerConst::Method_createTransaction:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			return std::string();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageTransactionConst::Method_createDocument:
		{
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
		case StorageTransactionConst::Method_createDocumentUpdate:
		{
			RpcSerializer msg;
			StorageDocumentUpdateInterface* p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createDocumentUpdate(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case StorageTransactionConst::Method_updateMetaData:
		{
			RpcSerializer msg;
			Index p1;
			std::string p2;
			ArithmeticVariant p3;
			p1 = serializedMsg.unpackIndex();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackArithmeticVariant();
			try {
				obj->updateMetaData(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			return std::string();
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
			return std::string();
		}
	}
	break;
	}
	case ClassId_SummarizerFunctionContext:
	{
	SummarizerFunctionContextInterface* obj = getObject<SummarizerFunctionContextInterface>( classId, objId);
	switch( (SummarizerFunctionContextConst::MethodId)methodId)
	{
		case SummarizerFunctionContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionContextConst::Method_addSummarizationFeature:
		{
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
		case SummarizerFunctionContextConst::Method_getSummary:
		{
			RpcSerializer msg;
			std::vector<SummarizerFunctionContextInterface::SummaryElement> p0;
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
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_addStringParameter:
		{
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
		case SummarizerFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			SummarizerFunctionContextInterface* p0;
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
				p0 = obj->createFunctionContext(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionConst::Method_createInstance:
		{
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
			deleteObject( classId, objId);
			return std::string();
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
			return std::string();
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
		}
		case TextProcessorConst::Method_getTokenizer:
		{
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
		case TextProcessorConst::Method_getAggregator:
		{
			RpcSerializer msg;
			const AggregatorFunctionInterface* p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->getAggregator(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case TextProcessorConst::Method_detectDocumentClass:
		{
			RpcSerializer msg;
			bool p0;
			DocumentClass p1;
			const char* p2;
			std::size_t p3;
			serializedMsg.unpackBuffer( p2, p3);
			try {
				p0 = obj->detectDocumentClass(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			msg.packDocumentClass( p1);
			msg.packCrc32();
			return msg.content();
		}
		case TextProcessorConst::Method_defineDocumentClassDetector:
		{
			RpcSerializer msg;
			const DocumentClassDetectorInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_DocumentClassDetector) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p1 = getConstObject<DocumentClassDetectorInterface>( classId_1, objId_1);
			try {
				obj->defineDocumentClassDetector(p1);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case TextProcessorConst::Method_defineTokenizer:
		{
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
		case TextProcessorConst::Method_defineAggregator:
		{
			RpcSerializer msg;
			std::string p1;
			const AggregatorFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_AggregatorFunction) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getConstObject<AggregatorFunctionInterface>( classId_2, objId_2);
			try {
				obj->defineAggregator(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
	case ClassId_TokenizerFunctionContext:
	{
	TokenizerFunctionContextInterface* obj = getObject<TokenizerFunctionContextInterface>( classId, objId);
	switch( (TokenizerFunctionContextConst::MethodId)methodId)
	{
		case TokenizerFunctionContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionContextConst::Method_tokenize:
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
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionInstanceConst::Method_concatBeforeTokenize:
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
		}
		case TokenizerFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			TokenizerFunctionContextInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			try {
				p0 = obj->createFunctionContext();
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionConst::Method_createInstance:
		{
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
	case ClassId_WeightingFunctionContext:
	{
	WeightingFunctionContextInterface* obj = getObject<WeightingFunctionContextInterface>( classId, objId);
	switch( (WeightingFunctionContextConst::MethodId)methodId)
	{
		case WeightingFunctionContextConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionContextConst::Method_addWeightingFeature:
		{
			RpcSerializer msg;
			std::string p1;
			PostingIteratorInterface* p2;
			float p3;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw std::runtime_error("error in RPC serialzed message: output parameter object type mismatch");
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			p3 = serializedMsg.unpackFloat();
			try {
				obj->addWeightingFeature(p1,p2,p3);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
		case WeightingFunctionContextConst::Method_call:
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
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_addStringParameter:
		{
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
		case WeightingFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			WeightingFunctionContextInterface* p0;
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
				p0 = obj->createFunctionContext(p1,p2);
				msg.packByte( MsgTypeAnswer);
			} catch (const std::runtime_error& err) {
				msg.packByte( MsgTypeException_RuntimeError);
				msg.packString( err.what());
				return msg.content();
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
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionConst::Method_createInstance:
		{
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
