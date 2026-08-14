#include <stdio.h>

void debug(char *msg)
{
#ifdef DEBUG
	printf("\x1b[33m* debug: %s\n\x1b[0m", msg);
#endif
}
