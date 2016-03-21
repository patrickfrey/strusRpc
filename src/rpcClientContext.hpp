/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_CLIENT_CONTEXT_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_CONTEXT_HPP_INCLUDED
#include "strus/rpcClientMessagingInterface.hpp"
#include "constConstructor.hpp"
#include <string>

namespace strus {
/// \brief Forward declaration
class ErrorBufferInterface;

class RpcClientContext
{
public:
	/// \brief Destructor
	virtual ~RpcClientContext();

	/// \brief Constructor
	RpcClientContext( RpcClientMessagingInterface* messaging_);
	/// \brief Default constructor
	explicit RpcClientContext();

	/// \brief Get the constructor for constants on the server
	ConstConstructor* constConstructor() const			{return &m_constConstructor;}

	/// \brief Generate an id for a new object (object ids are generated on the client side to avoid unnecessary round trips)
	unsigned int newObjId() const					{return ++m_objIdCnt;}

	/// \brief Send a request to the server that expects and answer
	std::string rpc_sendRequest( const std::string& msg) const;

	/// \brief Send a request to the server without waiting for answer (use rpc_synchronize() later to detect errors)
	void rpc_sendMessage( const std::string& msg) const;

	/// \brief Wait for empty answer from server (throws on error)
	void rpc_synchronize() const;

	/// \brief Explicit close of the connection
	void rpc_close();

private:
	void handleError( const std::string& msgstr) const;

private:
	mutable unsigned int m_objIdCnt;
	mutable RpcClientMessagingInterface* m_messaging;
	mutable ConstConstructor m_constConstructor;
};

}//namespace
#endif


