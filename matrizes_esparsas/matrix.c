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
	printf("right:%p\n", m->right );
//	printf("below:%p\n", m->below );
	printf("line:%d\n", m->line );
//	printf("column:%d\n", m->column);
//	printf("info:%f\n", m->info);
	printf("******************\n");
}

/**
*	aux function responsable for create nodes to insert on matrix
*/
Matrix* insert_on_Create(Matrix *m, int line, int column, int info){
/*	Matrix *mNew = malloc(sizeof(Matrix));
	mNew->info = info;
	mNew->line = line;
	mNew->column = column;

	int i;
	Matrix *pilot = m->right;
	for(i=0; i<line; i++)
		pilot = pilot->right;

	printf("addr line %p\n", pilot);

	pilot->below = pilot;
	for(i=0;i<=pilot->line;i++){
		pilot=p->below;	
	}

	return m;*/
}
	
void prepare_elements(float md[], int size){
	int i;
	for(i=2;i<size;i++)
		printf("item %d : %.2f\n",i-1,md[i]);
}

int matrix_create(Matrix **m){
	float matrixDescription[1000];
	
	int matrixDescriptionSize=0;
	while(scanf("%f", &matrixDescription[matrixDescriptionSize]) > 0)
		matrixDescriptionSize++;
	
	//MasterHeadNode
	(*m) = malloc (sizeof (Matrix));
	(*m)->right = (*m);
	(*m)->below = (*m);
	(*m)->line = -1;
	(*m)->column = -1;
	(*m)->info = FLT_MIN;
	
	int i, lines, columns;
	lines =(int) matrixDescription[0];
	columns =(int) matrixDescription[1];
	
	printf("MATRIX SIZE: %d x %d\n", lines, columns);

	//create lines Heads
	for(i=0; i<lines; i++){
		Matrix *mNew = malloc(sizeof (Matrix));
		mNew->column = -1;
		mNew->info = FLT_MIN;
		mNew->right = (*m)->right;
		(*m)->right = mNew;
	}
	
	//create columns Heads
	for(i=0; i<columns; i++){
		Matrix *mNew = malloc(sizeof (Matrix));
		mNew->line = -1;
		mNew->info = FLT_MIN;
		mNew->below = (*m)->below;
		(*m)->below = mNew;
	}
	
	//insert itens

	Matrix *pilot = (*m);
	for(i=0;i<6;i++){
		imprimeNode(pilot);
		pilot = pilot->right;
	}
	prepare_elements(matrixDescription, matrixDescriptionSize);

//	insert_on_Create((*m), 2, 3, 50.0);
	return 1;
}
