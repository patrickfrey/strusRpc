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
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <nn.h>
#include <reqrep.h>
#include <stdint.h>
#include <netinet/in.h>

static void printUsage()
{
	std::cerr << "strusRpcServer [options] <storageconfig>" << std::endl;
	std::cerr << "options:" << std::endl;
	std::cerr << "-h|--help" << std::endl;
	std::cerr << "   Print this usage and do nothing else" << std::endl;
	std::cerr << "-v|--version" << std::endl;
	std::cerr << "    Print the program version and do nothing else" << std::endl;
	std::cerr << "-m|--module <MOD>" << std::endl;
	std::cerr << "    Load components from module <MOD>" << std::endl;
	std::cerr << "-M|--moduledir <DIR>" << std::endl;
	std::cerr << "    Search modules to load first in <DIR>" << std::endl;
}

static void unpackUint( char const*& itr, const char* end, void* ptr)
{
	if (itr+4 > end) throw std::runtime_error( "message to small to encode next dword");
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	*(uint32_t*)ptr = ntohl( val);
}

static void runServer( const char *config, strus::RpcRequestHandlerInterface* handler)
{
	// Startup:
	int sock = nn_socket( AF_SP, NN_REP);
	if (sock < 0) switch (errno)
	{
		case EAFNOSUPPORT:
			throw std::runtime_error( "error socket (nanomsg: specified address family is not supported)");
		case EINVAL:
			throw std::runtime_error( "error socket (nanomsg: unknown protocol)");
		case EMFILE:
			throw std::runtime_error( "error socket (nanomsg: the limit on the total number of open SP sockets or OS limit for file descriptors has been reached");
		case ETERM:
			throw std::runtime_error( "error socket (nanomsg: the library is terminating");
		default:
			throw std::runtime_error( "error socket (socket create)");
	}
	int endpointid = nn_bind( sock, config);
	if (endpointid < 0) switch (errno)
	{
		case EBADF:
			throw std::runtime_error( "error bind (nanomsg: the provided socket is invalid");
		case EMFILE:
			throw std::runtime_error( "error bind (nanomsg: maximum number of active endpoints was reached");
		case ETERM:
			throw std::runtime_error( "error bind (nanomsg: the library is terminating");
		case EINVAL:
			throw std::runtime_error( "error bind (nanomsg: the syntax of the supplied address is invalid");
		case ENAMETOOLONG:
			throw std::runtime_error( "error bind (nanomsg: the supplied address is too long");
		case EPROTONOSUPPORT:
			throw std::runtime_error( "error bind (nanomsg: the requested transport protocol is not supported");
		case EADDRNOTAVAIL:
			throw std::runtime_error( "error bind (nanomsg: the requested endpoint is not local");
		case ENODEV:
			throw std::runtime_error( "error bind (nanomsg: the address specifies a nonexistent interface");
		case EADDRINUSE:
			throw std::runtime_error( "error bind (nanomsg: the requested local endpoint is already in use");
		default:
			throw std::runtime_error( "error bind (nanomsg: unknown error)");
	}
	// Serving requests:
	for (;;)
	{
		char* msg = NULL;
		int msgsize = nn_recv( sock, &msg, NN_MSG, 0);
		if (msgsize < 0) switch (errno)
		{
			case EBADF:
				throw std::runtime_error( "error receive (nanomsg: the provided socket is invalid");
			case ETERM:
				throw std::runtime_error( "error receive (nanomsg: the library is terminating");
			case ENOTSUP:
				throw std::runtime_error( "error receive (nanomsg: the operation is not supported by this socket type");
			case EFSM:
				throw std::runtime_error( "error receive (nanomsg: the operation cannot be performed on this socket at the moment because socket is not in the appropriate state");
			case EAGAIN:
				throw std::runtime_error( "error receive (nanomsg: non-blocking mode was requested and there’s no message to receive at the moment");
			case EINTR:
				std::cerr << "got EINTR, shutting down...";
				nn_shutdown( sock, endpointid);
				nn_close( sock);
				if (msg) nn_freemsg( msg);
				msg = 0;
				return;
			case ETIMEDOUT:
				throw std::runtime_error( "error receive (nanomsg: got timeout on socket");
		}
		try
		{
			std::string answer = handler->handleRequest( msg, msgsize);
			if (answer.size() > 5)
			{
				int bytes = nn_send( sock, answer.c_str(), answer.size(), 0);
				if ((std::size_t)bytes != answer.size())
				{
					const char* errmsg;
					switch (errno)
					{
						case EFAULT:
							errmsg = "error sending answer to client (nanomsg: buf is NULL or len is NN_MSG and the message pointer (pointed to by buf) is NULL";
						case EBADF:
							errmsg = "error sending answer to client (nanomsg: the provided socket is invalid";
						case ENOTSUP:
							errmsg = "error sending answer to client (nanomsg: the operation is not supported by this socket type";
						case EFSM:
							errmsg = "error sending answer to client (nanomsg: the operation cannot be performed on this socket at the moment because the socket is not in the appropriate state";
						case EAGAIN:
							errmsg = "error sending answer to client (nanomsg: non-blocking mode was requested and the message cannot be sent at the moment";
						case EINTR:
							errmsg = "error sending answer to client (nanomsg: the operation was interrupted by delivery of a signal before the message was sent";
						case ETIMEDOUT:
							errmsg = "error sending answer to client (nanomsg: timeout on socket";
						case ETERM:
							errmsg = "error sending answer to client (nanomsg: the library is terminating";
						default:
							errmsg = "error sending answer to client (nanomsg: unknown error)";
					}
					nn_shutdown( sock, endpointid);
					nn_close( sock);
					if (msg) nn_freemsg( msg);
					msg = 0;
					throw std::runtime_error( errmsg);
				}
			}
		}
		catch (std::bad_alloc& err)
		{
			nn_shutdown( sock, endpointid);
			nn_close( sock);
			if (msg) nn_freemsg( msg);
			msg = 0;
			throw err;
		}
		nn_shutdown( sock, endpointid);
		nn_close( sock);
		if (msg) nn_freemsg( msg);
		msg = 0;
	}
}

