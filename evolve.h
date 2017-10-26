#ifndef EVOLVE_H_
#define EVOLVE_H_

#define ROW  6
#define COLUMN  6

const int neighbours[8][2];

int *evolve(int * next_state , int row, int col);

#endif