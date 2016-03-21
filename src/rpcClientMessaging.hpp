/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

