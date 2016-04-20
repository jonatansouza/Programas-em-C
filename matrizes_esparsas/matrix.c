/**
   *@author Jonatan Souza
 */

#include "matrix.h"

struct matrix {
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

        int i;
        const int LINES =(int) matrixDescription[0];
        const int COLUMNS =(int) matrixDescription[1];

        float * matrixElements = matrixDescription+2;
        const int matrixElementsSize = matrixDescriptionSize-3;

        //MasterHeadNode
        (*m) = malloc (sizeof (Matrix));
        (*m)->right = (*m);
        (*m)->below = (*m);
        (*m)->line = -1;
        (*m)->column = -1;
        (*m)->info = FLT_MIN;

        printf("MATRIX SIZE: %d x %d\n", LINES, COLUMNS);

        //create LINES Heads
        for(i=0; i<LINES; i++) {
                Matrix *mNew = malloc(sizeof (Matrix));
                mNew->column = -1;
                mNew->line = 0;
                mNew->info = FLT_MIN;
                mNew->right = mNew;
                mNew->below = (*m)->below;
                (*m)->below = mNew;
        }

        //create COLUMNS Heads
        for(i=0; i<COLUMNS; i++) {
                Matrix *mNew = malloc(sizeof (Matrix));
                mNew->line = -1;
                mNew->column = 0;
                mNew->info = FLT_MIN;
                mNew->below = mNew;
                mNew->right = (*m)->right;
                (*m)->right = mNew;
        }

        for(i=0; i < 6; i++)
                insert_element((*m), matrixElements[(i*3)],matrixElements[(i*3)+1], matrixElements[(i*3)+2]);

        float *foo;
        for(i=0; i < 6; i++)
                matrix_getelem((*m), matrixElements[(i*3)],matrixElements[(i*3)+1], foo);


        return 1;
}

int matrix_getelem( const Matrix* m, int x, int y, float *elem ){
        Matrix *head = (Matrix *)m;
        int i;
//set Line
        for(i=0; i<=x; i++)
                head = head->below;

        int found = 0;
        Matrix *aux;
        for(aux = head->right; aux != head; aux = aux->right) {
                if(aux->line == x && aux->column == y) {
                        found = 1;
                        break;
                }
        }

        if(found) {
                printf("Valor encontrado!\n");
                imprimeNode(aux);
        }
        return 1;
}

int matrix_destroy( Matrix* m ){
        printf("Destroy -> %p\n", m);
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
        for(i=0; i<=line; i++)
                aux = aux->below;

        mNew->right = aux->right;
        aux->right = mNew;

//set column
//set origin
        aux = m;
        for(i=0; i<=column; i++)
                aux = aux->right;

        mNew->below = aux->below;
        aux->below = mNew;

}
