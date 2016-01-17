/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2015 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public
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
#include "private/internationalization.hpp"
#include "private/dll_tags.hpp"
#include <string>

using namespace strus;
std::string RpcRequestHandler::handleRequest( const char* src, std::size_t srcsize)
{
	RpcDeserializer serializedMsg( src, srcsize);
	if (!serializedMsg.unpackCrc32()) throw strus::runtime_error(_TXT("message CRC32 check failed"));
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
			p0 = obj->evaluate(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createInstance(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case AggregatorFunctionConst::Method_getDescription:
		{
			RpcSerializer msg;
			const char* p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
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
			p0 = obj->getTextProcessor();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createSegmenter(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createDocumentAnalyzer(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case AnalyzerObjectBuilderConst::Method_createQueryAnalyzer:
		{
			RpcSerializer msg;
			QueryAnalyzerInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createQueryAnalyzer();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->elementHandle(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case AttributeReaderConst::Method_skipDoc:
		{
			RpcSerializer msg;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			obj->skipDoc(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case AttributeReaderConst::Method_getValue:
		{
			RpcSerializer msg;
			std::string p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->getValue(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packString( p0);
			msg.packCrc32();
			return msg.content();
		}
		case AttributeReaderConst::Method_getAttributeNames:
		{
			RpcSerializer msg;
			std::vector<std::string> p0;
			p0 = obj->getAttributeNames();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->fetch(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
		case DatabaseClientConst::Method_createTransaction:
		{
			RpcSerializer msg;
			DatabaseTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createTransaction();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createCursor(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseClientConst::Method_createBackupCursor:
		{
			RpcSerializer msg;
			DatabaseBackupCursorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createBackupCursor();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->writeImm(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DatabaseClientConst::Method_removeImm:
		{
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			obj->removeImm(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->readValue(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->seekUpperBound(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->seekFirst(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->seekLast(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekNext:
		{
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			p0 = obj->seekNext();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_seekPrev:
		{
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			p0 = obj->seekPrev();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_key:
		{
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			p0 = obj->key();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSlice( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseCursorConst::Method_value:
		{
			RpcSerializer msg;
			DatabaseCursorInterface::Slice p0;
			p0 = obj->value();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->exists(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createClient(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case DatabaseConst::Method_createDatabase:
		{
			RpcSerializer msg;
			bool p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			p0 = obj->createDatabase(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseConst::Method_restoreDatabase:
		{
			RpcSerializer msg;
			bool p0;
			std::string p1;
			DatabaseBackupCursorInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseBackupCursor) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<DatabaseBackupCursorInterface>( classId_2, objId_2);
			p0 = obj->restoreDatabase(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseConst::Method_destroyDatabase:
		{
			RpcSerializer msg;
			bool p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			p0 = obj->destroyDatabase(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseConst::Method_getConfigDescription:
		{
			RpcSerializer msg;
			const char* p0;
			DatabaseInterface::ConfigType p1;
			p1 = serializedMsg.unpackDatabaseConfigType();
			p0 = obj->getConfigDescription(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getConfigParameters(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createCursor(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->write(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DatabaseTransactionConst::Method_remove:
		{
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			obj->remove(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DatabaseTransactionConst::Method_removeSubTree:
		{
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			obj->removeSubTree(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DatabaseTransactionConst::Method_commit:
		{
			RpcSerializer msg;
			bool p0;
			p0 = obj->commit();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case DatabaseTransactionConst::Method_rollback:
		{
			RpcSerializer msg;
			obj->rollback();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
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
			obj->putInput(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DocumentAnalyzerContextConst::Method_analyzeNext:
		{
			RpcSerializer msg;
			bool p0;
			analyzer::Document p1;
			p0 = obj->analyzeNext(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			obj->addSearchIndexFeature(p1,p2,p3,p4,p5);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			p5 = serializedMsg.unpackFeatureOptions();
			obj->addForwardIndexFeature(p1,p2,p3,p4,p5);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			obj->defineMetaData(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_AggregatorFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<AggregatorFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineAggregatedMetaData(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			obj->defineAttribute(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case DocumentAnalyzerConst::Method_defineSubDocument:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			obj->defineSubDocument(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->analyze(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packAnalyzerDocument( p0);
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
			p0 = obj->createContext(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->detect(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->skipDoc(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case ForwardIteratorConst::Method_skipPos:
		{
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->skipPos(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case ForwardIteratorConst::Method_fetch:
		{
			RpcSerializer msg;
			std::string p0;
			p0 = obj->fetch();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->skipDoc(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->hasElement(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->elementHandle(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_nofElements:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->nofElements();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case MetaDataReaderConst::Method_skipDoc:
		{
			RpcSerializer msg;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			obj->skipDoc(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case MetaDataReaderConst::Method_getValue:
		{
			RpcSerializer msg;
			ArithmeticVariant p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->getValue(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getType(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getName(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->normalize(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createFunctionContext();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_TextProcessor) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getConstObject<TextProcessorInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createInstance(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case NormalizerFunctionConst::Method_getDescription:
		{
			RpcSerializer msg;
			const char* p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
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
			p0 = obj->skipDoc(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_skipDocCandidate:
		{
			RpcSerializer msg;
			Index p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->skipDocCandidate(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->skipPos(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_featureid:
		{
			RpcSerializer msg;
			const char* p0;
			p0 = obj->featureid();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_documentFrequency:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->documentFrequency();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_frequency:
		{
			RpcSerializer msg;
			unsigned int p0;
			p0 = obj->frequency();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packUint( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_docno:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->docno();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_posno:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->posno();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			msg.packByte( MsgTypeError);
			msg.packString( "the method 'createResultIterator' is not implemented for RPC");
			return msg.content();
		}
		case PostingJoinOperatorConst::Method_getDescription:
		{
			RpcSerializer msg;
			PostingJoinOperatorInterface::Description p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packPostingJoinOperatorDescription( p0);
			msg.packCrc32();
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
			if (classId_3 != ClassId_TokenizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getObject<TokenizerFunctionInstanceInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			std::size_t n4 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n4; ++ii) {
				unsigned char classId_; unsigned int objId_;
				serializedMsg.unpackObject( classId_, objId_);
				if (classId_ != ClassId_NormalizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
				NormalizerFunctionInstanceInterface* ee = getObject<NormalizerFunctionInstanceInterface>( classId_, objId_);
				p4.push_back( ee);
				markObjectToRelease( classId_, objId_);
			}
			obj->definePhraseType(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->analyzePhrase(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packAnalyzerTerm( p0[ii]);
			}
			msg.packCrc32();
			return msg.content();
		}
		case QueryAnalyzerConst::Method_analyzePhraseBulk:
		{
			RpcSerializer msg;
			std::vector<analyzer::TermVector> p0;
			std::vector<QueryAnalyzerInterface::Phrase> p1;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				QueryAnalyzerInterface::Phrase ee = serializedMsg.unpackPhrase();
				p1.push_back( ee);
			}
			p0 = obj->analyzePhraseBulk(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSize( p0.size());
			for (std::size_t ii=0; ii < p0.size(); ++ii) {
				msg.packAnalyzerTermVector( p0[ii]);
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
			obj->addTerm(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryEvalConst::Method_addSelectionFeature:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->addSelectionFeature(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryEvalConst::Method_addRestrictionFeature:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->addRestrictionFeature(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryEvalConst::Method_addExclusionFeature:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->addExclusionFeature(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_SummarizerFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<SummarizerFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				QueryEvalInterface::FeatureParameter ee = serializedMsg.unpackFeatureParameter();
				p3.push_back( ee);
			}
			p4 = serializedMsg.unpackString();
			obj->addSummarizerFunction(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_WeightingFunctionInstance) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<WeightingFunctionInstanceInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			std::size_t n3 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n3; ++ii) {
				QueryEvalInterface::FeatureParameter ee = serializedMsg.unpackFeatureParameter();
				p3.push_back( ee);
			}
			p4 = serializedMsg.unpackFloat();
			obj->addWeightingFunction(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryEvalConst::Method_createQuery:
		{
			RpcSerializer msg;
			QueryInterface* p0;
			const StorageClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createQuery(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->pushTerm(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_pushExpression:
		{
			RpcSerializer msg;
			const PostingJoinOperatorInterface* p1;
			std::size_t p2;
			int p3;
			unsigned int p4;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_PostingJoinOperator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<PostingJoinOperatorInterface>( classId_1, objId_1);
			p2 = serializedMsg.unpackSize();
			p3 = serializedMsg.unpackInt();
			p4 = serializedMsg.unpackUint();
			obj->pushExpression(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_attachVariable:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->attachVariable(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_defineFeature:
		{
			RpcSerializer msg;
			std::string p1;
			float p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackFloat();
			obj->defineFeature(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_defineTermStatistics:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			TermStatistics p3;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p3 = serializedMsg.unpackTermStatistics();
			obj->defineTermStatistics(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_defineGlobalStatistics:
		{
			RpcSerializer msg;
			GlobalStatistics p1;
			p1 = serializedMsg.unpackGlobalStatistics();
			obj->defineGlobalStatistics(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->defineMetaDataRestriction(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_addDocumentEvaluationSet:
		{
			RpcSerializer msg;
			std::vector<Index> p1;
			std::size_t n1 = serializedMsg.unpackSize();
			for (std::size_t ii=0; ii < n1; ++ii) {
				Index ee = serializedMsg.unpackIndex();
				p1.push_back( ee);
			}
			obj->addDocumentEvaluationSet(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_setMaxNofRanks:
		{
			RpcSerializer msg;
			std::size_t p1;
			p1 = serializedMsg.unpackSize();
			obj->setMaxNofRanks(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_setMinRank:
		{
			RpcSerializer msg;
			std::size_t p1;
			p1 = serializedMsg.unpackSize();
			obj->setMinRank(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_addUserName:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->addUserName(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case QueryConst::Method_evaluate:
		{
			RpcSerializer msg;
			std::vector<ResultDocument> p0;
			p0 = obj->evaluate();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_PostingJoinOperator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<PostingJoinOperatorInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->definePostingJoinOperator(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getPostingJoinOperator(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_WeightingFunction) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<WeightingFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineWeightingFunction(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getWeightingFunction(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_SummarizerFunction) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<SummarizerFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineSummarizerFunction(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getSummarizerFunction(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case QueryProcessorConst::Method_getFunctionList:
		{
			RpcSerializer msg;
			std::vector<std::string> p0;
			QueryProcessorInterface::FunctionType p1;
			p1 = serializedMsg.unpackQueryProcessorFunctionType();
			p0 = obj->getFunctionList(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->putInput(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getNext(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
	case ClassId_SegmenterInstance:
	{
	SegmenterInstanceInterface* obj = getObject<SegmenterInstanceInterface>( classId, objId);
	switch( (SegmenterInstanceConst::MethodId)methodId)
	{
		case SegmenterInstanceConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterInstanceConst::Method_defineSelectorExpression:
		{
			RpcSerializer msg;
			int p1;
			std::string p2;
			p1 = serializedMsg.unpackInt();
			p2 = serializedMsg.unpackString();
			obj->defineSelectorExpression(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case SegmenterInstanceConst::Method_defineSubSection:
		{
			RpcSerializer msg;
			int p1;
			int p2;
			std::string p3;
			p1 = serializedMsg.unpackInt();
			p2 = serializedMsg.unpackInt();
			p3 = serializedMsg.unpackString();
			obj->defineSubSection(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case SegmenterInstanceConst::Method_createContext:
		{
			RpcSerializer msg;
			SegmenterContextInterface* p0;
			DocumentClass p1;
			p1 = serializedMsg.unpackDocumentClass();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createContext(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
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
			const char* p0;
			p0 = obj->mimeType();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
		case SegmenterConst::Method_createInstance:
		{
			RpcSerializer msg;
			SegmenterInstanceInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createInstance();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StatisticsBuilder:
	{
	StatisticsBuilderInterface* obj = getObject<StatisticsBuilderInterface>( classId, objId);
	switch( (StatisticsBuilderConst::MethodId)methodId)
	{
		case StatisticsBuilderConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case StatisticsBuilderConst::Method_setNofDocumentsInsertedChange:
		{
			RpcSerializer msg;
			int p1;
			p1 = serializedMsg.unpackInt();
			obj->setNofDocumentsInsertedChange(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StatisticsBuilderConst::Method_addDfChange:
		{
			RpcSerializer msg;
			const char* p1;
			const char* p2;
			int p3;
			p1 = serializedMsg.unpackConstCharp();
			p2 = serializedMsg.unpackConstCharp();
			p3 = serializedMsg.unpackInt();
			obj->addDfChange(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StatisticsBuilderConst::Method_start:
		{
			RpcSerializer msg;
			obj->start();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StatisticsBuilderConst::Method_rollback:
		{
			RpcSerializer msg;
			obj->rollback();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StatisticsBuilderConst::Method_fetchMessage:
		{
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			p0 = obj->fetchMessage(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packBuffer( p1, p2);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_StatisticsIterator:
	{
	StatisticsIteratorInterface* obj = getObject<StatisticsIteratorInterface>( classId, objId);
	switch( (StatisticsIteratorConst::MethodId)methodId)
	{
		case StatisticsIteratorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case StatisticsIteratorConst::Method_getNext:
		{
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			p0 = obj->getNext(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packBuffer( p1, p2);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_StatisticsProcessor:
	{
	StatisticsProcessorInterface* obj = getObject<StatisticsProcessorInterface>( classId, objId);
	switch( (StatisticsProcessorConst::MethodId)methodId)
	{
		case StatisticsProcessorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case StatisticsProcessorConst::Method_createViewer:
		{
			RpcSerializer msg;
			StatisticsViewerInterface* p0;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createViewer(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StatisticsProcessorConst::Method_createBuilder:
		{
			RpcSerializer msg;
			StatisticsBuilderInterface* p0;
			StatisticsProcessorInterface::BuilderOptions p1;
			p1 = serializedMsg.unpackStatisticsProcessorBuilderOptions();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createBuilder(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
	}
	break;
	}
	case ClassId_StatisticsViewer:
	{
	StatisticsViewerInterface* obj = getObject<StatisticsViewerInterface>( classId, objId);
	switch( (StatisticsViewerConst::MethodId)methodId)
	{
		case StatisticsViewerConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case StatisticsViewerConst::Method_nofDocumentsInsertedChange:
		{
			RpcSerializer msg;
			int p0;
			p0 = obj->nofDocumentsInsertedChange();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packInt( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StatisticsViewerConst::Method_nextDfChange:
		{
			RpcSerializer msg;
			bool p0;
			StatisticsViewerInterface::DocumentFrequencyChange p1;
			p0 = obj->nextDfChange(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packStatisticsViewerDocumentFrequencyChange( p1);
			msg.packCrc32();
			return msg.content();
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
			obj->addElement(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->alterElement(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_renameElement:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			obj->renameElement(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_deleteElement:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->deleteElement(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_clearElement:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->clearElement(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageAlterMetaDataTableConst::Method_commit:
		{
			RpcSerializer msg;
			bool p0;
			p0 = obj->commit();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageAlterMetaDataTableConst::Method_rollback:
		{
			RpcSerializer msg;
			obj->rollback();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createTermPostingIterator(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createForwardIterator(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createInvAclIterator(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_nofDocumentsInserted:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->nofDocumentsInserted();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_documentFrequency:
		{
			RpcSerializer msg;
			Index p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p0 = obj->documentFrequency(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_maxDocumentNumber:
		{
			RpcSerializer msg;
			Index p0;
			p0 = obj->maxDocumentNumber();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->documentNumber(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packIndex( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_createTermTypeIterator:
		{
			RpcSerializer msg;
			ValueIteratorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createTermTypeIterator();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createTermValueIterator:
		{
			RpcSerializer msg;
			ValueIteratorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createTermValueIterator();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createDocIdIterator:
		{
			RpcSerializer msg;
			ValueIteratorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createDocIdIterator();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createUserNameIterator:
		{
			RpcSerializer msg;
			ValueIteratorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createUserNameIterator();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
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
			p0 = obj->documentStatistics(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createMetaDataReader();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createAttributeReader:
		{
			RpcSerializer msg;
			AttributeReaderInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createAttributeReader();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createTransaction:
		{
			RpcSerializer msg;
			StorageTransactionInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createTransaction();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createInitStatisticsIterator:
		{
			RpcSerializer msg;
			StatisticsIteratorInterface* p0;
			bool p1;
			p1 = serializedMsg.unpackBool();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createInitStatisticsIterator(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_createUpdateStatisticsIterator:
		{
			RpcSerializer msg;
			StatisticsIteratorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createUpdateStatisticsIterator();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_getStatisticsProcessor:
		{
			RpcSerializer msg;
			const StatisticsProcessorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->getStatisticsProcessor();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineConstObject( classId_0, objId_0, p0);
			
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
			p0 = obj->createDocumentChecker(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageClientConst::Method_checkStorage:
		{
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeError);
			msg.packString( "the method 'checkStorage' is not implemented for RPC");
			return msg.content();
		}
		case StorageClientConst::Method_createDump:
		{
			RpcSerializer msg;
			StorageDumpInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createDump();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->addSearchIndexTerm(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->addForwardIndexTerm(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentConst::Method_setMetaData:
		{
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			obj->setMetaData(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentConst::Method_setAttribute:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			obj->setAttribute(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentConst::Method_setUserAccessRight:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->setUserAccessRight(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentConst::Method_done:
		{
			RpcSerializer msg;
			obj->done();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeSynchronize);
			return msg.content();
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
			obj->setMetaData(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_setAttribute:
		{
			RpcSerializer msg;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			obj->setAttribute(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_clearAttribute:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->clearAttribute(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_setUserAccessRight:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->setUserAccessRight(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_clearUserAccessRight:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->clearUserAccessRight(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_clearUserAccessRights:
		{
			RpcSerializer msg;
			obj->clearUserAccessRights();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_done:
		{
			RpcSerializer msg;
			obj->done();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeSynchronize);
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
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageDumpConst::Method_nextChunk:
		{
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			p0 = obj->nextChunk(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			const StatisticsProcessorInterface* p3;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			unsigned char classId_3; unsigned int objId_3;
			serializedMsg.unpackObject( classId_3, objId_3);
			if (classId_3 != ClassId_StatisticsProcessor) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p3 = getConstObject<StatisticsProcessorInterface>( classId_3, objId_3);
			markObjectToRelease( classId_3, objId_3);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createClient(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageConst::Method_createStorage:
		{
			RpcSerializer msg;
			bool p0;
			std::string p1;
			DatabaseClientInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_DatabaseClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			p0 = obj->createStorage(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageConst::Method_createAlterMetaDataTable:
		{
			RpcSerializer msg;
			StorageAlterMetaDataTableInterface* p0;
			DatabaseClientInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_DatabaseClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getObject<DatabaseClientInterface>( classId_1, objId_1);
			markObjectToRelease( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createAlterMetaDataTable(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageConst::Method_getConfigDescription:
		{
			RpcSerializer msg;
			const char* p0;
			StorageInterface::ConfigType p1;
			p1 = serializedMsg.unpackStorageConfigType();
			p0 = obj->getConfigDescription(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getConfigParameters(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getStorage();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getDatabase(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getQueryProcessor:
		{
			RpcSerializer msg;
			const QueryProcessorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->getQueryProcessor();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineConstObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_getStatisticsProcessor:
		{
			RpcSerializer msg;
			const StatisticsProcessorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->getStatisticsProcessor();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createStorageClient(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createAlterMetaDataTable(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageObjectBuilderConst::Method_createQueryEval:
		{
			RpcSerializer msg;
			QueryEvalInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createQueryEval();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
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
			p1 = serializedMsg.unpackString();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createDocument(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createDocumentUpdate(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case StorageTransactionConst::Method_deleteDocument:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->deleteDocument(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageTransactionConst::Method_deleteUserAccessRights:
		{
			RpcSerializer msg;
			std::string p1;
			p1 = serializedMsg.unpackString();
			obj->deleteUserAccessRights(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->updateMetaData(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case StorageTransactionConst::Method_commit:
		{
			RpcSerializer msg;
			bool p0;
			p0 = obj->commit();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageTransactionConst::Method_rollback:
		{
			RpcSerializer msg;
			obj->rollback();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			float p4;
			TermStatistics p5;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
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
			p4 = serializedMsg.unpackFloat();
			p5 = serializedMsg.unpackTermStatistics();
			obj->addSummarizationFeature(p1,p2,p3,p4,p5);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case SummarizerFunctionContextConst::Method_getSummary:
		{
			RpcSerializer msg;
			std::vector<SummarizerFunctionContextInterface::SummaryElement> p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->getSummary(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->addStringParameter(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_addNumericParameter:
		{
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			obj->addNumericParameter(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			SummarizerFunctionContextInterface* p0;
			const StorageClientInterface* p1;
			MetaDataReaderInterface* p2;
			GlobalStatistics p3;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_MetaDataReader) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<MetaDataReaderInterface>( classId_2, objId_2);
			p3 = serializedMsg.unpackGlobalStatistics();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createFunctionContext(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case SummarizerFunctionInstanceConst::Method_tostring:
		{
			RpcSerializer msg;
			std::string p0;
			p0 = obj->tostring();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_1 != ClassId_QueryProcessor) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<QueryProcessorInterface>( classId_1, objId_1);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createInstance(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case SummarizerFunctionConst::Method_getDescription:
		{
			RpcSerializer msg;
			SummarizerFunctionInterface::Description p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packSummarizerFunctionDescription( p0);
			msg.packCrc32();
			return msg.content();
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
			obj->addResourcePath(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case TextProcessorConst::Method_getResourcePath:
		{
			RpcSerializer msg;
			std::string p0;
			std::string p1;
			p1 = serializedMsg.unpackString();
			p0 = obj->getResourcePath(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getTokenizer(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getNormalizer(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->getAggregator(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->detectDocumentClass(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packBool( p0);
			msg.packDocumentClass( p1);
			msg.packCrc32();
			return msg.content();
		}
		case TextProcessorConst::Method_defineDocumentClassDetector:
		{
			RpcSerializer msg;
			DocumentClassDetectorInterface* p1;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_DocumentClassDetector) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getObject<DocumentClassDetectorInterface>( classId_1, objId_1);
			markObjectToRelease( classId_1, objId_1);
			obj->defineDocumentClassDetector(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case TextProcessorConst::Method_defineTokenizer:
		{
			RpcSerializer msg;
			std::string p1;
			TokenizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_TokenizerFunction) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<TokenizerFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineTokenizer(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case TextProcessorConst::Method_defineNormalizer:
		{
			RpcSerializer msg;
			std::string p1;
			NormalizerFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_NormalizerFunction) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<NormalizerFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineNormalizer(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case TextProcessorConst::Method_defineAggregator:
		{
			RpcSerializer msg;
			std::string p1;
			AggregatorFunctionInterface* p2;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_AggregatorFunction) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<AggregatorFunctionInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			obj->defineAggregator(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				unmarkObjectsToRelease();
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			releaseObjectsMarked();
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case TextProcessorConst::Method_getFunctionList:
		{
			RpcSerializer msg;
			std::vector<std::string> p0;
			TextProcessorInterface::FunctionType p1;
			p1 = serializedMsg.unpackTextProcessorFunctionType();
			p0 = obj->getFunctionList(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->tokenize(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->concatBeforeTokenize();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createFunctionContext();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			if (classId_2 != ClassId_TextProcessor) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getConstObject<TextProcessorInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createInstance(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case TokenizerFunctionConst::Method_getDescription:
		{
			RpcSerializer msg;
			const char* p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packCharp( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	case ClassId_ValueIterator:
	{
	ValueIteratorInterface* obj = getObject<ValueIteratorInterface>( classId, objId);
	switch( (ValueIteratorConst::MethodId)methodId)
	{
		case ValueIteratorConst::Method_Destructor:
		{
			deleteObject( classId, objId);
			return std::string();
		}
		case ValueIteratorConst::Method_skip:
		{
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			obj->skip(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case ValueIteratorConst::Method_fetchValues:
		{
			RpcSerializer msg;
			std::vector<std::string> p0;
			std::size_t p1;
			p1 = serializedMsg.unpackSize();
			p0 = obj->fetchValues(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			TermStatistics p4;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			p3 = serializedMsg.unpackFloat();
			p4 = serializedMsg.unpackTermStatistics();
			obj->addWeightingFeature(p1,p2,p3,p4);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case WeightingFunctionContextConst::Method_call:
		{
			RpcSerializer msg;
			float p0;
			Index p1;
			p1 = serializedMsg.unpackIndex();
			p0 = obj->call(p1);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			obj->addStringParameter(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_addNumericParameter:
		{
			RpcSerializer msg;
			std::string p1;
			ArithmeticVariant p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackArithmeticVariant();
			obj->addNumericParameter(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_createFunctionContext:
		{
			RpcSerializer msg;
			WeightingFunctionContextInterface* p0;
			const StorageClientInterface* p1;
			MetaDataReaderInterface* p2;
			GlobalStatistics p3;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_MetaDataReader) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<MetaDataReaderInterface>( classId_2, objId_2);
			p3 = serializedMsg.unpackGlobalStatistics();
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createFunctionContext(p1,p2,p3);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case WeightingFunctionInstanceConst::Method_tostring:
		{
			RpcSerializer msg;
			std::string p0;
			p0 = obj->tostring();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->createInstance();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			defineObject( classId_0, objId_0, p0);
			
			return std::string();
		}
		case WeightingFunctionConst::Method_getDescription:
		{
			RpcSerializer msg;
			WeightingFunctionInterface::Description p0;
			p0 = obj->getDescription();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packWeightingFunctionDescription( p0);
			msg.packCrc32();
			return msg.content();
		}
	}
	break;
	}
	}
	throw strus::runtime_error(_TXT("calling undefined request handler"));
}
