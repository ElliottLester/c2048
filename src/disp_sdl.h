#ifndef DISPLAY_SDL_H_   /* Include guard */
#define DISPLAY_SDL_H_

#include "board.h"
#include "SDL2/SDL.h"

//drawing constants
//keep in mind the charaters
//are taller than they are wide
#define CELL_HIGH 9
#define CELL_WIDE 12

//exported functions

/*
 *  sets up the terminal for input and drawing
 */
void disp_sdl_init(void);

/*
 * clean up the terminal for exit
 */
void disp_sdl_end(void);

/*
 * prints an single cell at the given position with
 * the given value inside
 */
void disp_sdl_printCell(int column,int row, int value,int type);

/*
 *calls print cell and prints size * size of them
 */
void disp_sdl_printBoard(struct game * input);

#endif
