#ifndef DISPLAY_SDL_H_   /* Include guard */
#define DISPLAY_SDL_H_

#include "board.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

//drawing constants
//keep in mind the charaters
//are taller than they are wide
#define COLORS 14

struct color_tuple {
    int r;
    int g;
    int b;
};

//DISPLAY_SDL_VARS
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font[8];
int font_size;
SDL_Event* event;

//exported functions

/*
 *  sets up the terminal for input and drawing
 */
int disp_sdl_init(void);

/*
 * clean up the terminal for exit
 */
void disp_sdl_end(void);

/*
 * prints an single cell at the given position with
 * the given value inside
 */
void disp_sdl_printCell(int column,int row, int value,int cell_width,int cell_high);

/*
 *calls print cell and prints size * size of them
 */
void disp_sdl_printBoard(struct game * input);

int sdl_main(struct game * input, unsigned int seed);

char *itoa(long n);
#endif
