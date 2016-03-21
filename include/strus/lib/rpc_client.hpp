/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Exported functions of the strus rpc client library
/// \file rpc_client.hpp
#ifndef _STRUS_LIB_RPC_CLIENT_HPP_INCLUDED
#define _STRUS_LIB_RPC_CLIENT_HPP_INCLUDED

/// \brief strus toplevel namespace
namespace strus {

/// \brief Forward declaration
class RpcClientInterface;
/// \brief Forward declaration
class RpcClientMessagingInterface;
/// \brief Forward declaration
class ErrorBufferInterface;

/// \brief Creates an RPC Client connection to the server
/// \param[in] connector interface (passed with ownership) to use for sending and receiving messages to and from the server
/// \param[in] errorhnd buffer for reporting errors
RpcClientInterface*
	createRpcClient(
		RpcClientMessagingInterface* connector,
		ErrorBufferInterface* errorhnd);

}//namespace
#endif

