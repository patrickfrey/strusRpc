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
#include "private/dll_tags.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/storageClientInterface.hpp"
#include <string>
#include <map>

using namespace strus;

RpcRequestHandler::RpcRequestHandler(
			StorageObjectBuilderInterface* storageBuilder_,
			AnalyzerObjectBuilderInterface* analyzerBuilder_,
			StorageClientInterface* storage_)
{
	if (storageBuilder_)
	{
		defineObjectPtr( ClassId_StorageObjectBuilder, 0, storageBuilder_, 0/*deleter (object is singleton with ownership at caller)*/);
	}
	if (analyzerBuilder_)
	{
		defineObjectPtr( ClassId_AnalyzerObjectBuilder, 0, analyzerBuilder_, 0/*deleter (object is singleton with ownership at caller)*/);
	}
	if (storage_)
	{
		defineObjectPtr( ClassId_StorageClient, 0, storage_, 0/*deleter (object is singleton with ownership at caller)*/);
	}
}

RpcRequestHandler::~RpcRequestHandler()
{
	clear();
}

void RpcRequestHandler::defineObjectPtr( unsigned char classId_, unsigned int objId_, void* obj_, ObjDeleter deleter_)
{
	ObjKey objkey( classId_, objId_);
	Object obj( obj_, deleter_);
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

void* RpcRequestHandler::getObjectPtr( unsigned char classId_, unsigned int objId_) const
{
	ObjKey objkey( classId_, objId_);
	ObjMap::const_iterator oi = m_objmap.find( objkey);
	if (oi != m_objmap.end())
	{
		return oi->second.ptr;
	}
	else
	{
		throw std::runtime_error( "accessing non existing object (invalid reference)");
	}
}

void RpcRequestHandler::deleteObject( unsigned char classId_, unsigned int objId_)
{
	if (objId_)
	{
		// ... objId_ == 0 is reserved for constant objects that cannot be deleted
		ObjKey objkey( classId_, objId_);
		ObjMap::iterator oi = m_objmap.find( objkey);
		if (oi != m_objmap.end() && oi->second.deleter)
		{
			oi->second.deleter( oi->second.ptr);
		}
		m_objmap.erase( objkey);
	}
}

void RpcRequestHandler::releaseObject( unsigned char classId_, unsigned int objId_)
{
	ObjKey objkey( classId_, objId_);
	m_objmap.erase( objkey);
}

void RpcRequestHandler::clear()
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

