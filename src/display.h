#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

//display lib
#include <curses.h>

//drawing constants
#define CELL_HIGH 6
#define CELL_WIDE 9

//exported functions

void printCell(int column,int row, int value,int type);
void printBoard(struct game * input);

#endif