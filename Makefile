CC = gcc
CFLAGS = -Wall -g -std=c11
LDFLAGS = -lm

statistica: statistica.o dist.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm statistica *.o
