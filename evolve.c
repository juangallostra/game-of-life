#include <stdio.h>
#include <stdlib.h>

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
	// Most of the cases the new cell is 0
	int decision = 0;

	// Only 2 or 3 neighboors are alive the cell is also alive -> stay alive
	if (cell_state == 1 && (cont == 2 || cont == 3))
	{
		decision = 1;
	}
	// Cell is dead and there are 3 neighboors alive -> bring cell to live
	else if (cell_state == 0 && cont == 3)
	{
		decision = 1;
	}
	return decision;
}


unsigned short *evolve(unsigned short * state , int row, int col, unsigned short terminator)
{

	// Reserve memory for the worst case scenario (all alive)
	unsigned short *pointer = (unsigned short *)malloc(row*col*sizeof(unsigned short));
	unsigned short alive_cells_count = 0;
	// Loop for each cell of the map to know the state 
	// of the cell and its neighboors
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			// Check if cell is alive in the current state
			unsigned short cell = (i << 8) | j; // cell value in array if alive
			int curr_cell = 0; // until found otherwise, cell is dead
			unsigned short index = 0;	// current index in alive cells array
			// while termination condition is not reached
			while (*(state + index) != terminator) 
			{
				if (*(state + index) == cell)
				{
					curr_cell = 1;
					break;
				}
				index++;
			}
			// Check if neighbours are present in alive cells array
			// and keep count on how many of them are alive
			int neighbour_count = 0;
			for (int k = 0; k < 8; k++)
			{
				unsigned short neighbour = ((i + neighbours[k][0])<<8) | (j + neighbours[k][1]);
				unsigned short index = 0;
				while (*(state + index) != terminator) 
				{
					if (*(state + index) == neighbour)
					{
						neighbour_count++;
						break;
					}
					index++;
				}
			}			
			// check if the cell will be alive in the next state and, if so, increment counter
			if (is_alive(neighbour_count, curr_cell))
			{
				*(pointer + alive_cells_count) = (i<<8) | j;
				alive_cells_count++;
			}
		}
	}
	// Once all decisions have been made, build the final state
	unsigned short *final_state = (unsigned short *)malloc((alive_cells_count)*sizeof(unsigned short));
	for (int k = 0; k < alive_cells_count; k++)
	{
		*(final_state + k) = *(pointer + k);
	}
	// Add terminator flag at the end of the array
	*(final_state + alive_cells_count) = terminator;
	free(pointer);
	// Return  a pointer to the first element of the memory block that allocates the state
	return final_state;
}