#include <stdio.h>
#include <unistd.h>

int select()
{
	char c;

	write(1, "\x1b[0m Card: ", 11);

	do {
		if (read(0, &c, 1) <= 0)
			return -1;
	} while (c == '\n' || c == '\r');

	return c;
}
