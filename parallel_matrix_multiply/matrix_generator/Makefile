CC := cc
CFLAGS := -Wall -pedantic -Wimplicit-function-declaration
LIBS := -Wcpp

OBJECTS := main.o

main:${OBJECTS}
	${CC} ${CFLAGS} -o main ${OBJECTS} ${LIBS}

clean:
	rm *.o main
