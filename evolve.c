#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "evolve.h"

#define ALIVE 1
#define DEAD 0 

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
	Given two values, return if the first value is greater, equal or lower
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
	previously used memory block. Finally it orders all the elements
	and returns the address of the first element of the updated array.
	*/
	unsigned short *new_array = malloc((last_position + 1)*sizeof(*first_array_element));
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

	The terminator always present at the end of the array assures that at
	least the last element of the array will be bigger than the current cell.

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
 			  unsigned short terminator)
{
	/*
	Given a state defined by the state array and its length,
	and the value of the terminator that marks the end of the
	array this functions computes and returns the next state.

	To do so the function focuses only in interest cells 
	(cells that are alive or cells that are next to a cell that
	is alive) and processes them with two loops. First of all, it 
	iterates over the cells that are alive in the current 
	state and checks if they will be alive in the next state.
	While doing so it adds the dead neighbours (the ones that are
	alive will be also processed in this first loop) of the alive
	cells in another array because this are the ones that may
	become alive. After finishing this loop the second loop
	processes the just created array of dead neighbours,
	checks if any of them will be alive in the next state and if
	so, adds them to the next state array.

	It returns a struct that holds a pointer to first
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
	// Iterate through the fisrt set of interest cells.
	// This are the current alive cells of the map 
	// for which we should check the state of its neighbours to 
	// decide if it will be alive on the next iteration
	int index = 0; 
	while (*(state+index) != terminator)
	{
		unsigned short cell = *(state+index);
		// retrieve cell coordinates from cell value in array
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
				// if a cell is dead but it is next to a cell that is
				// alive we track it to process it later because it may
				// become alive
				if(!neigh_to_check_count)
				{
					neigh_to_check = malloc(sizeof(*state));
					neigh_to_check = add_to_array(neigh_to_check,
						                          terminator,
						                          neigh_to_check_count);
				}
				if(!find_in_array(neigh_to_check, neighbour))
				{
					neigh_to_check = add_to_array(neigh_to_check, 
						                          neighbour, 
						                          neigh_to_check_count);
					neigh_to_check_count++;
					neigh_to_check = add_to_array(neigh_to_check,
						                          terminator, 
						                          neigh_to_check_count);
				}
			}
		}	
		// check if the cell will be alive in the next state and, if so update array
		// and add the current cell
		if (is_alive(neighbour_count, ALIVE))
		{	
			// The first time the array for the next state
			// has to be initialized
			if (!alive_cells_count)
			{
				next_state = malloc(sizeof(*state));
			}
			// add cell to dynamic array and update count
			next_state = add_to_array(next_state, cell, alive_cells_count);
			alive_cells_count++;
		}
		index++;
	}

	if (!neigh_to_check_count)
	{
		neigh_to_check = malloc(sizeof(*state));
		neigh_to_check = add_to_array(neigh_to_check, terminator, neigh_to_check_count);
	}

	// Now we process the second set of interest cells.
	// Those cells that are dead but next to an alive cell and that
	// might become alive
	index = 0;
	while(*(neigh_to_check + index) != terminator)
	{
		unsigned short cell = *(neigh_to_check + index);
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
		if (is_alive(neighbour_count, DEAD))
		{	
			// The first time the array for the next state
			// has to be initialized
			if (!alive_cells_count)
			{
				next_state = malloc(sizeof(*state));
			}
			// add cell to dynamic array and update count
			next_state = add_to_array(next_state, cell, alive_cells_count);
			alive_cells_count++;
		}
		index++;
	}
	free(neigh_to_check);
	if (!alive_cells_count)
	{
		next_state = malloc(sizeof(*state));
	}
	next_state = add_to_array(next_state, terminator, alive_cells_count);
	// Build the structure to be returned from the evolved state and its length
	(*evolved).length = alive_cells_count + 1;
	(*evolved).state = next_state;
	return evolved;
}