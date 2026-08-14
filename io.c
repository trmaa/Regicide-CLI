#include <stdio.h>
#include <unistd.h>

int select()
{
	int card;
	write(0, "\x1b[0m Card: ", 11);
	read(1, &card, 1);
	return card;
}
