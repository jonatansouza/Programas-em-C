CC := cc
CFLAGS := -ansi -Wall -pedantic -Wimplicit-function-declaration
LIBS := -pthread

OBJECTS := main.o matrix.o

main:${OBJECTS}
	${CC} ${CFLAGS} -o main ${OBJECTS} ${LIBS}

clean:
	rm *.o main
