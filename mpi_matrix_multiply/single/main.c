#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "matrix.h"

#define BUFFER_SIZE 256

Matrix *A = NULL, *B = NULL, *C = NULL;
int ELEMENTS = 0;
struct timeval start, finish;

long module(long n){
	return ((n >= 0 ) ? n : -(n));
}


int main(int argc, char const *argv[]) {
	char input[BUFFER_SIZE];
	int i, j;


/*	printf("*******************************\n" );
	printf("*                             *\n" );
	printf("*   Matrix product caculator  *\n" );
	printf("*                             *\n" );
	printf("*******************************\n" );
*/
	/**
	 * Check the user insert the file path from args
	 */
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
	/*printf("Calculando matrix %d x %d\n",ELEMENTS, ELEMENTS);*/
	/*gettimeofday(&start, NULL);*/
	for (i = 0; i < ELEMENTS; i++)
		for(j=0; j< ELEMENTS; j++)
			matrix_multiply_by_element(C, i, j, A, B);
	/*gettimeofday(&finish, NULL);
	printf("%ld.%ld \n", (long) (finish.tv_sec - start.tv_sec), module((long) (finish.tv_usec - start.tv_usec)));
	*/
	matrix_print(A);
	matrix_print(B);
	matrix_print(C);
	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);



	return 0;
}
