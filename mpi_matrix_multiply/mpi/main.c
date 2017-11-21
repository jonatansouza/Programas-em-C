#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <mpi.h>
#include "matrix.h"

#define BUFFER_SIZE 256
#define DEFAULT_TAG 0
#define END_TASK -1

long module(long n){
	return ((n >= 0 ) ? n : -(n));
}


int main(int argc, char *argv[]) {
	double *A = NULL, *B = NULL, *C = NULL;
	int ELEMENTS = 0;
	struct timeval start, finish;
	char input[BUFFER_SIZE];
	int i, count, totalJobs, child = 0;
	int npes, myrank;
	double *col_array, *response;
	char nome[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	gethostname(nome, 100);
	/*printf("From process %d out of %d, Hello World! (%s)\n",
	       myrank, npes, nome);*/

/*
        printf("*******************************\n" );
        printf("*                             *\n" );
        printf("*   Matrix product caculator  *\n" );
        printf("*                             *\n" );
        printf("*******************************\n" );
        /**
 * Check the user insert the file path from args
 */


	if (myrank == (npes-1)) {
		if(argc > 2) {
			strcpy(input, argv[1]);
			if ((ELEMENTS = matrix_register(&A, input)) < 0) {
				return 0;
			}
			strcpy(input, argv[2]);
			if(matrix_register(&B, input) != ELEMENTS) {
				printf("ERRO: Não é possível realizar a multipĺicação!\n");
				return 0;
			}
			if(!matrix_result_create(&C, ELEMENTS)) {
				return 0;
			}
		}else{
			printf("ERRO: Numero incorreto de argumentos\n");
			printf("Usage: ./main <matrix_A> <matrix_B>\n");
			return 1;
		}

		child = 0;
		while (matrix_out_of_bounds(C, child, ELEMENTS*ELEMENTS)) {
			matrix_multiply_by_element(C, ELEMENTS, child / ELEMENTS, child % ELEMENTS, A, B);
			child++;
		}

	}
	/*matrix_print(A, ELEMENTS);
	   matrix_print(B, ELEMENTS);
	   matrix_print(C, ELEMENTS);
	 */
	/*	matrix_destroy(A);
	        matrix_destroy(B);
	        matrix_destroy(C);*/

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&ELEMENTS, 1, MPI_INT, npes-1, MPI_COMM_WORLD);

	if(myrank != npes-1){
		matrix_result_create(&A, ELEMENTS);
		matrix_result_create(&B, ELEMENTS);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(B, ELEMENTS*ELEMENTS, MPI_DOUBLE, npes-1, MPI_COMM_WORLD);
	MPI_Bcast(A, ELEMENTS*ELEMENTS, MPI_DOUBLE, npes-1, MPI_COMM_WORLD);

	if(myrank != npes-1){

	}else{

	}

	MPI_Finalize();

	return 0;
}
