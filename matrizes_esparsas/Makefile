CC=gcc

all:main 
main:main.o matrix.o
	gcc -g -o main main.o matrix.o -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition 
list.o:matrix.c matrix.h
	$(CC) -o matrix.o -c matrix.c -Wall
main.o:main.c matrix.h
	$(CC) -o main.o -c main.c -Wall

clean:
	rm *.o main
