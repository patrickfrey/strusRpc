cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( source_files
	libstrus_rpc.cpp
	serialize/rpcSerializer.cpp
	serialize/rpcRequestHandler.cpp
	serialize/rpcObjects.cpp
	serialize/rpcInterfaceStub.cpp
	serialize/rpcClient.cpp
)

include_directories(
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src"
        "${Boost_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/src/serialize"
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
add_library( strus_rpc_nanomsg SHARED  client/rpcClientMessaging.cpp libstrus_rpc_nanomsg.cpp )
target_link_libraries( strus_rpc_nanomsg dl nanomsg )

add_library( strus_rpc SHARED ${source_files} )
target_link_libraries( strus_rpc dl "${strusmodule_LIBRARIES}" )

set_target_properties(
    strus_rpc_nanomsg
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

set_target_properties(
    strus_rpc
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
install( TARGETS strus_rpc_nanomsg
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strusRpcServer
	   RUNTIME DESTINATION bin )


