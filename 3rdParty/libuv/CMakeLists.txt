cmake_minimum_required(VERSION 2.6)

# Patch for libuv to compile (not C99 because of non POSIX extensions and no-strict-aliasing)
set( CMAKE_C_FLAGS "-Wall -pedantic -Wfatal-errors -fPIC -fno-strict-aliasing -O${STRUS_OPTIMIZATION_LEVEL}" )

#
# This CMakeLists.txt file is a patched clone from the project https://github.com/aseprite/libuv-cmake
# 
set( LIBUVDIR ${PROJECT_SOURCE_DIR}/3rdParty/libuv/libuv-1.x )

include_directories(${LIBUVDIR}/include ${LIBUVDIR}/src)
set(SOURCES
  ${LIBUVDIR}/src/threadpool.c
  ${LIBUVDIR}/src/fs-poll.c
  ${LIBUVDIR}/src/inet.c
  ${LIBUVDIR}/src/uv-common.c
  ${LIBUVDIR}/src/version.c
)


if(WIN32)
  add_definitions(-DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0600 -D_CRT_SECURE_NO_WARNINGS)
  include_directories(${LIBUVDIR}/src/win)
  set(SOURCES ${SOURCES}
    ${LIBUVDIR}/src/win/async.c
    ${LIBUVDIR}/src/win/core.c
    ${LIBUVDIR}/src/win/dl.c
    ${LIBUVDIR}/src/win/error.c
    ${LIBUVDIR}/src/win/fs-event.c
    ${LIBUVDIR}/src/win/fs.c
    ${LIBUVDIR}/src/win/getaddrinfo.c
    ${LIBUVDIR}/src/win/handle.c
    ${LIBUVDIR}/src/win/loop-watcher.c
    ${LIBUVDIR}/src/win/pipe.c
    ${LIBUVDIR}/src/win/poll.c
    ${LIBUVDIR}/src/win/process-stdio.c
    ${LIBUVDIR}/src/win/process.c
    ${LIBUVDIR}/src/win/req.c
    ${LIBUVDIR}/src/win/signal.c
    ${LIBUVDIR}/src/win/stream.c
    ${LIBUVDIR}/src/win/tcp.c
    ${LIBUVDIR}/src/win/thread.c
    ${LIBUVDIR}/src/win/timer.c
    ${LIBUVDIR}/src/win/tty.c
    ${LIBUVDIR}/src/win/udp.c
    ${LIBUVDIR}/src/win/util.c
    ${LIBUVDIR}/src/win/winapi.c
    ${LIBUVDIR}/src/win/winsock.c)
else()
    if( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
       set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/linux-syscalls.c
           ${LIBUVDIR}/src/unix/linux-core.c
	   ${LIBUVDIR}/src/unix/linux-inotify.c
	 )
    elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
       set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/darwin.c
	 )
    elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD" )
       set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/freebsd.c
           ${LIBUVDIR}/src/unix/kqueue.c
	 )
    elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "OpenBSD" )
       set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/openbsd.c
	 )
    elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "NetBSD" )
        set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/netbsd.c
	 )
    elseif  ( ${CMAKE_SYSTEM_NAME} STREQUAL "SunOS" )
        set( SOURCES ${SOURCES}
           ${LIBUVDIR}/src/unix/sunos.c
         )
  endif()
  include_directories(${LIBUVDIR}/src/unix)
  set(SOURCES ${SOURCES}
    ${LIBUVDIR}/src/unix/async.c
    ${LIBUVDIR}/src/unix/core.c
    ${LIBUVDIR}/src/unix/dl.c
    ${LIBUVDIR}/src/unix/fs.c
    ${LIBUVDIR}/src/unix/getaddrinfo.c
    ${LIBUVDIR}/src/unix/loop-watcher.c
    ${LIBUVDIR}/src/unix/loop.c
    ${LIBUVDIR}/src/unix/pipe.c
    ${LIBUVDIR}/src/unix/poll.c
    ${LIBUVDIR}/src/unix/process.c
    ${LIBUVDIR}/src/unix/signal.c
    ${LIBUVDIR}/src/unix/stream.c
    ${LIBUVDIR}/src/unix/tcp.c
    ${LIBUVDIR}/src/unix/thread.c
    ${LIBUVDIR}/src/unix/timer.c
    ${LIBUVDIR}/src/unix/tty.c
    ${LIBUVDIR}/src/unix/udp.c)
endif()

add_library(uv ${SOURCES})