int main( int argc, const char* argv[])
{
	bool doExit = false;
	int argi = 1;
	std::vector<std::string> moduledirs;
	std::vector<std::string> modules;
	std::string storageconfig;
	try
	{
		// Parsing arguments:
		while (argi < argc)
		{
			if (0==std::strcmp( argv[argi], "-h") || 0==std::strcmp( argv[argi], "--help"))
			{
				printUsage();
				doExit = true;
			}
			if (0==std::strcmp( argv[argi], "-h") || 0==std::strcmp( argv[argi], "--help"))
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
			else if (argv[argi][0] == '-')
			{
				throw std::runtime_error( std::string( "unknown option ") + argv[argi]);
			}
			else
			{
				storageconfig = argv[argi];
				if (argi +1 != argc) throw std::runtime_error("too many arguments");
			}
		}
		if (doExit) return 0;

		// Create server request handler:
		if (storageconfig.empty())
		{
			throw std::runtime_error("too few arguments, missing storage config");
		}
		std::auto_ptr<strus::ModuleLoaderInterface>
			moduleLoader( strus::createModuleLoader());

		std::vector<std::string>::const_iterator
			di = moduledirs.begin(), de = moduledirs.end();
		for (; di != de; ++di)
		{
			moduleLoader->addModulePath( *di);
		}
		moduleLoader->addSystemModulePath();
		std::vector<std::string>::const_iterator
			mi = modules.begin(), me = modules.end();
		for (; mi != me; ++mi)
		{
			moduleLoader->loadModule( *mi);
		}
		std::auto_ptr<strus::StorageObjectBuilderInterface>
			storageBuilder( moduleLoader->createStorageObjectBuilder());
		std::auto_ptr<strus::AnalyzerObjectBuilderInterface>
			analyzerBuilder( moduleLoader->createAnalyzerObjectBuilder());

		std::auto_ptr<strus::RpcRequestHandlerInterface>
			requestHandler( strus::createRpcRequestHandler(
				storageBuilder.get(), analyzerBuilder.get()));
		(void)storageBuilder.release();
		(void)analyzerBuilder.release();

		// Start server:
		runServer( "tcp://*:7181", requestHandler.get());
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
	return -1;
}


