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
#include "rpcSerializer.hpp"
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <netinet/in.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

#undef STRUS_LOWLEVEL_DEBUG

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
	std::cerr << "-R|--resourcedir <DIR>" << std::endl;
	std::cerr << "    Define a resource path <DIR> for the analyzer" << std::endl;
	std::cerr << "-p|--port <PORT>" << std::endl;
	std::cerr << "    Define the port to listen for requests as <PORT> (default 7181)" << std::endl;
	std::cerr << "-s|--storage <CONFIG>" << std::endl;
	std::cerr << "    Define configuration <CONFIG> of storage hosted by this server" << std::endl;
}

static strus::ModuleLoaderInterface* g_moduleLoader = 0;
static strus::StorageObjectBuilderInterface* g_storageObjectBuilder = 0;
static strus::AnalyzerObjectBuilderInterface* g_analyzerObjectBuilder = 0;
static strus::StorageClientInterface* g_storageClient = 0;

struct handler_context
{
	strus::RpcRequestHandlerInterface* obj;
	std::string* buf;
	uint32_t msgsize;
	uint32_t msgsizebuf;
	uint32_t msgsizepos;
};

static void destroy_handler_context( handler_context* ctx)
{
	if (ctx->obj)
	{
		delete ctx->obj;
		ctx->obj = 0;
	}
	if (ctx->buf)
	{
		delete ctx->buf;
		ctx->buf = 0;
	}
	std::free( ctx);
}

static void reset_handler_context_input( handler_context* ctx)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "reset handler context input" << std::endl;
#endif
	ctx->buf->clear();
	ctx->msgsize = 0;
	ctx->msgsizebuf = 0;
	ctx->msgsizepos = 0;
}

static int init_handler_context( handler_context* ctx)
{
	try
	{
		ctx->obj = strus::createRpcRequestHandler(
				g_storageObjectBuilder, g_analyzerObjectBuilder, g_storageClient);
		ctx->buf = new std::string();
		ctx->msgsize = 0;
		ctx->msgsizebuf = 0;
		ctx->msgsizepos = 0;
	}
	catch (const std::runtime_error& err)
	{
		std::cout << "runtime error initializing handler context: " << err.what() << std::endl;
		return 1;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "memory allocation error initializing handler context: " << err.what() << std::endl;
		return 2;
	}
	catch (const std::exception& err)
	{
		std::cout << "exception initializing handler context: " << err.what() << std::endl;
		return 3;
	}
	catch (...)
	{
		std::cout << "unknown exception initializing handler context" << std::endl;
		return 4;
	}
	return 0;
}

static uint32_t unpackMessageLen( char const*& itr, const char* end)
{
	if (itr+4 > end) throw std::runtime_error( "message to small to encode message length");
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	return ntohl( val);
}

static int handler_context_consume_input( handler_context* ctx, struct evbuffer *input)
{
	int res = 0;
	if (!ctx->obj)
	{
		int ec;
		if (0!=(ec=init_handler_context( ctx)))
		{
			return 10+ec;
		}
	}
	if (!ctx->msgsize)
	{
		while (ctx->msgsizepos < sizeof(ctx->msgsizebuf)
			&& 0<(res=evbuffer_remove( input, (char*)&ctx->msgsizebuf + ctx->msgsizepos, sizeof(ctx->msgsizebuf)-ctx->msgsizepos)))
		{
			ctx->msgsizepos += res;
			if (ctx->msgsizepos == sizeof(ctx->msgsizebuf)) break;
		}
		if (res == 0) return 1;
		if (res < 0) return -1;
	
		ctx->msgsize = ntohl( ctx->msgsizebuf);
		if (!ctx->msgsize) return -1;
	}
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "consumed input message size " << ctx->msgsize << std::endl;
#endif
	enum {bufsize=256};
	char buf[ bufsize];
	unsigned int fetchsize = bufsize;
	if (ctx->msgsize < ctx->buf->size() + fetchsize)
	{
		fetchsize = ctx->msgsize - ctx->buf->size();
	}
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "consumed input fetch size " << fetchsize << std::endl;
#endif
	while (0<(res=evbuffer_remove( input, buf, fetchsize)))
	{
		ctx->buf->append( buf, res);
		if (ctx->msgsize == ctx->buf->size()) break;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "consumed input buf size " << ctx->buf->size() << std::endl;
#endif
	}
	if (res > 0) return 0;
	if (res == 0) return 1;
	return -1;
}

