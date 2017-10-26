#include <stdio.h>
#include <stdlib.h>

// Function definition

int decision(int cont, int cell_state)
{
	// Most of the cases the new cell is 0
	int decision = 0;
	if (cell_state == 1 && (cont == 2 | cont == 3))
	{
		decision = 1;
	}
	else if (cell_state == 0 && cont == 3)
	{
		decision = 1;
	}
	printf("Cell %d", decision);
	printf("\n");
	return decision;
}


int *evolve(int * next_state , int row, int col)
{

	// Declare a new 2D array
	// Is filled with 0 because the size of de array
	// is bigger then the world (2 rows and 2 columns bigger)
	//int array[row][col];
	// Pointer declaration
	//int * pointer;
	// Allocate memory for the new array
	//int array[row][col];
	int *pointer = (int *)malloc(row*col*sizeof(int));
	printf("CACA:%lu\n",sizeof(pointer));
	// Point to the existing array
	//pointer = &array[0][0];
	for (int e = 0; e < row*col;e++)
	{
		printf("HOLA%d: %d\n",e,*(pointer + e) );
	}
	
	// Loop for each cell of the map to know the state 
	// of the cell and its 
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			// Count the number of neighbours alive
			int cont = 0;
			// Accessing to the upper-left neighboor
			if(*(next_state + (i-1)*row + (j-1)) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the upper neighbour
			if(*(next_state + (i-1)*row + j) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the upper-right neighbour
			if(*(next_state + (i-1)*row + (j+1)) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the left neighbour
			if(*(next_state + i*row + (j-1)) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the right neighbour
			if(*(next_state + i*row + (j+1)) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the bottom left neighbour
			if(*(next_state + (i+1)*row + (j-1)) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the bottom neighbour
			if(*(next_state + (i+1)*row + j) == 1)
			{
				cont = cont + 1;
			}
			// Accessing to the bottom-right neighbour
			if(*(next_state + (i+1)*row + (j+1)) == 1)
			{
				cont = cont + 1;
			}
			// Call to the function that decides the new state
			// of the cell acording to the neighbors and
			// the cell state
			printf("Row: %d, Column: %d",i,j);
			//array[i][j] = decision(cont,*(next_state + i*row +j));
			*(pointer + i*row + j) = decision(cont,*(next_state + i*row +j));
		}
	}

	// Free memory of the old state of the cells
	//freeMem(next_state, row, col);
	// Pointer to the first element of the 2D array
	return pointer;
}