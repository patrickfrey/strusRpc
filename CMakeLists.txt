cmake_minimum_required(VERSION 2.8 FATAL_ERROR )

# must be done BEFORE project in order to work!
include(cmake/install_prefix.cmake)

# Project globals:
project( StrusRpc )
set( STRUS_RPC_PROTOCOL_WITH_CRC32_CHECKSUM 1 )
set( STRUS_RPC_PROTOCOL_WITH_TYPED_ATOMS 0 )
set( STRUS_MAJOR_VERSION 0 )
set( STRUS_MINOR_VERSION 15 )
set( STRUS_PATCH_VERSION 4 )
set( STRUS_VERSION ${STRUS_MAJOR_VERSION}.${STRUS_MINOR_VERSION}.${STRUS_PATCH_VERSION} )

if(NOT STRUS_ALL)
include(cmake/dist.cmake)
include(cmake/LinuxDistribution.cmake)
include( cmake/build_rules.cmake )
include( cmake/boost.cmake)
include( cmake/intl.cmake )
find_package( Threads )
include( cmake/find_strus_package.cmake )
include( cmake/link_rules.cmake )
endif()

find_strus_package( base )
find_strus_package( core )
find_strus_package( analyzer )
find_strus_package( trace )
find_strus_package( module )

set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
configure_file( "${PROJECT_SOURCE_DIR}/include/strus/versionRpc.hpp.in"  "${CMAKE_CURRENT_BINARY_DIR}/include/strus/versionRpc.hpp"  @ONLY )
configure_file( "${PROJECT_SOURCE_DIR}/src/rpcProtocolDefines.hpp.in"  "${CMAKE_CURRENT_BINARY_DIR}/src/rpcProtocolDefines.hpp"  @ONLY )
configure_file( "${PROJECT_SOURCE_DIR}/dist/obs/deploy_to_obs.sh.in"  "${PROJECT_SOURCE_DIR}/dist/obs/deploy_to_obs.sh"  @ONLY )
configure_file( "${PROJECT_SOURCE_DIR}/dist/archlinux/PKGBUILD.in"  "${PROJECT_SOURCE_DIR}/dist/archlinux/PKGBUILD"  @ONLY )
configure_file( "${PROJECT_SOURCE_DIR}/dist/obs/strusrpc.dsc.in"  "${PROJECT_SOURCE_DIR}/dist/obs/strusrpc.dsc"  @ONLY )
configure_file( "${PROJECT_SOURCE_DIR}/dist/redhat/strusrpc.spec.in"  "${PROJECT_SOURCE_DIR}/dist/redhat/strusrpc.spec"  @ONLY )

set( STRUS_GETTEXT_PACKAGE "strus-dom" )	#... 1st parameter of bindtextdomain(...)
set( STRUS_GETTEXT_LOCALEDIR "" )			#... 2nd parameter of bindtextdomain(...)
configure_file( "${PROJECT_SOURCE_DIR}/src/internationalization.cpp.in"  "${PROJECT_SOURCE_DIR}/src/internationalization.cpp"  @ONLY )

enable_testing()

# Path declarations:
set( RPC_INCLUDE_DIRS                   "${CMAKE_CURRENT_BINARY_DIR}/include"  "${PROJECT_SOURCE_DIR}/include" )
set( RPC_LIBRARY_DIRS                    "${CMAKE_CURRENT_BINARY_DIR}/src" )
set( LIBUV_INCLUDE_DIRS                 "${PROJECT_SOURCE_DIR}/3rdParty/libuv/libuv-1.x/include" )
set( LIBUV_LIBRARY_DIRS                 "${CMAKE_CURRENT_BINARY_DIR}/3rdParty/libuv" )
set( MAIN_SOURCE_DIR                     "${PROJECT_SOURCE_DIR}/src" )
set( MAIN_TESTS_DIR                        "${PROJECT_SOURCE_DIR}/tests" )

# Subdirectories:
add_subdirectory( 3rdParty )
add_subdirectory( src )
  
if(NOT STRUS_ALL)
include( cmake/report_build_settings.cmake )
endif()

# Install header files:
install(DIRECTORY include/strus
          DESTINATION include
          FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/strus"
          DESTINATION include
          FILES_MATCHING PATTERN "*.hpp")
if(NOT STRUS_ALL)
include( cmake/standard_targets.cmake )
endif()
