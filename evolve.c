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

	// Only 2 or 3 neighboors are alive the cell is also alive
	if (cell_state == 1 && (cont == 2 || cont == 3))
	{
		decision = 1;
	}
	// Cell is dead and there are 3 neighboors alive
	else if (cell_state == 0 && cont == 3)
	{
		decision = 1;
	}
	return decision;
}


unsigned short *evolve(unsigned short * state , int row, int col)
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
			// Check if current_state[cell]=alive
			unsigned short cell = (i << 8) | j; // cell value in array if alive
			//printf("Checking at: %d\n", cell);
			int curr_cell = 0; // until found otherwise, cell is dead
			unsigned short index = 0;	// current index in alive cells array
			// while termination condition is not reached
			while (*(state + index) != 65535) 
			{
				if (*(state + index) == cell)
				{
					curr_cell = 1;
					break;
				}
				index++;
			}
			
			// Check if neighbours are present in alive cells array

			int neighbour_count = 0;
			for (int k = 0; k < 8; k++)
			{
				// neighbour cell = i + neighbours[k][0], neighbours[k][1]
				unsigned short neighbour = ((i + neighbours[k][0])<<8) | (j + neighbours[k][1]);
				unsigned short index = 0;
				while (*(state + index) != 65535) 
				{
					if (*(state + index) == neighbour)
					{
						neighbour_count++;
						break;
					}
					index++;
				}
			}			
			// decide if  next_state[cell]=alive and increment counter
			//printf("%d\n", is_alive(neighbour_count, curr_cell));

			if (is_alive(neighbour_count, curr_cell))
			{
				*(pointer + alive_cells_count) = (i<<8) | j;
				alive_cells_count++;
			}
			// if alive, add to local scope list

			// allocate memory for the final state
			// build alive vector and return

			// Call to the de decision function and store the content into its corresponding adress
			//*(pointer + i*row + j) = decision(cont,*(state + i*row +j));
		}
	}
	// Once all decisions have been made, build the final state
	unsigned short *final_state = (unsigned short *)malloc((alive_cells_count)*sizeof(unsigned short));

	for (int k = 0; k < alive_cells_count; k++)
	{
		*(final_state + k) = *(pointer + k);
	}
	*(final_state + alive_cells_count) = 65535;
	free(pointer);
	// Return pointer of the first element of the the memory
	return final_state;
}