#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include "board.h"
#include "disp_curses.h"
#include "disp_sdl.h"

int main(int argc, char **argv) {

    unsigned int seed;
    int board_size;

    int flag_curses = 1;
    int flag_sdl = 0;
    char* opt_seed = NULL;
    char* opt_board = NULL;
    int c;
    while ((c = getopt(argc, argv, "CSs:b:")) != -1){
        switch(c)
        {
            case 'C':
                flag_curses = 1;
                flag_sdl = 0;
                break;
            case 'S':
                flag_curses = 0;
                flag_sdl = 1;
                break;
            case 's':
                opt_seed = optarg;
                break;
            case 'b':
                opt_board = optarg;
                break;
        }
    }

    if (opt_seed == NULL) {
        seed = time(0);
    } else {
        seed = atoi(opt_seed);
    }

    if (opt_board == NULL) {
        board_size = 4;
    } else {
        board_size = atoi(opt_board);
        if (board_size < 3 || board_size > 15)
            board_size = 4;
    }

    struct game * localBoard = board_create(board_size);

    srand(seed);

    insertNewNumber(localBoard);
    insertNewNumber(localBoard);

    if(flag_curses == 1) {
        curses_main(localBoard,seed);
    }
    else if (flag_sdl == 1) {
        sdl_main(localBoard,seed);
    }

    board_free(localBoard);

    return 0;
}
