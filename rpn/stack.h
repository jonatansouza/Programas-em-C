/**
*@author Jonatan Souza
*/

#ifndef _Stack
#define _Stack

#include <stdio.h>
#include <stdlib.h>

struct _stack;
typedef struct _stack Stack;

int stackCreate(Stack **s);
void printStack(Stack *s);
int push(Stack **s, double value);
int pop(Stack **s, double *value);
int stackDestroy(Stack **s);

#endif
