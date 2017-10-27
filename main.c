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
		// Call the function to draw the actual state
		draw(pnew_state, ROW, COLUMN);
		// Call the function to compute the next state 
		int *stateUpdated = evolve(pnew_state, ROW, COLUMN);
		// Copy all the information stored from the pointer stateUpdate 
		// till the size to the pointer pnew_state
		memcpy(pnew_state, stateUpdated, ROW*COLUMN*sizeof(int));
		// Free memory
		free(stateUpdated);


	}
	return 0;
}
