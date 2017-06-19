/**
   *@author Jonatan Souza
 */

#ifndef _Matrix
#define _Matrix
#define INPUT_MAX_SIZE 1000
#define ACCURACY 1e-5
#define POLLUTANT 200 /* define o valor de poluente */

#include <stdlib.h>
#include <stdio.h>
#include "colorterminal.h"

struct matrix;
typedef struct matrix Matrix;

struct node;
typedef struct node Node;


int PSRegister(Matrix **mtx, char *filename);
int PSCompute(Matrix *mtx);
int PSPrint(Matrix *mtx);
int PSMatrixDestroy(Matrix *mtx);
#endif
