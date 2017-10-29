#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "evolve.h"

// Coders: Gakusei and #define true rand()&1

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

int is_alive(int cont, int cell_state)
{
	// Only 2 or 3 neighboors are alive the cell is also alive -> stay alive
	if (cell_state == 1 && (cont == 2 || cont == 3))
	{
		return 1;
	}
	// Cell is dead and there are 3 neighboors alive -> bring cell to live
	else if (cell_state == 0 && cont == 3)
	{
		return 1;
	}
	// otherwise cell is dead
	return 0;
}

unsigned short *add_to_array(unsigned short *pointer, unsigned short cell, int count)
{
	unsigned short *new_array = malloc((count+2)*sizeof(*pointer));
	memcpy(new_array, pointer, (count+1)*sizeof(*pointer));
	free(pointer);
	*(new_array + count) = cell;
	return new_array;
}

int find_in_array(unsigned short *state, int cell, int terminator)
{
	// while termination condition is not reached
	// iterate through the state array to see if
	// the specified cell is found
	unsigned short index = 0;
	while (*(state + index) != terminator) 
	{
		if (*(state + index) == cell)
		{
			return 1;
		}
		index++;
	}
	return 0;
}

tuple *evolve(unsigned short * state , int row, int col, unsigned short terminator)
{
	// pointer will store the evolved state of the system
	unsigned short *pointer;
	int alive_cells_count = 0;
	tuple *evolved = malloc(sizeof(tuple));
	// Loop for each cell of the map to know the state 
	// of the cell and its neighboors
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			// Check if cell is alive in the current state of the system
			unsigned short cell = (i << 8) | j; // cell value in array if alive
			int curr_cell_state = 0; 			// until found otherwise, cell is dead
			unsigned short index = 0;			// current index in alive cells array
			// see if the current cell is found alive
			curr_cell_state = find_in_array(state, cell, terminator);
			// Check if neighbours are present in alive cells array
			// and keep count on how many of them are alive
			int neighbour_count = 0;
			for (int k = 0; k < 8; k++)
			{
				unsigned short neighbour = ((i + neighbours[k][0])<<8) | (j + neighbours[k][1]);
				unsigned short index = 0;
				if(find_in_array(state, neighbour, terminator))
				{
					neighbour_count++;
				}
			}	
			// The first time the memory allocation has to be initialized
			if (!alive_cells_count)
			{
				pointer = malloc(sizeof(*pointer));
			}
			// check if the cell will be alive in the next state and, if so update array
			if (is_alive(neighbour_count, curr_cell_state))
			{	
				// add cell to dynamic array
				pointer = add_to_array(pointer, (i<<8) | j, alive_cells_count);
				alive_cells_count++;
			}
		}
	}
	// Add the terminator at the end of the array
	*(pointer + alive_cells_count) = terminator;
	// Return  a pointer to the first element of the memory block that allocates the state
	(*evolved).length = alive_cells_count + 1;
	(*evolved).state = pointer;
	return evolved;
}