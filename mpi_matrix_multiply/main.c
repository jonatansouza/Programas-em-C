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
	Matrix *A = NULL, *B = NULL, *C = NULL;
	int ELEMENTS = 0;
	struct timeval start, finish;
	char input[BUFFER_SIZE];
	int i, child = 0;
	int npes, myrank;
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
			if (!matrix_register(&A, input)) {
				return 0;
			}
			strcpy(input, argv[2]);
			if(!matrix_register(&B, input)) {
				return 0;
			}
			if(!matrix_result_create(&C, A, B)) {
				return 0;
			}
			ELEMENTS = matrix_get_elements(C);

		}else{

			printf("ERRO: Numero incorreto de argumentos\n");
			printf("Usage: ./main <matrix_A> <matrix_B>\n");
			return 1;

		}
		/*for (i = 0; i < ELEMENTS; i++)
		        for(j=0; j< ELEMENTS; j++)
		                matrix_multiply_by_element(C, i, j, A, B);
		*/

		while (matrix_out_of_bounds(C, child)) {
			MPI_Send(&child, 1, MPI_INT, child%(npes-1), DEFAULT_TAG, MPI_COMM_WORLD);
			child++;
		}
		child = END_TASK;
		for (i = 0; i < (npes-1); i++) {
			printf("finalizando %d\n", i);
			MPI_Send(&child, 1, MPI_INT, i, DEFAULT_TAG, MPI_COMM_WORLD);
		}
		matrix_print(A);
		matrix_print(B);
		matrix_print(C);

		matrix_destroy(A);
		matrix_destroy(B);
		matrix_destroy(C);
	}else{
		int result = 0;
		MPI_Status st;
		while (result != END_TASK) {
			MPI_Recv(&result, 1, MPI_INT, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);
			if (result != END_TASK) {
				
			}
		}
	}

	MPI_Finalize();


	return 0;
}