static int handler_context_process_input( handler_context* ctx, struct evbuffer *output)
{
	try
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "got request [" << ctx->buf->size() << " bytes]" << std::endl;
#endif
		std::string answer;
		if (ctx->buf->size() > 0 && ctx->buf->at(0) == (char)0xFF)
		{
#ifdef STRUS_LOWLEVEL_DEBUG
			std::cerr << "got multipart request" << std::endl;
#endif
			char const* itr = ctx->buf->c_str()+1;
			const char* end = itr + ctx->buf->size() -1;
			while (itr < end)
			{
				uint32_t msglen = unpackMessageLen( itr, end);
#ifdef STRUS_LOWLEVEL_DEBUG
				std::cerr << "call request handler [" << msglen << " bytes]" << std::endl;
#endif
				answer = ctx->obj->handleRequest( itr, msglen);
				if (answer.size() > 0)
				{
					if (answer[0] == (char)strus::MsgTypeAnswer && itr+msglen != end)
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
			std::cerr << "call request handler [" << ctx->buf->size() << " bytes]" << std::endl;
#endif
			answer = ctx->obj->handleRequest( ctx->buf->c_str(), ctx->buf->size());
		}
		uint32_t answersize = htonl( answer.size());
		if (-1==evbuffer_add( output, &answersize, sizeof(answersize)))
		{
			std::cerr << "error when copying request answer to output ... closing connection" << std::endl;
			return 7;
		}
		if (-1==evbuffer_add( output, answer.c_str(), answer.size()))
		{
			std::cerr << "error when copying request answer to output ... closing connection" << std::endl;
			return 8;
		}

#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "request reply [" << answer.size() << " bytes] sent back" << std::endl;
#endif
		return 0;
	}
	catch (const std::runtime_error& err)
	{
		std::cout << "unrecoverable runtime error processing input: " << err.what() << " ... closing connection now" << std::endl;
		return 1;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "memory allocation processing input: " << err.what() << " ... closing connection now" << std::endl;
		return 2;
	}
	catch (const std::exception& err)
	{
		std::cout << "unrecoverable exception processing input: " << err.what() << " ... closing connection now" << std::endl;
		return 3;
	}
	catch (...)
	{
		std::cout << "unknown unrecoverable exception processing input" << std::endl;
		return 4;
	}
	return 0;
}

static void handler_read_cb( struct bufferevent *bev, void *ctx_)
{
	/* This callback is invoked when there is data to read on bev. */
	handler_context* ctx = (handler_context*)ctx_;
	struct evbuffer *input = bufferevent_get_input( bev);
	struct evbuffer *output = bufferevent_get_output( bev);

#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "handler got data" << std::endl;
#endif
	// Consume input:
	int ec = handler_context_consume_input( ctx, input);
	if (ec < 0)
	{
		// ... got unrecoverable error
		bufferevent_free( bev);
		destroy_handler_context( ctx);
	}
	if (ec > 0)
	{
		// ... input not yet complete
		return;
	}
	// Handle the request:
	if (0!=handler_context_process_input( ctx, output))
	{
		bufferevent_free( bev);
		destroy_handler_context( ctx);
		return;
	}
	if (0>bufferevent_write_buffer( bev, output))
	{
		perror( "error writing buffer with request answer");
		bufferevent_free( bev);
		destroy_handler_context( ctx);
		return;
	}
	reset_handler_context_input( ctx);
}

static void handler_event_cb( struct bufferevent *bev, short events, void *ctx_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "got event" << std::endl;
#endif
	handler_context* ctx = (handler_context*)ctx_;
	if (events & BEV_EVENT_ERROR)
	{
		perror( "error from bufferevent");
	}
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR))
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		if (0!=(events & BEV_EVENT_EOF)) std::cerr << "got eof" << std::endl;
#endif
		bufferevent_free( bev);
		destroy_handler_context( ctx);
	}
}

