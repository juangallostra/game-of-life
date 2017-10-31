#ifndef EVOLVE_H_
#define EVOLVE_H_

// Coder: Gakusei

// We have to be sure that the max size of the world
// when codified is smaller than the value used to
// mark the end of the array (the terminator) to avoid
// unexpected and undesired behaviours.  
#define ROW  250
#define COLUMN  250
#define TERMINATOR 65535

// Define what should be exposed (public functions and data)
// form evolve.c to the files including this headers

typedef struct tuple {
	int length;
	unsigned short * state;
} tuple;

tuple *evolve(unsigned short * next_state, int length, unsigned short terminator);

#endif