#include "hexdump.h"

#define MAXDUMPSIZE 32

void strus_hexdump( FILE* output, const char* title, const unsigned char* data, size_t datasize)
{
	static const char HEX[] = "0123456789ABCDEF";
	size_t di = 0;
	size_t de = datasize;

	fprintf( output, "hexdump %s (size=%u):", title, (unsigned int)datasize);
	if (datasize == 0)
	{
		fprintf( output, "(empty)");
	}
	for (; di != de && di < MAXDUMPSIZE; ++di)
	{
		if (di % 16 == 0)
		{
			fprintf( output, "\n");
		}
		fprintf( output, "%c%c ", HEX[ data[di] / 16], HEX[ data[di] % 16]);
	}
	if (di != de)
	{
		fprintf( output, " ...");
	}
	fprintf( output, "\n");
}