static void signal_cb( evutil_socket_t sig, short events, void *user_data)
{
	struct event_base* base = (struct event_base*)user_data;
	std::cerr << "got an interrupt signal, exiting now" << std::endl;

	event_base_loopexit( base, NULL);
}

static void accept_conn_cb(
	struct evconnlistener *listener,
	evutil_socket_t fd, struct sockaddr *address, int socklen,
	void* /*context for acceptor*/)
{
	/* We got a new connection! Set up a bufferevent for it. */
	struct event_base *base = evconnlistener_get_base( listener);
	struct bufferevent *bev = bufferevent_socket_new( base, fd, BEV_OPT_CLOSE_ON_FREE);

	handler_context* ctx = (handler_context*)std::calloc( 1, sizeof( handler_context));
	if (!ctx)
	{
		std::cerr << "out of memory on connection accept, refusing connection." << std::endl;
		event_base_loopexit( base, NULL);
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "accept connection" << std::endl;
#endif
		bufferevent_setcb( bev, handler_read_cb, NULL, handler_event_cb, ctx);
		bufferevent_enable( bev, EV_READ|EV_WRITE);
	}
}

static void accept_error_cb( struct evconnlistener *listener, void *ctx)
{
	struct event_base *base = evconnlistener_get_base( listener);
	int err = EVUTIL_SOCKET_ERROR();
	std::cerr << "got an error " << err << " (" << evutil_socket_error_to_string(err) << ") on the listener, shutting down." << std::endl;

	event_base_loopexit( base, NULL);
}

// Run the server (the code that served as 'inspiration' for the strus rpc server can be found
// at http://www.wangafu.net/~nickm/libevent-book/Ref8_listener.html
static int runServer( int port)
{
	struct event_base *base = event_base_new();
	if (!base)
	{
		puts( "couldn't open event base");
		return 1;
	}

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	/* This is an INET address */
	sin.sin_family = AF_INET;
	/* Listen on 0.0.0.0 */
	sin.sin_addr.s_addr = htonl(0);
	/* Listen on the given port. */
	sin.sin_port = htons(port);

	struct evconnlistener *listener = evconnlistener_new_bind( base, accept_conn_cb, NULL,
		LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
		(struct sockaddr*)&sin, sizeof(sin));
	if (!listener)
	{
		perror( "couldn't create listener");
		return 2;
	}
	evconnlistener_set_error_cb( listener, accept_error_cb);

	struct event *signal_event = evsignal_new( base, SIGINT, signal_cb, (void *)base);
	if (!signal_event || event_add( signal_event, NULL)<0)
	{
		perror( "could not create signal event");
		return 3;
	}
	std::cerr << "strus RPC server listening on port " << port << std::endl;
	event_base_dispatch( base);
	event_base_free( base);
	std::free( signal_event);
	std::free( listener);
	return 0;
}

int main( int argc, const char* argv[])
{
	bool doExit = false;
	int argi = 1;
	std::vector<std::string> moduledirs;
	std::vector<std::string> modules;
	std::vector<std::string> resourcedirs;
	std::string storageconfig;
	int port = 7181; //... default port
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
				port = atoi( argv[argi]);
				if (port <= 0 || port > 65535)
				{
					throw std::runtime_error( "invalid port");
				}
			}
			else if (0==std::strcmp( argv[argi], "-s") || 0==std::strcmp( argv[argi], "--storage"))
			{
				if (!storageconfig.empty()) throw std::runtime_error("option --storage specified twice");
				++argi;
				if (argi == argc) throw std::runtime_error("option --storage expects argument (storage configuration string)");
				storageconfig.append( argv[argi]);
				if (storageconfig.empty()) throw std::runtime_error("option --storage with empty argument");
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
			storageClient.reset( g_storageObjectBuilder->createStorageClient( storageconfig));
			std::cerr << "strus RPC server is hosting storage '" << storageconfig << "'" << std::endl;
			g_storageClient = storageClient.get();
		}

		// Start server:
		if (!!runServer( port))
		{
			throw std::runtime_error( "failed to start server");
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


