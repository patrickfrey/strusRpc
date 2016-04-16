/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Exported functions of the strus rpc messaging library based on sockets
/// \file rpc_client_socket.hpp
#ifndef _STRUS_LIB_RPC_CLIENT_SOCKET_HPP_INCLUDED
#define _STRUS_LIB_RPC_CLIENT_SOCKET_HPP_INCLUDED

/// \brief strus toplevel namespace
namespace strus {

/// \brief Forward declaration
class RpcClientMessagingInterface;
/// \brief Forward declaration
class ErrorBufferInterface;

/// \brief Create a messaging interface for the strus RPC Client based on sockets
/// \param[in] config configuration string for connecting to the server
/// \param[in] errorhnd buffer for reporting errors
RpcClientMessagingInterface*
	createRpcClientMessaging(
		const char* config,
		ErrorBufferInterface* errorhnd);

}//namespace
#endif

