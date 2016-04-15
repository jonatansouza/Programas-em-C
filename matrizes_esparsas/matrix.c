/**
*@author Jonatan Souza
*/

#include "matrix.h"

struct matrix{
	struct matrix *right;
	struct matrix *below;
	int line;
	int column;
	float info;
};

void imprimeNode(Matrix *m){
	printf("\n*****************\n");
	printf("ITSELF:%p\n", m);
	printf("right:%p\n", m->right );
	printf("below:%p\n", m->below );
	printf("line:%d\n", m->line );
	printf("column:%d\n", m->column);
	printf("info:%f\n", m->info);
	printf("******************\n");
}

void insert_element(Matrix *m, int line, int column, float info);

int matrix_create(Matrix **m){
	float matrixDescription[1000];

	int matrixDescriptionSize=0;
	while(scanf("%f", &matrixDescription[matrixDescriptionSize]) > 0)
		matrixDescriptionSize++;

		int i, lines, columns;
		lines =(int) matrixDescription[0];
		columns =(int) matrixDescription[1];

	//MasterHeadNode
	(*m) = malloc (sizeof (Matrix));
	(*m)->right = (*m);
	(*m)->below = (*m);
	(*m)->line = -1;
	(*m)->column = -1;
	(*m)->info = FLT_MIN;


	printf("MATRIX SIZE: %d x %d\n", lines, columns);

	//create lines Heads
	for(i=0; i<lines; i++){
		Matrix *mNew = malloc(sizeof (Matrix));
		mNew->column = -1;
		mNew->line = 0;
		mNew->info = FLT_MIN;
		mNew->right = mNew;
		mNew->below = (*m)->below;
		(*m)->below = mNew;
	}

	//create columns Heads
	for(i=0; i<columns; i++){
		Matrix *mNew = malloc(sizeof (Matrix));
		mNew->line = -1;
		mNew->column = 0;
		mNew->info = FLT_MIN;
		mNew->below = mNew;
		mNew->right = (*m)->right;
		(*m)->right = mNew;
	}

	//insert itens
	insert_element((*m), 1,1,5);
	insert_element((*m), 3,2,7);
	insert_element((*m), 4,4,9);

	/*Matrix *pilot = (*m);
	for(i=0;i<6;i++){
		imprimeNode(pilot);
		pilot = pilot->below;
	}*/
	float *foo;
	matrix_getelem((*m), 1,1,foo);
	matrix_getelem((*m), 3,2,foo);
	matrix_getelem((*m), 4,4,foo);

	return 1;
}

int matrix_getelem( const Matrix* m, int x, int y, float *elem ){
	Matrix *aux = (Matrix *)m;
	int i;
	//set Line
	for(i=0;i<=x;i++)
		aux = aux->below;

	for(i=0;i<=aux->line;i++){
		if(aux->line == x && aux->column == y){
			break;
		}
		aux = aux->right;
	}
	printf("Valor encontrado!\n");
	imprimeNode(aux);
	return 1;
}

//********************//
// AUXILIAR FUNCTIONS //
//********************//
void insert_element(Matrix *m, int line, int column, float info){
	Matrix *aux = m;
	int i;

	//new node
	Matrix *mNew = (Matrix *) malloc(sizeof(Matrix));
	mNew->info = info;
	mNew->column = column;
	mNew->line = line;
	//set Line
	for(i=0;i<=line;i++)
		aux = aux->below;

	for(i=0;i<=aux->line;i++)
		aux = aux->right;

	mNew->right = aux->right;
	aux->right = mNew;
	aux->line++;

	//set column
	//set origin
	aux = m;
	for(i=0;i<=column;i++)
		aux = aux->right;

	for(i=0; i<=aux->column; i++)
		aux = aux->below;

	mNew->below = aux->below;
	aux->below = mNew;
	aux->column++;

}
