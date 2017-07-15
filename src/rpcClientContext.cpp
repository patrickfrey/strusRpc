/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "private/utils.hpp"
#include "private/internationalization.hpp"
#include "rpcClientContext.hpp"
#include "rpcProtocolDefines.hpp"
#include "rpcSerializer.hpp"
#include <stdexcept>
#include <limits>

#ifndef STRUS_RPC_PROTOCOL_WITH_TYPED_ATOMS
#error Missing include of rpcProtocolDefines.hpp
#endif
#if STRUS_RPC_PROTOCOL_WITH_TYPED_ATOMS
#define EMPTY_ANSWER_SIZE 2
#else
#define EMPTY_ANSWER_SIZE 1
#endif

using namespace strus;

RpcClientContext::RpcClientContext( RpcClientMessagingInterface* messaging_)
	:m_objIdCnt(0),m_messaging(messaging_)
{}

RpcClientContext::RpcClientContext()
	:m_objIdCnt(0),m_messaging(0){}

RpcClientContext::~RpcClientContext()
{
	delete m_messaging;
}

void RpcClientContext::handleError( const std::string& msgstr) const
{
	if (msgstr.empty())
	{
		throw strus::runtime_error( _TXT("got no answer from server"));
	}
	RpcDeserializer msg( msgstr.c_str(), msgstr.size());
	RpcReturnType returntype = (RpcReturnType)msg.unpackByte();
	switch (returntype)
	{
		case MsgTypeError:
		{
			const char* errorstr = msg.unpackConstCharp();
			throw strus::runtime_error( _TXT("method call failed: %s"), errorstr);
		}
		case MsgTypeSynchronize:
			break;
		case MsgTypeAnswer:
			if (!msg.unpackCrc32())
			{
				throw strus::runtime_error( _TXT("answer CRC32 check failed"));
			}
			break;
	}
}

std::string RpcClientContext::rpc_sendRequest( const std::string& msg) const
{
	std::string answer = m_messaging->sendRequest( msg);
	handleError( answer);
	return answer;
}

void RpcClientContext::rpc_sendMessage( const std::string& msg) const
{
	m_messaging->sendMessage( msg);
}

void RpcClientContext::rpc_synchronize() const
{
	std::string answer = m_messaging->synchronize();
	if (answer.empty()) return;
	handleError( answer);
	if (answer.size() > EMPTY_ANSWER_SIZE)
	{
		throw strus::runtime_error( _TXT("got unexpected (non empty) answer from server calling rpc_synchronize"));
	}
}

void RpcClientContext::rpc_close()
{
	m_messaging->close();
}



