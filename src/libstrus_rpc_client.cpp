/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "strus/lib/rpc_client.hpp"
#include "strus/rpcClientInterface.hpp"
#include "strus/rpcClientMessagingInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "rpcClient.hpp"
#include "private/dll_tags.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"

using namespace strus;

DLL_PUBLIC RpcClientInterface* strus::createRpcClient( RpcClientMessagingInterface* connector, ErrorBufferInterface* errorhnd)
{
	try
	{
		static bool intl_initialized = false;
		if (!intl_initialized)
		{
			strus::initMessageTextDomain();
			intl_initialized = true;
		}
		return new RpcClient( connector, errorhnd);
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error creating RPC client: %s"), *errorhnd, 0);
}


