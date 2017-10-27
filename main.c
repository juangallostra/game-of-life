#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"

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


	new_state[2][23] = 1;
	new_state[2][24] = 1;
	new_state[3][24] = 1;
	new_state[3][22] = 1;

	new_state[5][20] = 1;
	new_state[6][20] = 1;
	new_state[6][21] = 1;
	new_state[7][20] = 1;
	
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
