/**
   *@author Jonatan Souza
 */

#ifndef _Idx
#define _Idx
#define  M 100

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct index;
typedef struct index Idx;
typedef Idx* Index[M];


int index_createfrom(const char *key_file, const char *text_file, Index **idx);
int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences );
int index_put( Index *idx, const char *key );
int index_print( const Index *idx );

#endif
