#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "display.h"

int main(int argc, char *argv[]) {
    struct game * localBoard = malloc(sizeof(struct game));
    int ch, score, moveScore, gameState, numbersRead;
    unsigned int seed;
    WINDOW * mainWin;

    localBoard->size = SIZE;
    localBoard->board = malloc(sizeof(int)*localBoard->size*localBoard->size);


    //ncurses screen init
    initscr();
    cbreak();
    noecho();

    //capture special keys
    keypad(stdscr, TRUE);

    //no blocking read enable
    //nodelay(stdscr, TRUE);

    //hide cursor
    curs_set(0);

    //create stdscr window
    mainWin = newwin(17, 21, 0, 0);

    // initialize random generator with command-line argument if provided
    // or with current time
    if (argc > 1){
        seed = atoi(argv[1]);
    } else {
        seed = time(0);
    }
    srand(seed);

    moveScore = 0;

    while (gameState == 0) {
        wrefresh(stdscr);
        printBoard(board);
        wrefresh(mainWin);

        if ((ch = getch()) == ERR) {
            //user has not responded.
            usleep(100);
        }
        else {
            //the user has responded.
            switch(ch) {
                case 'q':
                    gameState = -1;
                    moveScore = -1;
                    break;
                case KEY_UP:
                    moveScore = moveUp(board);
                    break;
                case KEY_DOWN:
                    moveScore = moveDown(board);
                    break;
                case KEY_LEFT:
                    moveScore = moveLeft(board);
                    break;
                case KEY_RIGHT:
                    moveScore = moveRight(board);
                    break;
                default:
                    moveScore = -1;
                    break;
            }
            if (moveScore >= 0) {
                insertNewNumber(board);
            }

        }
    }

    //turn off all the ncurses code
    endwin();

    return 0;
}