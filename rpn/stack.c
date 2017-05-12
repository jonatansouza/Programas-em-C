#include "stack.h"

struct _stack {
	struct _stack * next;
	double value;
};

struct _stackc {
	struct _stackc * next;
	char value;
};

/**
        Doubles
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
int getTop(Stackc *s, char *value){
	if(s == NULL) {
		return 0;
	}
	*value = s->value;
	return 1;
}

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
