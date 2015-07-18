#include "server.h"
#include <stdlib.h>

struct strus_connection_t
{
	enum {
		CTX_READDATASIZE0,
		CTX_READDATASIZE1,
		CTX_READDATASIZE2,
		CTX_READDATA,
		CTX_PROCESS,
		CTX_TERMINATED
	} state;

	uv_tcp_t tcp;
	uv_write_t write_req;
	strus_globalctx_t* glbctx;
	unsigned char* readbuf;
	size_t readbufsize;
};

static strus_connection_t* strus_alloc_connection( uv_tcp_t tcp, uv_write_t write_req, strus_globalctx_t* glbctx);
static void strus_free_connection( strus_connection_t* ctx);



strus_connection_t* strus_alloc_connection( uv_tcp_t tcp, uv_write_t write_req, strus_globalctx_t* glbctx)
{
	strus_connection_t* rt = (strus_connection_t*)calloc( 1, sizeof( strus_connection_t));
	rt->tcp = tcp;
	rt->write_req = write_req;
	rt->glbctx = glbctx;
}

void strus_free_connection( strus_connection_t* ctx)
{
	if (ctx)
	{
		if (ctx->readbuf) free( ctx->readbuf);
		free( ctx);
	}
}


int strus_run_server( unsigned int nofThreads, strus_globalctx_t* glbctx)
{
	
}


