cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

# Patch for server.c/client.c to compile (not C99 because of non POSIX extensions)
set( CMAKE_C_FLAGS "-Wall -pedantic -Wfatal-errors -fPIC -O${STRUS_OPTIMIZATION_LEVEL}" )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( private_utils_source_files
	utils.cpp
	internationalization.cpp
)

set( server_source_files
	server.c
	hexdump.c
	rpcSerializer.cpp
	rpcRequestHandler.cpp
	rpcRequestHandler_gen.cpp
)

set( client_source_files
	rpcSerializer.cpp
	objects_gen.cpp
	rpcInterfaceStub.cpp
	rpcClientContext.cpp
	rpcClient.cpp
)

set( client_socket_source_files
	client.c
	hexdump.c
	rpcClientMessaging.cpp
)

include_directories(
        "${Boost_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/3rdParty/libuv/libuv-1.x/include"
	"${strusmodule_INCLUDE_DIRS}"
	"${strus_INCLUDE_DIRS}"
	"${strusanalyzer_INCLUDE_DIRS}" )

link_directories(
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/3rdParty/libuv"
	"${strusmodule_LIBRARY_DIRS}"
)


# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( strus_private_utils STATIC ${private_utils_source_files} )
target_link_libraries( strus_private_utils  "${Boost_LIBRARIES}" )

add_library( strus_rpc_client_socket SHARED ${client_socket_source_files} libstrus_rpc_client_socket.cpp )
target_link_libraries( strus_rpc_client_socket strus_private_utils dl uv )

add_library( strus_rpc_client SHARED ${client_source_files} libstrus_rpc_client.cpp )
target_link_libraries( strus_rpc_client strus_private_utils dl )

add_library( strus_rpc_server SHARED ${server_source_files} libstrus_rpc_server.cpp )
target_link_libraries( strus_rpc_server strus_private_utils strus_utils strus_module "${Boost_LIBRARIES}" uv dl )

set_target_properties(
    strus_rpc_client_socket
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

set_target_properties(
    strus_rpc_client
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

set_target_properties(
    strus_rpc_server
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

# ------------------------------
# PROGRAMS
# ------------------------------
add_executable( strusRpcServer strusRpcServer.cpp utils.cpp )
target_link_libraries( strusRpcServer  "${strusmodule_LIBRARIES}"  strus_rpc_server strus_error )

# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS strus_rpc_client_socket
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc_client
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc_server
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strusRpcServer
	   RUNTIME DESTINATION bin )


