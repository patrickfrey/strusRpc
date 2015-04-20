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
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "objects_gen.hpp"
#include <string>
#include <map>

namespace strus
{

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
			AnalyzerObjectBuilderInterface* analyzerBuilder_);
	virtual ~RpcRequestHandler();

	virtual std::string handleRequest( const char* msg, std::size_t msgsize);

public:
	template <class Interface>
	void defineObject( unsigned char classId_, unsigned int objId_, Interface* obj_)
	{
		ObjKey objkey( classId_, objId_);
		Object obj( obj_, &RpcObjDeleter<Interface>::call);
		ObjMap::iterator oi = m_objmap.find( objkey);
		if (oi != m_objmap.end() && oi->second.deleter)
		{
			oi->second.deleter( oi->second.ptr);
			oi->second = obj;
		}
		else
		{
			m_objmap[ objkey] = obj;
		}
	}

	template <class Interface>
	unsigned int createObject( unsigned char classId_, Interface* obj_)
	{
		defineObject( classId_, ++m_objIdCnt, obj_);
		return m_objIdCnt;
	}

	template <class Interface>
	Interface* getObject( unsigned char classId_, unsigned int objId_) const
	{
		ObjKey objkey( classId_, objId_);
		ObjMap::const_iterator oi = m_objmap.find( objkey);
		if (oi != m_objmap.end())
		{
			return (Interface*)oi->second.ptr;
		}
		else
		{
			throw std::runtime_error( "accessing non existing object (invalid reference)");
		}
	}

	void deleteObject( unsigned char classId_, unsigned int objId_)
	{
		ObjKey objkey( classId_, objId_);
		ObjMap::iterator oi = m_objmap.find( objkey);
		if (oi != m_objmap.end() && oi->second.deleter)
		{
			oi->second.deleter( oi->second.ptr);
		}
		m_objmap.erase( objkey);
	}

	void releaseObject( unsigned char classId_, unsigned int objId_)
	{
		ObjKey objkey( classId_, objId_);
		m_objmap.erase( objkey);
	}

	void clear()
	{
		ObjMap::iterator oi = m_objmap.begin(), oe = m_objmap.end();
		for (; oi != oe; ++oi)
		{
			if (oi->second.deleter)
			{
				oi->second.deleter( oi->second.ptr);
			}
		}
	}

private:
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

	typedef void (*ObjDeleter)( void* objptr);

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
	int unsigned m_objIdCnt;
};
}
#endif

