#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>

void draw(int *state, int rows, int cols)
{
	initscr();
	noecho();
	curs_set(FALSE);
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (*(state+i*rows+j)==1)
			{
				mvprintw(i, j, "X");
			}
			else
			{
				mvprintw(i, j, " ");
			}
		}
	}
	refresh();
	usleep(60000);
	endwin();
}