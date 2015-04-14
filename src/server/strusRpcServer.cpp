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
#include "strus/lib/rpc.hpp"
#include "strus/lib/module.hpp"
#include "strus/rpcRequestHandlerInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "strus/analyzerObjectBuilderInterface.hpp"
#include "strus/versionRpc.hpp"
#include <nn.h>
#include <pipeline.h>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

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

static std::auto_ptr<StorageClientInterface> g_storageclient;
class LocalStorageClient
	:public StorageClientInterface
{
public:
	LocalStorageClient(){}

	virtual ~StorageClientInterface(){}

	virtual void close(){};

	virtual PostingIteratorInterface*
		createTermPostingIterator(
			const std::string& type,
			const std::string& value) const
	{
		return g_storageclient->createTermPostingIterator( type, value);
	}

	virtual ForwardIteratorInterface*
		createForwardIterator(
			const std::string& type) const
	{
		return g_storageclient->createForwardIterator( type);
	}

	virtual InvAclIteratorInterface*
		createInvAclIterator(
			const std::string& username) const
	{
		return g_storageclient->createInvAclIterator( username);
	}

	virtual GlobalCounter globalNofDocumentsInserted() const
	{
		return g_storageclient->globalNofDocumentsInserted();
	}

	virtual Index localNofDocumentsInserted() const
	{
		return g_storageclient->localNofDocumentsInserted();
	}

	virtual GlobalCounter globalDocumentFrequency(
			const std::string& type,
			const std::string& term) const
	{
		return g_storageclient->globalDocumentFrequency( type, term);
	}

	virtual Index localDocumentFrequency(
			const std::string& type,
			const std::string& term) const
	{
		return g_storageclient->localDocumentFrequency( type, term);
	}

	virtual Index maxDocumentNumber() const
	{
		return g_storageclient->maxDocumentNumber();
	}

	virtual Index documentNumber( const std::string& docid) const
	{
		return g_storageclient->documentNumber( docid);
	}

	virtual MetaDataReaderInterface* createMetaDataReader() const
	{
		return g_storageclient->createMetaDataReader();
	}

	virtual AttributeReaderInterface* createAttributeReader() const
	{
		return g_storageclient->createAttributeReader();
	}

	virtual DocnoRangeAllocatorInterface* createDocnoRangeAllocator()
	{
		return g_storageclient->createDocnoRangeAllocator();
	}

	virtual StorageTransactionInterface* createTransaction()
	{
		return g_storageclient->createTransaction();
	}

	virtual PeerStorageTransactionInterface* createPeerStorageTransaction()
	{
		return g_storageclient->createPeerStorageTransaction();
	}

	virtual void defineStoragePeerInterface(
			const StoragePeerInterface* storagePeer,
			bool doPopulateInitialState)
	{
		g_storageclient->defineStoragePeerInterface( storagePeer, doPopulateInitialState);
	}

	virtual StorageDocumentInterface* createDocumentChecker(
			const std::string& docid,
			const std::string& logfilename) const
	{
		return g_storageclient->createDocumentChecker( docid, logfilename);
	}

	virtual void checkStorage( std::ostream& errorlog) const
	{
		g_storageclient->checkStorage( errorlog);
	}

	virtual StorageDumpInterface* createDump() const
	{
		return g_storageclient->createDump();
	}
};


class ServerStorageObjectBuilder
	:public StorageObjectBuilderInterface
{
public:
	explicit ServerStorageObjectBuilder( StorageObjectBuilderInterface* builder)
		:m_builder(builder)
	{}

	virtual ~ServerStorageObjectBuilder(){}

	virtual const StorageInterface* getStorage() const
	{
		return m_builder->getStorage();
	}

	virtual const DatabaseInterface* getDatabase( const std::string& config) const
	{
		return m_builder->getDatabase( config);
	}

	virtual const QueryProcessorInterface* getQueryProcessor() const
	{
		return m_builder->getQueryProcessor();
	}

	virtual StorageClientInterface* createStorageClient( const std::string& config) const
	{
		if (config.empty())
		{
			return new LocalStorageClient();
		}
		else
		{
			return m_builder->createStorageClient( config);
		}
	}

	virtual StorageAlterMetaDataTableInterface* createAlterMetaDataTable( const std::string& config) const
	{
		return m_builder->createAlterMetaDataTable( config);
	}

	virtual QueryEvalInterface* createQueryEval() const
	{
		return m_builder->createQueryEval();
	}

private:
	StorageObjectBuilderInterface* m_builder;
};

void serverNode( const char *url, RpcRequestHandlerInterface* handler)
{
	int sock = nn_socket( AF_SP, NN_PULL);
	if (sock >= 0) throw std::runtime_error( "failed to create socket");
	if (nn_bind( sock, url) < 0) throw std::runtime_error( "failed to bind to socket");
	for (;;)
	{
		char* buf = NULL;
		int bytes = nn_recv( sock, &buf, NN_MSG, 0);
		if (bytes < 0)
		{
			std::cerr << "Failed to receive message" << std::endl;
			continue;
		}
		std::string answer = handler->handleRequest( buf);
		if (answer.size() > 5)
		{
			int bytes = nn_send( sock, answer.c_str(), answer.size(), 0);
			if (bytes != answer.size())
			{
				std::cerr << "Failed to send message" << std::endl;
				
			}
		}
	}
}

int main( int argc, const char* argv[])
{
	int rt = 0;
	bool doExit = false;
	int argi = 1;
	std::vector<std::string> moduledirs;
	std::vector<std::string> modules;
	std::string storageconfig;
	try
	{
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
		if (storageconfig.empty())
		{
			throw std::runtime_error("too few arguments, missing storage config");
		}
		std::auto_ptr<ModuleLoaderInterface> moduleLoader( createModuleLoader());

		std::vector<std::string>::const_iterator di = moduledirs.begin(), de = moduledirs.end();
		for (; di != de; ++di)
		{
			moduleLoader.addModulePath( *mi);
		}
		moduleLoader.addSystemModulePath();
		std::vector<std::string>::const_iterator mi = modules.begin(), me = modules.end();
		for (; mi != me; ++mi)
		{
			moduleLoader.loadModule( *mi);
		}
		g_storageclient.reset( moduleLoader.createStorageClient( storageconfig));
		std::auto_ptr<StorageObjectBuilderInterface>
			storageBuilderGlobal( moduleLoader.createStorageObjectBuilder());
		std::auto_ptr<AnalyzerObjectBuilderInterface>
			analyzerBuilder( moduleLoader.createAnalyzerObjectBuilder());
		std::auto_ptr<StorageObjectBuilderInterface>
			storageBuilder( new ServerStorageObjectBuilder( storageBuilderGlobal.get()));

		std::auto_ptr<RpcRequestHandlerInterface>
			requestHandler( createRpcRequestHandler(
				storageBuilder.get(), analyzerBuilder.get()));
		(void)storageBuilder.release();
		(void)analyzerBuilder.release();

		serverNode( "tcp://*:7181", requestHandler.get());
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


