#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

void draw(unsigned short *state)
{
	initscr();
	noecho();
	erase();
	curs_set(FALSE);
	unsigned short index = 0;
	while (*(state + index) != 65535)
	{
		int x = (*(state + index)) >> 8;
		int y = (*(state + index)) & 255;
		index++;
		mvprintw(x, y, "X");
	}
	printf("printed %d\n cells", index);
	refresh();
	usleep(700000);
	endwin();
}