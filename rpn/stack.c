#include "stack.h"

struct _stack {
	struct _stack * next;
	double value;
};

int push(Stack **s, double value){
	Stack *aux = (Stack *) malloc (sizeof (Stack));
	aux->value = value;
	aux->next = NULL;
	if((*s) == NULL) {
		(*s) = aux;
	}else{
		aux->next = (*s);
		(*s) = aux;
	}
	return 1;
}

int pop(Stack **s, double *value){
	Stack * aux = NULL;
	if((*s) == NULL) {
		return -1;
	}
	*value = (*s)->value;
	aux = (*s);
	(*s) = (*s)->next;
	free(aux);
	return 1;
}

int stackDestroy(Stack **s){
	Stack *aux = (*s);
	while((*s) != NULL) {
		aux = (*s);
		(*s) = (*s)->next;
		free(aux);
	}
	free(*s);
	return 1;
}

void printStack(Stack *s){
	Stack *aux = NULL;
	if(s == NULL) {
		printf("Empty Stack\n");
		return;
	}
	for(aux = s; aux != NULL; aux = aux->next) {
		printf("%f \n", aux->value);
	}
}
