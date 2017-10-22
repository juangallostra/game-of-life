#import <stdio.h>


// Variable declaration

// definir la nueva matriz que voy a utilizar
#define ROW  6
#define COLUMN  6

int new_state[ROW][COLUMN] = { { 0, 0, 0, 0, 0, 0},
								{ 0, 1, 1, 0, 1, 0},
								{ 0, 0, 0, 0, 0, 0},
								{ 0, 1, 1, 1, 0, 0},
								{ 0, 1, 0, 1, 1, 0},
								{ 0, 0, 0, 0, 0, 0}};



int *pnew_state;








// Function declaration

int * evolve (int* next_state, int row, int col);
int decision(int cont, int cell_state);

int main(void)
{
	// Pointer to the first element of the 2D array
	pnew_state = &new_state[0][0]; 
	// Call the function which returns the pointer to the 
	// new state 2D array
	int *caca = evolve(pnew_state, ROW, COLUMN);
	return 0;
}

// Function definition

int *evolve(int * next_state , int row, int col)
{

	// Define new array
	int array[row][col];
	// Loop for each cell of the map to know the state 
	// of the cell and its neighbours
	for (int i = 1; i < col - 1; i++)
	{
		for (int j = 1; j < row - 1; j++)
		{
			int cont = 0;
			// Count the number of neighbours alive
			if (new_state[i-1][j-1] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i][j-1] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i+1][j-1] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i-1][j] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i+1][j] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i-1][j+1] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i][j+1] == 1)
			{
				cont = cont + 1;
			}
			if (new_state[i+1][j+1] == 1)
			{
				cont = cont + 1;
			}
			// Call to the function that decides the new state
			// of the cell acording to the neighbors and its state
			array[row][col] = decision(cont,new_state[i][j]);
			
		}
	}

	int * pointer;
	pointer = &array[0][0];
	// Si queremos hacer una matrix 100x100, la haremos 102x102 para
	// poder saber la informacion de los bordes y evitar errores

	// 1. Recuperar la matriz

	// 2. Doble for para acceder a cada celda

	// 3. Conjunto de IF para saber el el siguiente estado


	// Crear nueva matriz 

	// Crear pointer de esta nueva matriz y asociarlo

	// Return el pointer
	return pointer;
}

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