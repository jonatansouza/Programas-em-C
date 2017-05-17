/**
   *@author Jonatan Souza
 */

#include "matrix.h"

#define INPUT_MAX_SIZE 1000

struct matrix {
	char * filename;
	int rows;
	int cols;
	double **matrix;
};
/**
 * AUXILIAR FUNCTIONS
 */

int PSCopyMatrix(Matrix *a, Matrix **b);

/**
 * AUXILIAR FUNCTIONS
 * END
 */

/**
 * Alloc a matrix and read all data from file
 *
 */
int PSRegister(Matrix **mtx, char *filename){
	FILE *fp;
	Matrix *m = (Matrix *) malloc(sizeof(Matrix));
	int i=0, j=0;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Não foi possivel encontrar o arquivo\n" );
		return 0;
	}
	fscanf(fp, "%d %d", &m->rows, &m->cols);
	m->matrix = (double **) malloc(m->rows * sizeof(double *));
	for(i = 0; i < m->cols; i++) {
		m->matrix[i] = (double *) malloc(m->cols * sizeof(double));
	}

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			if((fscanf(fp, "%lf", &m->matrix[i][j])) < 1) {
				printf("Arquivo com dados incorretos!\n" );
				return 0;
			}
		}
	}
	fclose(fp);
	(*mtx) = m;
	return 1;
}
/**
 * Compute the pollution spread
 */
int PSCompute(Matrix *mtx){
	int i=0, j=0;
	Matrix *aux = NULL;
	for (i = 0; i < mtx->rows; i++) {
		for (j = 0; j < mtx->cols; j++) {
			if (mtx->matrix[i][j] == 2) {
				printf("Fonte de poluente encontrada! em %d %d\n", i, j);
			}
		}
	}

	if(!PSCopyMatrix(mtx, &aux)) {
		printf("Erro na criação da matrix auxiliar\n" );
	}
	PSMatrixDestroy(aux);
	return 1;
}
/**
 * Print Matrix content
 */
int PSPrint(Matrix *mtx){
	int i=0, j=0;
	for (i = 0; i < mtx->rows; i++) {
		for (j = 0; j < mtx->cols; j++) {
			printf("%1.0f ", mtx->matrix[i][j]);
		}
		printf("\n" );
	}
	return 0;
}

/**
 * Release all memory allocated
 */
int PSMatrixDestroy(Matrix *mtx){
	int i = 0;
	for(i = 0; i < mtx->cols; i++) {
		free(mtx->matrix[i]);
	}
	free(mtx->matrix);
	free(mtx);
	return 1;
}

/**
 * AUXILIAR FUNCTIONS
 */

/**
 * copy all data from matrix a -> b and allocate memory
 */
int PSCopyMatrix(Matrix *a, Matrix **b){
	int i=0, j=0;
	(*b) = (Matrix *) malloc(sizeof(Matrix));
	(*b)->rows = a->rows;
	(*b)->cols = a->cols;
	(*b)->matrix = (double **) malloc((*b)->rows * sizeof(double *));
	for(i = 0; i < (*b)->cols; i++) {
		(*b)->matrix[i] = (double *) malloc((*b)->cols * sizeof(double));
	}
	for (i = 0; i < (*b)->rows; i++) {
		for (j = 0; j < (*b)->cols; j++) {
			(*b)->matrix[i][j] = a->matrix[i][j];
		}
	}
	return 1;
}
