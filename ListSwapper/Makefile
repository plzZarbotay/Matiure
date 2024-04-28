CC = gcc
CFLAGS = -std=c99 --pedantic -Wall -g

all: main	
	gcc -std=c99 --pedantic -Wall -g   -c -o main.o main.c      
	gcc -std=c99 --pedantic -Wall -g   -c -o list.o list.c
	gcc -std=c99 --pedantic -Wall -g   -c -o iterator.o iterator.c
	gcc list.o main.o iterator.o -o main                            
	
main: list.o main.o iterator.o
	$(CC) $^ -o $@

