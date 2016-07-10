/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "strus/lib/module.hpp"
#include "strus/lib/error.hpp"
#include "strus/lib/storage_objbuild.hpp"
#include "strus/reference.hpp"
#include "rpcRequestHandler.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/moduleLoaderInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "strus/versionRpc.hpp"
#include "strus/base/configParser.hpp"
#include "strus/base/fileio.hpp"
#include "private/errorUtils.hpp"
#include "private/internationalization.hpp"
#include "private/utils.hpp"
#include "private/traceUtils.hpp"
#include "rpcSerializer.hpp"
extern "C" {
#include "server.h"
#include "hexdump.h"
}
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
	std::cout << "    " << _TXT("Print this usage and do nothing else") << std::endl;
	std::cout << "-v|--version" << std::endl;
	std::cout << "    " << _TXT("Print the program version and do nothing else") << std::endl;
	std::cout << "-m|--module <MOD>" << std::endl;
	std::cout << "    " << _TXT("Load components from module <MOD>") << std::endl;
	std::cout << "-M|--moduledir <DIR>" << std::endl;
	std::cout << "    " << _TXT("Search modules to load first in <DIR>") << std::endl;
	std::cout << "-R|--resourcedir <DIR>" << std::endl;
	std::cout << "    " << _TXT("Define a resource path <DIR> for the analyzer") << std::endl;
	std::cout << "-p|--port <PORT>" << std::endl;
	std::cout << "    " << _TXT("Define the port to listen for requests as <PORT> (default 7181)") << std::endl;
	std::cout << "-s|--storage <CONFIG>" << std::endl;
	std::cout << "    " << _TXT("Define configuration <CONFIG> of storage hosted by this server") << std::endl;
	std::cout << "-S|--configfile <CFGFILE>" << std::endl;
	std::cout << "    " << _TXT("Define storage configuration as content of file <CFGFILE>") << std::endl;
	std::cout << "-c|--create <CONFIG>" << std::endl;
	std::cout << "    " << _TXT("Implicitely create storage with <CONFIG> if it does not exist yet") << std::endl;
	std::cout << "-l|--logfile <FILE>" << std::endl;
	std::cout << "    " << _TXT("Write logs to file <FILE>") << std::endl;
	std::cout << "-T|--trace <CONFIG>" << std::endl;
	std::cout << "    " << _TXT("Print method call traces configured with <CONFIG>") << std::endl;
}

static strus::ErrorBufferInterface* g_errorBuffer = 0;
static strus::ModuleLoaderInterface* g_moduleLoader = 0;
static strus::StorageObjectBuilderInterface* g_storageObjectBuilder = 0;
static strus::AnalyzerObjectBuilderInterface* g_analyzerObjectBuilder = 0;
static strus::StorageClientInterface* g_storageClient = 0;

static strus_globalctx_t g_glbctx = {0,0,0,0};

struct handler_context_t
{
	strus::RpcRequestHandler* obj;
	std::string resultbuf;
};

int g_static_assert_sizeof_handlerdata[ (sizeof(handler_context_t) > sizeof(strus_handlerdata_t)) ? 0 : 1];

static uint32_t unpackMessageLen( unsigned char const*& itr, const unsigned char* end)
{
	if (itr+4 > end) throw strus::runtime_error( _TXT("message to small to encode message length"));
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
			ctx->obj = new strus::RpcRequestHandler(
					g_storageObjectBuilder, g_analyzerObjectBuilder, g_storageClient, g_errorBuffer);
		}
		ctx->resultbuf.clear();
		ctx->resultbuf.append( "\0\0\0\0", sizeof( uint32_t));
		if (readbufsize > 0 && readbuf[0] == 0xFF)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			fprintf( g_glbctx.logf, _TXT("got multipart request [%u bytes]\n"), readbufsize);
