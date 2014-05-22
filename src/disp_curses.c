#include "disp_curses.h"
#include <math.h>

#define TILE2       1
#define TILE4       2
#define TILE8       3
#define TILE16      4
#define TILE32      5
#define TILE64      6
#define TILE128     7
#define TILE256     8
#define TILE512     9
#define TILE1024    10
#define TILE2048    11

void display_init() {

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

    //start colours
    start_color();

    //skip first 8 colours
    //blank
    init_color(8,933,894,854);
    //2 tile background - forground(text)
    init_color(9,238,228,218);
    //4 tile background
    init_color(10,929,878,784);
    //8 tile background - forground
    init_color(11,242,177,121);
    init_color(12,249,246,242);
    //16 tile background
    init_color(13,245,149,99);
    //32 tile background
    init_color(14,246,124,95);
    //64 tile background
    init_color(15,246,94,59);
    //128 tile background
    init_color(16,237,207,114);
    //256 tile background
    init_color(17,237,204,97);
    //512 tile background
    init_color(18,237,200,80);
    //1024 tile background
    init_color(19,237,197,63);
    //2048 tile background - forground
    init_color(20,237,194,46);

    init_pair(0,COLOR_BLACK,8);
    init_pair(TILE2,COLOR_WHITE,9);
    init_pair(TILE4,COLOR_BLACK,10);
    init_pair(TILE8,11,12);
    init_pair(TILE16,11,13);
    init_pair(TILE32,COLOR_BLACK,14);
    init_pair(TILE64,COLOR_BLACK,15);
    init_pair(TILE128,COLOR_WHITE,16);
    init_pair(TILE256,11,17);
    init_pair(TILE512,11,18);
    init_pair(TILE1024,11,19);
    init_pair(TILE2048,11,20);
}

void display_end() {
    endwin();
}

int display_code(int input) {
    double result;
    result = (log10(input)/log10(2));
    return round(result);

}

void printCell(int column,int row, int value,int type) {

    int cell_row_center = CELL_HIGH / 2;
    int cell_col_center = CELL_WIDE / 2;

    //center top bottom edges
    for(int i = 1 ;i < CELL_WIDE ; i++) {
        mvaddch(row,column+i,ACS_HLINE);
        mvaddch(row+CELL_HIGH,column+i,ACS_HLINE);
    }

    //center 3 lines
    for(int i = 1 ; i < CELL_HIGH ; i++) {
        mvaddch(row+i,column,ACS_VLINE);
        mvaddch(row+i,column+CELL_WIDE,ACS_VLINE);
    }

    attron(COLOR_PAIR(display_code(value)));
    attron(A_BOLD);

    for (int i = 1 ; i < CELL_HIGH ; i++) {
        for (int j=1 ; j < CELL_WIDE-1 ; j++) {
            mvaddch(row+i,column+j,' ');
        }
    }

    if (value > 0 && value < 100) {
        mvprintw(row+cell_row_center,(column+cell_col_center)-1,"%2d",value);
    }
    else if (value > 0 && value < 10000) {
        mvprintw(row+cell_row_center,(column+cell_col_center)-2,"%4d",value);
    }
    else {
        mvprintw(row+cell_row_center,column+cell_row_center-1,"    ");
    }
    attroff(COLOR_PAIR(display_code(value)));
    attroff(A_BOLD);
}

// printBoard displays the board.

void printBoard(struct game * input) {
    int size = input->size;
    int cell = 0;
    for(int y = 0 ; y < size ; y++) {
        for(int x = 0 ; x < size ; x++) {
            cell = board_get(input,x,y);
            printCell((x*CELL_WIDE),(y*CELL_HIGH),cell,0);
        }
    }
    //decorate table
    for (int y = 0 ; y <= size ; y++) {
        for(int x = 0 ; x <= size ; x++) {
            if (x == 0 && y != 0) {
                mvaddch(y*(CELL_HIGH),0,ACS_LTEE);
            }
            else if (x != 0 && y == 0) {
                mvaddch(0,x*(CELL_WIDE),ACS_TTEE);
            }
            else if (x == size && y != size) {
                mvaddch(y*(CELL_HIGH),size*(CELL_WIDE),ACS_RTEE);
            }
            else if (x != size && y == size) {
                mvaddch(size*(CELL_HIGH),x*(CELL_WIDE),ACS_BTEE);
            }
            else {
                mvaddch((y)*(CELL_HIGH),(x)*(CELL_WIDE),ACS_PLUS);
            }
        }
    }
    mvaddch(0,0,ACS_ULCORNER);
    mvaddch(size*(CELL_HIGH),0,ACS_LLCORNER);
    mvaddch(0,size*(CELL_WIDE),ACS_URCORNER);
    mvaddch(size*(CELL_HIGH),size*(CELL_WIDE),ACS_LRCORNER);
}

void curses_main(struct game * localBoard, unsigned int seed) {
    int ch,moveScore,gameState;
    gameState = 0;
    moveScore = 0;

    display_init();

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
                    moveScore = moveUp(localBoard);
                    break;
                case KEY_DOWN:
                    moveScore = moveDown(localBoard);
                    break;
                case KEY_LEFT:
                    moveScore = moveLeft(localBoard);
                    break;
                case KEY_RIGHT:
                    moveScore = moveRight(localBoard);
                    break;
                default:
                    moveScore = -1;
                    break;
            }
            if (moveScore >= 0) {
                insertNewNumber(localBoard);
            }

        }
    }

    //turn off all the ncurses code
    display_end();
}

