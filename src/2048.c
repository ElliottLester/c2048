
// add your header comment here

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
// put any extra includes here, but don't delete the ones above
#include <curses.h>
#include <unistd.h>

#define SIZE    4
#define CELL_HIGH 6
#define CELL_WIDE 9


// The functions moveLeft, moveRight, moveUp, moveDown
// return -1 if the specified moving numbers  is not possible.
// Otherwise they move the numbers as indicated and return
// the change to the score from combining adjacent identical numbers.
// They return 0 if no numbers were combined.


//return zero for out of bound reads
int getvalue(int board[SIZE][SIZE] ,int x , int y) {
    if (x < SIZE && y < SIZE && x >= 0 && y >= 0) {
        return board[x][y];
    }
    else {
        return 0;
    }
}


int moveLeft(int board[SIZE][SIZE]) {
    //forward rows
    int row = 0, cell = 0, localScore = 0 , offset;
    bool hasMoved = false;
    for(row = 0; row < SIZE ; row++){
    offset = 0;
    //pack the row to the left
    for(int i = 0 ; i < SIZE; i++){
        cell = getvalue(board,i,row);
        if(cell != 0){
            board[offset][row] = cell;
            if(offset != i){
                board[i][row] = 0;
                hasMoved = true;
            }
            offset++;
        }
    }
    //compact row if possible
    for(int i = 0 ; i < SIZE; i++){
        cell = getvalue(board,i,row);
        if (cell == getvalue(board,i+1,row)) {
            if(cell != 0) {
                hasMoved = true;
            }
            board[i][row] = cell*2;
            localScore += cell*2;
            //shift
            for(int j = i+1 ; j < SIZE; j++) {
                board[j][row] = getvalue(board,j+1,row);
            }
        }
    }
    }
    if (hasMoved == false) {
        localScore = -1;
    }
    return localScore;
}

int moveRight(int board[SIZE][SIZE]) {
    //backwards rows
    int row = 0, cell = 0, localScore = 0 , offset;
    bool hasMoved = false;
    for(row = 0; row < SIZE ; row++){
    offset = SIZE-1;
    //pack the row to the right
    for(int i = SIZE-1 ; i >= 0 ; i--){
        cell = getvalue(board,i,row);
        if(cell != 0){
            board[offset][row] = cell;
            if(offset != i){
                board[i][row] = 0;
                hasMoved = true;
            }
            offset--;
        }
    }
    //compact the row if possible
    for(int i = SIZE-1 ; i >= 0; i--){
        cell = getvalue(board,i,row);
        if (cell == getvalue(board,i-1,row)) {
            if (cell != 0) {
            hasMoved = true;
            }
            board[i][row] = cell*2;
            localScore += cell*2;
            //shift
            for(int j = i-1 ; j >= 0; j--) {
                board[j][row] = getvalue(board,j-1,row);
            }
        }
    }
    }
    if (hasMoved == false) {
        localScore = -1;
    }
    return localScore;
}

int moveUp(int board[SIZE][SIZE]) {
    //forward columns
    int col = 0, cell = 0, localScore = 0 , offset;
    bool hasMoved = false;
    for(col = 0; col < SIZE ; col++){
    offset = 0;
    //pack the cols to the top
    for(int i = 0 ; i < SIZE; i++){
        cell = getvalue(board,col,i);
        if(cell != 0){
            board[col][offset] = cell;
            if(offset != i){
                board[col][i] = 0;
                hasMoved = true;
            }
            offset++;
        }
    }
    //compact the row if possible
    for(int i = 0 ; i < SIZE; i++){
        cell = getvalue(board,col,i);
        if (cell == getvalue(board,col,i+1)) {
            if (cell != 0) {
            hasMoved = true;
            }
            board[col][i] = cell*2;
            localScore += cell*2;
            //shift
            for(int j = i+1 ; j < SIZE; j++) {
                board[col][j] = getvalue(board,col,j+1);
            }
        }
    }
    }
    if (hasMoved == false) {
        localScore = -1;
    }
    return localScore;

    return -1;
}

