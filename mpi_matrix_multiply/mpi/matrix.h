/**
   *@author Jonatan Souza
 */

#ifndef _Matrix
#define _Matrix

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int matrix_register_A(double **nodes, char *filename);
int matrix_register_B(double **nodes, char *filename);
int matrix_result_create(double **nodes, int els);
int matrix_result_alloc(double **nodes, int els);
int matrix_print(double *nodes, int els);
int matrix_multiply_by_element(double *C, int els, int row, int col, double *A, double *B);
int matrix_multiply_by_segment(double *segA, double *segB, int els, double *result);
int matrix_set_elements(double *nodes, int position, double value);
int matrix_destroy(double *mtx);
int matrix_out_of_bounds( double *m, int position, int limits);





#endif
