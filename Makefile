CC = gcc
CFLAGS = -Wall -std=c11 -g
OBJS = statistica.o samples.o str.o list.o dist.o array.o

statistica : $(OBJS) -lm	

clean:
	rm -f statistica *.o
