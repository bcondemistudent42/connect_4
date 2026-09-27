#include <locale.h>
#include <ncurses.h>

#include "tui/renderer.h"

int	init_ncurses(void)
{
	setlocale(LC_CTYPE, "");
	if (!initscr() || init_colors())
		return (1);
	curs_set(false);
	noecho();
	cbreak();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	set_escdelay(1);
	clear();
	return (0);
}

int	init_colors(void)
{
	if (!has_colors())
		return (1);
	start_color();
	init_pair(PAIR_COMPUTER, COLOR_RED, COLOR_BLACK);
	init_pair(PAIR_PLAYER, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PAIR_GUI, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAIR_GUI_HIGHLIGHT, COLOR_BLACK, COLOR_CYAN);
	init_pair(PAIR_CURSOR, COLOR_CYAN, COLOR_BLACK);
	return (0);
}

void	free_ncurses(void)
{
	nodelay(stdscr, false);
	curs_set(true);
	clear();
	refresh();
	endwin();
}
