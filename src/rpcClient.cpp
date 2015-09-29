/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#include "rpcClient.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "objects_gen.hpp"
#include "private/dll_tags.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"

using namespace strus;

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
		return new StorageObjectBuilderImpl( 0, m_ctx);
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
		return new AnalyzerObjectBuilderImpl( 0, m_ctx);
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

