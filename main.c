#include "io.h"
#include "gfx.h"

static bool end;

static void
start()
{
	scr_init();
	ui_init();
	fill_dungeon();
	fill_deck();
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
	}
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
}
