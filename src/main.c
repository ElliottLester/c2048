#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "display.h"

int main(int argc, char *argv[]) {
    struct game * localBoard = board_create(4);
    int ch, moveScore, gameState ;
    unsigned int seed;
    //int score;

    display_init();

    // initialize random generator with command-line argument if provided
    // or with current time
    if (argc > 1){
        seed = atoi(argv[1]);
    } else {
        seed = time(0);
    }
    srand(seed);

    moveScore = 0;

    board_set(localBoard,1,0,2);
    board_set(localBoard,3,0,2);

    while (gameState == 0) {
        wrefresh(stdscr);
        printBoard(localBoard);
        wrefresh(stdscr);

        if ((ch = getch()) == ERR) {
            //user has not responded.
        }
        else {
            //the user has responded.
            switch(ch) {
                case 'q':
                    gameState = -1;
                    moveScore = -1;
                    break;
                case KEY_UP:
                    //moveScore = moveUp(board);
                    break;
                case KEY_DOWN:
                    //moveScore = moveDown(board);
                    break;
                case KEY_LEFT:
                    //moveScore = moveLeft(board);
                    break;
                case KEY_RIGHT:
                    //moveScore = moveRight(board);
                    break;
                default:
                    moveScore = -1;
                    break;
            }
            if (moveScore >= 0) {
                //insertNewNumber(board);
            }

        }
    }

    //turn off all the ncurses code
    display_end();

    return 0;
}
