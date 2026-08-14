#include <stdio.h>

void debug(char *msg)
{
#ifdef DEBUG
	printf("\x1b[33m* debug: %s\n\x1b[0m", msg);
#endif
}

void help()
{
	printf("\x1b[1;1H\x1b[2J");

	FILE *f = fopen("help.txt", "rb");

	char buf[1024] = "";
	int b = 0;
	while (fgets(buf, 1024, f))
		printf("%s", buf);

	fclose(f);
}
