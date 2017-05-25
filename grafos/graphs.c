/**
   @author Jonatan Souza
 */
#include "graphs.h"

struct _vertex {
	int id;
	int connections;
	struct _edge *edges;
};

struct _edge {
	struct _vertex *vertex;
	struct _edge *next;
};

struct _graph {
	int elements;
	struct _vertex *vertex;
	struct _graph *next;
};

/**
 *      AUXILIAR FUNCTIONS
 **/
Vertex* searchVertex(Graph *g, int id);
Edge * searchEdge(Edge *e, Vertex *v);
Edge * searchEdgeByNext(Edge *e, Edge *n);
Graph * searchVertexByNext(Graph *g, Graph *n);
Graph * searchGraphVertex(Graph *g, int id);
int createConnection(Vertex *v1, Vertex *v2);
int removeConnection(Vertex *v1, Vertex *v2);
/**
 *        AUXILIAR FUNCTIONS END
 **/


int insertVertex(Graph **g, int id){
	Graph *n, *aux;
	if ((*g) == NULL) {
		aux = (Graph *) malloc(sizeof(Graph));
		aux->vertex = (Vertex *) malloc(sizeof(Vertex));
		aux->vertex->id = id;
		aux->vertex->connections = 0;
		aux->elements = 1;
		aux->vertex->edges = NULL;
		aux->next = NULL;
		(*g) = aux;
		return 0;
	}else{
		if(searchVertex(*g, id) == NULL) {
			n = (Graph *) malloc(sizeof(Graph));
			n->vertex = (Vertex *)malloc(sizeof(Vertex));
			n->vertex->id = id;
			n->vertex->connections = 0;
			n->vertex->edges = NULL;
			n->elements = (*g)->elements + 1;
			aux = (*g);
			(*g) = n;
			(*g)->next = aux;
			return 0;
		}
		printf("Valor Duplicado\n");
		return 1;
	}
}

int insertEdge(Graph *g, int a, int b){
	Vertex *vertex1 = NULL, *vertex2 = NULL;
	if((vertex1 = searchVertex(g, a)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", a);
		return 1;
	}
	if((vertex2 = searchVertex(g, b)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", b);
		return 1;
	}
	createConnection(vertex1, vertex2);
	if(vertex1 != vertex2)
		createConnection(vertex2, vertex1);
	return 0;
}

int removeVertex(Graph **g, int id){
	Graph *trash = NULL, *p = NULL;
	Edge *e = NULL;
	if((trash = searchGraphVertex(*g, id)) != NULL) {
		for (e = trash->vertex->edges; e!=NULL; e = e->next){
			removeConnection(e->vertex, trash->vertex);
		}

		if((p = searchVertexByNext(*g, trash)) == NULL) {
			trash = (*g);
			(*g) = (*g)->next;
			(*g)->elements --;
			free(trash);
			return 0;
		}else{
			p->next = trash->next;
			(*g)->elements --;
			free(trash);
			return 0;
		}
	}
	printf("Vertex id:%d nao encontrado!\n", id);
	return 1;

}

int removeEdge(Graph *g, int a, int b){
	Vertex *vertex1 = NULL, *vertex2 = NULL;
	if((vertex1 = searchVertex(g, a)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", a);
		return 1;
	}
	if((vertex2 = searchVertex(g, b)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", b);
		return 1;
	}
	removeConnection(vertex1, vertex2);
	if(vertex1 != vertex2)
		removeConnection(vertex2, vertex1);
	return 0;
}

void displayGraph(Graph *g){
	Graph *aux = NULL;
	Edge *e = NULL;
	printf("Grafo com %d elementos\n", g->elements);
	for(aux = g; aux != NULL; aux = aux->next) {
		printf("id: %d [", aux->vertex->id);
		for(e = aux->vertex->edges; e != NULL; e = e->next)
			printf(" %d ", e->vertex->id);
		printf("]\n");
	}
}

int greedyGraph(Graph *g){
	int *visited = (int *) malloc(sizeof(g->elements));
	Graph *aux = NULL;
	Edge *e = NULL;
	for(aux = g; aux != NULL; aux = aux->next) {
		printf("id: %d [", aux->vertex->id);
		for(e = aux->vertex->edges; e != NULL; e = e->next)
			printf(" %d ", e->vertex->id);
		printf("]\n");
	}
	return 0;
}

/**
 * AUXILIAR FUNCTIONS
 */
int createConnection(Vertex *v1, Vertex *v2){
	Edge *n;
	if(v1->edges == NULL) {
		v1->edges = (Edge *)malloc(sizeof(Edge));
		v1->edges->vertex = v2;
		v1->edges->next = NULL;
		v1->connections++;
		return 0;
	}
	if(searchEdge((v1->edges), v2) == NULL) {
		n = (Edge *)malloc(sizeof(Edge));
		n->vertex = v2;
		n->next = v1->edges;
		v1->edges = n;
		v1->connections++;
		return 0;
	}
	printf("A conexão dos vertices [%d] <-> [%d] ja existe!\n", v1->id, v2->id);
	return 1;
}

int removeConnection(Vertex *v1, Vertex *v2){
	Edge *trash, *p;
	if(v1->edges == NULL) {
		printf("nenhuma conexao encontrada no vertice\n");
		return 1;
	}
	if((trash = searchEdge((v1->edges), v2)) != NULL) {
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
	printf("A conexão dos vertices [%d] <-> [%d] não existe!\n", v1->id, v2->id);
	return 1;
}


Vertex * searchVertex(Graph *g, int id){
	Graph *aux = NULL;
	for(aux = g; aux != NULL; aux = aux->next)
		if (aux->vertex->id == id)
			return aux->vertex;
	return NULL;
}

Graph * searchGraphVertex(Graph *g, int id){
	Graph *aux = NULL;
	for(aux = g; aux != NULL; aux = aux->next)
		if (aux->vertex->id == id)
			return aux;
	return NULL;
}

Graph * searchVertexByNext(Graph *g, Graph *n){
	Graph *aux = NULL;
	for(aux = g; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}


Edge * searchEdge(Edge *e, Vertex *v){
	Edge *aux = NULL;
	for(aux = e; aux != NULL; aux = aux->next)
		if (aux->vertex == v)
			return aux;
	return NULL;
}

Edge * searchEdgeByNext(Edge *e, Edge *n){
	Edge *aux = NULL;
	for(aux = e; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}
