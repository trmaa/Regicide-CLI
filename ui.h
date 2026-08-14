#pragma once

#include "game.h"
#include "gfx.h"

#define UIC 0xffffcc

#define UICMIX(c) ((struct col){ \
	(char)(((unsigned)(unsigned char)(c).r + (UIC >> 16)) / 2), \
	(char)(((unsigned)(unsigned char)(c).g + ((UIC >> 8) & 0xff)) / 2), \
	(char)(((unsigned)(unsigned char)(c).b + (UIC & 0xff)) / 2) })

extern struct px *boss_dp;
extern struct px *card_dp[HAND_SIZE];

extern struct px *deck_dp;
extern struct px *hp_dp;
extern struct px *dp_dp;

void ui_init();
