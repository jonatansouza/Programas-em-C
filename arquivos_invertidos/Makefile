CC=gcc

all:main
main:main.o index.o
	$(CC) -o main main.o index.o -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
list.o:index.c index.h
	$(CC) -o index.o -c index.c -Wall
main.o:main.c index.h
	$(CC) -o main.o -c main.c -Wall

clean:
	rm *.o main
