#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "gfx.h"

struct px scr[H][W];

void term_conf()
{
	// Hide cursor
	//printf("\x1b[?25l");
}

void term_deconf()
{
	// Cursor block
	printf("\x1b[?25h");
}

void scr_init()
{
	int fd = open("bg.ppm", O_RDONLY);
	int img_w = W/2;

	if (fd != -1) {
		char _[13];
		read(fd, _, 13); // header
	}

	struct px *px;

	for (int y = 0; y < H; y++)
		for (int x = 0; x < img_w; x++) {
			px = &scr[y][x * 2];

			if (fd != -1)
				read(fd, &px->col, 3);
			else
				px->col = COL(0x002233);

			px->c = '@';

			px[1] = px[0];
		}

	close(fd);
}

void render()
{
	printf("\x1b[1;1H\x1b[2J");

	printf("\x1b[1;33m\n REGICIDE\n\n");

	printf("\x1b[1;35m Copyright (c) 2026\n");
	printf("\x1b[0;35m   Author: Pablo Trik Marin <mail@pablotrik.online>\n");
	printf("\x1b[0;35m   License: GPL\n\n");

	printf("\x1b[1;34m press (q) to quit.\n\n");

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++)
			put_px(scr[y][x]);
		putchar('\n');
	}
}

void put_px(struct px p)
{
	char o[ANSI_LEN+1] = ANSI(p.col);
	o[ANSI_LEN] = p.c;
	write(0, o, ANSI_LEN+1);
}
