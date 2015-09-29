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
/// \brief Exported functions of the strus rpc server library
/// \file rpc_server.hpp
#ifndef _STRUS_LIB_RPC_SERVER_HPP_INCLUDED
#define _STRUS_LIB_RPC_SERVER_HPP_INCLUDED

/// \brief strus toplevel namespace
namespace strus {

/// \brief Forward declaration
class StorageObjectBuilderInterface;
/// \brief Forward declaration
class AnalyzerObjectBuilderInterface;
/// \brief Forward declaration
class StorageClientInterface;
/// \brief Forward declaration
class RpcRequestHandlerInterface;
/// \brief Forward declaration
class ErrorBufferInterface;

/// \brief Creates an RPC request handler object to be used by a server implementation
/// \param[in] storageBuilder_ storage builder (singleton, ownership hold by caller)
/// \param[in] analyzerBuilder_ analyzer builder reference (singleton, ownership hold by caller)
/// \param[in] storageClient_ storage client reference for the storage instance hosted by the server (singleton, ownership hold by caller)
/// \param[in] errorhnd_ buffer for reporting errors
RpcRequestHandlerInterface*
	createRpcRequestHandler(
		StorageObjectBuilderInterface* storageBuilder_,
		AnalyzerObjectBuilderInterface* analyzerBuilder_,
		StorageClientInterface* storageClient_,
		ErrorBufferInterface* errorhnd_);

}//namespace
#endif

