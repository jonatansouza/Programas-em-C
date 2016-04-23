/**
   *@author Jonatan Souza
 */
#ifndef _Matrix
#define _Matrix

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

struct matrix;
typedef struct matrix Matrix;

int matrix_create(Matrix **m);
int matrix_getelem( const Matrix* m, int x, int y, float *elem );
int matrix_setelem( Matrix* m, int x, int y, float elem );
int matrix_destroy( Matrix* m );
int matrix_print( const Matrix* m );
int matrix_add( const Matrix* m, const Matrix* n, Matrix** r );
int matrix_multiply( const Matrix* m, const Matrix* n, Matrix** r );
int matrix_transpose( const Matrix* m, Matrix** r );

#endif
