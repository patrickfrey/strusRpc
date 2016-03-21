/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Interface for the client to issue RPC requests
/// \file rpcClientMessagingInterface.hpp
#ifndef _STRUS_RPC_CLIENT_MESSAGING_INTERFACE_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_MESSAGING_INTERFACE_HPP_INCLUDED
#include <string>

/// \brief strus toplevel namespace
namespace strus
{

/// \brief Interface providing a mechanism for the client to send and receive messages
class RpcClientMessagingInterface
{
public:
	/// \brief Destructor
	virtual ~RpcClientMessagingInterface(){}

	/// \brief Send a message (request) and wait for reply
	/// \param[in] content the content of the message to send
	/// \return the answer of the request
	virtual std::string sendRequest( const std::string& content)=0;

	/// \brief Send a message and do not wait for reply
	/// \param[in] content the content of the message to send
	virtual void sendMessage( const std::string& content)=0;

	/// \brief Get result of previous sendMessage(const std::string&) calls
	virtual std::string synchronize()=0;

	/// \brief Explicit close of the connection
	virtual void close()=0;
};

}//namespace
#endif

