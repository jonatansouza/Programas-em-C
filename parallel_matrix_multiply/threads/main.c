#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include "matrix.h"

#define BUFFER_SIZE 256

Matrix *A = NULL, *B = NULL, *C = NULL;
int ELEMENTS = 0;
int qtd_ants;
struct timeval start, finish;

long module(long n){
	return ((n >= 0 ) ? n : -(n));
}

void *ant(void *itr){
	int val = (intptr_t) itr;
	while (matrix_out_of_bounds(C, val)) {
		matrix_multiply_by_element(C, val / ELEMENTS, val % ELEMENTS, A, B);
		val += qtd_ants;
	}
	pthread_exit(0);
}

int main(int argc, char const *argv[]) {
	pthread_t *threads = NULL;
	char input[BUFFER_SIZE];
	int i;


	/*printf("*******************************\n" );
	printf("*                             *\n" );
	printf("*   Matrix product caculator  *\n" );
	printf("*                             *\n" );
	printf("*******************************\n" );*/

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

	threads = (pthread_t *) malloc(sizeof(pthread_t) * qtd_ants);

	for (i = 0; i < qtd_ants; i++) {
		pthread_create(&threads[i], NULL, ant, (void *) (intptr_t) i);
	}

	gettimeofday(&start, NULL);

	for (i = 0; i < qtd_ants; i++) {
		pthread_join(threads[i], NULL);
	}

	gettimeofday(&finish, NULL);
	printf("%ld.%ld \n", (long) (finish.tv_sec - start.tv_sec), module((long) (finish.tv_usec - start.tv_usec)));
/*	matrix_print(A);
	matrix_print(B);
	matrix_print(C);*/

	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);



	return 0;
}
