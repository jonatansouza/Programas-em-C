/**
   *@author Jonatan Souza
 */

#ifndef _Matrix
#define _Matrix

#include <stdlib.h>
#include <stdio.h>

struct matrix;
typedef struct matrix Matrix;

struct node;
typedef struct node Node;


int matrix_register(Matrix **mtx, char *filename);
int matrix_print(Matrix *mtx);
int matrix_multiply_by_element(Matrix *C, int row, int col , Matrix *A, Matrix *B);
int matrix_result_create(Matrix **mtx, Matrix *A, Matrix *B);
int matrix_get_elements(Matrix *m);
int matrix_out_of_bounds(Matrix *m, int position);
int matrix_destroy(Matrix *mtx);


#endif
