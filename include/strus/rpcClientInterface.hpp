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
#ifndef _STRUS_RPC_CLIENT_INTERFACE_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_INTERFACE_HPP_INCLUDED

namespace strus
{

/// \brief Forward declaration
class AnalyzerObjectBuilderInterface;
/// \brief Forward declaration
class StorageObjectBuilderInterface;


/// \brief Interface providing a mechanism to create complex objects
class RpcClientInterface
{
public:
	/// \brief Destructor
	virtual ~RpcClientInterface(){}

	/// \brief Creates an object builder for using the strus storage and query evaluation to be accessed via RPC calls
	/// \return the storage object builder(with ownership returned)
	virtual StorageObjectBuilderInterface* createStorageObjectBuilder() const=0;

	/// \brief Creates an object builder for using the strus analyzer to be accessed via RPC calls
	/// \return the analyzer object builder(with ownership returned)
	virtual AnalyzerObjectBuilderInterface* createAnalyzerObjectBuilder() const=0;
};

}//namespace
#endif

