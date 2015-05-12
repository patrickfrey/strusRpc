cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( server_source_files
	utils.cpp
	loadGlobalStatistics.cpp
	rpcSerializer.cpp
	rpcRequestHandler.cpp
	rpcRequestHandler_gen.cpp
)

set( client_source_files
	utils.cpp
	rpcSerializer.cpp
	objects_gen.cpp
	rpcInterfaceStub.cpp
	rpcClientContext.cpp
	rpcClient.cpp
)

include_directories(
	"${libevent_INCLUDE_DIRS}"
        "${Boost_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/include"
	"${strusmodule_INCLUDE_DIRS}"
	"${strus_INCLUDE_DIRS}"
	"${strusanalyzer_INCLUDE_DIRS}" )

link_directories(
	"${libevent_LIBRARY_DIRS}"
	"${PROJECT_SOURCE_DIR}/src"
	"${strusmodule_LIBRARY_DIRS}"
)


# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( strus_rpc_client_socket SHARED  rpcClientMessaging.cpp libstrus_rpc_client_socket.cpp )
target_link_libraries( strus_rpc_client_socket dl "${libevent_LIBRARIES}" )

add_library( strus_rpc_client SHARED ${client_source_files} libstrus_rpc_client.cpp )
target_link_libraries( strus_rpc_client dl )

add_library( strus_rpc_server SHARED ${server_source_files} libstrus_rpc_server.cpp )
target_link_libraries( strus_rpc_server dl "${strusmodule_LIBRARIES}" "${Boost_LIBRARIES}"  )

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
add_executable( strusRpcServer strusRpcServer.cpp )
target_link_libraries( strusRpcServer  "${libevent_LIBRARIES}"  "${strusmodule_LIBRARIES}"  strus_rpc_server )

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


