/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_CLIENT_IMPLEMENTATION_HPP_INCLUDED
#define _STRUS_RPC_CLIENT_IMPLEMENTATION_HPP_INCLUDED
#include "strus/rpcClientInterface.hpp"
#include "strus/reference.hpp"
#include "rpcClientContext.hpp"

namespace strus
{

/// \brief Forward declaration
class RpcClientMessagingInterface;
/// \brief Forward declaration
class ErrorBufferInterface;

/// \brief Interface providing a mechanism to create complex objects
class RpcClient
	:public RpcClientInterface
{
public:
	/// \brief Constructor
	RpcClient( RpcClientMessagingInterface* messaging_, ErrorBufferInterface* errorhnd_)
		:m_ctx( new RpcClientContext( messaging_)),m_errorhnd(errorhnd_){}

	RpcClient( const RpcClient& o)
		:m_ctx(o.m_ctx),m_errorhnd(o.m_errorhnd){}

	/// \brief Destructor
	virtual ~RpcClient(){}

	virtual StorageObjectBuilderInterface* createStorageObjectBuilder() const;

	virtual AnalyzerObjectBuilderInterface* createAnalyzerObjectBuilder() const;

	virtual void close();

private:
	Reference<RpcClientContext> m_ctx;
	ErrorBufferInterface* m_errorhnd;
};

}//namespace
#endif

