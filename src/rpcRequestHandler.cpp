/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "rpcRequestHandler.hpp"
#include "strus/base/dll_tags.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/storageClientInterface.hpp"
#include "private/internationalization.hpp"
#include <iostream>
#include <string>
#include <map>

using namespace strus;

#undef STRUS_LOWLEVEL_DEBUG

RpcRequestHandler::RpcRequestHandler(
			StorageObjectBuilderInterface* storageBuilder_,
			AnalyzerObjectBuilderInterface* analyzerBuilder_,
			StorageClientInterface* storage_,
			ErrorBufferInterface* errorhnd_)
		:m_errorhnd(errorhnd_)
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
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "define object classid=" << (unsigned int)classId_ << " objid=" << objId_ << " ptr=" << (uintptr_t)obj_ << " deleter " << (uintptr_t)deleter_ << std::endl;
#endif
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

void RpcRequestHandler::defineConstObjectPtr( unsigned char classId_, unsigned int objId_, const void* obj_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "define const object classid=" << (unsigned int)classId_ << " objid=" << objId_ << " ptr=" << (uintptr_t)obj_ << std::endl;
#endif
	defineObjectPtr( classId_, objId_, const_cast<void*>(obj_), 0);
}

void* RpcRequestHandler::getObjectPtr( unsigned char classId_, unsigned int objId_) const
{
	ObjKey objkey( classId_, objId_);
	ObjMap::const_iterator oi = m_objmap.find( objkey);
	if (oi != m_objmap.end())
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "get object classid=" << (unsigned int)classId_ << " objid=" << objId_ << " ptr=" << (uintptr_t)oi->second.ptr << std::endl;
#endif
		if (!oi->second.ptr)
		{
			throw strus::runtime_error( _TXT("accessing object NULL pointer"));
		}
		return oi->second.ptr;
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "object not found classid=" << (unsigned int)classId_ << " objid=" << objId_ << " ptr=" << std::endl;
#endif
		throw strus::runtime_error( _TXT("accessing non existing object (invalid reference)"));
	}
}

const void* RpcRequestHandler::getConstObjectPtr( unsigned char classId_, unsigned int objId_) const
{
	return const_cast<const void*>( getObjectPtr( classId_, objId_));
}

void RpcRequestHandler::deleteObject( unsigned char classId_, unsigned int objId_)
{
	if (objId_)
	{
		// ... objId_ == 0 is reserved for constant objects that cannot be deleted
		ObjKey objkey( classId_, objId_);
		ObjMap::iterator oi = m_objmap.find( objkey);
		if (oi != m_objmap.end())
		{
			if (oi->second.deleter && oi->second.ptr)
			{
#ifdef STRUS_LOWLEVEL_DEBUG
				std::cerr << "delete object classid=" << (unsigned int)classId_ << " objid=" << objId_ << std::endl;
#endif
				oi->second.deleter( oi->second.ptr);
			}
			m_objmap.erase( objkey);
		}
	}
}

void RpcRequestHandler::releaseObject( unsigned char classId_, unsigned int objId_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "release object classid=" << (unsigned int)classId_ << " objid=" << objId_ << std::endl;
#endif
	ObjKey objkey( classId_, objId_);
	m_objmap.erase( objkey);
}

void RpcRequestHandler::releaseObjectsMarked()
{
	std::vector<ObjKey>::const_iterator ri = m_objsMarkedToRelease.begin(), re = m_objsMarkedToRelease.end();
	for (; ri != re; ++ri)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "release object classid=" << (unsigned int)ri->classId << " objid=" << ri->objId << std::endl;
#endif
		m_objmap.erase( *ri);
	}
	m_objsMarkedToRelease.clear();
}

void RpcRequestHandler::clear()
{
	ObjMap::iterator oi = m_objmap.begin(), oe = m_objmap.end();
	for (; oi != oe; ++oi)
	{
		if (oi->second.deleter)
		{
			if (oi->second.ptr)
			{
				oi->second.deleter( oi->second.ptr);
			}
			oi->second.ptr = 0;
			oi->second.deleter = 0;
		}
	}
}

