strusRpc	 {#mainpage}
========

The project strusRpc provides a proxy interface to StorageObjectBuilderInterface
and AnalyzerObjectBuilderInterface and all the objects created from these interfaces.
The calls to these interfaces are forwarded via a proprietary RPC protocol to an rpcServer 
process. With RPC you can use strus in the context of a webserver, where objects should
not persist beyond a single connection. It also allow to obey the rules of a webserver,
that may not allow the loading of modules not declared in the webserver configuration.

How to use RPC in a client
--------------------------
The strus [RPC client interface] (@ref strus::RpcClientInterface) is constructed by calling the
function [createRpcClient](@ref strus::createRpcClient) (rpc_client.hpp) with a message
handler object [RpcClientMessagingInterface](@ref strus::RpcClientMessagingInterface) as parameter.
The message handler based on sockets can be created by calling the function
[createRpcClientMessaging](@ref strus::createRpcClientMessaging) (rpc_client_socket.hpp).


How to start the rpc server
---------------------------
The program strusRpcServer implements the rpc server. See the man pages or use the option -h to
get the possible options of the program.



