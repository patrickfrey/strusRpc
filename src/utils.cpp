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
#include "private/utils.hpp"
#include <boost/lexical_cast.hpp>

using namespace strus;
using namespace strus::utils;

class Crc32Table
{
public:
	Crc32Table()
	{
		for (unsigned int ii = 0; ii <= 0xFF; ii++)
		{
			enum {Polynomial=0xEDB88320U};
			uint32_t crc = ii;
			for (unsigned int jj = 0; jj < 8; jj++)
			{
				crc = (crc >> 1) ^ (-int(crc & 1) & Polynomial);
			}
			m_ar[ ii] = crc;
		}
	}
	inline uint32_t operator[]( unsigned char idx) const
	{
		return m_ar[ idx];
	}

private:
	uint32_t m_ar[ 0x100];
};

///\note CRC32 Standard implementation from blog post http://create.stephan-brumme.com/crc32/#sarwate, Thanks
static uint32_t crc32_standardImplementation_1byte( const void* data, size_t length, uint32_t previousCrc32 = 0)
{
	static const Crc32Table crc32Lookup;
	uint32_t crc = ~previousCrc32;
	unsigned char* current = (unsigned char*) data;
	while (length--)
	{
		crc = (crc >> 8) ^ crc32Lookup[(crc & 0xFF) ^ *current++];
	}
	return ~crc;
}

uint32_t Crc32::calc( const char* blk, std::size_t blksize)
{
	return crc32_standardImplementation_1byte( blk, blksize);
}

std::string utils::tostring( int val)
{
	try
	{
		return boost::lexical_cast<std::string>( val);
	}
	catch (...)
	{
		throw std::runtime_error( "failed to convert number to string");
	}
}

unsigned int utils::touint( const std::string& val)
{
	try
	{
		return boost::lexical_cast<unsigned int>( val);
	}
	catch (...)
	{
		throw std::runtime_error( "failed to convert string to number");
	}
}

