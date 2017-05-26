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
int push(Stack **s, int value);
int pop(Stack **s, int *value);
int pickTop(Stack *s, int *value);
int stackDestroy(Stack **s);

#endif
