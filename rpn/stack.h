/**
*@author Jonatan Souza
*/

#ifndef _Stack
#define _Stack

#include <stdio.h>
#include <stdlib.h>
/**
  Stack for double values
*/
struct _stack;
typedef struct _stack Stack;

void printStack(Stack *s);
int push(Stack **s, double value);
int pop(Stack **s, double *value);
int stackDestroy(Stack **s);

/**
  Stack for char values
*/
struct _stackc;
typedef struct _stackc Stackc;

void printStackc(Stackc *s);
int pushc(Stackc **s, char value);
int popc(Stackc **s, char *value);
int getTop(Stackc *s, char *value);
int stackDestroyc(Stackc **s);

#endif
