#include "disp_sdl.h"

//drawing constants
//keep in mind the charaters
//are taller than they are wide

static int display_code(int input) {
    double result;
    if (input > 0 && input <= 2048) {
    result = (log10(input)/log10(2));
    } else if (input == 0) {
        result = 0 ;
    } else {
        result = 13;
    }
    return round(result);

}

static struct color_tuple backgrounds[COLORS] = {
    {238,228,218},
    {238,228,218},
    {237,224,200},
    {242,177,121},
    {245,149,99},
    {246,124,95},
    {246,94,59},
    {237,207,114},
    {237,204,97},
    {237,200,80},
    {237,197,63},
    {237,194,46},
    {60,58,50},
    {0,0,0}
};

static struct color_tuple forgrounds[COLORS] = {
    {119,110,101},
    {119,110,101},
    {119,110,101},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242},
    {249,246,242}
};


/*
 *  sets up the terminal for input and drawing
 */
int disp_sdl_init(void){

    if(window == NULL) {

        // Initialize SDL video.
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0)
        return 1;

        // Create the window where we will draw.
        window = SDL_CreateWindow("SDL_RenderClear",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              768, 768,
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

        if(TTF_Init() != 0)
            return 1;

        // load font.ttf at size 16 into font
        font=TTF_OpenFont("/usr/share/fonts/corefonts/comic.ttf", 48);
        if(!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            return 1;
        }
        TTF_SetFontStyle(font,TTF_STYLE_BOLD);
        TTF_SetFontKerning(font,1);
        event = malloc(sizeof(SDL_Event));
        return 0;
    } else {
        return 1;
    }
}

void disp_sdl_end(void){
    free(event);
    TTF_Quit();
    SDL_Quit();
    return;
}

void disp_sdl_printCell(int column,int row, int value,int cell_width, int cell_height)
{
    char* buffer;  // store the chars to print
    SDL_Surface* text_surface; //the render on that text
    //create the cell canvas
    SDL_Surface* cell;
    cell = SDL_CreateRGBSurface(0,cell_width,cell_height,32,0,0,0,0);
    SDL_FillRect(cell,NULL,SDL_MapRGBA((cell->format),187,173,160,89));
    //Create the background for the cell
    SDL_Rect rectangle={4,4,cell_width-8,cell_height-8};

    //calculate cell color_code
    int color_code = display_code(value);
    //apply the cell background to the surface
    SDL_FillRect(cell, &rectangle, SDL_MapRGBA((cell->format),
            backgrounds[color_code].r,backgrounds[color_code].g,backgrounds[color_code].b,255));

    //if the value is not zero print the number in the cell
    if (color_code > 0){
        //convert and Create the text layer
        buffer = itoa(value);
        SDL_Color text_color = {forgrounds[color_code].r,forgrounds[color_code].g,forgrounds[color_code].b};
        //resize the text to fit in the cell
        text_surface = TTF_RenderUTF8_Blended(font,buffer,text_color);
        if (text_surface->w > cell_width) {
            double scale_ratio = cell_width/text_surface->w;
            text_surface->w = floor(text_surface->w*scale_ratio);
            text_surface->h = floor(text_surface->h*scale_ratio);
        }

        SDL_Rect text_region = {(cell_width-text_surface->w)/2,(cell_height-text_surface->h)/2,0,0};
        //copy the text_surface to the cell surface
        SDL_BlitSurface(text_surface,NULL,cell,&text_region);
    }
    //the location where the cell will go
    SDL_Rect cell_region = {cell_width*column,cell_height*row,cell_width,cell_height};
    //render the cell
    SDL_Texture* rendered_cell = SDL_CreateTextureFromSurface(renderer,cell);

    //render the cell to the board
    SDL_RenderCopy(renderer,rendered_cell,NULL,&cell_region);

    //free the cell surface
    SDL_FreeSurface(cell);
    if (color_code > 0) {
        //free the text buffer
        free(buffer);
        //free the text surface
        SDL_FreeSurface(text_surface);
    }
    return;
}

void disp_sdl_printBoard(struct game * input){
    int* win_width = malloc(sizeof(int));
    int* win_height = malloc(sizeof(int));
    SDL_GetWindowSize(window,win_width,win_height);
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
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
    struct game * old_board;
    gameState = 0;
    moveScore = 0;
    totalScore = 0;
    if (disp_sdl_init() != 0){
        disp_sdl_end();
        return 1;
    }
    disp_sdl_printBoard(localboard);
    while(gameState == 0 && SDL_WaitEvent( event ) != 0) {
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
                    old_board = board_create(localboard->size);
                    board_copy(localboard,old_board);
                    moveScore = moveUp(localboard);
                    board_free(old_board);
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

    disp_sdl_end();
    return totalScore;
}

char *itoa(long n)
{
    int len = n==0 ? 1 : floor(log10l(abs(n)))+1;
    if (n<0) len++; // room for negative sign '-'

    char    *buf = (char*) calloc(sizeof(char), len+1); // +1 for null
    snprintf(buf, len+1, "%ld", n);
    return   buf;
}
