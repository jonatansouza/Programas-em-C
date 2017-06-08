/**
   *@author Jonatan Souza
 */

#include "matrix.h"

struct node {
	int type;
	double value;
};

struct matrix {
	char * filename;
	int rows;
	int cols;
	Node *nodes;
};

/**
 * AUXILIAR FUNCTIONS
 */

int PSCopyMatrix(Matrix *a, Matrix **b);
double PSPoiseCheck(Matrix *a, Matrix *b);
double PSModule(double value);
double PSConvertPercent(double value);
double PSCheckNeighbors(Matrix *m,int i,int j);
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
	m->nodes = (Node *) malloc(m->rows * m->cols * sizeof(Node));
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			if((fscanf(fp, "%d", &m->nodes[i*m->cols+j].type)) < 1) {
				printf("Arquivo com dados incorretos!\n" );
				return 0;
			}else if(m->nodes[i*m->cols+j].type < 0 || m->nodes[i*m->cols+j].type > 2) {
				printf("Arquivo com dados incorretos, [0 1 2] valores permitidos!\n" );
				return 0;
			}
			if(m->nodes[i*m->cols+j].type == 2) {
				m->nodes[i*m->cols+j].value = POLLUTANT;
			}else{
				m->nodes[i*m->cols+j].value = 0;
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
	int i=0, j=0, count=0;
	int rows = mtx->rows;
	int cols = mtx->cols;
	Matrix * aux = NULL, * mtxcpy = NULL;
	if(!PSCopyMatrix(mtx, &mtxcpy)) {
		printf("Erro ao alocar matriz auxiliar\n");
		return 0;
	}
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (mtx->nodes[i*cols+j].type == 2) {
				count++;
			}
		}
	}
	if (count == 0) {
		printf("Nenhum fonte de poluente encontrada\n" );
		return 1;
	}
	printf("%d Fontes de poluente encontradas\n", count);
	count = 0;
	do {
		aux = mtx;
		mtx = mtxcpy;
		mtxcpy = aux;
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				if(mtxcpy->nodes[i*cols+j].type == 1)
					mtxcpy->nodes[i*cols+j].value = PSCheckNeighbors(mtx, i, j);
			}
		}
		count++;
	} while(PSPoiseCheck(mtxcpy, mtx) >= ACCURACY);
	printf("Calculo concluido com  %d iterações \n",count);
	PSPrint(mtxcpy);
	PSMatrixDestroy(aux);

	return 1;
}
/**
 * Print Matrix content
 */
int PSPrint(Matrix *mtx){
	int i=0, j=0;
	Node *node = mtx->nodes;
	for (i = 0; i < mtx->rows; i++) {
		for (j = 0; j < mtx->cols; j++) {
			if(node[i*mtx->cols+j].type == 0)
				printf("%s", BLU);
			if(node[i*mtx->cols+j].type == 1)
				printf("%s", GRN);
			if(node[i*mtx->cols+j].type == 2)
				printf("%s", RED);
			printf("%5.1f ", node[i*mtx->cols+j].value);
			printf("%s", RESET);
		}
		printf("\n" );
	}
	return 0;
}

/**
 * Release all memory allocated
 */
int PSMatrixDestroy(Matrix *mtx){
	free(mtx->nodes);
	free(mtx);
	return 1;
}

/**
 * AUXILIAR FUNCTIONS
 */

/**
 * verify if position required is inside the array limits
 */
int PSCheckNodeLimits(int limits, int current){
	return current > limits || current < 0 ? 0 : 1;
}
/**
 * return a value
 */
double PSReturnNodeValue(Matrix * m, int position){
	return (PSCheckNodeLimits(m->rows*m->cols, position)) ? m->nodes[position].value : 0;
}


/**
 *
 */
double PSCheckNeighbors(Matrix *m,int i,int j){
	int cols = m->cols;
	double teste = PSReturnNodeValue(m, ((i-1)*cols+j)) + PSReturnNodeValue(m,((i+1)*cols+j)) + PSReturnNodeValue(m,(i*cols+(j-1))) + PSReturnNodeValue(m,(i*cols+(j+1)));
	return teste / 4;
}

/**
 * Convert the values to percent values
 */

double PSConvertPercent(double value){
	return (value - 1) * 100;
}
/**
 * Check the residual value between matrix and return it
 */
double PSPoiseCheck(Matrix *a, Matrix *b){
	int i = 0, j = 0;
	int locate[2] = {0, 0};
	double deltaMax = 0;
	for (i = 0; i < a->rows; i++) {
		for (j = 0; j < a->cols; j++) {
			if ((a->nodes[i*a->cols+j].value - b->nodes[i*a->cols+j].value) > deltaMax) {
				deltaMax = (a->nodes[i*a->cols+j].value - b->nodes[i*a->cols+j].value);
				locate[0] = i;
				locate[1] = j;
			}
		}
	}
	return PSModule(deltaMax / b->nodes[locate[0]*a->cols+locate[1]].value);
}

double PSModule(double value){
	return value < 0 ? value * (-1) : value;
}

/**
 * copy all data from matrix a -> b and allocate memory
 */
int PSCopyMatrix(Matrix *a, Matrix **b){
	int i=0, j=0;
	(*b) = (Matrix *) malloc(sizeof(Matrix));
	(*b)->rows = a->rows;
	(*b)->cols = a->cols;
	(*b)->filename = a->filename;
	(*b)->nodes = (Node *) malloc(a->rows * a->cols * sizeof(Node));
	for (i = 0; i < a->rows; i++) {
		for (j = 0; j < a->cols; j++) {
			(*b)->nodes[i*a->cols+j] = a->nodes[i*a->cols+j];
		}
	}
	return 1;
}
