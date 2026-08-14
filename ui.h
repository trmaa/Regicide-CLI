#pragma once

#include "game.h"
#include "gfx.h"

#define UIC 0xffffcc

extern struct px *boss_tag;
extern struct px *card_tags[HAND_SIZE];

void ui_init();
void ui_draw();
