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
#ifndef _STRUS_RPC_CLIENT_MESSAGING_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_MESSAGING_HPP_INCLUDED
#include "strus/rpcClientMessagingInterface.hpp"

extern "C" {
	struct strus_connection_t;
}

namespace strus
{
/// \brief Forward declaration
class ErrorBufferInterface;

class RpcClientMessaging
	:public RpcClientMessagingInterface
{
public:
	RpcClientMessaging( const char* config, ErrorBufferInterface* errorhnd_);
	virtual ~RpcClientMessaging();

	virtual std::string sendRequest( const std::string& content);
	virtual void sendMessage( const std::string& content);
	virtual std::string synchronize();
	virtual void close();

private:
	static std::string errorstr( const char* msg, struct strus_connection_t* conn);
	void send_req( const char* msg, std::size_t msgsize);
	std::string recv_rep();

private:
	struct strus_connection_t* m_conn;
	double m_starttime;
	std::string m_messageBuffer;
	bool m_conn_open;
	ErrorBufferInterface* m_errorhnd;
};

}
#endif

