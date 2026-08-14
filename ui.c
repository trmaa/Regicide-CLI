#include "gfx.h"
#include "ui.h"

struct px *boss_tag;

static void
draw_outline(int t, int b, int l, int r)
{
	scr[t][l].c = '+';
	scr[t][l].col = COL(UIC);
	scr[t][r].c = '+';
	scr[t][r].col = COL(UIC);
	scr[b][l].c = '+';
	scr[b][l].col = COL(UIC);
	scr[b][r].c = '+';
	scr[b][r].col = COL(UIC);

	for (int i = l+1; i < r; i++) {
		scr[t][i].c = '-';
		scr[t][i].col = COL(UIC);
		scr[b][i].c = '-';
		scr[b][i].col = COL(UIC);
	}
	for (int i = t+1; i < b; i++) {
		scr[i][l].c = '|';
		scr[i][l].col = COL(UIC);
		scr[i][r].c = '|';
		scr[i][r].col = COL(UIC);
	}
}

void ui_init()
{
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


	for (int s = 1; s <= 2; s++) {
		t = H - H/10 - s*(h+2);
		b = t + h;

		for (int i = 0; i < HAND_SIZE / 2; i++) {
			l = W/2 - ((HAND_SIZE+1)/2)*(w+2)/2 + i*(w+2);
			r = l + w;

			draw_outline(t, b, l, r);
		}
	}
}
