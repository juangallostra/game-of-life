#ifndef EVOLVE_H_
#define EVOLVE_H_

#define ROW  225
#define COLUMN  ROW

const int neighbours[8][2];

int *evolve(int * next_state , int row, int col);

#endif