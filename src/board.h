#ifndef BOARD_H_   /* Include guard */
#define BOARD_H_

//game board struct
struct game {
    //pointer to the array that is size*size long
    int * board;
    //the size of the grid
    int size;
};

//exported functions

/*
 * Creates a new board in memory
 * Returns a pointer to the new struct
 */
struct game * board_create(int size);

/*
 * Cleans up a board given from board_create
 * Returns 0 on sucess
 */
int board_free(struct game * input);

/*
 * Returns the value at the given position on the given board
 * Returns 0 if outside the grid
 * (used for shifting on new cells)
 */
int board_get(struct game * input ,int x , int y);

/*
 * Sets the value at the given postion on the given table
 * Returns 0 on sucess
 */
int board_set(struct game * input ,int x , int y,int value);

/*
 * Performs a left,right,up,down move actions on the given board
 * Returns:
 * -1 if the move fails
 * 0 if there was a move but no merges
 * >0 the value of the merges
 */
int moveLeft(struct game * input );
int moveRight(struct game * input );
int moveDown(struct game * input );
int moveUp(struct game * input );

/*
 *inserts new numbers into the given grid over blank(0) spaces
 */
void insertNewNumber(struct game * input );

#endif
