#ifndef BOARD_H_   /* Include guard */
#define BOARD_H_

//game board struct
struct game {
    int * board;
    int size;
};

//exported functions
struct game * board_create( int size);
int board_free(struct game * input);

int board_get(struct game * input ,int x , int y);
int board_set(struct game * input ,int x , int y,int value);
int moveLeft(struct game * input );
int moveRight(struct game * input );
int moveDown(struct game * input );
int moveUp(struct game * input );
void insertNewNumber(struct game * input );

#endif
