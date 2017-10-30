#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

// Coders: MadMax and #define true rand()&1

// Define ax and y offset so that the (0,0)
// is not located on the top left and the world
// extends beyond the terminal
#define X_OFFSET 90
#define Y_OFFSET 90

void draw(unsigned short *state, unsigned short terminator)
{
	/*
	This functions draws the actual state of the system
	in the terminal via the ncurses library. It iterates
	through the state of the system, which only stores alive
	cells, decodes its x and y values and prints them in the
	screen
	*/
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