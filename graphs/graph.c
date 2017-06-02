/**
   *@author Jonatan Souza
 */

#include "graph.h"

struct _vertex {
	char name;
	struct _edge *edges;
	struct _vertex *next;
};

struct _edge {
	int cost;
	struct _vertex *vertex;
	struct _edge *next;
};

/**
 * AUXILIAR FUNCTIONS
 */

Vertex * searchVertex(Graph *g, char name);
Edge* createConnection(Vertex *v1, Vertex *v2, int cost);
Edge * searchEdge(Edge *e, Vertex *v,int cost);
Edge * searchEdgeByNext(Edge *e, Edge *n);
Vertex * searchVertexByNext(Vertex *g, Vertex *n);
int removeConnection(Vertex *v1, Vertex *v2, int cost);
int removeAllConnections(Vertex *v, Vertex *del);
int countVertex(Graph *g);
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
void displayGraph(Graph *g){
	Vertex *aux = NULL;
	Edge *e = NULL;
	printf("\n########## GRAFO COM %d vertices ############\n", countVertex(g));
	if(*g == NULL){
		printf("grafo vazio\n");
		return;
	}
	for(aux = *g; aux != NULL; aux = aux->next) {
		printf("id: %c [", aux->name);
		for(e = aux->edges; e != NULL; e = e->next)
			printf(" %c (%d) ", e->vertex->name, e->cost);
		printf("]\n");
	}
	printf("#############################################\n\n");

}
int insertVertex(Graph *g, char name){
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
		printf("Erro: O vertice ja existe!\n");
		return 1;
	}
}

int removeVertex(Graph *g, char name){
	Vertex *trash = NULL, *p = NULL;
	Edge *e = NULL;
	if((trash = searchVertex(g, name)) != NULL) {
		for (e = trash->edges; e!=NULL; e = e->next) {
			removeAllConnections(e->vertex, trash);
		}
		if((p = searchVertexByNext(*g, trash)) == NULL) {
			trash = (*g);
			(*g) = (*g)->next;
			free(trash);
			return 0;
		}else{
			p->next = trash->next;
			free(trash);
			return 0;
		}
	}
	printf("Vertex id:%c nao encontrado!\n", name);
	return 1;

}

int insertEdge(Graph *g, char origin, char destiny, int cost){
	Vertex *vertex1 = NULL, *vertex2 = NULL;
	Edge *e = NULL;
	if((vertex1 = searchVertex(g, origin)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", origin);
		return 1;
	}
	if((vertex2 = searchVertex(g, destiny)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", destiny);
		return 1;
	}
	e = createConnection(vertex1, vertex2, cost);
	if (e == NULL)
		return 1;
	if(searchEdge(e, vertex1, cost) == NULL) {
		e = createConnection(vertex2, vertex1, cost);
		if (e == NULL)
			return 1;
	}
	return 0;
}

int removeEdge(Graph *g, int a, int b, int cost){
	Vertex *vertex1 = NULL, *vertex2 = NULL;
	if((vertex1 = searchVertex(g, a)) == NULL) {
		printf("Vertex id:%c nao encontrado!\n", a);
		return 1;
	}
	if((vertex2 = searchVertex(g, b)) == NULL) {
		printf("Vertex id:%c nao encontrado!\n", b);
		return 1;
	}
	if(removeConnection(vertex1, vertex2, cost)){
		printf("A conexão dos vertices [%c] <-> [%c] com custo (%d) não existe!\n", vertex1->name, vertex2->name, cost);
		return 1;
	}
	removeConnection(vertex2, vertex1, cost);
	return 0;
}

/* AUXILIAR FUNCTIONS */

Vertex * searchVertex(Graph *g, char name){
	Vertex *aux = NULL;
	for(aux = *g; aux != NULL; aux = aux->next)
		if (aux->name == name)
			return aux;
	return NULL;
}

Vertex * searchVertexByNext(Vertex *g, Vertex *n){
	Vertex *aux = NULL;
	for(aux = g; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}


Edge * searchEdge(Edge *e, Vertex *v, int cost){
	Edge *aux = NULL;
	for(aux = e; aux != NULL; aux = aux->next)
		if (aux->vertex == v && aux->cost == cost)
			return aux;
	return NULL;
}

Edge* createConnection(Vertex *v1, Vertex *v2, int cost){
	Edge *n = NULL;
	if(v1->edges == NULL) {
		v1->edges = (Edge *)malloc(sizeof(Edge));
		v1->edges->vertex = v2;
		v1->edges->cost = cost;
		v1->edges->next = NULL;
		return v1->edges;
	}
	if(searchEdge((v1->edges), v2, cost) == NULL) {
		n = (Edge *)malloc(sizeof(Edge));
		n->vertex = v2;
		n->cost = cost;
		n->next = v1->edges;
		v1->edges = n;
		return n;
	}
	printf("A conexão dos vertices [%c] <-> [%c] ja existe!\n", v1->name, v2->name);
	return NULL;
}

Edge * searchEdgeByNext(Edge *e, Edge *n){
	Edge *aux = NULL;
	for(aux = e; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}

int removeAllConnections(Vertex *v, Vertex *del){
	Edge *trash, *p = NULL, *aux;
	if(v->edges == NULL) {
		printf("nenhuma conexao encontrada no vertice\n");
		return 1;
	}
	aux = v->edges;
	while (aux != NULL) {
		if(aux->vertex == del){
			trash = aux;
			if(p == NULL){
				aux = v->edges = trash->next;
				free(trash);
				continue;
			}else{
				p->next = aux = aux->next;
				free(trash);
				continue;
			}
			p = aux;
			aux = aux->next;
		}
	}
	return 0;
}

int removeConnection(Vertex *v1, Vertex *v2, int cost){
	Edge *trash, *p;
	if(v1->edges == NULL) {
		printf("nenhuma conexao encontrada no vertice\n");
		return 1;
	}
	if((trash = searchEdge((v1->edges), v2, cost)) != NULL) {
		if((p = searchEdgeByNext(v1->edges, trash)) == NULL) {
			trash = v1->edges;
			v1->edges = v1->edges->next;
			free(trash);
			return 0;
		}
		p->next = trash->next;
		free(trash);
		return 0;
	}
	return 1;
}

int countVertex(Graph *g){
	Vertex *aux = NULL;
	int count = 0;
	if(*g == NULL){
		return 0;
	}
	for(aux = *g; aux != NULL; aux = aux->next)
		count ++;
	return count;
}
