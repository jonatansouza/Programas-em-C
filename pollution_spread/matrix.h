/**
   *@author Jonatan Souza
 */

#ifndef _Matrix
#define _Matrix

#include <stdlib.h>
#include <stdio.h>

struct matrix;
typedef struct matrix Matrix;

int PSRegister(Matrix **mtx, char *filename);
int PSCompute(Matrix *mtx);
int PSPrint(Matrix *mtx);
int PSMatrixDestroy(Matrix *mtx);
#endif
