#include "stack.h"

struct _stack {
	int size;
	int top;
	float *stack;
};

/*Auxiliar Functions*/

int stackCreate(Stack **s, int size){
    *s = (Stack *) malloc (sizeof (Stack));
    (*s)->size = size;
    (*s)->top = -1;
    (*s)->stack = (float *) malloc (size * sizeof (float));    
    return 1;
}
int push(Stack *s, int value){
    if(s->top == (s->size-1))
        return -1;    
    s->stack[++s->top] = value;
    return 1;
}

int pop(Stack *s, int *value){
    if(s->top == -1)
        return -1;
    *value = s->stack[s->top--];
    return 1;
}
int stackDestroy(Stack *s){
    Stack * trash = (Stack * ) s;
    free(trash->stack);
    free(trash);
    return 1;
}

void printStack(Stack *s){
    int i; 
    for(i=0; i <= s->top; i++){
        printf("%f ", s->stack[i]);
    }
    printf("\n");
}
