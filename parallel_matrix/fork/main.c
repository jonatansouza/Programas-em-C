#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include "matrix.h"

#define BUFFER_SIZE 256


int main(int argc, char const *argv[]) {
	Matrix *A = NULL, *B = NULL, *C = NULL;
	int ELEMENTS = 0;
	int qtd_ants, i;
	int father=0, child=0;
	char input[BUFFER_SIZE];

	printf("*******************************\n" );
	printf("*                             *\n" );
	printf("*   Matrix product caculator  *\n" );
	printf("*                             *\n" );
	printf("*******************************\n" );

	/**
	 * Check the user insert the file path from args
	 */
	if(argc > 3) {
		strcpy(input, argv[1]);
		matrix_register(&A, input);
		strcpy(input, argv[2]);
		matrix_register(&B, input);
		matrix_result_create( &C, A, B);

		ELEMENTS = matrix_get_elements(C);
		qtd_ants = atoi(argv[3]);
	}else{

		printf("ERRO: Numero incorreto de argumentos\n");
		printf("Usage: ./main <matrix_A> <matrix_B> <qtd_threads>\n");
		return 1;

	}

	father = getpid();
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

		/*matrix_print(A);
		matrix_print(B);
		matrix_print(C);*/
		matrix_destroy(A);
		matrix_destroy(B);
	}


	return 0;
}
