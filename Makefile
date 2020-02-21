CC = gcc
CFLAGS = -g -std=gnu11 -Wall
LDFLAGS = -lm

statistica: array.o list.o dist.o samples.o statistica.o

clean:
	del *.o *.exe
