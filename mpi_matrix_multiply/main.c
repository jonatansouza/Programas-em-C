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

typedef struct {
	double *row;
	double *col;
	int position;
} Job_To_Do;

typedef struct {
	double value;
	int position;
} Results_Collection;


int main(int argc, char *argv[]) {
	Matrix *A = NULL, *B = NULL, *C = NULL;
	int ELEMENTS = 0;
	struct timeval start, finish;
	char input[BUFFER_SIZE];
	int i, child = 0;
	int npes, myrank;
	double *col_array;
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
			col_array = (double *) malloc(sizeof(double) * ELEMENTS);
		}else{

			printf("ERRO: Numero incorreto de argumentos\n");
			printf("Usage: ./main <matrix_A> <matrix_B>\n");
			return 1;

		}
		/*for (i = 0; i < ELEMENTS; i++)
		        for(j=0; j< ELEMENTS; j++)
		                matrix_multiply_by_element(C, i, j, A, B);
		 */

		for (i = 0; i < (npes-1); i++) {
			MPI_Send(&ELEMENTS, 1, MPI_INT, i, DEFAULT_TAG, MPI_COMM_WORLD);
		}

		double *row = get_all_nodes(A);
		while (matrix_out_of_bounds(C, child)) {
			MPI_Send(&child, 1, MPI_INT, child%(npes-1), DEFAULT_TAG, MPI_COMM_WORLD);

			matrix_recieve_col_array(B, col_array, child%ELEMENTS);

			MPI_Send(&row[(child/ELEMENTS)*ELEMENTS], ELEMENTS, MPI_DOUBLE, child%(npes-1), DEFAULT_TAG, MPI_COMM_WORLD);
			MPI_Send(col_array, ELEMENTS, MPI_DOUBLE, child%(npes-1), DEFAULT_TAG, MPI_COMM_WORLD);
			child++;
		}

		/* Finalizando todos os processos*/
		child = END_TASK;
		for (i = 0; i < (npes-1); i++) {
			MPI_Send(&child, 1, MPI_INT, i, DEFAULT_TAG, MPI_COMM_WORLD);
		}

		MPI_Status st;

	/*	for (i = 0; i < (npes-1); i++) {
			MPI_Recv(rc, (jobsPerProcess+1), MPI_INT, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);
			int count = 0;
			while (rc[count].position != END_TASK) {
				matrix_set_elements(C, rc[count].position, rc[count].value);
				count++;
			}
		}*/

		/* matrix_print(A);
		matrix_print(B);
		matrix_print(C);
 */

		matrix_destroy(A);
		matrix_destroy(B);
		matrix_destroy(C);
	}else{
		int position = 0, count = 0,  ELEMENTS = 0;
		double *row, *col;
		double response[2];
		MPI_Status st;
		MPI_Recv(&ELEMENTS, 1, MPI_INT, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);
		row = (double * ) malloc (sizeof(double) * ELEMENTS);
		col = (double * ) malloc (sizeof(double) * ELEMENTS);
		while (position != END_TASK) {
			MPI_Recv(&position, 1, MPI_INT, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);
			if (position != END_TASK) {
				MPI_Recv(row, ELEMENTS, MPI_DOUBLE, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);
				MPI_Recv(col, ELEMENTS, MPI_DOUBLE, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD, &st);

				printf("****** %d \n", myrank);
				printf("linha \n");
				for (i = 0; i < ELEMENTS; i++) {
					printf(" %lf ", row[i]);
				}
				printf("\ncoluna \n");
				for (i = 0; i < ELEMENTS; i++) {
					printf(" %lf ", col[i]);
				}
				printf("\n");

				/* calcular aqui */

				/* remover isso */
				response[0] = END_TASK;
				response[1] = END_TASK;
				/* remover isso */

				MPI_Send(response, 2, MPI_DOUBLE, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD);
			}else{
				break;
			}
		}
		response[0] = END_TASK;
		response[1] = END_TASK;

		MPI_Send(response, 2, MPI_DOUBLE, (npes-1), DEFAULT_TAG, MPI_COMM_WORLD);

	}

	MPI_Finalize();


	return 0;
}
