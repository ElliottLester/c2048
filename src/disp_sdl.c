#include "disp_sdl.h"

//drawing constants
//keep in mind the charaters
//are taller than they are wide

/*
 *  sets up the terminal for input and drawing
 */
int disp_sdl_init(void){

    if(window == NULL) {

        // Initialize SDL video.
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

        // Create the window where we will draw.
        window = SDL_CreateWindow("SDL_RenderClear",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              512, 512,
                              0);

        // We must call SDL_CreateRenderer in order for draw calls to affect this window.
        renderer = SDL_CreateRenderer(window, -1, 0);

        // Select the color for drawing. It is set to red here.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,0,0,255);

        SDL_Rect rectangle={256,256,64,64};

        SDL_RenderFillRect(renderer, &rectangle);

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

        //Initialize SDL Input
        if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0)
            return 1;
        //Initialize SDL Events
        if (SDL_Init(SDL_INIT_EVENTS) != 0)
            return 1;

        event = malloc(sizeof(SDL_Event));
        return 0;
    } else {
        return 1;
    }
}

void disp_sdl_end(void){
    return;
}

void disp_sdl_printCell(int column,int row, int value,int type)
    {
    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    SDL_Rect rectangle={256,256,64,64};

    SDL_RenderFillRect(renderer, &rectangle);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);
    return;
}

void disp_sdl_printBoard(struct game * input){
    int* win_width = NULL;
    int* win_height = NULL;
    SDL_GetWindowSize(window,win_width,win_height);
    SDL_RenderClear(renderer);
    SDL_Rect backGround = {0,0,*(win_width),*(win_height)};
    (void)backGround;
    return;
}

void sdl_main(struct game * input, unsigned int seed) {
    int gameState,moveScore;
    gameState = 0;
    moveScore = 0;
    disp_sdl_init();
    while (gameState == 0) {
        while(SDL_PollEvent( event ) != 0) {
        //NULL pointer
        if (event == NULL) {
            gameState =1;
        }
        //the user sends a quit
        else if( event->type == SDL_QUIT ) { gameState = 1; }

        //normal key press
        else if( event->type == SDL_KEYDOWN ) {
            switch (event->key.keysym.sym) {
                case SDLK_q:
                    gameState = 1;
                    break;
                case SDLK_UP:
                    gameState = 1;
                    break;
                case SDLK_DOWN:
                    gameState = 1;
                    break;
                case SDLK_LEFT:
                    gameState = 1;
                    break;
                case SDLK_RIGHT:
                    gameState = 1;
                    break;
            }
        }


        }
    }

    disp_sdl_end();
}

