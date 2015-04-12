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
	ConstConstructor();
	ConstConstructor( const ConstConstructor& o);

	void reset() const
	{
		m_ar.clear();
	}

	const void* get( const void* ptr, std::size_t size) const
	{
		Value val( ptr, size);
		const void* rt = val.value;
		m_ar.push_back( val);
		return rt;
	}

private:
	struct Value
	{
		void* value;
		std::size_t size;

		~Value()
		{
			if (value) std::free( value);
		}

		Value()
			:value(0),size(0){}
		Value( const Value& o)
			:value(o.value),size(o.size){}
		Value( const void* value_, std::size_t size_)
			:value(0),size(size_)
		{
			value = std::malloc(size_);
			if (!value) throw std::bad_alloc();
			std::memcpy( value, value_, size);
		}
	};

	mutable std::vector<Value> m_ar;
};

}//namespace
#endif
