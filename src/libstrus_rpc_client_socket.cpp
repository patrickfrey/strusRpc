/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "strus/lib/rpc_client_socket.hpp"
#include "strus/rpcClientMessagingInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "rpcClientMessaging.hpp"
#include "private/internationalization.hpp"
#include "private/errorUtils.hpp"
#include "strus/base/dll_tags.hpp"

DLL_PUBLIC strus::RpcClientMessagingInterface*
	strus::createRpcClientMessaging(
		const std::string& config,
		ErrorBufferInterface* errorhnd)
{
	try
	{
		static bool intl_initialized = false;
		if (!intl_initialized)
		{
			strus::initMessageTextDomain();
			intl_initialized = true;
		}
		return new RpcClientMessaging( config, errorhnd);
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error creating RPC messaging client: %s"), *errorhnd, 0);
}



