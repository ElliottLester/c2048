#include "display.h"

void printCell(int column,int row, int value,int type) {

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

    if (value > 0 && value < 100) {
        mvprintw(row+2,column+2," %2d",value);
    }
    else if (value > 0 && value < 10000) {
        mvprintw(row+2,column+1,"%4d",value);
    }
    else {
        mvprintw(row+2,column+1,"    ");
    }
}

// printBoard displays the board.

void printBoard(struct game * input) {
    int size = input->size;
    int * board = *input->board;
    for(int y = 0 ; y < size ; y++) {
        for(int x = 0 ; x < size ; x++) {
            printCell((x*CELL_WIDE),(y*CELL_HIGH),board[x][y],0);
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
