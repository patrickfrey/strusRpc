/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_RPC_INTERFACE_STUB_HPP_INCLUDED
#define _STRUS_RPC_INTERFACE_STUB_HPP_INCLUDED
#include "constConstructor.hpp"
#include "rpcClientContext.hpp"
#include "strus/reference.hpp"
#include <string>

namespace strus {
/// \brief Forward declaration
class ErrorBufferInterface;

class RpcInterfaceStub
{
public:
	virtual ~RpcInterfaceStub(){}

	RpcInterfaceStub( unsigned char classId_, unsigned int objId_, const Reference<RpcClientContext>& ctx_, bool isConst_, ErrorBufferInterface* errorhnd_);
	RpcInterfaceStub( const RpcInterfaceStub& o);
	explicit RpcInterfaceStub( ErrorBufferInterface* errorhnd_);

	unsigned char classId() const					{return m_classId;}
	unsigned int objId() const					{return m_objId;}

	const Reference<RpcClientContext>& ctx() const			{return m_ctx;}
	bool isConst() const						{return m_isConst;}
	void release()							{m_isConst = true;}

protected:
	ErrorBufferInterface* errorhnd() const				{return m_errorhnd;}

private:
	unsigned char m_classId;
	unsigned int m_objId;
	Reference<RpcClientContext> m_ctx;
	bool m_isConst;
	ErrorBufferInterface* m_errorhnd;
};

}//namespace
#endif


