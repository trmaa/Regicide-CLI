#include "io.h"
#include "gfx.h"
#include "game.h"

enum state {
	WON,
	LOST
};

static bool end;
static enum state state = LOST;

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

	int id = select(); // user inp (pause)

	switch (id) {
	case 'q':
		end = true;
		break;
	default:
		if (id >= '0' && id <= '0' + HAND_SIZE - 1)
			use(id - '0');
		break;
	}

	int len = l_size(hand);
	if (len < 1)
		end = true;
}

main(void)
{
	term_conf();

	start();

#ifndef DEBUG
	while (!end) {
		loop();
	}
#endif
	term_deconf();

	if (state == WON)
		return 0;
	else if (state == LOST)
		return 69;
	else
		return -1;
}
