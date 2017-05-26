/**
   @author Jonatan Souza
 */
#include "stack.h"
/**
 * Structure to double values
 */
struct _stack {
	struct _stack * next;
	int value;
};

/**
 * push values on stack
 */
int push(Stack **s, int value){
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
/**
 * pop values from stack
 */
int pop(Stack **s, int *value){
	Stack * aux = NULL;
	if((*s) == NULL) {
		return -1;
	}
	if(value != NULL)
		*value = (*s)->value;
	aux = (*s);
	(*s) = (*s)->next;
	free(aux);
	return 1;
}

int pickTop(Stack *s, int *value){
	if(s == NULL) {
		return 0;
	}
	*value = s->value;
	return 1;
}


/**
 * Destroy all values on stack and release memory
 */

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
/**
 * Print on screen the values on stack
 */
void printStack(Stack *s){
	Stack *aux = NULL;
	printf("********TOPO V********************************\n");
	if(s == NULL) {
		printf("Empty Stack\n");
		return;
	}
	for(aux = s; aux != NULL; aux = aux->next) {
		printf("%d \n", aux->value);
	}
	printf("****************************************\n");
}
