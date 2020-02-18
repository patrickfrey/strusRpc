/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_CONST_CONSTRUCTOR_HPP_INCLUDED
#define _STRUS_RPC_CONST_CONSTRUCTOR_HPP_INCLUDED
#include "strus/base/shared_ptr.hpp"
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>

namespace strus {

class ConstObject
{
public:
	virtual ~ConstObject(){}
};

typedef strus::shared_ptr<ConstObject> ConstObjectRef;

class ConstString
	:public ConstObject
{
public:
	virtual ~ConstString(){}
	ConstString( const char* ptr_, std::size_t size_)
		:m_val(ptr_,size_){}
	ConstString( const char* ptr_)
		:m_val(ptr_){}
	const char* ptr() const {return m_val.c_str();}

private:
	std::string m_val;
};

class ConstMem
	:public ConstObject
{
public:
	virtual ~ConstMem(){}
	ConstMem( const void* ptr_, std::size_t size_)
		:m_val((const char*)ptr_,size_){}
	const void* ptr() const {return (const void*)m_val.c_str();}

private:
	std::string m_val;
};

template <typename ELEMTYPE>
class ConstArray
	:public ConstObject
{
public:
	virtual ~ConstArray(){}
	ConstArray( ELEMTYPE const* val_, std::size_t size_)
		:m_val( size_)
	{
		std::size_t ii = 0;
		for (;ii<size_; ++ii) m_val.push_back( val_[ii]);
	}
	ConstArray( const std::vector<ELEMTYPE>& val_)
		:m_val(val_){}
	const std::vector<ELEMTYPE>& ref() const	{return m_val;}
	std::vector<ELEMTYPE>& ref()			{return m_val;}
	const ELEMTYPE* data() const			{return m_val.data();}

private:
	std::vector<ELEMTYPE> m_val;
};



class ConstConstructor
{
public:
	ConstConstructor(){}
	~ConstConstructor()
	{}

	void reset()
	{
		m_ar.clear();
	}

	const char* getCharp( const char* ptr)
	{
		m_ar.reserve( m_ar.size()+1);
		ConstString* obj = new ConstString( ptr);
		m_ar.push_back( obj);
		return obj->ptr();
	}
	const char* getCharpLongLiving( const char* ptr)
	{
		m_longliving_ar.reserve( m_longliving_ar.size()+1);
		ConstString* obj = new ConstString( ptr);
		m_longliving_ar.push_back( obj);
		return obj->ptr();
	}

	typedef ConstArray<char const*> ConstCharpArray;

	const char** getCharpp( char const* const* ptr)
	{
		char const* const* pp = ptr;
		while (*pp)++pp;

		m_ar.reserve( m_ar.size()+1);
		ConstCharpArray* obj = new ConstCharpArray( ptr, pp-ptr+1);
		m_ar.push_back( obj);
		return const_cast<const char**>( obj->data());
	}
	const char** getCharppLongLiving( char const* const* ptr)
	{
		char const* const* pp = ptr;
		while (*pp)++pp;

		m_longliving_ar.reserve( m_longliving_ar.size()+1);
		ConstCharpArray* obj = new ConstCharpArray( ptr, pp-ptr+1);
		m_longliving_ar.push_back( obj);
		return const_cast<const char**>( obj->data());
	}

	const void* get( const void* ptr, std::size_t size)
	{
		m_ar.reserve( m_ar.size()+1);
		ConstMem* obj = new ConstMem( ptr, size);
		m_ar.push_back( obj);
		return obj->ptr();
	}
	const void* getLongLiving( const void* ptr, std::size_t size)
	{
		m_longliving_ar.reserve( m_longliving_ar.size()+1);
		ConstMem* obj = new ConstMem( ptr, size);
		m_longliving_ar.push_back( obj);
		return obj->ptr();
	}

	template <typename ELEMTYPE>
	const std::vector<ELEMTYPE>& getArrayRef( const std::vector<ELEMTYPE>& val)
	{
		m_ar.reserve( m_ar.size()+1);
		ConstArray<ELEMTYPE>* obj = new ConstArray<ELEMTYPE>( val);
		m_ar.push_back( obj);
		return obj->ref();
	}

private:
	std::vector<ConstObjectRef> m_ar;
	std::vector<ConstObjectRef> m_longliving_ar;
};

}//namespace
#endif
