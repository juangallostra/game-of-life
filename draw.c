#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

// coder #define true rand()&1

void draw(unsigned short *state, unsigned short terminator)
{
	initscr();
	noecho();
	erase();
	curs_set(FALSE);
	unsigned short index = 0;
	while (*(state + index) != terminator)
	{
		int x = (*(state + index)) >> 8;
		int y = (*(state + index)) & 255;
		index++;
		mvprintw(x, y, "X");
	}
	refresh();
	usleep(70000);
	endwin();
}