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
#include "strus/lib/rpc_server.hpp"
#include "strus/lib/module.hpp"
#include "strus/rpcRequestHandlerInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/moduleLoaderInterface.hpp"
#include "strus/versionRpc.hpp"
#include "strus/private/configParser.hpp"
#include "strus/private/fileio.hpp"
#include "private/utils.hpp"
#include "loadGlobalStatistics.hpp"
#include "rpcSerializer.hpp"
extern "C" {
#include "server.h"
#include "hexdump.h"
}
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <netinet/in.h>

#undef STRUS_LOWLEVEL_DEBUG

static void printUsage()
{
	std::cout << "strusRpcServer [options]" << std::endl;
	std::cout << "options:" << std::endl;
	std::cout << "-h|--help" << std::endl;
	std::cout << "    Print this usage and do nothing else" << std::endl;
	std::cout << "-v|--version" << std::endl;
	std::cout << "    Print the program version and do nothing else" << std::endl;
	std::cout << "-m|--module <MOD>" << std::endl;
	std::cout << "    Load components from module <MOD>" << std::endl;
	std::cout << "-M|--moduledir <DIR>" << std::endl;
	std::cout << "    Search modules to load first in <DIR>" << std::endl;
	std::cout << "-R|--resourcedir <DIR>" << std::endl;
	std::cout << "    Define a resource path <DIR> for the analyzer" << std::endl;
	std::cout << "-p|--port <PORT>" << std::endl;
	std::cout << "    Define the port to listen for requests as <PORT> (default 7181)" << std::endl;
	std::cout << "-s|--storage <CONFIG>" << std::endl;
	std::cout << "    Define configuration <CONFIG> of storage hosted by this server" << std::endl;
	std::cout << "-S|--configfile <CFGFILE>" << std::endl;
	std::cout << "    Define storage configuration as content of file <CFGFILE>" << std::endl;
	std::cout << "-c|--create <CONFIG>" << std::endl;
	std::cout << "    Implicitely create storage with <CONFIG> if it does not exist yet" << std::endl;
	std::cout << "-g|--globalstats <FILE>" << std::endl;
	std::cout << "    Load global statistics of peers from file <FILE>" << std::endl;
	std::cout << "-l|--logfile <FILE>" << std::endl;
	std::cout << "    Write logs to file <FILE>" << std::endl;
}

static strus::ModuleLoaderInterface* g_moduleLoader = 0;
static strus::StorageObjectBuilderInterface* g_storageObjectBuilder = 0;
static strus::AnalyzerObjectBuilderInterface* g_analyzerObjectBuilder = 0;
static strus::StorageClientInterface* g_storageClient = 0;

static strus_globalctx_t g_glbctx = {0,0,0,0};

struct handler_context_t
{
	strus::RpcRequestHandlerInterface* obj;
	std::string resultbuf;
};

int g_static_assert_sizeof_handlerdata[ (sizeof(handler_context_t) > sizeof(strus_handlerdata_t)) ? 0 : 1];

static uint32_t unpackMessageLen( unsigned char const*& itr, const unsigned char* end)
{
	if (itr+4 > end) throw std::runtime_error( "message to small to encode message length");
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	return ntohl( val);
}

