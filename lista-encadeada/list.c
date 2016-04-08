#include "list.h"

int isEmpty(List *l){
	if(l->next == NULL){
		return 1;
	}else{
		return 0;
	}
}

List* create_list(){
	List *l = malloc(sizeof(List));
	l->next = NULL;
	return l;
}

List* destroy_list(List *l){
	while(!isEmpty(l)){
		List *rm = l->next;
		l->next = rm->next;
		free(rm);
		rm=l->next;
	}
	free(l);
	return l;

}

List* insert_item(List *l, int val){	
	List *n = malloc(sizeof(List));
	n->val = val;
	n->next = l->next;
	l->next = n;
	return l;
}

List* remove_item(List *l){
	List *rm = l->next;
	l->next = rm->next;
	free(rm);
	return l;
}

void print_list(List *l){
	List *aux;
	if(isEmpty(l)){
		printf("Lista Vazia\n");
		return;
	}
	for(aux = l->next; aux != NULL; aux = aux->next)
		printf("%d\n", aux->val);
}
