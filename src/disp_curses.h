#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

#include "board.h"
#include <curses.h>

//drawing constants
//keep in mind the charaters
//are taller than they are wide
#define CELL_HIGH 9
#define CELL_WIDE 12

//exported functions

/*
 *  sets up the terminal for input and drawing
 */
void display_init(void);

/*
 * clean up the terminal for exit
 */
void display_end(void);

/*
 * prints an single cell at the given position with
 * the given value inside
 */
void printCell(int column,int row, int value,int type);

/*
 *calls print cell and prints size * size of them
 */
void printBoard(struct game * input);

/*
 *The main curses control loop returns when the game ends
 */
void curses_main(struct game * input,unsigned int seed);

#endif
