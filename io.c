#include <stdio.h>
#include <unistd.h>

int prompt(char *str)
{
	printf("\x1b[0m %s: ", str);
	fflush(stdout);

	char c;

	do {
		if (read(0, &c, 1) <= 0)
			return -1;
	} while (c == '\n' || c == '\r');

	char r = c;

	do {
		if (read(0, &c, 1) <= 0)
			break;
	} while (c != '\n' && c != '\r');

	return r;
}