#endif
			unsigned char const* itr = readbuf+1;
			unsigned const char* end = itr + readbufsize -1;
			while (itr < end)
			{
				uint32_t msglen = unpackMessageLen( itr, end);
#ifdef STRUS_LOWLEVEL_DEBUG
				fprintf( g_glbctx.logf, _TXT("call request handler [%u bytes]\n"), msglen);
#endif
				ctx->resultbuf.append( ctx->obj->handleRequest( (const char*)itr, (std::size_t)msglen));
				if (ctx->resultbuf.size() > sizeof(uint32_t))
				{
					if (ctx->resultbuf[sizeof(uint32_t)] == (char)strus::MsgTypeAnswer && itr+msglen != end)
					{
						fprintf( g_glbctx.logf, _TXT("got unexpected answer (protocol error) ... closing connection\n"));
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
			fprintf( g_glbctx.logf, _TXT("got singlepart request [%u bytes]\n"), readbufsize);
			fprintf( g_glbctx.logf, _TXT("call request handler [%u bytes]\n"), readbufsize);
#endif
			ctx->resultbuf.append( ctx->obj->handleRequest( (const char*)readbuf, (std::size_t)readbufsize));
		}
		*output = (const unsigned char*)ctx->resultbuf.c_str();
		*outputsize = ctx->resultbuf.size();
	}
	catch (const std::runtime_error& err)
	{
		fprintf( g_glbctx.logf, _TXT("runtime error in request handler: %s\n"), err.what());
		return 1;
	}
	catch (const std::bad_alloc& err)
	{
		fprintf( g_glbctx.logf, _TXT("memory allocation error in request handler\n"));
		return 2;
	}
	catch (const std::exception& err)
	{
		fprintf( g_glbctx.logf, _TXT("exception in request handler: %s\n"), err.what());
		return 3;
	}
	catch (...)
	{
		fprintf( g_glbctx.logf, _TXT("unknown exception in request handler\n"));
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
		fprintf( g_glbctx.logf, _TXT("memory allocation error initializing request handler object: %s\n"), err.what());
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
		std::cerr << _TXT("strus RPC server writing logs to file '") << logfile << "'" << std::endl;
		g_glbctx.logf = ::fopen( logfile, "a+");
	}
	else
	{
		g_glbctx.logf = stderr;
	}
}

