#include <string.h>
#include "gfx.h"
#include "ui.h"

struct px *boss_tag;
struct px *card_tags[HAND_SIZE];

#define UICMIX(c) ((struct col){ \
	(char)(((unsigned)(unsigned char)(c).r + (UIC >> 16)) / 2), \
	(char)(((unsigned)(unsigned char)(c).g + ((UIC >> 8) & 0xff)) / 2), \
	(char)(((unsigned)(unsigned char)(c).b + (UIC & 0xff)) / 2) })

static void
draw_outline(int t, int b, int l, int r)
{
	scr[t][l].c = '+';
	scr[t][l].col = UICMIX(scr[t][l].col);
	scr[t][r].c = '+';
	scr[t][r].col = UICMIX(scr[t][r].col);
	scr[b][l].c = '+';
	scr[b][l].col = UICMIX(scr[b][l].col);
	scr[b][r].c = '+';
	scr[b][r].col = UICMIX(scr[b][r].col);

	for (int i = l+1; i < r; i++) {
		scr[t][i].c = '-';
		scr[t][i].col = UICMIX(scr[t][i].col);
		scr[b][i].c = '-';
		scr[b][i].col = UICMIX(scr[b][i].col);
	}
	for (int i = t+1; i < b; i++) {
		scr[i][l].c = '|';
		scr[i][l].col = UICMIX(scr[i][l].col);
		scr[i][r].c = '|';
		scr[i][r].col = UICMIX(scr[i][r].col);
	}
}

static void
draw_str(char *str, int x, int y)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		scr[y][x + i].c = str[i];
		scr[y][x + i].col = COL(UIC);
	}
}

void ui_init()
{
	// BOSS
	int w = W / 7, h = H / 5;
	int t, b, l, r;

	t = H / 10;
	b = t + h;
	l = W / 2 - w / 2;
	r = l + w;

	boss_tag = &scr[t + h / 2][l + w / 2];
	boss_tag[0].col = COL(UIC);
	boss_tag[1].col = COL(UIC);

	boss_tag[0].c = 'E';
	boss_tag[1].c = 'E';

	draw_outline(t, b, l, r);

	// STATS
	draw_str("DECK: EE", 2, 2);
	draw_str("HP: EE, DP: EE", l - 2, b + 1);

	// HAND
	for (int s = 0; s < 2; s++) {
		t = H - H/10 - (s+1)*(h+2) + 1;
		b = t + h;

		for (int i = 0; i < HAND_SIZE / 2; i++) {
			l = W/2 - ((HAND_SIZE+1)/2)*(w+2)/2 + i*(w+2);
			r = l + w;

			int id = i + s*HAND_SIZE/2;

			card_tags[id] = &scr[t + h/2][l + w/2];

			card_tags[id][0].col = COL(UIC);
			card_tags[id][1].col = COL(UIC);

			card_tags[id][0].c = 'E';
			card_tags[id][1].c = 'E';

			draw_outline(t, b, l, r);
		}
	}
}
