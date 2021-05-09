CC = gcc
CFLAGS = -g -std=gnu11 -Wall
LDFLAGS = -lm

statistica: array.o list.o str.o dist.o samples.o statistica.o

clean:
	rm *.o
