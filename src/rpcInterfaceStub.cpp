/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "private/utils.hpp"
#include "rpcInterfaceStub.hpp"
#include "rpcSerializer.hpp"
#include <stdexcept>
#include <limits>

using namespace strus;

RpcInterfaceStub::RpcInterfaceStub( unsigned char classId_, unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_)
	:m_classId(classId_),m_objId(objId_),m_ctx(ctx_),m_isConst(isConst_),m_errorhnd(errorhnd_)
{}

RpcInterfaceStub::RpcInterfaceStub( const RpcInterfaceStub& o)
	:m_classId(o.m_classId),m_objId(o.m_objId),m_ctx(o.m_ctx),m_isConst(o.m_isConst),m_errorhnd(o.m_errorhnd){}

RpcInterfaceStub::RpcInterfaceStub( ErrorBufferInterface* errorhnd_)
	:m_classId(0),m_objId(0),m_ctx(0),m_isConst(true),m_errorhnd(errorhnd_){}


