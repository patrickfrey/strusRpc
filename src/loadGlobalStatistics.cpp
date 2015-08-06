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
#include "loadGlobalStatistics.hpp"
#include "strus/private/protocol.hpp"
#include "strus/storageClientInterface.hpp"
#include "strus/peerStorageTransactionInterface.hpp"
#include "strus/constants.hpp"
#include "private/dll_tags.hpp"
#include "private/utils.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <utility>

using namespace strus;

static bool isSpace( char ch)
{
	return ch > 0 && (unsigned char)ch <= 32;
}

static bool isDigit( char ch)
{
	return ch >= '0' && ch <= '9';
}

static std::string readToken( std::string::const_iterator& si, const std::string::const_iterator& se)
{
	std::string rt;
	for (;*si && !isSpace( *si); ++si)
	{
		rt.push_back( *si);
	}
	for (; *si && isSpace( *si); ++si){}
	return rt;
}

static int readInteger( std::string::const_iterator& si, const std::string::const_iterator& se)
{
	int rt = 0, prev_rt = 0;
	bool sign = false;
	if (*si == '-')
	{
		sign = true;
		++si;
	}
	for (;*si && isDigit( *si); ++si)
	{
		rt = rt * 10 + *si - '0';
		if (prev_rt > rt)
		{
			throw std::runtime_error( "integer value out of range");
		}
		prev_rt = rt;
	}
	for (; isSpace( *si); ++si){}
	return (sign)?-rt:rt;
}

DLL_PUBLIC void strus::loadGlobalStatistics(
		StorageClientInterface& storage,
		std::istream& stream)
{
	std::auto_ptr<PeerStorageTransactionInterface>
		transaction( storage.createPeerStorageTransaction());
	std::size_t linecnt = 1;
	try
	{
		std::string line;
		for (; std::getline( stream, line); ++linecnt)
		{
			std::string::const_iterator li = line.begin(), le = line.end();
			if (li != le)
			{
				std::string tok = readToken( li, le);
				if (tok == Constants::storage_statistics_document_frequency())
				{
					int df = readInteger( li, le);
					std::string termtype = readToken( li, le);
					std::string termvalue = Protocol::decodeString( readToken( li, le));

					transaction->updateDocumentFrequencyChange(
							termtype.c_str(), termvalue.c_str(), df, true);
				}
				else if (tok == Constants::storage_statistics_number_of_documents())
				{
					int nofDocs = readInteger( li, le);
					transaction->updateNofDocumentsInsertedChange( nofDocs);
				}
				else
				{
					throw std::runtime_error( "unexpected token at start of line");
				}
			}
			if (li != le)
			{
				throw std::runtime_error( "unconsumed characters at end of line");
			}
		}
		(void)transaction->commit();
	}
	catch (const std::istream::failure& err)
	{
		if (stream.eof())
		{
			transaction->commit();
			return;
		}
		throw std::runtime_error( std::string( "file read error on line ")
			+ utils::tostring( linecnt)
			+ ": " + err.what());
	}
	catch (const std::runtime_error& err)
	{
		throw std::runtime_error( std::string( "error on line ")
			+ utils::tostring( linecnt)
			+ ": " + err.what());
	}
}

