#include "disp_sdl.h"

//drawing constants
//keep in mind the charaters
//are taller than they are wide

/*
 *  sets up the terminal for input and drawing
 */
void disp_sdl_init(void){
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    // Create the window where we will draw.
    window = SDL_CreateWindow("SDL_RenderClear",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              512, 512,
                              0);

    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);
    
    return;
}

void disp_sdl_end(void){
    return;
}

void disp_sdl_printCell(int column,int row, int value,int type){
    return;
}

void disp_sdl_printoard(struct game * input){
    return;
}
