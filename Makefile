#
#  Makefile
#
#  Created on: 24/08/2011
#  Modified on: 09/09/2011
#  Author: Elliott
#  Student No: Z3333600
#

CC = gcc
CFLAGS = -Wall -g -lncurses -std=c99 -lm -lSDL2

MAIN =  src/main.o

OBJS = src/board.o src/disp_curses.o src/disp_sdl.o

LIBS =


TARGET = 2048

all:	 $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OPTDEBUG) $(OBJS) $(MAIN) -o $(TARGET)

clean:
	rm -f $(OBJS) $(MAIN) $(TARGET)
