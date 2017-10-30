#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"



int main(void)
{
	unsigned short *pnew_state;
	int length;
	int pattern;
	tuple *next_state;

	printf("Insert pattern from 1 to 3:\n");
	scanf("%i",&pattern);
	switch (pattern) 
	{
		case 1:/*The R-pentomino */
			length = 6;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) =  ((110<<8))|(175+1);
			*(pnew_state + 1) = ((110+1)<<8)|(175);
			*(pnew_state + 2) = ((110+1)<<8)|(175+1);
			*(pnew_state + 3) = ((110+2)<<8)|(175+1);
			*(pnew_state + 4) = ((110<<8))|(175+2);
			break;
		case 2:	/*Diehard*/
			length = 8;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = ((110+1)<<8)|(175-2);
			*(pnew_state + 1) =  ((110+1)<<8)|(175-1);
			*(pnew_state + 2) = ((110+2)<<8)|(175-1);
			*(pnew_state + 3) = (110<<8)|(175+4);
			*(pnew_state + 4) = ((110+2)<<8)|(175+3);
			*(pnew_state + 5) = ((110+2)<<8)|(175+4);
			*(pnew_state + 6) = ((110+2)<<8)|(175+5);
			break;
		case 3: /*Acorn*/
			length = 8;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = ((110+1)<<8)|(175+1);
			*(pnew_state + 1) = ((110<<8))|(175-1);
			*(pnew_state + 2) = ((110+2)<<8)|(175-1);
			*(pnew_state + 3) = ((110+2)<<8)|(175-2);
			*(pnew_state + 4) = ((110+2)<<8)|(175+2);
			*(pnew_state + 5) = ((110+2)<<8)|(175+3);
			*(pnew_state + 6) = ((110+2)<<8)|(175+4);
			break;
		case 4: /* Glider */
			length = 6;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = ((110+1)<<8) | (175+2);
			*(pnew_state + 1) = ((110+2)<<8) | (175+3);
			*(pnew_state + 2) = ((110+3)<<8) | (175+1);
			*(pnew_state + 3) = ((110+3)<<8) | (175+2);
			*(pnew_state + 4) = ((110+3)<<8) | (175+3);
			break;
		default:
			printf("Invalid pattern\n");
			return 0;	
	}

	*(pnew_state + length - 1) = TERMINATOR;
	while(1)
	{
		// Call the function to draw the actual state
		draw(pnew_state, TERMINATOR);
		// Call the function to compute the next state 
		next_state = evolve(pnew_state, length, ROW, COLUMN, TERMINATOR);
		free(pnew_state);
		// Copy all the infor*(pnew_state(ion stored from the pointer stateUpdate 
		// till the size to the pointer pnew_state
		pnew_state = malloc((*next_state).length*sizeof(*pnew_state));
		memcpy(pnew_state, (*next_state).state, (*next_state).length*sizeof(*pnew_state));
		length = (*next_state).length;
		// Free memory
		free((*next_state).state);
		free(next_state);
	}
	return 0;
}