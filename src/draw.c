#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

// coder: #define true rand()&1

void draw(int *state, int rows, int cols)
{
	initscr();
	noecho();
	erase();
	curs_set(FALSE);
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (*(state+i*rows+j)==1)
			{
				mvaddch(i, j, ACS_CKBOARD);
			}	
		}
	}
	refresh();
	usleep(70000);
}