static void done_global_context()
{
	if (g_glbctx.logf != NULL && g_glbctx.logf != stderr && g_glbctx.logf != stdout)
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

static void createStorageIfNotExist( const std::string& cfg)
{
	const strus::DatabaseInterface* dbi = g_storageObjectBuilder->getDatabase( cfg);
	if (dbi->exists( cfg)) return;
	const strus::StorageInterface* sti = g_storageObjectBuilder->getStorage();

	std::string databasecfg( cfg);
	std::string dbname;
	(void)strus::extractStringFromConfigString( dbname, databasecfg, "database", g_errorBuffer);
	std::string storagecfg( databasecfg);

	strus::removeKeysFromConfigString(
			databasecfg,
			sti->getConfigParameters(
				strus::StorageInterface::CmdCreateClient), g_errorBuffer);
	//... In database_cfg is now the pure database configuration without the storage settings

	strus::removeKeysFromConfigString(
			storagecfg,
			dbi->getConfigParameters(
				strus::DatabaseInterface::CmdCreateClient), g_errorBuffer);
	//... In storage_cfg is now the pure storage configuration without the database settings
	if (g_errorBuffer->hasError())
	{
		throw strus::runtime_error(_TXT("error creating storage"));
	}
	dbi->createDatabase( databasecfg);

	std::auto_ptr<strus::DatabaseClientInterface>
		database( dbi->createClient( databasecfg));
	if (!database.get())
	{
		throw strus::runtime_error(_TXT("error creating storage"));
	}
	sti->createStorage( storagecfg, database.get());
}


int main( int argc, const char* argv[])
{
	std::auto_ptr<strus::ErrorBufferInterface> errorBuffer( strus::createErrorBuffer_standard( 0, 2));
	if (!errorBuffer.get())
	{
		std::cerr << _TXT("failed to create error buffer") << std::endl;
		return -1;
	}
	g_errorBuffer = errorBuffer.get();

	bool doExit = false;
	int argi = 1;
	std::string logfile;
	std::vector<std::string> moduledirs;
	std::vector<std::string> modules;
	std::vector<std::string> resourcedirs;
	std::vector<std::string> tracecfglist;
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
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--module");
				modules.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-M") || 0==std::strcmp( argv[argi], "--moduledir"))
			{
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--moduledir");
				moduledirs.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-R") || 0==std::strcmp( argv[argi], "--resourcedir"))
			{
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--resourcedir");
				resourcedirs.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-p") || 0==std::strcmp( argv[argi], "--port"))
			{
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--port");
				try
				{
					port = strus::utils::touint( argv[argi]);
					if (port == 0 || port > 65535)
					{
						throw strus::runtime_error( _TXT("value out of range"));
					}
				}
				catch (const std::runtime_error& err)
				{
					throw strus::runtime_error( _TXT("illegal argument for option %s: %s"), "--port", err.what());
				}
			}
			else if (0==std::strcmp( argv[argi], "-s") || 0==std::strcmp( argv[argi], "--storage"))
			{
				if (!storageconfig.empty()) throw strus::runtime_error( _TXT("option %s or %s specified twice"), "--storage","--configfile");
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--storage");
				storageconfig.append( argv[argi]);
				if (storageconfig.empty()) throw strus::runtime_error(_TXT("option %s with empty argument"), "--storage");
			}
			else if (0==std::strcmp( argv[argi], "-S") || 0==std::strcmp( argv[argi], "--configfile"))
			{
				if (!storageconfig.empty()) throw strus::runtime_error( _TXT("option %s or %s specified twice"), "--storage","--configfile");
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--configfile");
				int ec = strus::readFile( argv[argi], storageconfig);
				if (ec)
				{
					throw strus::runtime_error(_TXT("failed to read configuration file %s (file system error %u)"), argv[argi], ec);
				}
				std::string::iterator di = storageconfig.begin(), de = storageconfig.end();
				for (; di != de; ++di)
				{
					if ((unsigned char)*di < 32) *di = ' ';
				}
				if (storageconfig.empty()) throw strus::runtime_error(_TXT("option %s with empty file"), "--configfile");
			}
			else if (0==std::strcmp( argv[argi], "-c") || 0==std::strcmp( argv[argi], "--create"))
			{
				doCreateIfNotExist = true;
			}
			else if (0==std::strcmp( argv[argi], "-T") || 0==std::strcmp( argv[argi], "--trace"))
			{
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument (trace configuration)"), "--trace");
				tracecfglist.push_back( argv[argi]);
			}
			else if (0==std::strcmp( argv[argi], "-t") || 0==std::strcmp( argv[argi], "--threads"))
			{
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects number as argument"), "--threads");
				try
				{
					nofThreads = strus::utils::touint( argv[argi]);
				}
				catch (const std::runtime_error& err)
				{
					throw strus::runtime_error(_TXT("illegal argument for option %s: %s"),"--threads", err.what());
				}
			}
			else if (0==std::strcmp( argv[argi], "-l") || 0==std::strcmp( argv[argi], "--logfile"))
			{
				if (logfile.size()) throw strus::runtime_error(_TXT("duplicate definition of option %s"), "--logfile");
				++argi;
				if (argi == argc) throw strus::runtime_error(_TXT("option %s expects argument"), "--logfile");
				logfile = argv[argi];
				if (logfile.empty()) throw strus::runtime_error(_TXT("empty definition of option %s"), "--logfile");
			}
			else if (argv[argi][0] == '-')
			{
				throw strus::runtime_error(_TXT("unknown option %s"), argv[argi]);
			}
			else
			{
				throw strus::runtime_error( _TXT("no arguments expected (only options)"));
			}
		}
		if (doExit) return 0;
		init_global_context( logfile.empty()?0:logfile.c_str());
		g_errorBuffer->setLogFile( g_glbctx.logf);
		g_errorBuffer->setMaxNofThreads( strus_threadpool_size()+2);

		// Create the global context:
		std::auto_ptr<strus::ModuleLoaderInterface>
			moduleLoader( strus::createModuleLoader( g_errorBuffer));
		g_moduleLoader = moduleLoader.get();
		if (!g_moduleLoader) throw strus::runtime_error( _TXT("failed to create module loader"));

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
		if (g_errorBuffer->hasError())
		{
			throw strus::runtime_error(_TXT("error in initialization: %s"), g_errorBuffer->fetchError());
		}

		// Declare trace proxy objects:
		typedef strus::Reference<strus::TraceProxy> TraceReference;
		std::vector<TraceReference> trace;
		if (!tracecfglist.empty())
		{
			std::vector<std::string>::const_iterator ti = tracecfglist.begin(), te = tracecfglist.end();
			for (; ti != te; ++ti)
			{
				trace.push_back( new strus::TraceProxy( g_moduleLoader, *ti, g_errorBuffer));
			}
		}

		// Create objects:
		std::auto_ptr<strus::StorageObjectBuilderInterface>
			storageBuilder( g_moduleLoader->createStorageObjectBuilder());
		if (!storageBuilder.get())
		{
			throw strus::runtime_error( _TXT("failed to create storage builder"));
		}
		std::auto_ptr<strus::AnalyzerObjectBuilderInterface>
			analyzerBuilder( g_moduleLoader->createAnalyzerObjectBuilder());
		if (!analyzerBuilder.get())
		{
			throw strus::runtime_error( _TXT("failed to create analyzer builder"));
		}

		// Create proxy objects if tracing enabled:
		std::vector<TraceReference>::const_iterator ti = trace.begin(), te = trace.end();
		for (; ti != te; ++ti)
		{
			strus::AnalyzerObjectBuilderInterface* aproxy = (*ti)->createProxy( analyzerBuilder.get());
			analyzerBuilder.release();
			analyzerBuilder.reset( aproxy);
			strus::StorageObjectBuilderInterface* sproxy = (*ti)->createProxy( storageBuilder.get());
			storageBuilder.release();
			storageBuilder.reset( sproxy);
		}

		std::auto_ptr<strus::StorageClientInterface> storageClient;

		g_storageObjectBuilder = storageBuilder.get();
		g_analyzerObjectBuilder = analyzerBuilder.get();

		if (!storageconfig.empty())
		{
			if (doCreateIfNotExist)
			{
				createStorageIfNotExist( storageconfig);
			}
			storageClient.reset( strus::createStorageClient( g_storageObjectBuilder, g_errorBuffer, storageconfig));
			if (!storageClient.get())
			{
				throw strus::runtime_error( _TXT("failed to create storage client"), storageconfig.c_str());
			}
			std::cerr << _TXT("strus RPC server is hosting storage ") << "'" << storageconfig << "'" << std::endl;
			g_storageClient = storageClient.get();
		}

		// Start server:
		std::cerr << "strus RPC server listening on port " << port << std::endl;
		int err = strus_run_server( (unsigned short)(unsigned int)port, nofThreads, &g_glbctx);
		if (err)
		{
			throw strus::runtime_error( _TXT("server terminated with error (see logs)"));
		}
		std::cerr << _TXT("strus RPC server terminated") << std::endl;

		// Cleanup when done:
		done_global_context();
		return 0;
	}
	catch (const std::exception& e)
	{
		const char* errormsg = g_errorBuffer?g_errorBuffer->fetchError():0;
		if (errormsg)
		{
			std::cerr << e.what() << ": " << errormsg << std::endl;
		}
		else
		{
			std::cerr << e.what() << std::endl;
		}
	}
	std::cerr << _TXT("strus RPC server terminated") << std::endl;
	done_global_context();
	return -1;
}


