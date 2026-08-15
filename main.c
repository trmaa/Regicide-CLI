/*
 * SEE THE ORIGINAL GAME AT: https://www.regicidegame.com/
 *
 * Regicide CLI
 * The same game but in the tty.
 *
 * Copyright (c) 2026 Pablo Trik Marin
 * License GPL
 */

#include <stdio.h>
#include "io.h"
#include "gfx.h"
#include "game.h"
#include "err.h"
#include "highscore.h"

enum state {
	WON,
	LOST,
	NONE
};

static enum state state = LOST;

bool end;

static void
start()
{
	scr_init();
	ui_init();
	fill_dungeon();
	fill_deck();
	draw(HAND_SIZE);
}

static void
loop()
{
	display_info();
	render();

	if (boss_id >= DUNGEON_SIZE) {
		state = WON;
		end = true;
	}

	int id;

	do {
		id = prompt("Play");

		if (id == 'q') {
			end = true;
			return;
		}

		if (id == 'h') {
			end = true;
			help();
			state = NONE;
			return;
		}
	} while (id-'0' < 0 || id-'0' >= d_size(hand));

	use(id - '0');

	display_info();
	render();

	if (dungeon[boss_id].hp <= 0) {
		boss_id++;
	} else {
		for (int paid = 0; paid < dungeon[boss_id].dp;) {
			id = prompt("Discard");
			if (id == 'q') {
				end = true;
				return;
			}
			if (id == 'h') {
				end = true;
				help();
				state = NONE;
				return;
			}
			id -= '0';
			if (id < 0 || id >= d_size(hand))
				continue;
			struct card c = d_at(hand, id)->top;
			discard(id);
			paid += c.val;

			display_info();
			render();

			int len = d_size(hand);
			if (len < 1) {
				end = true;
				return;
			}
		}
	}
	int len = d_size(hand);
	if (len < 1) {
		end = true;
		return;
	}
}

main(void)
{
	term_conf();

	name();
	start();

#ifndef DEBUG
	while (!end) {
		loop();
	}
#endif
	term_deconf();
	cleanup();

	if (state == WON)
		printf(" \x1b[32mWon\x1b[0m\n");
	else if (state == LOST)
		printf(" \x1b[31mLost\x1b[0m\n");

	highscore();
}
