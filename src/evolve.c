#include <stdio.h>
#include <stdlib.h>

// Coder: Gakusei

// Variable definition

// Define an array of the neighboors coordinates
// to facilitate the acces to the cell state
int neighbours[8][2] = {{-1,-1},
                        {-1, 0},
                        {-1, 1},
                        {0, -1},
                        {0,  1},
                        {1, -1},
                        {1,  0},
                        {1,  1}};


// Function definition

int decision(int cont, int cell_state)
{
	// Only 2 or 3 neighboors are alive the cell is also alive
	if (cell_state == 1 && (cont == 2 || cont == 3))
	{
		return 1;
	}
	// Cell is dead and there are 3 neighboors alive
	else if (cell_state == 0 && cont == 3)
	{
		return 1;
	}
	return 0;
}


int *evolve(int * state , int row, int col)
{

	// Reserve memory for the cells
	int *pointer = malloc(row*col*sizeof(*state));
	// Loop for each cell of the map to know the state 
	// of the cell and its neighboors
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			int cont = 0;
			for (int k = 0; k < 8; k++)
			{
				if (*(state + (i + neighbours[k][0])*col + j+ neighbours[k][1]) == 1)
				{
					cont++;
				} 
			}
			// Call to the de decision function and store the content into its corresponding adress
			*(pointer + i*col + j) = decision(cont,*(state + i*col +j));
		}
	}

	// Return pointer of the first element of the the memory
	return pointer;
}
