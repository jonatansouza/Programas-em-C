/**
   *@author Jonatan Souza
 */

#include "matrix.h"

struct matrix {
	char * filename;
	int rows;
	int cols;
	double *nodes;
};


/**
 * Alloc a matrix and read all data from file
 *
 */
int matrix_register(Matrix **mtx, char *filename){
	FILE *fp;
	float dump;
	Matrix *m = (Matrix *) malloc(sizeof(Matrix));
	int i=0, j=0;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Nao foi possivel encontrar o arquivo\n" );
		return 0;
	}
	fscanf(fp, "%d %d", &m->rows, &m->cols);
	m->nodes = (double *) malloc(m->rows * m->cols * sizeof(double));
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			fscanf(fp, "%f", &dump);
			m->nodes[i*m->cols+j] = dump;
		}
	}
	fclose(fp);
	(*mtx) = m;
	return 1;
}



int matrix_result_create(Matrix **mtx, Matrix *A, Matrix *B){
	int rows, cols;
	Matrix *m = (Matrix *) malloc(sizeof(Matrix));
	m->rows = rows = A->rows;
	m->cols = cols =  B->cols;
	m->nodes = (double *) malloc(rows * cols * sizeof(double));
	(*mtx) = m;
	return 1;
}

int matrix_print(Matrix *mtx){
	int i=0, j=0;
	double *node = mtx->nodes;
	printf("print matrix\n");
	for (i = 0; i < mtx->rows; i++) {
		for (j = 0; j < mtx->cols; j++) {
			printf("%5.1f ", node[i*mtx->cols+j]);
		}
		printf("\n" );
	}
	return 0;
}


int matrix_recieve_col_array(Matrix *A, double *col_array, int position){
	int i;
	for (i = 0; i < A->cols; i++) {
		col_array[i] = A->nodes[i*A->cols+position];
	}
	return 1;
}

double * get_all_nodes(Matrix *A){
		return A->nodes;
}

int matrix_multiply_by_element(Matrix *C, int row, int col , Matrix *A, Matrix *B){
			int i, elements;
			C->nodes[row*C->cols+col] = 0;
			elements = A->rows;
			for(i=0; i <  elements; i++){
				C->nodes[row*elements+col] += A->nodes[row*elements+i] * B->nodes[i*elements+col];
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


int matrix_get_elements(Matrix *m){
	return m->rows;
}

int matrix_set_elements(Matrix *m, int position, double value){
	return m->nodes[position] = value;
}

/**
 * Release all memory allocated
 */
int matrix_destroy(Matrix *mtx){
	free(mtx->nodes);
	free(mtx);
	return 1;
}
int matrix_out_of_bounds( Matrix *m , int position){
	return position < (m->rows * m->cols) ? 1 : 0;
}
