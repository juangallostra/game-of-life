#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"

// Coders: #define true rand()&1

int main(void)
{
	int mat[ROW][COLUMN];
	int pattern;

	for (int i = 0; i < ROW; i++)
	{

		for (int j = 0; j < COLUMN; j++)
		{
			mat[i][j]=0;
		}
	}
	printf("Insert pattern from 1 to 3:\n");
	scanf("%i",&pattern);

	switch (pattern) 
	{
		case 1:/*The R-pentomino */
			mat[20][85+1]=1;
			mat[20+1][85]=1;
			mat[20+1][85+1]=1;
			mat[20+2][85+1]=1;
			mat[20][85+2]=1;
			break;
		case 2:	/*Diehard*/
			mat[20+1][85-2]=1;
			mat[20+1][85-1]=1;
			mat[20+2][85-1]=1;
			mat[20][85+4]=1;
			mat[20+2][85+3]=1;
			mat[20+2][85+4]=1;
			mat[20+2][85+5]=1;
			break;
		case 3: /*Acorn*/
			mat[20+1][85+1]=1;
			mat[20][85-1]=1;
			mat[20+2][85-1]=1;
			mat[20+2][85-2]=1;
			mat[20+2][85+2]=1;
			mat[20+2][85+3]=1;
			mat[20+2][85+4]=1;
			break;
		default:
			printf("Invalid pattern\n");
			return 0;

	}
	
	int *pnew_state;
	pnew_state = &mat[0][0];

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
