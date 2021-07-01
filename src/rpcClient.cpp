/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "rpcClient.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "objects_gen.hpp"
#include "strus/base/dll_tags.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"

using namespace strus;
using namespace strus::rpc;

static bool g_intl_initialized = false;

StorageObjectBuilderInterface* RpcClient::createStorageObjectBuilder() const
{
	try
	{
		if (!g_intl_initialized)
		{
			strus::initMessageTextDomain();
			g_intl_initialized = true;
		}
		return new StorageObjectBuilderImpl( 0, m_ctx, false, m_errorhnd);
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error creating storage object builder: %s"), *m_errorhnd, 0);
}

AnalyzerObjectBuilderInterface* RpcClient::createAnalyzerObjectBuilder() const
{
	try
	{
		if (!g_intl_initialized)
		{
			strus::initMessageTextDomain();
			g_intl_initialized = true;
		}
		return new AnalyzerObjectBuilderImpl( 0, m_ctx, false, m_errorhnd);
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error creating analyzer object builder: %s"), *m_errorhnd, 0);
}

void RpcClient::close()
{
	try
	{
		m_ctx->rpc_close();
	}
	CATCH_ERROR_MAP( _TXT("error closing RPC client connection: %s"), *m_errorhnd);
}

std::string RpcClient::config() const
{
	try
	{
		return m_ctx->config();
	}
	CATCH_ERROR_MAP_RETURN( _TXT("error getting RPC client connection configuration: %s"), *m_errorhnd, std::string());
}