static int request_handler(
		struct strus_handlerdata_t* handlerdata,
		const unsigned char* readbuf,
		size_t readbufsize,
		size_t outputhdrsize,
		const unsigned char** output,
		size_t* outputsize)
{
	handler_context_t* ctx = reinterpret_cast<handler_context_t*>( handlerdata);
	try
	{
		if (!ctx->obj)
		{
			ctx->obj = strus::createRpcRequestHandler(
						g_storageObjectBuilder, g_analyzerObjectBuilder, g_storageClient);
		}
		ctx->resultbuf.clear();
		ctx->resultbuf.append( "\0\0\0\0", sizeof( uint32_t));
		if (readbufsize > 0 && readbuf[0] == 0xFF)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			fprintf( g_glbctx.logf, "got multipart request [%u bytes]\n", readbufsize);
#endif
			unsigned char const* itr = readbuf+1;
			unsigned const char* end = itr + readbufsize -1;
			while (itr < end)
			{
				uint32_t msglen = unpackMessageLen( itr, end);
#ifdef STRUS_LOWLEVEL_DEBUG
				fprintf( g_glbctx.logf, "call request handler [%u bytes]\n", msglen);
#endif
				ctx->resultbuf.append( ctx->obj->handleRequest( (const char*)itr, (std::size_t)msglen));
				if (ctx->resultbuf.size() > sizeof(uint32_t))
				{
					if (ctx->resultbuf[sizeof(uint32_t)] == (char)strus::MsgTypeAnswer && itr+msglen != end)
					{
						std::cerr << "got unexpected answer (protocol error) ... closing connection" << std::endl;
						return 6;
					}
					break;
				}
				itr += msglen;
			}
		}
		else
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			fprintf( g_glbctx.logf, "got singlepart request [%u bytes]\n", readbufsize);
			fprintf( g_glbctx.logf, "call request handler [%u bytes]\n", readbufsize);
#endif
			ctx->resultbuf.append( ctx->obj->handleRequest( (const char*)readbuf, (std::size_t)readbufsize));
		}
		*output = (const unsigned char*)ctx->resultbuf.c_str();
		*outputsize = ctx->resultbuf.size();
	}
	catch (const std::runtime_error& err)
	{
		fprintf( g_glbctx.logf, "runtime error in request handler: %s\n", err.what());
		return 1;
	}
	catch (const std::bad_alloc& err)
	{
		fprintf( g_glbctx.logf, "memory allocation error  in request handler\n");
		return 2;
	}
	catch (const std::exception& err)
	{
		fprintf( g_glbctx.logf, "exception in request handler: %s\n", err.what());
		return 3;
	}
	catch (...)
	{
		fprintf( g_glbctx.logf, "unknown exception in request handler\n");
		return 4;
	}
	return 0;
}

static int init_handlerdata( struct strus_handlerdata_t* handlerdata)
{
	handler_context_t* ctx = reinterpret_cast<handler_context_t*>( handlerdata);
	try
	{
		ctx->obj = 0;
		new (&ctx->resultbuf) std::string();
	}
	catch (const std::bad_alloc& err)
	{
		fprintf( g_glbctx.logf, "memory allocation error initializing request handler object: %s\n", err.what());
		return 1;
	}
	catch (...)
	{
		fprintf( g_glbctx.logf, "unknown exception initializing request handler object\n");
		return 2;
	}
	return 0;
}

static void done_handlerdata( struct strus_handlerdata_t* handlerdata)
{
	handler_context_t* ctx = reinterpret_cast<handler_context_t*>( handlerdata);
	if (ctx->obj)
	{
		delete ctx->obj;
		ctx->obj = 0;
	}
	typedef std::string string;
	ctx->resultbuf.~string();
}

static void init_global_context( const char* logfile)
{
	g_glbctx.init_handlerdata = &init_handlerdata;
	g_glbctx.done_handlerdata = &done_handlerdata;
	g_glbctx.request_handler = &request_handler;
	if (logfile)
	{
		g_glbctx.logf = ::fopen ( logfile, "a+");
	}
	else
	{
		g_glbctx.logf = stderr;
	}
}

static void done_global_context()
{
	if (g_glbctx.logf != stderr)
	{
		fclose( g_glbctx.logf);
		g_glbctx.logf = stderr;
	}
}

enum
{
	STRUS_ERR_EVBASE=1,
	STRUS_ERR_LISTEN=2,
	STRUS_ERR_SIGNALEV=3
};

static int runServer( int port, unsigned int nofThreads, const char* logfile)
{
	std::cerr << "strus RPC server listening on port " << port << std::endl;
	if (logfile) std::cerr << "strus RPC server writing logs to file '" << logfile << "'" << std::endl;
	init_global_context( logfile);
	int rt = strus_run_server( (unsigned short)(unsigned int)port, nofThreads, &g_glbctx);
	done_global_context();
	return rt;
}

