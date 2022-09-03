#include <assert.h>
#include "io.h"

int main()
{
	char bytes[256];
	int i;

	for (i = 0; i < 256; i++)
		bytes[i] = i;

	writefile("bytes.bin", bytes, 256);

	char *bytes2;
	int len;

	bytes2 = readfile("bytes.bin", &len);
	assert(len == 256);

	for (i = 0; i < 256; i++)
		assert(bytes[i] == bytes2[i]);

	return 0;
}

