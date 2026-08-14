#pragma once

#include "game.h"
#include "gfx.h"

#define UIC 0xffffcc

extern struct px *boss_dp;
extern struct px *card_dp[HAND_SIZE];

extern struct px *deck_dp;
extern struct px *hp_dp;
extern struct px *dp_dp;

void ui_init();
