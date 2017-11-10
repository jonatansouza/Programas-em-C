#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "matrix.h"

#define BUFFER_SIZE 256


long module(long n){
	return ((n >= 0 ) ? n : -(n));
}

int main(int argc, char const *argv[]) {
	Matrix *A = NULL, *B = NULL, *C = NULL;
	int ELEMENTS = 0;
	int qtd_ants, i;
	int father=0, child=0;
	char input[BUFFER_SIZE];
	struct timeval start, finish;

	/*printf("*******************************\n" );
	printf("*                             *\n" );
	printf("*   Matrix product caculator  *\n" );
	printf("*                             *\n" );
	printf("*******************************\n" );
*/
	/**
	 * Check the user insert the file path from args
	 */
	if(argc > 3) {
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
		qtd_ants = atoi(argv[3]);
	}else{

		printf("ERRO: Numero incorreto de argumentos\n");
		printf("Usage: ./main <matrix_A> <matrix_B> <qtd_threads>\n");
		return 1;

	}

	father = getpid();
	/* printf("Criando processos e executando a multiplicação!\n"); */
	gettimeofday(&start, NULL);

	for (i = 0; i < qtd_ants; i++) {
		if(father == getpid()) {
			child = fork();
			if(child == 0) {
				child = i;
				while (matrix_out_of_bounds(C, child)) {
					matrix_multiply_by_element(C, child / ELEMENTS, child % ELEMENTS, A, B);
					child += qtd_ants;
				}
			}
		}
	}
	if (father == getpid()) {
		/*WAIrT ALL PROCESS */
		while ((wait( NULL)) != -1);

		gettimeofday(&finish, NULL);
		printf("%ld.%ld \n", (long) (finish.tv_sec - start.tv_sec), module((long) (finish.tv_usec - start.tv_usec)));
		/*matrix_print(A);
		matrix_print(B);
		matrix_print(C);*/


		matrix_destroy(A);
		matrix_destroy(B);
		matrix_destroyShm(C);
	}


	return 0;
}
