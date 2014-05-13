#
#  Makefile
#
#  Created on: 24/08/2011
#  Modified on: 09/09/2011
#  Author: Elliott
#  Student No: Z3333600
#

CC = gcc
CFLAGS = -Wall -g -lncurses -std=c99

MAIN =  src/main.o

OBJS = src/board.o src/display.o

LIBS =


TARGET = 2048

all:	 $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $(TARGET)

clean:
	rm -f $(OBJS) $(MAIN) $(TARGET)
