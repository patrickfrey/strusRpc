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
#ifndef _STRUS_RPC_REQUEST_HANDLER_IMPLEMENTATION_HPP_INCLUDED
#define _STRUS_RPC_REQUEST_HANDLER_IMPLEMENTATION_HPP_INCLUDED
#include "strus/rpcRequestHandlerInterface.hpp"
#include "objects_gen.hpp"
#include <string>
#include <map>

namespace strus
{

/// \brief Forward declaration
class AnalyzerObjectBuilderInterface;
/// \brief Forward declaration
class StorageObjectBuilderInterface;
/// \brief Forward declaration
class StorageClientInterface;

template <class Interface>
class RpcObjDeleter
{
public:
	static void call( void* objptr)
	{
		delete reinterpret_cast<Interface*>(objptr);
	}
};

class RpcRequestHandler
	:public RpcRequestHandlerInterface
{
public:
	RpcRequestHandler(
			StorageObjectBuilderInterface* storageBuilder_,
			AnalyzerObjectBuilderInterface* analyzerBuilder_,
			StorageClientInterface* storageClient_);
	virtual ~RpcRequestHandler();

	virtual std::string handleRequest( const char* msg, std::size_t msgsize);

public:
	template <class Interface>
	void defineObject( unsigned char classId_, unsigned int objId_, Interface* obj_)
	{
		defineObjectPtr( classId_, objId_, obj_, &RpcObjDeleter<Interface>::call);
	}

	template <class Interface>
	Interface* getObject( unsigned char classId_, unsigned int objId_) const
	{
		return (Interface*)getObjectPtr( classId_, objId_);
	}

	void deleteObject( unsigned char classId_, unsigned int objId_);
	void releaseObject( unsigned char classId_, unsigned int objId_);
	void clear();

private:
	typedef void (*ObjDeleter)( void* objptr);

	void defineObjectPtr( unsigned char classId_, unsigned int objId_, void* obj_, ObjDeleter deleter_);
	void* getObjectPtr( unsigned char classId_, unsigned int objId_) const;

	struct ObjKey
	{
		ObjKey( unsigned char classId_, unsigned int objId_)
			:classId(classId_),objId(objId_){}
		ObjKey( const ObjKey& o)
			:classId(o.classId),objId(o.objId){}
		ObjKey()
			:classId(0),objId(0){}

		bool operator<( const ObjKey& o) const
		{
			if (classId != classId) return (classId < classId);
			if (objId != objId) return (objId < objId);
			return false;
		}

		unsigned char classId;
		unsigned int objId;
	};

	struct Object
	{
		void* ptr;
		ObjDeleter deleter;

		Object( void* ptr_, ObjDeleter deleter_)
			:ptr(ptr_),deleter(deleter_){}
		Object( const Object& o)
			:ptr(o.ptr),deleter(o.deleter){}
		Object()
			:ptr(0),deleter(0){}
	};

	typedef std::map<ObjKey,Object> ObjMap;
	ObjMap m_objmap;
};
}
#endif

