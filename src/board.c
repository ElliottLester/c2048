#include "board.h"

//return zero for out of bound reads
int getvalue(struct game * input  ,int x , int y) {
    if (x < SIZE && y < SIZE && x >= 0 && y >= 0) {
        return board[x][y];
    }
    else {
        return 0;
    }
}



// The functions moveLeft, moveRight, moveUp, moveDown
// return -1 if the specified moving numbers  is not possible.
// Otherwise they move the numbers as indicated and return
// the change to the score from combining adjacent identical numbers.
// They return 0 if no numbers were combined.

int moveLeft(struct game * input ) {
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

int moveRight(struct game * input ) {
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

int moveUp(struct game * input ) {
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

int moveDown(struct game * input ) {
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


// add a new number to the board
// it will either be a 2 (90% probability) or a 4 (10% probability)
// do not change this function

void insertNewNumber(struct game * input) {
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