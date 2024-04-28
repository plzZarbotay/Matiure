CC = gcc
CFLAGS = -std=c99 --pedantic -Wall

compile: main.o stack.o
	$(CC) $^ -o main
	del /s *.o

clean:
	del main
	del *.o

