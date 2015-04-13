cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( source_files
	libstrus_rpc.cpp
	rpcSerializer.cpp
	rpcServer.cpp
	rpcObjects.cpp
	rpcRemoteEndPoint.cpp
	rpcInterfaceStub.cpp
)

include_directories(
        "${Boost_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/include"
	"${strusmodule_INCLUDE_DIRS}"
	"${strus_INCLUDE_DIRS}"
	"${strusanalyzer_INCLUDE_DIRS}" )

link_directories(
	"${PROJECT_SOURCE_DIR}/src"
)


# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( strus_rpc SHARED ${source_files} )
target_link_libraries( strus_rpc dl "${strusmodule_LIBRARIES}" )
set_target_properties(
    strus_rpc
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)


# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS strus_rpc
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

