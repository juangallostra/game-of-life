#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <ncurses.h>
#include <unistd.h>

#include "evolve.h"


// Se necessita reservar la memoria con alloc
// Si no se declaran estas variables de forma global
// Al salir de la funcion "evolve" como no se ha reservado 
// que corresponde a los valores de la array esta se alibera
// de forma automatica y hace que los resultado obtenidos
// no se parezcan ni en pintura a los reales

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

int main(void)
{
	// int new_state[ROW][COLUMN] = { { 0, 0, 1, 0, 0, 0},
	// 							   { 0, 0, 0, 1, 0, 0},
	// 							   { 0, 1, 1, 1, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0}};
	//int *pnew_state = (int *)malloc(ROW*COLUMN*sizeof(int));

	int new_state[ROW][COLUMN] = {0};
	new_state[0][2] = 1;
	new_state[1][3] = 1;
	new_state[2][1] = 1;
	new_state[2][2] = 1;
	new_state[2][3] = 1;
	
	int *pnew_state;
	pnew_state = &new_state[0][0];

	while(1)
	{
		draw(pnew_state, ROW, COLUMN);
		int *stateUpdated = evolve(pnew_state, ROW, COLUMN);
		memcpy(pnew_state, stateUpdated, ROW*COLUMN*sizeof(int));
		free(stateUpdated);
		// for (int e = 0; e < ROW*COLUMN;e++)
		// {
		// 	printf("World %d: %d\n",e,*(pnew_state + e) );
		// }

	}
	return 0;
}
