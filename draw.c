#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

#define X_OFFSET 90
#define Y_OFFSET 90

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
		mvaddch(x-X_OFFSET, y-Y_OFFSET, ACS_CKBOARD);
	}
	refresh();
	usleep(70000);
}