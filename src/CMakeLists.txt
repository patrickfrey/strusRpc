cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( server_source_files
	serialize/rpcSerializer.cpp
	serialize/rpcRequestHandler.cpp
)

set( client_source_files
	serialize/rpcSerializer.cpp
	serialize/rpcObjects.cpp
	serialize/rpcInterfaceStub.cpp
	serialize/rpcClient.cpp
)

include_directories(
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src"
        "${Boost_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/src/serialize"
	"${PROJECT_SOURCE_DIR}/src/client"
	"${strusmodule_INCLUDE_DIRS}"
	"${strus_INCLUDE_DIRS}"
	"${strusanalyzer_INCLUDE_DIRS}" )

link_directories(
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/"
	"${strusmodule_LIBRARY_DIRS}"
)


# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( strus_rpc_client_nanomsg SHARED  client/rpcClientMessaging.cpp libstrus_rpc_client_nanomsg.cpp )
target_link_libraries( strus_rpc_client_nanomsg dl nanomsg )

add_library( strus_rpc_client SHARED ${client_source_files} )
target_link_libraries( strus_rpc_client dl )

add_library( strus_rpc_server SHARED ${server_source_files} )
target_link_libraries( strus_rpc_server dl "${strusmodule_LIBRARIES}" )

set_target_properties(
    strus_rpc_client_nanomsg
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
add_executable( strusRpcServer server/strusRpcServer.cpp )
target_link_libraries( strusRpcServer  nanomsg strus_module )

# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS strus_rpc_client_nanomsg
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc_client
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc_server
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strusRpcServer
	   RUNTIME DESTINATION bin )


