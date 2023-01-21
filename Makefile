CC = gcc
CFLAGS = -Wall -g -std=c11
LDLIBS = -lm

statistica: statistica.o dist.o

clean:
	rm statistica *.o
