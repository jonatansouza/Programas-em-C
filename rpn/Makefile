CC := cc
CFLAGS := -ansi -Wall -pedantic -Wimplicit-function-declaration

OBJECTS := main.o stack.o queue.o rpn-utils.o 

main:${OBJECTS}
	${CC} ${CFLAGS} -o main ${OBJECTS}

clean:
	rm *.o main
