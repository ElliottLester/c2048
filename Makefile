#
#  Makefile
#
#  Created on: 24/08/2011
#  Modified on: 09/09/2011
#  Author: Elliott
#  Student No: Z3333600
#

CC = gcc
OPTFLAGS = -O3
OPTDEBUG = -g
CFLAGS = -Wall -lncurses -std=c99

MAIN =  src/main.o

OBJS = src/board.o src/display.o

LIBS =


TARGET = 2048

all:	 $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OPTDEBUG) $(OBJS) $(MAIN) -o $(TARGET)

clean:
	rm -f $(OBJS) $(MAIN) $(TARGET)

fast:	$(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) $(MAIN) -o $(TARGET)
