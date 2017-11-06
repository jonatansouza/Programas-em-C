/**
   *@author Jonatan Souza
 */

#include "matrix.h"

struct node {
	float value;
};

struct matrix {
	char * filename;
	int rows;
	int cols;
	Node *nodes;
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
	m->nodes = (Node *) malloc(m->rows * m->cols * sizeof(Node));
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			fscanf(fp, "%f", &dump);
			m->nodes[i*m->cols+j].value = dump;
		}
	}
	fclose(fp);
	(*mtx) = m;
	return 1;
}

int matrix_result_create(Matrix **mtx, Matrix *A, Matrix *B){
	int rows, cols;
	/* Matrix *m = (Matrix *) malloc(sizeof(Matrix)); */
	(*mtx) = mmap(NULL, sizeof(Matrix), PROT_READ | PROT_WRITE,
										MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	(*mtx)->rows = rows = A->rows;
	(*mtx)->cols = cols =  B->cols;
	/*(*mtx)->nodes = (Node *) malloc(rows * cols * sizeof(Node));*/
	(*mtx)->nodes = (Node *) mmap(NULL, rows * cols * sizeof(Node), PROT_READ | PROT_WRITE,
										MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	return 1;
}

int matrix_print(Matrix *mtx){
	int i=0, j=0;
	Node *node = mtx->nodes;
	printf("print matrix\n");
	for (i = 0; i < mtx->rows; i++) {
		for (j = 0; j < mtx->cols; j++) {
			printf("%5.1f ", node[i*mtx->cols+j].value);
		}
		printf("\n" );
	}
	return 0;
}

int matrix_multiply_by_element(Matrix *C, int row, int col , Matrix *A, Matrix *B){
			int i, elements;
			C->nodes[row*C->cols+col].value = 0;
			elements = A->rows;
			for(i=0; i <  elements; i++){
				C->nodes[row*elements+col].value += A->nodes[row*elements+i].value * B->nodes[i*elements+col].value;
			}
			return 1;
}

int matrix_get_elements(Matrix *m){
	return m->rows;
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
