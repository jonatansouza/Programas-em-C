/**
   *@author Jonatan Souza
 */

#include "graph.h"

struct _vertex{
	 char name;
	 int value;
	 struct _edge *edges;
	 struct _vertex *next;
};

struct _edge{
	int cost;
	struct _vertex *vertex;
	struct _edge *next;
};

/**
* AUXILIAR FUNCTIONS
*/

Vertex * searchVertex(Graph *g, char name);
/*
* END AUXILIAR FUNCTIONS
*/

int createGraph(Graph **g){
	(*g) = (Graph*) malloc(sizeof(Graph));
	if ((*g) == NULL) {
		return 1;
	}
	(**g) = NULL;
	return 0;
}

int insertVertex(Graph *g, char name, int value){
	Vertex *aux, *n;
	if ((*g) == NULL) {
		aux = (Vertex *) malloc(sizeof(Vertex));
		aux->name = name;
		aux->edges = NULL;
		aux->next = NULL;
		*g = aux;
		return 0;
	}else{
		if(searchVertex(g, name) == NULL) {
			n = (Vertex *)malloc(sizeof(Vertex));
			n->name = name;
			n->edges = NULL;
			aux = (*g);
			(*g) = n;
			(*g)->next = aux;
			return 0;
		}
		printf("Valor Duplicado\n");
		return 1;
	}
}

Vertex * searchVertex(Graph *g, char name){
	Vertex *aux = NULL;
	for(aux = *g; aux != NULL; aux = aux->next)
		if (aux->name == name)
			return aux;
	return NULL;
}
