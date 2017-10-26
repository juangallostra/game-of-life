#include <stdio.h>
#include <stdlib.h>
#include "evolve.h"

// int new_state[ROW][COLUMN] = {  { 0, 0, 0, 0, 0, 0},
// 								{ 0, 1, 1, 0, 1, 0},
// 								{ 0, 0, 0, 0, 0, 0},
// 								{ 0, 1, 1, 1, 0, 0},
// 								{ 0, 1, 0, 1, 1, 0},
// 								{ 0, 0, 0, 0, 0, 0}};



//int *pnew_state;


// Se necessita reservar la memoria con alloc
// Si no se declaran estas variables de forma global
// Al salir de la funcion "evolve" como no se ha reservado 
// que corresponde a los valores de la array esta se alibera
// de forma automatica y hace que los resultado obtenidos
// no se parezcan ni en pintura a los reales
int * pointer;



int main(void)
{
	int new_state[ROW][COLUMN] = { { 0, 0, 0, 0, 0, 0},
								{ 0, 1, 1, 0, 1, 0},
								{ 0, 0, 0, 0, 0, 0},
								{ 0, 1, 1, 1, 0, 0},
								{ 0, 1, 0, 1, 1, 0},
								{ 0, 0, 0, 0, 0, 0}};
	int *pnew_state = (int *)malloc(ROW*COLUMN*sizeof(int));
	// Pointer
	pnew_state = &new_state[0][0]; 
	// Call the function which returns the pointer to the 
	// new state 2D array
	//int *stateUpdated = (int *)malloc(ROW*COLUMN*sizeof(int));
	int *stateUpdated = evolve(pnew_state, ROW, COLUMN);

	for (int i= 0; i<(ROW*COLUMN); i++)
	{
		printf("World %d: %d\n", i,*(stateUpdated+i));
	}

	// Free memory
	free(stateUpdated);

	return 0;
}
