CC = gcc
CFLAGS = -g -std=c11 -Wall

statistica: dist.o statistica.o -lm

clean:
	rm statistica *.o
