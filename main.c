#include "io.h"
#include "gfx.h"

static bool end;

static void
start()
{
	scr_init();
	ui_init();
}

static void
loop()
{
	int id = select(); // user inp (pause)

	if (id == 'q')
		end = true;
}

main(void)
{
	term_conf();
	start();
	while (!end) {
		render();
		loop();
	}
	term_deconf();
}
