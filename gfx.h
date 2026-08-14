#pragma once

#define ESC 0x1b
#define W 64
#define H 32

// ESC[38;2;RRR;GGG;BBBm
#define ANSI_LEN 19
typedef char ansi_t[ANSI_LEN];

struct col {
	char r, g, b;
};

// 4 bytes
struct px {
	char c;
	struct col col;
};

#define COL(hex) \
	((struct col){ (char)((hex) >> 16), (char)((hex) >> 8), (char)(hex) })

#define ANSI(c) \
	{ ESC, '[', '3', '8', ';', '2', ';', \
	  '0' + (unsigned char)(c).r / 100, \
	  '0' + (unsigned char)(c).r / 10 % 10, \
	  '0' + (unsigned char)(c).r % 10, ';', \
	  '0' + (unsigned char)(c).g / 100, \
	  '0' + (unsigned char)(c).g / 10 % 10, \
	  '0' + (unsigned char)(c).g % 10, ';', \
	  '0' + (unsigned char)(c).b / 100, \
	  '0' + (unsigned char)(c).b / 10 % 10, \
	  '0' + (unsigned char)(c).b % 10, 'm' }

extern struct px scr[H][W];

void term_conf();
void term_deconf();
void scr_init();
void render();
void put_px(struct px p);
