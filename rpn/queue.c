#include "queue.h"

struct _queue {
	struct _queue * next;
	double value;
};

struct _queueC {
	struct _queueC * next;
	char value;
};

int queue(Queue **s, double value){
	Queue *aux = (Queue *) malloc (sizeof (Queue));
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

int dequeue(Queue **s, double *value){
	Queue * aux = NULL;
	if((*s) == NULL) {
		return -1;
	}
	if((*s)->next == NULL) {
		(*value) = (*s)->value;
		free(*s);
		(*s) = NULL;
		return 1;
	}

	for(aux = (*s); aux->next->next != NULL; aux = aux->next) ;
	(*value) = aux->next->value;
	free(aux->next);
	aux->next = NULL;
	return 1;
}

int queueC(QueueC **s, char value){
	QueueC *aux = (QueueC *) malloc (sizeof (QueueC));
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

int dequeueC(QueueC **s, char *value){
	QueueC * aux = NULL;
	if((*s) == NULL) {
		return 0;
	}
	if((*s)->next == NULL) {
		(*value) = (*s)->value;
		free(*s);
		(*s) = NULL;
		return 1;
	}

	for(aux = (*s); aux->next->next != NULL; aux = aux->next) ;

	(*value) = aux->next->value;
	free(aux->next);
	aux->next = NULL;
	return 1;
}

int queueDestroy(Queue **s){
	Queue *aux = (*s);
	while((*s) != NULL) {
		aux = (*s);
		(*s) = (*s)->next;
		free(aux);
	}
	free(*s);
	return 1;
}

void printQueue(Queue *s){
	Queue *aux = NULL;
	printf("****************************************\n");
	if(s == NULL) {
		printf("Empty Queue\n");
		return;
	}
	for(aux = s; aux != NULL; aux = aux->next) {
		printf("%f \n", aux->value);
	}
	printf("******Topo ^***************************\n");

}

void printQueueC(QueueC *s){
	QueueC *aux = NULL;
	printf("****************************************\n");
	if(s == NULL) {
		printf("Empty Queue\n");
		return;
	}
	for(aux = s; aux != NULL; aux = aux->next) {
		printf("%c \n", aux->value);
	}
	printf("******Topo ^***************************\n");

}
