CC=gcc

all:main
main:main.o list.o
	gcc -g -o main main.o list.o -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
list.o:list.c list.h
	$(CC) -o list.o -c list.c -Wall
main.o:main.c list.h
	$(CC) -o main.o -c main.c -Wall

clean:
	rm *.o main
