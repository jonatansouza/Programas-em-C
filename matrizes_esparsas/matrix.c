/**
   *@author Jonatan Souza
 */

#include "matrix.h"

#define INPUT_MAX_SIZE 1000

struct matrix {
        struct matrix *right;
        struct matrix *below;
        int line;
        int column;
        float info;
};

//AUXILIAR FUNCTIONS
void create_estructure(Matrix **m, int LINES, int COLUMNS);
void imprimeNode(Matrix *m);
void insert_element(Matrix *m, int line, int column, float info);
void destroy_line(Matrix *m);
void matrix_print_line(Matrix *m);
//AUXILIAR FUNCTIONS


int matrix_create(Matrix **m){
        int i;
        float matrixDescription[INPUT_MAX_SIZE];

        int matrixDescriptionSize=0;
        for(i=0; i< INPUT_MAX_SIZE; i++) {
                scanf("%f", &matrixDescription[matrixDescriptionSize]);
                if(matrixDescription[matrixDescriptionSize] == 0)
                        break;
                matrixDescriptionSize++;

        }


        const int LINES =(int) matrixDescription[0];
        const int COLUMNS =(int) matrixDescription[1];

        float * matrixElements = matrixDescription+2;
        const int matrixElementsSize = matrixDescriptionSize-2;

        create_estructure(m, LINES, COLUMNS);

        for(i=0; i < (matrixElementsSize/3); i++)
                insert_element((*m), matrixElements[(i*3)],matrixElements[(i*3)+1], matrixElements[(i*3)+2]);

        return 0;
}

int matrix_getelem( const Matrix* m, int x, int y, float *elem ){
        Matrix *head = (Matrix *) m;
        int i;
//set Line
        for(i=0; i < x; i++)
                head = head->below;

        int found = 0;
        Matrix *aux;
        for(aux = head->right; aux != head; aux = aux->right) {
                if(aux->line == x && aux->column == y) {
                        *elem = aux->info;
                        found = 1;
                        break;
                }
        }

        if(found) {
                return 0;
        }
        *elem = 0;
        return 1;
}

int matrix_setelem( Matrix* m, int x, int y, float elem ){
        Matrix *head = (Matrix *) m;
        int i;
        //set Line
        for(i=0; i < x; i++)
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
                aux->info = elem;
                return 0;
        }else
                return 1;

}

int matrix_destroy( Matrix* m ){
        Matrix *aux = m;
        Matrix *ref;
        if(m == NULL)
                return 0;
        if(m->below == m) {
                destroy_line(m);
                return 0;
        }
        ref = aux;
        while(aux->below != m) {
                ref = aux;
                aux = aux->below;
        }

        destroy_line(aux);
        ref->below = m;
        matrix_destroy(m);

}



int matrix_print( const Matrix* m ){
        Matrix *aux = (Matrix *) m->below;
        printf("********** MATRIX %d X %d **********\n", m->line,
               m->column);
        while(aux != m) {
                matrix_print_line(aux);
                aux = aux->below;
        }
        printf("\n");
}

int matrix_add( const Matrix* m, const Matrix* n, Matrix** r ){

        float inputs[INPUT_MAX_SIZE];
        int i, j, LINE, COLUMN, inputsSize = 0;
        float infoA, infoB;
        if(m->line != n->line || m->column != n->column)
                return 1;

        LINE = m->line;
        COLUMN = m->column;

        create_estructure(r, LINE, COLUMN);
        for(i=0; i<LINE; i++) {
                for(j=0; j<COLUMN; j++) {
                        matrix_getelem(m, i+1, j+1, &infoA);
                        matrix_getelem(n, i+1, j+1, &infoB);
                        //printf("matrix %d,%d, %f\n",i+1, j+1, infoA);
                        if(infoA != 0 || infoB !=0) {
                                inputs[inputsSize++] = i+1;
                                inputs[inputsSize++] = j+1;
                                inputs[inputsSize++] = infoA+infoB;
                        }
                }
        }
        for(i=0; i<inputsSize/3; i++) {
                insert_element((*r), (int)inputs[i*3], (int)inputs[i*3+1], inputs[i*3+2]);
        }
        return 0;
}

