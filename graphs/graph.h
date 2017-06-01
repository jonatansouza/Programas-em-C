/**
   *@author Jonatan Souza
 */

#ifndef _GRAPH
#define _GRAPH

#include <stdlib.h>
#include <stdio.h>

struct _vertex;
struct _edge;

typedef struct _vertex Vertex;
typedef struct _edge Edge;
typedef struct _vertex *Graph;

int createGraph(Graph **g);
void displayGraph(Graph *g);
int insertVertex(Graph *g, char name);
int removeVertex(Graph *g, char name);
int insertEdge(Graph *g, char origin, char destiny, int cost);
int removeEdge(Graph *g, int a, int b, int cost);
#endif