int moveDown(int board[SIZE][SIZE]) {
    //backwards columns
    int col = 0, cell = 0, localScore = 0 , offset;
    bool hasMoved = false;
    for(col = 0; col < SIZE ; col++){
    offset = SIZE-1;
    //pack the cols to the bottom
    for(int i = SIZE-1 ; i >= 0 ; i--){
        cell = getvalue(board,col,i);
        if(cell != 0){
            board[col][offset] = cell;
            if(offset != i){
                board[col][i] = 0;
                hasMoved = true;
            }
            offset--;
        }
    }
    //compact the row if possible
    for(int i = SIZE-1 ; i >= 0; i--){
        cell = getvalue(board,col,i);
        if (cell == getvalue(board,col,i-1)) {
            if(cell != 0) {
                hasMoved = true;
            }
            board[col][i] = cell*2;
            localScore += cell*2;
            //shift
            for(int j = i-1 ; j >= 0; j--) {
                board[col][j] = getvalue(board,col,j-1);
            }
        }
    }
    }
    if (hasMoved == false) {
        localScore = -1;
    }
    return localScore;
}

// gameOver returns 0 iff it is possible to make a move on the board
// It returns 1 otherwise.

int gameOver(int board[SIZE][SIZE]) {
    return 0;
}

// boardContains2048 returns 1 iff the board contains 2048.
// It returns 0 otherwise.

int boardContains2048(int board[SIZE][SIZE]) {
    return 0;
}

//print a cell

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

void printBoard(int board[SIZE][SIZE]) {
    int tile_type = 0;
    for(int y = 0 ; y < SIZE ; y++) {
        for(int x = 0 ; x < SIZE ; x++) {
            printCell((x*CELL_WIDE),(y*CELL_HIGH),board[x][y],0);
        }
    }
    //decorate table
    for (int y = 0 ; y <= SIZE ; y++) {
        for(int x = 0 ; x <= SIZE ; x++) {
            if (x == 0 && y != 0) {
                mvaddch(y*(CELL_HIGH),0,ACS_LTEE);
            }
            else if (x != 0 && y == 0) {
                mvaddch(0,x*(CELL_WIDE),ACS_TTEE);
            }
            else if (x == SIZE && y != SIZE) {
                mvaddch(y*(CELL_HIGH),SIZE*(CELL_WIDE),ACS_RTEE);
            }
            else if (x != SIZE && y == SIZE) {
                mvaddch(SIZE*(CELL_HIGH),x*(CELL_WIDE),ACS_BTEE);
            }
            else {
                mvaddch((y)*(CELL_HIGH),(x)*(CELL_WIDE),ACS_PLUS);
            }
        }
    }
    mvaddch(0,0,ACS_ULCORNER);
    mvaddch(SIZE*(CELL_HIGH),0,ACS_LLCORNER);
    mvaddch(0,SIZE*(CELL_WIDE),ACS_URCORNER);
    mvaddch(SIZE*(CELL_HIGH),SIZE*(CELL_WIDE),ACS_LRCORNER);
}

void printHelp(void);
void insertNewNumber(int board[SIZE][SIZE]);

int main(int argc, char *argv[]) {
    int board[SIZE][SIZE] = {{2,0,0,0},{0,0,0,0},{2,0,0,0},{0,0,0,0}};
    int ch, score, moveScore, gameState, numbersRead;
    unsigned int seed;
    WINDOW * mainWin;


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

// add a new number to the board
// it will either be a 2 (90% probability) or a 4 (10% probability)
// do not change this function

void insertNewNumber(int board[SIZE][SIZE]) {
    int row, column;
    int index, availableSquares = 0;

    // count vacant squares
    for (row = 0; row < SIZE; row = row + 1) {
        for (column = 0; column < SIZE; column = column + 1) {
            if (board[row][column] == 0) {
                availableSquares = availableSquares + 1;
            }
        }
    }

    if (availableSquares == 0) {
        //printf("Internal error no available square\n");
        return;
    }

    // randomly pick a vacant square
    index = rand() % availableSquares;
    for (row = 0; row < SIZE; row = row + 1) {
        for (column = 0; column < SIZE; column = column + 1) {
            if (board[row][column] == 0) {
                if (index == 0) {
                    if (rand() % 10 == 0) {
                        board[row][column] = 4;
                    } else {
                        board[row][column] = 2;
                    }
                    return;
                }
                index = index - 1;
            }
        }
    }
}

