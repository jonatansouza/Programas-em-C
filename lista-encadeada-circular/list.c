#include "list.h"

List* create_list(){
	List *l = malloc(sizeof(List));
	l->next = NULL;
	return l;
}


int insert_item(List *l, int val){
	if(l==NULL)return 0;
if(l->next == NULL){
		l->val = val;
		l->next=l;
	}else{
		List *n = malloc(sizeof(List));
		n->val = val;
		n->next = NULL;
		List *aux = l;
		while(aux->next != l){
			if(n->val < aux->next->val){
				n->next = aux->next;
				aux->next = n;
				break;
			}
			aux = aux->next;
		}
		if(n->next == NULL){
			aux->next = n;
			n->next = l;
		}
	}
	return 1;
}

void print_list(List *l){
	List *aux = l;
	if(l->next == NULL){
		printf("Lista Vazia\n");
		return;
	}
	while(1){
		printf("%d\n", aux->val);
		aux = aux->next;
		if(aux == l)break;
	}
}
