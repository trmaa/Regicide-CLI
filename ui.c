#include <string.h>
#include "gfx.h"
#include "ui.h"

struct px *boss_dp;
struct px *bossid_dp;
struct px *card_dp[HAND_SIZE];

struct px *deck_dp;
struct px *hp_dp;
struct px *dp_dp;

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
		scr[y][x + i].col = UICMIX(scr[y][x].col);
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

	boss_dp = &scr[t + h / 2][l + w / 2];
	boss_dp[0].col = COL(UIC);
	boss_dp[1].col = COL(UIC);

	boss_dp[0].c = 'E';
	boss_dp[1].c = 'E';

	draw_outline(t, b, l, r);

	bossid_dp = &scr[t-1][l+5];
	draw_str("BOSS XX/12:", l, t-1);

	// STATS
	l -= 2;
	b += 1;

	draw_str("DECK: EE/40", 2, 2);
	draw_str("HP: EE, DP: EE", l, b);

	deck_dp = &scr[2][8];
	hp_dp = &scr[b][l + 4];
	dp_dp = &scr[b][l + 12];

	// HAND
	l = W/2 - ((HAND_SIZE+1)/2)*(w+2)/2;
	t = H - H/10 - 2*(h+2) + 1;
	draw_str("HAND:", l, t-1);

	for (int s = 0; s < 2; s++) {
		t = H - H/10 - (2-s)*(h+2) + 1;
		b = t + h;

		for (int i = 0; i < HAND_SIZE / 2; i++) {
			l = W/2 - ((HAND_SIZE+1)/2)*(w+2)/2 + i*(w+2);
			r = l + w;

			int id = i + s*HAND_SIZE/2;

			card_dp[id] = &scr[t + h/2][l + w/2];

			card_dp[id][0].col = COL(UIC);
			card_dp[id][1].col = COL(UIC);

			card_dp[id][0].c = 'E';
			card_dp[id][1].c = 'E';

			draw_outline(t, b, l, r);

			scr[t+2][l+2].c = id + '0';
			scr[t+2][l+2].col = UICMIX(scr[t+2][r+2].col);
		}
	}
}
