all: main.o string.o table.o
	gcc -o main main.o string.o table.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

string.o:
	gcc --std=c99 --pedantic -Wall -c string.c

table.o:
	gcc --std=c99 --pedantic -Wall -c table.c

clean:
	rm main main.o string.o table.o