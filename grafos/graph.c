/**
 * *@author Jonatan Souza
 */

#include "graph.h"

struct _vertex {
	int id;
	struct _edge *edges;
	struct _vertex *next;
};

struct _edge {
	struct _vertex *vertex;
	struct _edge *  next;
};

/**
 * AUXILIAR FUNCTIONS
 */

Vertex *searchVertex(Graph *g, int id);
Edge *createConnection(Vertex *v1, Vertex *v2);
Edge *searchEdge(Edge *e, Vertex *v);
Edge *searchEdgeByNext(Edge *e, Edge *n);
Vertex *searchVertexByNext(Vertex *g, Vertex *n);
int removeConnection(Vertex *v1, Vertex *v2);
int removeAllConnections(Vertex *v, Vertex *del);
int countVertex(Graph *g);
/*greedySearch functions*/
int isVisited(Vertex *v[],int count, Vertex *n);
Vertex* searchMaxEdge(Vertex *v[], int count);
void freeEdges(Edge *e);

/*
 * END AUXILIAR FUNCTIONS
 */
int createGraph(Graph **g)
{
	(*g) = (Graph *)malloc(sizeof(Graph));
	if ((*g) == NULL)
		return 1;
	(**g) = NULL;
	return 0;
}
int destroyGraph(Graph *g)
{
	while (*g != NULL)
		removeVertex(g, (*g)->id);
	free(g);
	return 0;
}
void displayGraph(Graph *g)
{
	Vertex *aux = NULL;
	Edge *e = NULL;

	printf("\n########## GRAFO COM %d vertices ############\n", countVertex(g));
	if (*g == NULL) {
		printf("grafo vazio\n");
		return;
	}
	for (aux = *g; aux != NULL; aux = aux->next) {
		printf("id: %d [", aux->id);
		for (e = aux->edges; e != NULL; e = e->next)
			printf(" %d ", e->vertex->id);
		printf("]\n");
	}
	printf("#############################################\n\n");
}
int insertVertex(Graph *g, int id)
{
	Vertex *aux, *n;

	if ((*g) == NULL) {
		aux = (Vertex *)malloc(sizeof(Vertex));
		aux->id = id;
		aux->edges = NULL;
		aux->next = NULL;
		*g = aux;
		return 0;
	} else {
		if (searchVertex(g, id) == NULL) {
			n = (Vertex *)malloc(sizeof(Vertex));
			n->id = id;
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

int removeVertex(Graph *g, int id)
{
	Vertex *trash = NULL, *p = NULL, *aux = *g;
	Edge *e = NULL, *eTrash;
	if ((trash = searchVertex(g, id)) != NULL) {
		e = trash->edges;
		while( e != NULL) {
			eTrash = e;
			e = e->next;
			removeAllConnections(eTrash->vertex, trash);
		}
		freeEdges(trash->edges);
		while (aux != NULL) {
			if(aux == trash) {
				if(p == NULL) {
					*g = trash->next;
					free(trash);
					return 0;
				}else{
					p->next = aux = aux->next;
					free(trash);
					return 0;
				}
			}
			p = aux;
			aux = aux->next;
		}
	}
	printf("Vertex id:%d nao encontrado!\n", id);
	return 1;
}

int insertEdge(Graph *g, int origin, int destiny)
{
	Vertex *vertex1 = NULL, *vertex2 = NULL;
	Edge *e = NULL;

	if ((vertex1 = searchVertex(g, origin)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", origin);
		return 1;
	}
	if ((vertex2 = searchVertex(g, destiny)) == NULL) {
		printf("Vertex id:%d nao encontrado!\n", destiny);
		return 1;
	}
	e = createConnection(vertex1, vertex2);
	if (e == NULL)
		return 1;
	if (searchEdge(e, vertex1) == NULL) {
		e = createConnection(vertex2, vertex1);
		if (e == NULL)
			return 1;
	}
	return 0;
}

int removeEdge(Graph *g, int a, int b)
{
	Vertex *vertex1 = NULL, *vertex2 = NULL;

	if ((vertex1 = searchVertex(g, a)) == NULL) {
		printf("Vertex id:%c nao encontrado!\n", a);
		return 1;
	}
	if ((vertex2 = searchVertex(g, b)) == NULL) {
		printf("Vertex id:%c nao encontrado!\n", b);
		return 1;
	}
	if (removeConnection(vertex1, vertex2)) {
		printf("A conexao dos vertices [%d] <-> [%d] nao existe!\n", vertex1->id, vertex2->id);
		return 1;
	}
	if(vertex1 != vertex2)
		removeConnection(vertex2, vertex1);
	return 0;
}
void greedySearch(Graph *g, int id)
{
	int count = 0, total = countVertex(g);
	Vertex **discovered = (Vertex **) malloc(total * sizeof (Vertex *));
	Vertex *current = searchVertex(g, id);
	printf("Iniciando a busca por \'%d\' \n", id);
	discovered[count++] = current;
	printf("%d vertice descoberto!\n", count);
	while ((current = searchMaxEdge(discovered, count)) != NULL) {
		printf("    |\n");
		printf("    +-- inserindo vertice \'%d\' a lista de vertices descobertos\n", current->id);
		discovered[count++] = current;
		printf("%d vertices descobertos!\n", count);
	}
	printf("\n********************** RESULTADO ***************************\n");
	printf("*  Grafo com total de %d vertices e %d vertices conexos!     *\n", total, count);
	if (total != count) {
		printf("*  GRAFO DESCONEXO!                                        *\n");
	}else{
		printf("*  GRAFO CONEXO!                                           *\n");
	}
	printf("************************************************************\n");
	free(discovered);

}

/* AUXILIAR FUNCTIONS */

void freeEdges(Edge *e){
	Edge *trash, *aux = e;
	while(aux != NULL) {
		trash = aux;
		aux = aux->next;
		free(trash);
	}
}

Vertex *searchVertex(Graph *g, int id)
{
	Vertex *aux = NULL;
	for (aux = *g; aux != NULL; aux = aux->next)
		if (aux->id == id)
			return aux;
	return NULL;
}

Vertex *searchVertexByNext(Vertex *g, Vertex *n)
{
	Vertex *aux = NULL;

	for (aux = g; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}


Edge *searchEdge(Edge *e, Vertex *v)
{
	Edge *aux = NULL;

	for (aux = e; aux != NULL; aux = aux->next)
		if (aux->vertex == v)
			return aux;
	return NULL;
}

Edge *createConnection(Vertex *v1, Vertex *v2)
{
	Edge *n = NULL;
	if (v1->edges == NULL) {
		v1->edges = (Edge *)malloc(sizeof(Edge));
		v1->edges->vertex = v2;
		v1->edges->next = NULL;
		return v1->edges;
	}
	if (searchEdge((v1->edges), v2) == NULL) {
		n = (Edge *)malloc(sizeof(Edge));
		n->vertex = v2;
		n->next = v1->edges;
		v1->edges = n;
		return n;
	}
	printf("A conexao dos vertices [%d] <-> [%d] ja existe!\n", v1->id, v2->id);
	return NULL;
}

Edge *searchEdgeByNext(Edge *e, Edge *n)
{
	Edge *aux = NULL;
	for (aux = e; aux != NULL; aux = aux->next)
		if (aux->next == n)
			return aux;
	return NULL;
}

int removeAllConnections(Vertex *v, Vertex *del)
{
	Edge *trash, *p, *aux;
	if(v->edges == NULL) {
		return 1;
	}
	aux = v->edges;
	p = NULL;
	while(aux != NULL) {
		if(aux->vertex == del) {
			trash = aux;
			if(p == NULL) {
				v->edges = aux = aux->next;
				free(trash);
			}else{
				trash = aux;
				p->next = aux = aux->next;
				free(trash);
			}
		}else{
			p = aux;
			aux = aux->next;
		}
	}
	return 0;
}

int removeConnection(Vertex *v1, Vertex *v2)
{
	Edge *trash, *p;

	if (v1->edges == NULL)
		return 1;

	if ((trash = searchEdge((v1->edges), v2)) != NULL) {
		if ((p = searchEdgeByNext(v1->edges, trash)) == NULL) {
			trash = v1->edges;
			v1->edges = v1->edges->next;
			free(trash);
			return 0;
		}
		p->next = trash->next;
		free(trash);
		return 0;
	}
	return 2;
}

int countVertex(Graph *g)
{
	Vertex *aux = NULL;
	int count = 0;

	if (*g == NULL)
		return 0;
	for (aux = *g; aux != NULL; aux = aux->next)
		count++;
	return count;
}

/* greedySearch FUNCTIONS */

int isVisited(Vertex *v[], int count, Vertex *n){
	int i;
	for (i = 0; i < count; i++)
		if(v[i] == n)
			return 1;
	return 0;
}

Vertex* searchMaxEdge(Vertex *discovered[], int count){
	int i, max = INT_MIN;
	Edge *e = NULL, *candidate = NULL;
	for (i = 0; i < count; i++)
		for(e = discovered[i]->edges; e != NULL; e = e->next)
			if(e->vertex->id > max && !isVisited(discovered, count, e->vertex)) {
				candidate = e;
				max = e->vertex->id;
			}
	if(candidate != NULL) {
		printf("|\n");
		printf("+-- maior vertice nao visitado  [\'%d\'] \n", candidate->vertex->id);
	}
	return candidate == NULL ? NULL : candidate->vertex;
}