int matrix_multiply( const Matrix* m, const Matrix* n, Matrix** r ){
        float inputs[INPUT_MAX_SIZE];
        int i, j, k, LINE, COLUMN, ELEMENTS, inputsSize = 0;
        float infoA, infoB, result = 0;
        if(m->column != n->line)
                return 1;
        LINE = m->line;
        COLUMN = n->column;
        ELEMENTS = m->line;

        create_estructure(r, LINE, COLUMN);

        for(i=0; i<LINE; i++) {
                for(j=0; j<COLUMN; j++) {
                        for(k=0; k < ELEMENTS; k++) {
                                matrix_getelem(m, i+1, k+1, &infoA);
                                matrix_getelem(n, k+1, j+1, &infoB);
                                result += infoA * infoB;
                        }
                        if(result) {
                                inputs[inputsSize++] = i+1;
                                inputs[inputsSize++] = j+1;
                                inputs[inputsSize++] = result;
                        }
                        result = 0;
                }
        }

        for(i=0; i<inputsSize/3; i++) {
                insert_element((*r), (int)inputs[i*3], (int)inputs[i*3+1], inputs[i*3+2]);
        }
        return 0;

}

int matrix_transpose( const Matrix* m, Matrix** r ){
        float inputs[INPUT_MAX_SIZE];
        int i, j, LINE, COLUMN, inputsSize = 0;
        float info;

        LINE = m->column;
        COLUMN = m->line;

        create_estructure(r, LINE, COLUMN);

        for(i=0; i < COLUMN; i++) {
                for(j=0; j<LINE; j++ ) {
                        matrix_getelem(m, i+1, j+1, &info);
                        if(info) {
                                inputs[inputsSize++] = j+1;
                                inputs[inputsSize++] = i+1;
                                inputs[inputsSize++] = info;
                        }
                }
        }

        for(i=0; i<inputsSize/3; i++) {
                insert_element((*r), (int)inputs[i*3], (int)inputs[i*3+1], inputs[i*3+2]);
        }
        return 0;

}

//********************//
// AUXILIAR FUNCTIONS //
//********************//

void create_estructure(Matrix **m, int LINES, int COLUMNS){
        int i;
        //MasterHeadNode
        (*m) = malloc (sizeof (Matrix));
        (*m)->right = (*m);
        (*m)->below = (*m);
        (*m)->line = LINES;
        (*m)->column = COLUMNS;
        (*m)->info = FLT_MIN;

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
}

void matrix_print_line(Matrix *m){
        Matrix *aux = m->right;
        while(aux != m) {
                printf("%d , ", aux->line);
                printf("%d, ", aux->column);
                printf("info %f\n", aux->info);
                aux = aux->right;
        }
}

void insert_element(Matrix *m, int line, int column, float info){
        Matrix *aux = m;
        Matrix *ref;
        int i;

//new node
        Matrix *mNew = (Matrix *) malloc(sizeof(Matrix));
        mNew->info = info;
        mNew->column = column;
        mNew->line = line;
//set Line
        for(i=0; i<line; i++)
                aux = aux->below;

        ref = aux;
        while(aux->right != ref)
                aux = aux->right;

        mNew->right = aux->right;
        aux->right = mNew;
//set column
//set origin
        aux = m;

        for(i=0; i<column; i++)
                aux = aux->right;

        ref = aux;
        while(aux->below != ref)
                aux = aux->below;

        mNew->below = aux->below;
        aux->below = mNew;


}

void destroy_line(Matrix *m){
        Matrix *aux = m, *trash;
        while(aux->right != m) {
                trash = aux;
                aux = aux->right;
                free(trash);
        }
        free(aux);
}