static void createStorageIfNotExist( const std::string& cfg)
{
	const strus::DatabaseInterface* dbi = g_storageObjectBuilder->getDatabase( cfg);
	if (dbi->exists( cfg)) return;
	const strus::StorageInterface* sti = g_storageObjectBuilder->getStorage();

	std::string databasecfg( cfg);
	std::string dbname;
	(void)strus::extractStringFromConfigString( dbname, databasecfg, "database");
	std::string storagecfg( databasecfg);

	strus::removeKeysFromConfigString(
			databasecfg,
			sti->getConfigParameters(
				strus::StorageInterface::CmdCreateClient));
	//... In database_cfg is now the pure database configuration without the storage settings

	strus::removeKeysFromConfigString(
			storagecfg,
			dbi->getConfigParameters(
				strus::DatabaseInterface::CmdCreateClient));
	//... In storage_cfg is now the pure storage configuration without the database settings

	dbi->createDatabase( databasecfg);

	std::auto_ptr<strus::DatabaseClientInterface>
		database( dbi->createClient( databasecfg));

	sti->createStorage( storagecfg, database.get());
}


int main( int argc, const char* argv[])
{
	bool doExit = false;
	int argi = 1;
	std::string logfile;
	std::vector<std::string> moduledirs;
	std::vector<std::string> modules;
	std::vector<std::string> resourcedirs;
	std::vector<std::string> globalstatfiles;
	std::string storageconfig;
	bool doCreateIfNotExist = false;
	unsigned int nofThreads = 0;
	unsigned int port = 7181; //... default port
	try
	{
		// Parsing arguments:
		for (; argi < argc; ++argi)
		{
			if (0==std::strcmp( argv[argi], "-h") || 0==std::strcmp( argv[argi], "--help"))
			{
				printUsage();
				doExit = true;
			}
			else if (0==std::strcmp( argv[argi], "-v") || 0==std::strcmp( argv[argi], "--version"))
			{
				std::cerr << "strusRpc version " << STRUS_RPC_VERSION_STRING << std::endl;
				doExit = true;
			}
			else if (0==std::strcmp( argv[argi], "-m") || 0==std::strcmp( argv[argi], "--module"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --module expects argument");
				modules.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-M") || 0==std::strcmp( argv[argi], "--moduledir"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --moduledir expects argument");
				moduledirs.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-R") || 0==std::strcmp( argv[argi], "--resourcedir"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --resourcedir expects argument");
				resourcedirs.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-p") || 0==std::strcmp( argv[argi], "--port"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --port expects argument");
				try
				{
					port = strus::utils::touint( argv[argi]);
					if (port == 0 || port > 65535)
					{
						throw std::runtime_error( "value out of range");
					}
				}
				catch (const std::runtime_error& err)
				{
					throw std::runtime_error( std::string("illegal argument for option --port: ") + err.what());
				}
			}
			else if (0==std::strcmp( argv[argi], "-s") || 0==std::strcmp( argv[argi], "--storage"))
			{
				if (!storageconfig.empty()) throw std::runtime_error("option --storage or --configfile specified twice");
				++argi;
				if (argi == argc) throw std::runtime_error("option --storage expects argument (storage configuration string)");
				storageconfig.append( argv[argi]);
				if (storageconfig.empty()) throw std::runtime_error("option --storage with empty argument");
			}
			else if (0==std::strcmp( argv[argi], "-S") || 0==std::strcmp( argv[argi], "--configfile"))
			{
				if (!storageconfig.empty()) throw std::runtime_error("option --storage or --configfile specified twice");
				++argi;
				if (argi == argc) throw std::runtime_error("option --configfile expects argument (storage configuration file)");
				int ec = strus::readFile( argv[argi], storageconfig);
				if (ec)
				{
					std::ostringstream msg;
					msg << ec;
					throw std::runtime_error( std::string("failed to read configuration file ") + argv[argi] + " (file system error " + msg.str() + ")");
				}
				std::string::iterator di = storageconfig.begin(), de = storageconfig.end();
				for (; di != de; ++di)
				{
					if ((unsigned char)*di < 32) *di = ' ';
				}
				if (storageconfig.empty()) throw std::runtime_error( "option --configfile with empty file");
			}
			else if (0==std::strcmp( argv[argi], "-c") || 0==std::strcmp( argv[argi], "--create"))
			{
				doCreateIfNotExist = true;
			}
			else if (0==std::strcmp( argv[argi], "-g") || 0==std::strcmp( argv[argi], "--globalstats"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --storage expects argument (storage configuration string)");
				globalstatfiles.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-t") || 0==std::strcmp( argv[argi], "--threads"))
			{
				++argi;
				if (argi == argc) throw std::runtime_error("option --threads expects number as argument");
				try
				{
					nofThreads = strus::utils::touint( argv[argi]);
				}
				catch (const std::runtime_error& err)
				{
					throw std::runtime_error( std::string("illegal argument for option --threads: ") + err.what());
				}
			}
			else if (0==std::strcmp( argv[argi], "-l") || 0==std::strcmp( argv[argi], "--logfile"))
			{
				if (logfile.size())throw std::runtime_error( "duplicate definition of option --logfile");
				++argi;
				if (argi == argc) throw std::runtime_error("option --logfile expects argument (log file path)");
				logfile = argv[argi];
				if (logfile.empty())throw std::runtime_error( "empty definition of option --logfile");
			}
			else if (argv[argi][0] == '-')
			{
				throw std::runtime_error( std::string( "unknown option ") + argv[argi]);
			}
			else
			{
				throw std::runtime_error( "no arguments expected (only options)");
			}
		}
		if (doExit) return 0;

		// Create the global context:
		std::auto_ptr<strus::ModuleLoaderInterface>
			moduleLoader( strus::createModuleLoader());
		g_moduleLoader = moduleLoader.get();

		std::vector<std::string>::const_iterator
			di = moduledirs.begin(), de = moduledirs.end();
		for (; di != de; ++di)
		{
			g_moduleLoader->addModulePath( *di);
		}
		moduleLoader->addSystemModulePath();
		std::vector<std::string>::const_iterator
			mi = modules.begin(), me = modules.end();
		for (; mi != me; ++mi)
		{
			g_moduleLoader->loadModule( *mi);
		}
		std::vector<std::string>::const_iterator
			pi = resourcedirs.begin(), pe = resourcedirs.end();
		for (; pi != pe; ++pi)
		{
			g_moduleLoader->addResourcePath( *pi);
		}

		std::auto_ptr<strus::StorageObjectBuilderInterface>
			storageBuilder( g_moduleLoader->createStorageObjectBuilder());
		std::auto_ptr<strus::AnalyzerObjectBuilderInterface>
			analyzerBuilder( g_moduleLoader->createAnalyzerObjectBuilder());
		std::auto_ptr<strus::StorageClientInterface> storageClient;

		g_storageObjectBuilder = storageBuilder.get();
		g_analyzerObjectBuilder = analyzerBuilder.get();

		if (!storageconfig.empty())
		{
			if (doCreateIfNotExist)
			{
				createStorageIfNotExist( storageconfig);
			}
			storageClient.reset( g_storageObjectBuilder->createStorageClient( storageconfig));
			std::cerr << "strus RPC server is hosting storage '" << storageconfig << "'" << std::endl;
			g_storageClient = storageClient.get();
		}

		// Load global statistics from file if defined:
		std::vector<std::string>::const_iterator
			gi = globalstatfiles.begin(), ge = globalstatfiles.end();
		for (; gi != ge; ++gi)
		{
			std::cerr << "strus RPC server loading global statistics from file '" << *gi << "'" << std::endl;
			std::ifstream file;
			file.exceptions( std::ifstream::failbit | std::ifstream::badbit);
			try 
			{
				file.open( gi->c_str(), std::fstream::in);
				strus::loadGlobalStatistics( *g_storageClient, file);
			}
			catch (const std::ifstream::failure& err)
			{
				throw std::runtime_error( std::string( "failed to read global statistics from file '") + *gi + "': " + err.what());
			}
			catch (const std::runtime_error& err)
			{
				throw std::runtime_error( std::string( "failed to read global statistics from file '") + *gi + "': " + err.what());
			}
		}

		// Start server:
		std::cerr << "strus RPC server is starting ..." << std::endl;
		if (!!runServer( port, nofThreads, logfile.empty()?0:logfile.c_str()))
		{
			throw std::runtime_error( "server terminated with error (see logs)");
		}
		std::cerr << "strus RPC server terminated" << std::endl;
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "ERROR " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "EXCEPTION " << e.what() << std::endl;
	}
	std::cerr << "strus RPC server terminated" << std::endl;
	return -1;
}


