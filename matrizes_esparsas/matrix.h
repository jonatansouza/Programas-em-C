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
#endif
