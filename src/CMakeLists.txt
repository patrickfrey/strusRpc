cmake_minimum_required(VERSION 2.8 FATAL_ERROR )

string(REGEX REPLACE "-std=c[89]9" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
MESSAGE( STATUS "C compilation flags for libuv (remove C99): '${CMAKE_C_FLAGS}'" )
# ... patch for libuv to compile (not C99 because of non POSIX extensions and no-strict-aliasing)

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( private_utils_source_files
	traceUtils.cpp
	${CMAKE_CURRENT_BINARY_DIR}/internationalization.cpp
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
	hexdump.c
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
        ${Boost_INCLUDE_DIRS}
	"${RPC_INCLUDE_DIRS}"
	"${LIBUV_INCLUDE_DIRS}"
	"${strusbase_INCLUDE_DIRS}"
	"${strus_INCLUDE_DIRS}"
	"${strusanalyzer_INCLUDE_DIRS}"
	"${strustrace_INCLUDE_DIRS}"
	"${strusmodule_INCLUDE_DIRS}"
	"${CMAKE_CURRENT_BINARY_DIR}"
)

link_directories(
	"${RPC_LIBRARY_DIRS}"
	"${LIBUV_LIBRARY_DIRS}"
        ${Boost_LIBRARY_DIRS}
	"${strusbase_LIBRARY_DIRS}"
	"${strus_LIBRARY_DIRS}"
	"${strusanalyzer_LIBRARY_DIRS}"
	"${strusmodule_LIBRARY_DIRS}"
)


# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( strusrpc_private_utils STATIC ${private_utils_source_files} )
target_link_libraries( strusrpc_private_utils  "${Boost_LIBRARIES}" )
set_property( TARGET strusrpc_private_utils PROPERTY POSITION_INDEPENDENT_CODE TRUE )

add_library( strus_rpc_client_socket SHARED ${client_socket_source_files} libstrus_rpc_client_socket.cpp )
target_link_libraries( strus_rpc_client_socket strusrpc_private_utils ${Intl_LIBRARIES} ${CMAKE_DL_LIBS} uv )

add_library( strus_rpc_client SHARED ${client_source_files} libstrus_rpc_client.cpp )
target_link_libraries( strus_rpc_client strusrpc_private_utils strus_base ${CMAKE_DL_LIBS} ${Intl_LIBRARIES} )

# some old platforms still have real-time functions (clock_getres, clock_gettime) in librt.so
# and not in the C library
find_library( LIBRT_LIBRARIES rt )
if(LIBRT_LIBRARIES)
    target_link_libraries( strus_rpc_client_socket ${LIBRT_LIBRARIES} )
    target_link_libraries( strus_rpc_client ${LIBRT_LIBRARIES} )
endif()
target_link_libraries( strus_rpc_client_socket ${CMAKE_THREAD_LIBS_INIT} )

set_target_properties(
    strus_rpc_client_socket
    PROPERTIES
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

set_target_properties(
    strus_rpc_client
    PROPERTIES
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
    SOVERSION "${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}"
    VERSION ${STRUS_VERSION}
)

# ------------------------------
# PROGRAMS
# ------------------------------
add_executable( strusRpcServer strusRpcServer.cpp ${server_source_files} )
target_link_libraries( strusRpcServer  "${Boost_LIBRARIES}" strus_storage_objbuild strusrpc_private_utils strus_error strus_base strus_module uv ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${Intl_LIBRARIES} )
if(LIBRT_LIBRARIES)
    target_link_libraries( strusRpcServer ${LIBRT_LIBRARIES} )
endif()
# FreeBSD needs kernel data access library for libuv (-libkvm)
find_library( LIBKVM_LIBRARIES kvm )
if(LIBKVM_LIBRARIES)
	target_link_libraries( strusRpcServer ${LIBKVM_LIBRARIES} )
endif()

# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS strus_rpc_client_socket
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strus_rpc_client
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

install( TARGETS strusRpcServer
	   RUNTIME DESTINATION bin )


