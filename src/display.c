#include "display.h"

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

}

void display_end() {
    endwin();
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
    attron(A_STANDOUT);

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
    attroff(A_STANDOUT);
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
