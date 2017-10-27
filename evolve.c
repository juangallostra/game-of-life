#include <stdio.h>
#include <stdlib.h>


// Variable definition

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
	// Most of the cases the new cell is 0
	int decision = 0;
	if (cell_state == 1 && (cont == 2 || cont == 3))
	{
		decision = 1;
	}
	else if (cell_state == 0 && cont == 3)
	{
		decision = 1;
	}
	return decision;
}


int *evolve(int * state , int row, int col)
{

	// Allocate memory for the new array

	// Se necessita reservar la memoria con alloc
	// Si no se declaran estas variables de forma global
	// Al salir de la funcion "evolve" como no se ha reservado 
	// que corresponde a los valores de la array esta se alibera
	// de forma automatica y hace que los resultado obtenidos
	// no se parezcan ni en pintura a los reales

	int *pointer = (int *)malloc(row*col*sizeof(int));
	// Loop for each cell of the map to know the state 
	// of the cell and its 
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			int cont = 0;
			for (int k = 0; k < 8; k++)
			{
				if (*(state + (i + neighbours[k][0])*row + j+ neighbours[k][1]) == 1)
				{
					cont++;
				} 
			}
			// Call to the function that decides the new state
			// of the cell acording to the neighbors and
			// the cell state
			//array[i][j] = decision(cont,*(next_state + i*row +j));
			*(pointer + i*row + j) = decision(cont,*(state + i*row +j));
		}
	}

	// return pointer to the first element of the 2D array
	return pointer;
}