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
#include "private/utils.hpp"
#include "private/internationalization.hpp"
#include "rpcClientContext.hpp"
#include "rpcSerializer.hpp"
#include <stdexcept>
#include <limits>

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
	if (answer.size() > 1)
	{
		throw strus::runtime_error( _TXT("got unexpected (non empty) answer from server calling rpc_synchronize"));
	}
}

void RpcClientContext::rpc_close()
{
	m_messaging->close();
}



