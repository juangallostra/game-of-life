#ifndef EVOLVE_H_
#define EVOLVE_H_

#define ROW  200
#define COLUMN  200
#define TERMINATOR 65535

const int neighbours[8][2];

unsigned short *evolve(unsigned short * next_state , int row, int col, unsigned short terminator);

#endif