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
	int i, count, jobSize, jobExtra, child = 0;
	int npes, myrank;
	double *col_array, *response;
	char nome[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	gethostname(nome, 100);

	if (myrank == 0) {
		if(argc > 2) {
			strcpy(input, argv[1]);
			if ((ELEMENTS = matrix_register_A(&A, input)) < 0) {
				return 0;
			}
			strcpy(input, argv[2]);
			if(matrix_register_B(&B, input) != ELEMENTS) {
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



	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&ELEMENTS, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(myrank != 0) {
		matrix_result_create(&B, ELEMENTS);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(B, ELEMENTS*ELEMENTS, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if(myrank == 0) {
		MPI_Status status;
		MPI_Request request;
		jobSize = ELEMENTS/npes;
		jobExtra = ELEMENTS/npes + ELEMENTS%npes;
		int alreadyDone = ELEMENTS*jobExtra;
		for (i = 0; i < npes-1; i++) {
			MPI_Isend(&A[alreadyDone + ELEMENTS*i*jobSize], ELEMENTS*jobSize, MPI_DOUBLE, i+1, DEFAULT_TAG, MPI_COMM_WORLD, &request);
		}
		for (i = 0; i < jobExtra; i++) {
			matrix_multiply_by_segment(&A[i*ELEMENTS], B, ELEMENTS, &C[i*ELEMENTS]);
		}

		for ( i = 0; i < npes-1; i++)
			MPI_Recv(&C[alreadyDone + ELEMENTS*i*jobSize], ELEMENTS*jobSize, MPI_DOUBLE, i+1, DEFAULT_TAG, MPI_COMM_WORLD, &status);

		/*matrix_print(C, ELEMENTS);*/

	}else{

		MPI_Status status;
		MPI_Request request;
		jobSize = ELEMENTS/npes;
		matrix_result_alloc(&A, ELEMENTS*jobSize);
		matrix_result_alloc(&C, ELEMENTS*jobSize);
		MPI_Recv(A, ELEMENTS*jobSize, MPI_DOUBLE, 0, DEFAULT_TAG, MPI_COMM_WORLD, &status);
		for (i = 0; i < jobSize; i++)
			matrix_multiply_by_segment(&A[ELEMENTS*i], B, ELEMENTS, &C[i*ELEMENTS]);
		MPI_Isend(C, ELEMENTS*jobSize, MPI_DOUBLE, 0, DEFAULT_TAG, MPI_COMM_WORLD, &request);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);

	MPI_Finalize();

	return 0;
}
