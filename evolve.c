#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "evolve.h"

// Coders: Gakusei and #define true rand()&1

// Define the array of the neighbours coordinates
// to be checked for each cell
int neighbours[8][2] = {{-1,-1},
                        {-1, 0},
                        {-1, 1},
                        {0, -1},
                        {0,  1},
                        {1, -1},
                        {1,  0},
                        {1,  1}};

// Function definitions

int compare(const void* a, const void* b)
{
	/*
	Given to values, return if the first value is greater, equal or lower
	than the second number by returning respectively a number lower, equal
	or greater than 0
	*/
    return *(unsigned short *)a - *(unsigned short *)b;
}

int is_alive(int alive_neighbours, int cell_state)
{
	/*
	Given a current cell state and the number of its alive neighbours
	return if the cell will be alive in the next iteration following
	Conway's game of life rules.

	return values:
	0 -> dead
	1 -> alive
	*/
	// Only 2 or 3 neighboors are alive the cell is also alive -> stay alive
	if (cell_state == 1 && (alive_neighbours == 2 || alive_neighbours == 3))
	{
		return 1;
	}
	// Cell is dead and there are 3 neighboors alive -> bring cell to live
	else if (cell_state == 0 && alive_neighbours == 3)
	{
		return 1;
	}
	// Otherwise cell is dead
	return 0;
}

unsigned short *add_to_array(unsigned short *first_array_element,
							 unsigned short cell,
							 int last_position)
{
	/*
	This function is used to implement a dynamic array functionality.
	It adds the given element (cell) at the last position of the array
	that starts at the address specified by the pointer to the first
	array element. 

	It does so by first allocating a new memory block with the required
	size for storing the actual elements, the new element and the terminator.
	Hence the +2 in the first malloc call. Then it copies the current
	contents of the array to this new block and frees the memory of the
	previously used memory block. Then it orders all the elements
	and returns the address of the first element of the updated array.
	*/
	unsigned short *new_array = malloc((last_position + 2)*sizeof(*first_array_element));
	// Since array indexes start at 0 and last_position is
	// the last index -> lenght to copy = last_position + 1  
	memcpy(new_array, first_array_element, (last_position + 1)*sizeof(*first_array_element));
	free(first_array_element);
	*(new_array + last_position) = cell;
	qsort(new_array, last_position + 1, sizeof(*new_array), &compare);
	return new_array;
}

int find_in_array(unsigned short *state, int cell)
{
	/* 
	Look for the specified cell in the state array. Since the state
	array is ordered in increasing order, if the position of the array
	checked against holds a value bigger than the current cell it is
	guarantedd that the cell we are looking for is not in the array.

	The terminator at the end of the array assures that at least the last
	element of the array will be bigger than the current cell.

	return values:
	0 -> not found
	1 -> found
	*/
	unsigned short index = 0;
	while (*(state + index) <= cell) 
	{
		if (*(state + index) == cell)
		{
			return 1;
		}
		index++;
	}
	return 0;
}

tuple *evolve(unsigned short * state, int length,
 			  int row, int col,
 			  unsigned short terminator)
{
	/*
	Given a state defined by the state array and its length,
	a world size and the value of the terminator that marks
	the end of the array this functions computes and returns
	the next state.

	The function returns a struct that holds a pointer to first
	position of the array that stores the evolved state and the
	length of the the evolved state array.
	*/
	unsigned short *next_state;
	int alive_cells_count = 0;
	unsigned short neighbour;
	int neighbour_count;
	unsigned short *neigh_to_check;
	int neigh_to_check_count = 0;
	tuple *evolved = malloc(sizeof(tuple));
	// Since auxiliary functions assume the current state
	// array is sorted we sort it to be sure of it
	qsort(state, length, sizeof(*state), &compare);
	// Loop for each cell of the map retrieving its actual
	// state and the state of its neighbours to decide if
	// it will be alive on the next iteration
	int index = 0; 
	while (*(state+index) != terminator)
	{
		unsigned short cell = *(state+index); // cell value in array
		int i = cell >> 8;
		int j = cell & 255;
		// Check if neighbours are present in alive cells array
		// and keep count on how many of them are alive
		neighbour_count = 0;
		for (int k = 0; k < 8; k++)
		{
			neighbour = ((i + neighbours[k][0])<<8) | (j + neighbours[k][1]);
			if(find_in_array(state, neighbour))
			{
				neighbour_count++;
			}
			else
			{
				if(!neigh_to_check_count)
				{
					neigh_to_check = malloc(sizeof(*state));
					add_to_array(neigh_to_check, neighbour, neigh_to_check_count);
					neigh_to_check_count++;
					*(neigh_to_check + neigh_to_check_count) = terminator;
				}
				else
				{
					if(!find_in_array(neigh_to_check, neighbour))
					{
						add_to_array(neigh_to_check, neighbour, neigh_to_check_count);
						neigh_to_check_count++;
						*(neigh_to_check + neigh_to_check_count) = terminator;
					}
				}
			}
		}	
		// check if the cell will be alive in the next state and, if so update array
		// and add the current cell
		if (is_alive(neighbour_count, 1))
		{	
			// The first time the array for the next state
			// has to be initialized
			if (!alive_cells_count)
			{
				next_state = malloc(sizeof(*next_state));
			}
			// add cell to dynamic array and update count
			next_state = add_to_array(next_state, cell, alive_cells_count);
			alive_cells_count++;
		}
		index++;
	}

	
	index = 0;
	while(*(neigh_to_check + index) != terminator)
	{
		unsigned short cell = *(neigh_to_check + index); // cell value in array
		int i = cell >> 8;
		int j = cell & 255;
		neighbour_count = 0;
		for (int k = 0; k < 8; k++)
		{
			neighbour = ((i + neighbours[k][0])<<8) | (j + neighbours[k][1]);
			if(find_in_array(state, neighbour))
			{
				neighbour_count++;
			}
		}	
		// check if the cell will be alive in the next state and, if so update array
		// and add the current cell
		if (is_alive(neighbour_count, 0))
		{	
			// The first time the array for the next state
			// has to be initialized
			if (!alive_cells_count)
			{
				next_state = malloc(sizeof(*next_state));
			}
			// add cell to dynamic array and update count
			next_state = add_to_array(next_state, cell, alive_cells_count);
			alive_cells_count++;
		}
		index++;

	}
	// Return  a pointer to the first element of the memory block that allocates the state
	if (!alive_cells_count)
	{
		next_state = malloc(sizeof(*next_state));
	}
	*(next_state + alive_cells_count) = terminator;
	(*evolved).length = alive_cells_count + 1;
	(*evolved).state = next_state;
	return evolved;
}