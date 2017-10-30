#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"

// Coder: MadMax

int main(void)
{
	/*
	This is the main function of Conway's game of life
	implementation done by Gakusei, #define true rand()&1
	and MadMax.

	The main idea is to keep in an array of only the cells
	that are alive. To make it memory efficient the coordinates
	of each cell are stored in a short int where the rightmost
	byte will store the y coordinate and the second leftmost the
	x coordinate. By doing this the whole state of a 255 by 255
	grid can be stored in an array of short ints. 
	To encode a cell then: cell = (i << 8) | j.
	To decode a cell: x = cell >> 8; y = cell & 255;
	
	An implementation with a lookup table for the cell states,
	should be faster but theoretically not so memory efficient.
	Since we wanted to experiment with memory allocation and
	pointers wechose the dynamic array approach.

	This function initializes the world and the first state of
	th system from a predefined pattern. After that it keeps
	updating an drawing the state of the system forever.
	*/
	unsigned short *current_state;
	int length;
	int pattern;
	tuple *next_state;

	// Let the user choose one of the predefined 3 patterns.
	printf("Choose pattern by entering a number from 1 to 3:\n");
	scanf("%i", &pattern);
	switch (pattern) 
	{
		case 1:/*The R-pentomino */
			length = 6;
			current_state = malloc(length*sizeof(unsigned short));
			*(current_state) =  (120<<8)|(160+1);
			*(current_state + 1) = ((120+1)<<8)|(160);
			*(current_state + 2) = ((120+1)<<8)|(160+1);
			*(current_state + 3) = ((120+2)<<8)|(160+1);
			*(current_state + 4) = (120<<8)|(160+2);
			break;
		case 2:	/*Diehard*/
			length = 8;
			current_state = malloc(length*sizeof(unsigned short));
			*(current_state) = ((120+1)<<8)|(160-2);
			*(current_state + 1) =  ((120+1)<<8)|(160-1);
			*(current_state + 2) = ((120+2)<<8)|(160-1);
			*(current_state + 3) = (120<<8)|(160+4);
			*(current_state + 4) = ((120+2)<<8)|(160+3);
			*(current_state + 5) = ((120+2)<<8)|(160+4);
			*(current_state + 6) = ((120+2)<<8)|(160+5);
			break;
		case 3: /*Acorn*/
			length = 8;
			current_state = malloc(length*sizeof(unsigned short));
			*(current_state) = ((120+1)<<8)|(160+1);
			*(current_state + 1) = ((120<<8))|(160-1);
			*(current_state + 2) = ((120+2)<<8)|(160-1);
			*(current_state + 3) = ((120+2)<<8)|(160-2);
			*(current_state + 4) = ((120+2)<<8)|(160+2);
			*(current_state + 5) = ((120+2)<<8)|(160+3);
			*(current_state + 6) = ((120+2)<<8)|(160+4);
			break;
		case 4: /* Glider */
			length = 6;
			current_state = malloc(length*sizeof(unsigned short));
			*(current_state) = ((120+1)<<8) | (160+2);
			*(current_state + 1) = ((120+2)<<8) | (160+3);
			*(current_state + 2) = ((120+3)<<8) | (160+1);
			*(current_state + 3) = ((120+3)<<8) | (160+2);
			*(current_state + 4) = ((120+3)<<8) | (160+3);
			break;
		default:
			printf("Invalid pattern\n");
			return 0;	
	}

	*(current_state + length - 1) = TERMINATOR;

	while(1)
	{
		/*
		This is the main loop of the program that will keep iterating
		until the user stops the program. It does the following:
		1. Draw actual state
		2. Compute next state
		3. Free the memory that was storing the actual state and allocate
		   the memory required for the next state
		4. Copy the contents of the next state into the current state
		5. Free the memory that was allocated for the next state during
		   its computation
		*/
		draw(current_state, TERMINATOR);
		next_state = evolve(current_state, length, ROW, COLUMN, TERMINATOR);
		free(current_state);
		current_state = malloc((*next_state).length*sizeof(*current_state));
		memcpy(current_state, (*next_state).state, (*next_state).length*sizeof(*current_state));
		length = (*next_state).length;
		free((*next_state).state);
		free(next_state);
	}
	return 0;
}