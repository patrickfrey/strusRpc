/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Proxy client interface to the objects and functions callable via RPC.
/// \file rpcClientInterface.hpp
#ifndef _STRUS_RPC_CLIENT_INTERFACE_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_INTERFACE_HPP_INCLUDED
#include <string>

/// \brief strus toplevel namespace
namespace strus
{

/// \brief Forward declaration
class AnalyzerObjectBuilderInterface;
/// \brief Forward declaration
class StorageObjectBuilderInterface;


/// \brief Interface providing a mechanism to create and address objects residing on server side
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

	/// \brief Explicit close of the connection
	virtual void close()=0;

	/// \brief Get configuration string
	virtual std::string config() const=0;
};

}//namespace
#endif

