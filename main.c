#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "evolve.h"
#include "draw.h"



int main(void)
{
	unsigned short *pnew_state = (unsigned short *)malloc(6*sizeof(unsigned short));

	*pnew_state = (1<<8)| 2;
	*(pnew_state + 1) = (2<<8)| 3;
	*(pnew_state + 2) = (3<<8)| 1;
	*(pnew_state + 3) = (3<<8)| 2;
	*(pnew_state + 4) = (3<<8)| 3;
	*(pnew_state + 5) = TERMINATOR;
	while(1)
	{
		// Call the function to draw the actual state
		draw(pnew_state, TERMINATOR);
		// Call the function to compute the next state 
		unsigned short *stateUpdated = evolve(pnew_state, ROW, COLUMN, TERMINATOR);
		free(pnew_state);
		// Copy all the information stored from the pointer stateUpdate 
		// till the size to the pointer pnew_state
		unsigned short array_size = 0;
		while (*(stateUpdated + array_size) != TERMINATOR) 
		{
			array_size++;
		}
		unsigned short *pnew_state = (unsigned short *)malloc((array_size+1)*sizeof(unsigned short));
		memcpy(pnew_state, stateUpdated, (array_size+1)*sizeof(unsigned short));
		// Free memory
		free(stateUpdated);
	}
	return 0;
}
