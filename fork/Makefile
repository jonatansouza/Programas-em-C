CC := cc
CFLAGS := -ansi -Wall -pedantic -Wimplicit-function-declaration
LIBS := -lm

OBJECTS := main.o 

main:${OBJECTS}
	${CC} ${CFLAGS} -o main ${OBJECTS} ${LIBS}

clean:
	rm *.o main
