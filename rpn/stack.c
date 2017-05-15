/**
   @author Jonatan Souza
 */
#include "stack.h"
/**
 * Structure to double values
 */
struct _stack {
	struct _stack * next;
	double value;
};

/**
 *	Structure to char values
 */
struct _stackc {
	struct _stackc * next;
	char value;
};

/**
        Doubles
 */

/**
 * push values on stack
 */
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
/**
 * pop values from stack
 */
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
		printf("%f \n", aux->value);
	}
	printf("****************************************\n");
}

/**
        CHARS
 */


/**
 * Push values on stack
 */
int pushc(Stackc **s, char value){
	Stackc *aux = (Stackc *) malloc (sizeof (Stackc));
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
 * Pop values from stack
 */
int popc(Stackc **s, char *value){
	Stackc * aux = NULL;
	if((*s) == NULL) {
		return 0;
	}
	*value = (*s)->value;
	aux = (*s);
	(*s) = (*s)->next;
	free(aux);
	return 1;
}

/**
 * Insert on the parametter the value of the top element on stack,
 * however this method does not pop a value from stack. this value keep there.
 */
int pickTop(Stackc *s, char *value){
	if(s == NULL) {
		return 0;
	}
	*value = s->value;
	return 1;
}

/**
 * Destroy all elements from stack and release memory
 */
int stackDestroyc(Stackc **s){
	Stackc *aux = (*s);
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
void printStackc(Stackc *s){
	Stackc *aux = NULL;
	printf("********TOPO V********************************\n");
	if(s == NULL) {
		printf("Empty Stack\n");
		return;
	}
	for(aux = s; aux != NULL; aux = aux->next) {
		printf("%c \n", aux->value);
	}
	printf("****************************************\n");
}
