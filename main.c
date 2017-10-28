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
	unsigned short *pnew_state = (unsigned short *)malloc(6*sizeof(unsigned short));

	// int new_state[ROW][COLUMN] = {0};
	// new_state[0][2] = 1;
	// new_state[1][3] = 1;
	// new_state[2][1] = 1;
	// new_state[2][2] = 1;
	// new_state[2][3] = 1;


	// new_state[2][23] = 1;
	// new_state[2][24] = 1;
	// new_state[3][24] = 1;
	// new_state[3][22] = 1;

	// new_state[5][20] = 1;
	// new_state[6][20] = 1;
	// new_state[6][21] = 1;
	// new_state[7][20] = 1;
	unsigned short first_cell = (1<<8)| 2;
	*pnew_state = first_cell;
	*(pnew_state + 1) = (2<<8)| 3;
	*(pnew_state + 2) = (3<<8)| 1;
	*(pnew_state + 3) = (3<<8)| 2;
	*(pnew_state + 4) = (3<<8)| 3;
	*(pnew_state + 5) = 65535;
	while(1)
	{
		// Call the function to draw the actual state
		draw(pnew_state);
		// Call the function to compute the next state 
		unsigned short *stateUpdated = evolve(pnew_state, ROW, COLUMN);
		free(pnew_state);
		// Copy all the information stored from the pointer stateUpdate 
		// till the size to the pointer pnew_state
		unsigned short array_size = 0;
		while (*(stateUpdated + array_size) != 65535) 
		{
			array_size++;
		}
		unsigned short *pnew_state = (unsigned short *)malloc((array_size+1)*sizeof(unsigned short));
		memcpy(pnew_state, stateUpdated, (array_size+1)*sizeof(unsigned short));
		// Free memory
		free(stateUpdated);
	}
	return 0;
}
