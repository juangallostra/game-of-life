#ifndef EVOLVE_H_
#define EVOLVE_H_

// Coder: Gakusei

#define ROW  200
#define COLUMN  200
#define TERMINATOR 65535

typedef struct tuple {
	int length;
	unsigned short * state;
} tuple;

tuple *evolve(unsigned short * next_state , int row, int col, unsigned short terminator);

#endif