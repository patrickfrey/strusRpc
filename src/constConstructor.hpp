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
#ifndef _STRUS_RPC_CONST_CONSTRUCTOR_HPP_INCLUDED
#define _STRUS_RPC_CONST_CONSTRUCTOR_HPP_INCLUDED
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stdexcept>

namespace strus {

class ConstConstructor
{
public:
	ConstConstructor(){}

	void reset() const
	{
		std::vector<Value>::const_iterator ai = m_ar.begin(), ae = m_ar.end();
		for (; ai != ae; ++ai)
		{
			std::free( ai->value);
		}
		m_ar.clear();
	}

	const char* getCharp( const char* ptr) const
	{
		return (const char*)get( ptr, std::strlen(ptr)+1);
	}
	const char** getCharpp( const char** ptr) const
	{
		char const** pp = ptr;
		while (*pp)++pp;
		return (const char**)get( ptr, (pp-ptr)*sizeof(*pp));
	}

	const void* get( const void* ptr, std::size_t size) const
	{
		m_ar.push_back( Value::copy( ptr, size));
		return m_ar.back().value;
	}

private:
	struct Value
	{
		void* value;
		std::size_t size;

		~Value(){}

		Value()
			:value(0),size(0){}
		Value( const Value& o)
			:value(o.value),size(o.size){}
		Value( void* value_, std::size_t size_)
			:value(value_),size(size_)
		{}

		static Value copy( const void* ptr_, std::size_t size_)
		{
			void* ptr = std::malloc(size_);
			if (!ptr) throw std::bad_alloc();
			std::memcpy( ptr, ptr_, size_);
			return Value( ptr, size_);
		}
	};

	mutable std::vector<Value> m_ar;
};

}//namespace
#endif
