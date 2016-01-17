/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2015 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
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

