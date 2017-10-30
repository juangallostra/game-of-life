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

	// unsigned short *pnew_state = (unsigned short *)malloc(6*sizeof(unsigned short));

	// *(pnew_state = (1<<8)| 2;
	// *(pnew_state + 1) = (2<<8)| 3;
	// *(pnew_state + 2) = (3<<8)| 1;
	// *(pnew_state + 3) = (3<<8)| 2;
	// *(pnew_state + 4) = (3<<8)| 3;
	// *(pnew_state + 5) = TERMINATOR;

	printf("Insert pattern from 1 to 3:\n");
	scanf("%i",&pattern);
	switch (pattern) 
	{
		case 1:/*The R-pentomino */
			length = 6;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) =  ((20<<8)|85+1);
			*(pnew_state + 1) = ((20+1<<8)|85);
			*(pnew_state + 2) = ((20+1<<8)|85+1);
			*(pnew_state + 3) = ((20+2<<8)|85+1);
			*(pnew_state + 4) = ((20<<8)|85+2);
			break;
		case 2:	/*Diehard*/
			length = 8;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = ((20+1<<8)|85-2);
			*(pnew_state + 1) =  ((20+1<<8)|85-1);
			*(pnew_state + 2) = ((20+2<<8)|85-1);
			*(pnew_state + 3) = ((20<<8)|85+4);
			*(pnew_state + 4) = ((20+2<<8)|85+3);
			*(pnew_state + 5) = ((20+2<<8)|85+4);
			*(pnew_state + 6) = ((20+2<<8)|85+5);
			break;
		case 3: /*Acorn*/
			length = 8;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = ((20+1<<8)|85+1);
			*(pnew_state + 1) = ((20<<8)|85-1);
			*(pnew_state + 2) = ((20+2<<8)|85-1);
			*(pnew_state + 3) = ((20+2<<8)|85-2);
			*(pnew_state + 4) = ((20+2<<8)|85+2);
			*(pnew_state + 5) = ((20+2<<8)|85+3);
			*(pnew_state + 6) = ((20+2<<8)|85+4);
			break;
		case 4: /* Glider */
			length = 6;
			pnew_state = malloc(length*sizeof(unsigned short));
			*(pnew_state) = (1<<8)| 2;
			*(pnew_state + 1) = (2<<8)| 3;
			*(pnew_state + 2) = (3<<8)| 1;
			*(pnew_state + 3) = (3<<8)| 2;
			*(pnew_state + 4) = (3<<8)| 3;
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
		next_state = evolve(pnew_state, ROW, COLUMN, TERMINATOR);
		free(pnew_state);
		// Copy all the infor*(pnew_state(ion stored from the pointer stateUpdate 
		// till the size to the pointer pnew_state
		pnew_state = malloc((*next_state).length*sizeof(*pnew_state));
		memcpy(pnew_state, (*next_state).state, (*next_state).length*sizeof(*pnew_state));
		// Free memory
		free((*next_state).state);
		free(next_state);
	}
	return 0;
}