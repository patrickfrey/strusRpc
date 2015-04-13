cmake_minimum_required(VERSION 2.6 FATAL_ERROR )

set( CMAKE_C_FLAGS "-std=gnu99 -g -O2 -pthread -Wall -pedantic -fPIC -include ${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/config/config.h" )

# --------------------------------------
# SOURCES AND INCLUDES
# --------------------------------------
set( source_files
    core/ep.c
    core/epbase.c
    core/global.c
    core/pipe.c
    core/poll.c
    core/sock.c
    core/sockbase.c
    core/symbol.c
    aio/ctx.c
    aio/fsm.c
    aio/poller.c
    aio/pool.c
    aio/timer.c
    aio/timerset.c
    aio/usock.c
    aio/worker.c
    utils/alloc.c
    utils/atomic.c
    utils/chunk.c
    utils/chunkref.c
    utils/clock.c
    utils/closefd.c
    utils/efd.c
    utils/err.c
    utils/glock.c
    utils/hash.c
    utils/list.c
    utils/msg.c
    utils/mutex.c
    utils/queue.c
    utils/random.c
    utils/sem.c
    utils/sleep.c
    utils/thread.c
    utils/wire.c
    devices/device.c
    protocols/utils/dist.c
    protocols/utils/excl.c
    protocols/utils/fq.c
    protocols/utils/lb.c
    protocols/utils/priolist.c
    protocols/bus/bus.c
    protocols/bus/xbus.c
    protocols/pipeline/push.c
    protocols/pipeline/pull.c
    protocols/pipeline/xpull.c
    protocols/pipeline/xpush.c
    protocols/pair/pair.c
    protocols/pair/xpair.c
    protocols/pubsub/pub.c
    protocols/pubsub/sub.c
    protocols/pubsub/trie.c
    protocols/pubsub/xpub.c
    protocols/pubsub/xsub.c
    protocols/reqrep/req.c
    protocols/reqrep/rep.c
    protocols/reqrep/task.c
    protocols/reqrep/xrep.c
    protocols/reqrep/xreq.c
    protocols/survey/respondent.c
    protocols/survey/surveyor.c
    protocols/survey/xrespondent.c
    protocols/survey/xsurveyor.c
    transports/utils/backoff.c
    transports/utils/dns.c
    transports/utils/iface.c
    transports/utils/literal.c
    transports/utils/port.c
    transports/utils/streamhdr.c
    transports/inproc/binproc.c
    transports/inproc/cinproc.c
    transports/inproc/inproc.c
    transports/inproc/ins.c
    transports/inproc/msgqueue.c
    transports/inproc/sinproc.c
    transports/ipc/aipc.c
    transports/ipc/bipc.c
    transports/ipc/cipc.c
    transports/ipc/ipc.c
    transports/ipc/sipc.c
    transports/tcp/atcp.c
    transports/tcp/btcp.c
    transports/tcp/ctcp.c
    transports/tcp/stcp.c
    transports/tcp/tcp.c
)

include_directories(
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/aio"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/devices"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/protocols"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/transports"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/core"
	"${PROJECT_SOURCE_DIR}/3rdParty/nanomsg-0.5-beta/src/utils"
)

link_directories(
)

# -------------------------------------------
# LIBRARY
# -------------------------------------------
add_library( nanomsg SHARED ${source_files} )
target_link_libraries( nanomsg dl )
set_target_properties(
    nanomsg
    PROPERTIES
    DEBUG_POSTFIX "_d"
    SOVERSION "0.2"
    VERSION "0.2.1"
)


# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS nanomsg
           LIBRARY DESTINATION ${LIB_INSTALL_DIR}/strus )

