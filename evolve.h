#ifndef EVOLVE_H_
#define EVOLVE_H_

#define ROW  50
#define COLUMN  50

const int neighbours[8][2];

unsigned short *evolve(unsigned short * next_state , int row, int col);

#endif