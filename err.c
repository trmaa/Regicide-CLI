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

	if (!f)
		return;

	char buf[1024] = "";
	while (fgets(buf, 1024, f))
		printf("%s", buf);

	fclose(f);
}
