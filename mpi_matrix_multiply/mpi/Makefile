CC := mpicc

OBJECTS := main.o matrix.o
LIBS := -lm

main:${OBJECTS}
	${CC} -o main ${OBJECTS} ${LIBS}

clean:
	rm *.o main
