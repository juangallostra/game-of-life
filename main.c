#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"



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
			mat[40][60+1]=1;
			mat[40+1][60]=1;
			mat[40+1][60+1]=1;
			mat[40+2][60+1]=1;
			mat[40][60+2]=1;
			break;
		case 2:	/*Diehard*/
			mat[40+1][60-2]=1;
			mat[40+1][60-1]=1;
			mat[40+2][60-1]=1;
			mat[40][60+4]=1;
			mat[40+2][60+3]=1;
			mat[40+2][60+4]=1;
			mat[40+2][60+5]=1;
			break;
		case 3: /*Acorn*/
			mat[40+1][60+1]=1;
			mat[40][60-1]=1;
			mat[40+2][60-1]=1;
			mat[40+2][60-2]=1;
			mat[40+2][60+2]=1;
			mat[40+2][60+3]=1;
			mat[40+2][60+4]=1;
			break;
		default:
			printf("Please select a number between 1 a 3:");
			break;

	}
	// int new_state[ROW][COLUMN] = { { 0, 0, 1, 0, 0, 0},
	// 							   { 0, 0, 0, 1, 0, 0},
	// 							   { 0, 1, 1, 1, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0},
	// 							   { 0, 0, 0, 0, 0, 0}};
	//int *pnew_state = (int *)malloc(ROW*COLUMN*sizeof(int));

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
	//int *pnew_state = initialize(ROW, COL);
	
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
