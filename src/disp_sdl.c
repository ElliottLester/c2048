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

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

        //Initialize SDL Input
        if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0)
            return 1;
        //Initialize SDL Events
        if (SDL_Init(SDL_INIT_EVENTS) != 0)
            return 1;
        if(TTF_Init() != 0)
            return 1;

        // load font.ttf at size 16 into font
        font=TTF_OpenFont("/usr/share/fonts/corefonts/couri.ttf", 16);
        if(!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            return 1;
        }

        event = malloc(sizeof(SDL_Event));
        return 0;
    } else {
        return 1;
    }
}

void disp_sdl_end(void){
    TTF_Quit();
    SDL_Quit();
    return;
}

void disp_sdl_printCell(int column,int row, int value,int cell_width , int cell_height)
    {
    //create the cell canvas
    SDL_Surface* cell;
    cell = SDL_CreateRGBSurface(0,cell_width,cell_height,32,0,0,0,0);
    //Create the background for the cell
    SDL_Rect rectangle={1,1,cell_width-2,cell_height-2};

    //convert and Create the text layer
    //char* buffer = "1234";
    //buffer = itoa(value);
    //SDL_Surface* surf_text;
    //SDL_Color text_color = {0,0,0};
    //surf_text = TTF_RenderUTF8_Solid(font,buffer,text_color);

    //apply the cell background to the surface
    SDL_FillRect(cell, &rectangle, SDL_MapRGBA((cell->format),255,0,0,255));

    //copy the text_surface to the cell surface
    //SDL_BlitSurface(surf_text,NULL,cell,NULL);

    SDL_Rect cell_region = {cell_width*row,cell_height*cell_height,cell_width,cell_height};
    SDL_Texture* rendered_cell = SDL_CreateTextureFromSurface(renderer,cell);

    //SDL_RenderCopy(renderer,rendered_cell,NULL,&cell_region);
    return;
}

void disp_sdl_printBoard(struct game * input){
    int* win_width = malloc(sizeof(int));
    int* win_height = malloc(sizeof(int));
    SDL_GetWindowSize(window,win_width,win_height);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (win_width != NULL && win_height != NULL) {
        int cell_width = (((*win_width) / (input->size)));
        int cell_height = (((*win_height) / (input->size)));
        for(int i = 0 ; i < input->size ; i++) {
            for(int j = 0 ; j < input->size ; j++) {
                disp_sdl_printCell(i,j,board_get(input,i,j),cell_width,cell_height);
            }
        }
    }
    SDL_RenderPresent(renderer);
    free(win_width);
    free(win_height);
    return;
}

int sdl_main(struct game * localboard, unsigned int seed) {
    int gameState,moveScore,totalScore;
    gameState = 0;
    moveScore = 0;
    totalScore = 0;
    if (disp_sdl_init() != 0){
        disp_sdl_end();
        return 1;
    }
    disp_sdl_printBoard(localboard);
    while (gameState == 0) {
        while(SDL_PollEvent( event ) != 0) {
            //NULL pointer
            if (event == NULL) {
                gameState = 1;
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
                        moveScore = moveUp(localboard);
                        break;
                    case SDLK_DOWN:
                        moveScore = moveDown(localboard);
                        break;
                    case SDLK_LEFT:
                        moveScore = moveLeft(localboard);
                        break;
                    case SDLK_RIGHT:
                        moveScore = moveRight(localboard);
                        break;
                    default:
                        moveScore = -1;
                        break;
                }
                if (moveScore >=0 ) {
                    insertNewNumber(localboard);
                    totalScore += moveScore;
                    disp_sdl_printBoard(localboard);
                }
            }
        }
    }
    disp_sdl_end();
    return totalScore;
}

char *itoa(long n)
{
    int len = n==0 ? 1 : floor(log10l(abs(n)))+1;
    if (n<0) len++; // room for negative sign '-'

    char    *buf = (char*) calloc(sizeof(char), len+1); // +1 for null
    snprintf(buf, len, "%1ld", n);
    return   buf;
}
