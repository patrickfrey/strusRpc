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
			std::cerr << "called destructor of AggregatorFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case AggregatorFunctionInstanceConst::Method_evaluate:
		{
			std::cerr << "called method AggregatorFunctionInstanceImpl::evaluate [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of AggregatorFunctionImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case AggregatorFunctionConst::Method_createInstance:
		{
			std::cerr << "called method AggregatorFunctionImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AnalyzerObjectBuilderImpl::createSegmenter [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AnalyzerObjectBuilderImpl::createDocumentAnalyzer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AnalyzerObjectBuilderImpl::createQueryAnalyzer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AttributeReaderImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AttributeReaderImpl::getValue [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method AttributeReaderImpl::getAttributeNames [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of DatabaseClientImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseClientConst::Method_close:
		{
			std::cerr << "called method DatabaseClientImpl::close [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			obj->close();
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
		case DatabaseClientConst::Method_createTransaction:
		{
			std::cerr << "called method DatabaseClientImpl::createTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseClientImpl::createCursor [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseClientImpl::createBackupCursor [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseClientImpl::writeImm [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseClientImpl::removeImm [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseClientImpl::readValue [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::seekFirst [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::seekLast [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::seekNext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::seekPrev [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::key [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseCursorImpl::value [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of DatabaseImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DatabaseConst::Method_exists:
		{
			std::cerr << "called method DatabaseImpl::exists [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::createClient [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::createDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::restoreDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::destroyDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::getConfigDescription [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseImpl::getConfigParameters [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseTransactionImpl::write [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseTransactionImpl::remove [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseTransactionImpl::removeSubTree [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseTransactionImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DatabaseTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
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
			p0 = obj->allocDocnoRange(p1);
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
		case DocnoRangeAllocatorConst::Method_deallocDocnoRange:
		{
			std::cerr << "called method DocnoRangeAllocatorImpl::deallocDocnoRange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			Index p1;
			Index p2;
			p1 = serializedMsg.unpackIndex();
			p2 = serializedMsg.unpackIndex();
			p0 = obj->deallocDocnoRange(p1,p2);
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
			std::cerr << "called destructor of DocumentAnalyzerContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentAnalyzerContextConst::Method_putInput:
		{
			std::cerr << "called method DocumentAnalyzerContextImpl::putInput [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DocumentAnalyzerContextImpl::analyzeNext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DocumentAnalyzerImpl::defineAggregatedMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DocumentAnalyzerImpl::defineSubDocument [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DocumentAnalyzerImpl::analyze [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method DocumentAnalyzerImpl::createContext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of DocumentClassDetectorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case DocumentClassDetectorConst::Method_detect:
		{
			std::cerr << "called method DocumentClassDetectorImpl::detect [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method ForwardIteratorImpl::skipPos [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method ForwardIteratorImpl::fetch [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::elementHandle [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::nofElements [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::skipDoc [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::getValue [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::getType [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method MetaDataReaderImpl::getName [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of NormalizerFunctionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionContextConst::Method_normalize:
		{
			std::cerr << "called method NormalizerFunctionContextImpl::normalize [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of NormalizerFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case NormalizerFunctionInstanceConst::Method_createFunctionContext:
		{
			std::cerr << "called method NormalizerFunctionInstanceImpl::createFunctionContext [" << serializedMsg.size() << " bytes]" << std::endl;
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
	}
	break;
	}
	case ClassId_PeerMessageBuilder:
	{
	PeerMessageBuilderInterface* obj = getObject<PeerMessageBuilderInterface>( classId, objId);
	switch( (PeerMessageBuilderConst::MethodId)methodId)
	{
		case PeerMessageBuilderConst::Method_Destructor:
		{
			std::cerr << "called destructor of PeerMessageBuilderImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PeerMessageBuilderConst::Method_setNofDocumentsInsertedChange:
		{
			std::cerr << "called method PeerMessageBuilderImpl::setNofDocumentsInsertedChange [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case PeerMessageBuilderConst::Method_addDfChange:
		{
			std::cerr << "called method PeerMessageBuilderImpl::addDfChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			const char* p2;
			int p3;
			bool p4;
			p1 = serializedMsg.unpackConstCharp();
			p2 = serializedMsg.unpackConstCharp();
			p3 = serializedMsg.unpackInt();
			p4 = serializedMsg.unpackBool();
			obj->addDfChange(p1,p2,p3,p4);
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
		case PeerMessageBuilderConst::Method_start:
		{
			std::cerr << "called method PeerMessageBuilderImpl::start [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case PeerMessageBuilderConst::Method_rollback:
		{
			std::cerr << "called method PeerMessageBuilderImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case PeerMessageBuilderConst::Method_fetchMessage:
		{
			std::cerr << "called method PeerMessageBuilderImpl::fetchMessage [" << serializedMsg.size() << " bytes]" << std::endl;
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
	case ClassId_PeerMessageProcessor:
	{
	PeerMessageProcessorInterface* obj = getObject<PeerMessageProcessorInterface>( classId, objId);
	switch( (PeerMessageProcessorConst::MethodId)methodId)
	{
		case PeerMessageProcessorConst::Method_Destructor:
		{
			std::cerr << "called destructor of PeerMessageProcessorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PeerMessageProcessorConst::Method_createViewer:
		{
			std::cerr << "called method PeerMessageProcessorImpl::createViewer [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			PeerMessageViewerInterface* p0;
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
		case PeerMessageProcessorConst::Method_createBuilder:
		{
			std::cerr << "called method PeerMessageProcessorImpl::createBuilder [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			PeerMessageBuilderInterface* p0;
			PeerMessageProcessorInterface::BuilderOptions p1;
			p1 = serializedMsg.unpackPeerMessageProcessorBuilderOptions();
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
	case ClassId_PeerMessageViewer:
	{
	PeerMessageViewerInterface* obj = getObject<PeerMessageViewerInterface>( classId, objId);
	switch( (PeerMessageViewerConst::MethodId)methodId)
	{
		case PeerMessageViewerConst::Method_Destructor:
		{
			std::cerr << "called destructor of PeerMessageViewerImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PeerMessageViewerConst::Method_nofDocumentsInsertedChange:
		{
			std::cerr << "called method PeerMessageViewerImpl::nofDocumentsInsertedChange [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case PeerMessageViewerConst::Method_nextDfChange:
		{
			std::cerr << "called method PeerMessageViewerImpl::nextDfChange [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			PeerMessageViewerInterface::DocumentFrequencyChange p1;
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
			msg.packPeerMessageViewerDocumentFrequencyChange( p1);
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
		case PostingIteratorConst::Method_skipPos:
		{
			std::cerr << "called method PostingIteratorImpl::skipPos [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method PostingIteratorImpl::featureid [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case PostingIteratorConst::Method_subExpressions:
		{
			std::cerr << "called method PostingIteratorImpl::subExpressions [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeError);
			msg.packString( "the method 'subExpressions' is not implemented for RPC");
			return msg.content();
		}
		case PostingIteratorConst::Method_documentFrequency:
		{
			std::cerr << "called method PostingIteratorImpl::documentFrequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			p0 = obj->documentFrequency();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packGlobalCounter( p0);
			msg.packCrc32();
			return msg.content();
		}
		case PostingIteratorConst::Method_frequency:
		{
			std::cerr << "called method PostingIteratorImpl::frequency [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method PostingIteratorImpl::docno [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method PostingIteratorImpl::posno [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of PostingJoinOperatorImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case PostingJoinOperatorConst::Method_createResultIterator:
		{
			std::cerr << "called method PostingJoinOperatorImpl::createResultIterator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeError);
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
			std::cerr << "called method QueryAnalyzerImpl::analyzePhrase [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryAnalyzerImpl::analyzePhraseBulk [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::addSelectionFeature [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::addRestrictionFeature [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::addExclusionFeature [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::addSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::addWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryEvalImpl::createQuery [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::pushExpression [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const PostingJoinOperatorInterface* p1;
			std::size_t p2;
			int p3;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_PostingJoinOperator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<PostingJoinOperatorInterface>( classId_1, objId_1);
			p2 = serializedMsg.unpackSize();
			p3 = serializedMsg.unpackInt();
			obj->pushExpression(p1,p2,p3);
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
		case QueryConst::Method_pushDuplicate:
		{
			std::cerr << "called method QueryImpl::pushDuplicate [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			obj->pushDuplicate();
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
			std::cerr << "called method QueryImpl::attachVariable [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::defineFeature [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::addDocumentEvaluationSet [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::setMaxNofRanks [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::setMinRank [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::addUserName [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryImpl::evaluate [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryProcessorImpl::getPostingJoinOperator [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryProcessorImpl::defineWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryProcessorImpl::getWeightingFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryProcessorImpl::defineSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method QueryProcessorImpl::getSummarizerFunction [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of SegmenterContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterContextConst::Method_putInput:
		{
			std::cerr << "called method SegmenterContextImpl::putInput [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SegmenterContextImpl::getNext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of SegmenterInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterInstanceConst::Method_defineSelectorExpression:
		{
			std::cerr << "called method SegmenterInstanceImpl::defineSelectorExpression [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SegmenterInstanceImpl::defineSubSection [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SegmenterInstanceImpl::createContext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of SegmenterImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SegmenterConst::Method_mimeType:
		{
			std::cerr << "called method SegmenterImpl::mimeType [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SegmenterImpl::createInstance [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::alterElement [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::renameElement [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::deleteElement [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::clearElement [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageAlterMetaDataTableImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of StorageClientImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageClientConst::Method_close:
		{
			std::cerr << "called method StorageClientImpl::close [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			obj->close();
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
			std::cerr << "called method StorageClientImpl::createForwardIterator [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageClientImpl::createInvAclIterator [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case StorageClientConst::Method_globalNofDocumentsInserted:
		{
			std::cerr << "called method StorageClientImpl::globalNofDocumentsInserted [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			p0 = obj->globalNofDocumentsInserted();
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
			msg.packGlobalCounter( p0);
			msg.packCrc32();
			return msg.content();
		}
		case StorageClientConst::Method_localNofDocumentsInserted:
		{
			std::cerr << "called method StorageClientImpl::localNofDocumentsInserted [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			Index p0;
			p0 = obj->localNofDocumentsInserted();
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
		case StorageClientConst::Method_globalDocumentFrequency:
		{
			std::cerr << "called method StorageClientImpl::globalDocumentFrequency [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			GlobalCounter p0;
			std::string p1;
			std::string p2;
			p1 = serializedMsg.unpackString();
			p2 = serializedMsg.unpackString();
			p0 = obj->globalDocumentFrequency(p1,p2);
			const char* err = m_errorhnd->fetchError();
			if (err)
			{
				msg.packByte( MsgTypeError);
				msg.packCharp( err);
				return msg.content();
			}
			msg.packByte( MsgTypeAnswer);
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
			p0 = obj->localDocumentFrequency(p1,p2);
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
			std::cerr << "called method StorageClientImpl::maxDocumentNumber [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageClientImpl::documentNumber [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case StorageClientConst::Method_documentStatistics:
		{
			std::cerr << "called method StorageClientImpl::documentStatistics [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageClientImpl::createMetaDataReader [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageClientImpl::createAttributeReader [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case StorageClientConst::Method_createDocnoRangeAllocator:
		{
			std::cerr << "called method StorageClientImpl::createDocnoRangeAllocator [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			DocnoRangeAllocatorInterface* p0;
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createDocnoRangeAllocator();
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
			std::cerr << "called method StorageClientImpl::createTransaction [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case StorageClientConst::Method_definePeerMessageProcessor:
		{
			std::cerr << "called method StorageClientImpl::definePeerMessageProcessor [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeError);
			msg.packString( "the method 'definePeerMessageProcessor' is not implemented for RPC");
			return msg.content();
		}
		case StorageClientConst::Method_startPeerInit:
		{
			std::cerr << "called method StorageClientImpl::startPeerInit [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			obj->startPeerInit();
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
		case StorageClientConst::Method_pushPeerMessage:
		{
			std::cerr << "called method StorageClientImpl::pushPeerMessage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			const char* p1;
			std::size_t p2;
			serializedMsg.unpackBuffer( p1, p2);
			obj->pushPeerMessage(p1,p2);
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
		case StorageClientConst::Method_fetchPeerReply:
		{
			std::cerr << "called method StorageClientImpl::fetchPeerReply [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			p0 = obj->fetchPeerReply(p1,p2);
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
		case StorageClientConst::Method_fetchPeerMessage:
		{
			std::cerr << "called method StorageClientImpl::fetchPeerMessage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			bool p0;
			const char* p1;
			std::size_t p2;
			p0 = obj->fetchPeerMessage(p1,p2);
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
			std::cerr << "called method StorageClientImpl::checkStorage [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			(void)(obj);
			msg.packByte( MsgTypeError);
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
			std::cerr << "called method StorageDocumentImpl::addForwardIndexTerm [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentImpl::setMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentImpl::setAttribute [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentImpl::setUserAccessRight [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentImpl::done [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of StorageDocumentUpdateImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case StorageDocumentUpdateConst::Method_setMetaData:
		{
			std::cerr << "called method StorageDocumentUpdateImpl::setMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::setAttribute [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::clearAttribute [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::setUserAccessRight [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::clearUserAccessRight [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::clearUserAccessRights [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageDocumentUpdateImpl::done [" << serializedMsg.size() << " bytes]" << std::endl;
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
			if (classId_2 != ClassId_DatabaseClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<DatabaseClientInterface>( classId_2, objId_2);
			markObjectToRelease( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createClient(p1,p2);
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
			std::cerr << "called method StorageImpl::createStorage [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageImpl::createAlterMetaDataTable [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageImpl::getConfigDescription [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageImpl::getConfigParameters [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageObjectBuilderImpl::getDatabase [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageObjectBuilderImpl::getQueryProcessor [" << serializedMsg.size() << " bytes]" << std::endl;
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
		case StorageObjectBuilderConst::Method_createStorageClient:
		{
			std::cerr << "called method StorageObjectBuilderImpl::createStorageClient [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageObjectBuilderImpl::createAlterMetaDataTable [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageObjectBuilderImpl::createQueryEval [" << serializedMsg.size() << " bytes]" << std::endl;
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
			p0 = obj->createDocument(p1,p2);
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
			std::cerr << "called method StorageTransactionImpl::createDocumentUpdate [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageTransactionImpl::deleteDocument [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageTransactionImpl::deleteUserAccessRights [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageTransactionImpl::updateMetaData [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageTransactionImpl::commit [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method StorageTransactionImpl::rollback [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of SummarizerFunctionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case SummarizerFunctionContextConst::Method_addSummarizationFeature:
		{
			std::cerr << "called method SummarizerFunctionContextImpl::addSummarizationFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			PostingIteratorInterface* p2;
			std::vector<SummarizationVariable> p3;
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
			obj->addSummarizationFeature(p1,p2,p3);
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
			std::cerr << "called method SummarizerFunctionContextImpl::getSummary [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SummarizerFunctionInstanceImpl::addNumericParameter [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method SummarizerFunctionInstanceImpl::createFunctionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			SummarizerFunctionContextInterface* p0;
			const StorageClientInterface* p1;
			MetaDataReaderInterface* p2;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_MetaDataReader) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<MetaDataReaderInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createFunctionContext(p1,p2);
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
			std::cerr << "called method SummarizerFunctionInstanceImpl::tostring [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::getResourcePath [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::getTokenizer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::getNormalizer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::getAggregator [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::detectDocumentClass [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::defineDocumentClassDetector [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::defineTokenizer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::defineNormalizer [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TextProcessorImpl::defineAggregator [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of TokenizerFunctionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionContextConst::Method_tokenize:
		{
			std::cerr << "called method TokenizerFunctionContextImpl::tokenize [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of TokenizerFunctionInstanceImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case TokenizerFunctionInstanceConst::Method_concatBeforeTokenize:
		{
			std::cerr << "called method TokenizerFunctionInstanceImpl::concatBeforeTokenize [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method TokenizerFunctionInstanceImpl::createFunctionContext [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called destructor of WeightingFunctionContextImpl" << std::endl;
			deleteObject( classId, objId);
			return std::string();
		}
		case WeightingFunctionContextConst::Method_addWeightingFeature:
		{
			std::cerr << "called method WeightingFunctionContextImpl::addWeightingFeature [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			std::string p1;
			PostingIteratorInterface* p2;
			float p3;
			p1 = serializedMsg.unpackString();
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_PostingIterator) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<PostingIteratorInterface>( classId_2, objId_2);
			p3 = serializedMsg.unpackFloat();
			obj->addWeightingFeature(p1,p2,p3);
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
			std::cerr << "called method WeightingFunctionContextImpl::call [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method WeightingFunctionInstanceImpl::addNumericParameter [" << serializedMsg.size() << " bytes]" << std::endl;
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
			std::cerr << "called method WeightingFunctionInstanceImpl::createFunctionContext [" << serializedMsg.size() << " bytes]" << std::endl;
			RpcSerializer msg;
			WeightingFunctionContextInterface* p0;
			const StorageClientInterface* p1;
			MetaDataReaderInterface* p2;
			unsigned char classId_1; unsigned int objId_1;
			serializedMsg.unpackObject( classId_1, objId_1);
			if (classId_1 != ClassId_StorageClient) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p1 = getConstObject<StorageClientInterface>( classId_1, objId_1);
			unsigned char classId_2; unsigned int objId_2;
			serializedMsg.unpackObject( classId_2, objId_2);
			if (classId_2 != ClassId_MetaDataReader) throw strus::runtime_error(_TXT("error in RPC serialzed message: output parameter object type mismatch"));
			p2 = getObject<MetaDataReaderInterface>( classId_2, objId_2);
			unsigned char classId_0; unsigned int objId_0;
			serializedMsg.unpackObject( classId_0, objId_0);
			p0 = obj->createFunctionContext(p1,p2);
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
			std::cerr << "called method WeightingFunctionInstanceImpl::tostring [" << serializedMsg.size() << " bytes]" << std::endl;
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
	}
	throw strus::runtime_error(_TXT("calling undefined request handler"));
}
