/**
   *@author Jonatan Souza
 */

#include "matrix.h"


/**
 * Alloc a matrix and read all data from file
 *
 */
int matrix_register(double **nodes, char *filename){
	int rows, cols, i, j;
	FILE *fp;
	float dump;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Nao foi possivel encontrar o arquivo\n" );
		return -1;
	}
	fscanf(fp, "%d %d", &rows, &cols);
	(*nodes) = (double *) malloc(rows * cols * sizeof(double));
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			fscanf(fp, "%f", &dump);
			(*nodes)[i*rows+j] = dump;
		}
	}
	fclose(fp);
	return rows;
}



int matrix_result_create(double **nodes, int els){
	(*nodes) = (double *) malloc(els * els * sizeof(double));
	return 1;
}

int matrix_print(double *nodes, int els){
	int i, j;
	printf("print matrix\n");
	for (i = 0; i < els; i++) {
		for (j = 0; j < els; j++) {
			printf("%5.1f ", nodes[i*els+j]);
		}
		printf("\n" );
	}
	return 0;
}


int matrix_multiply_by_element(double *C, int els, int row, int col , double *A, double *B){
			int i;
			C[row*els+col] = 0;
			for(i=0; i <  els; i++){
				C[row*els+col] += A[row*els+i] * B[i*els+col];
			}
			return 1;
}

int matrix_multiply_by_segment(double *segA, double *segB, int els, double *result){
	int i;
	*result = 0;
	for (i = 0; i < els; i++) {
		*result += (segA[i]) * (segB[i]);
	}
	return 1;
}


int matrix_set_elements(double *nodes, int position, double value){
	return nodes[position] = value;
}

/**
 * Release all memory allocated
 */
int matrix_destroy(double *mtx){
	free(mtx);
	return 1;
}
int matrix_out_of_bounds( double *m , int position, int limits){
	return position < limits ? 1 : 0;
}
