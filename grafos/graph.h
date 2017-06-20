/**
   *@author Jonatan Souza
 */

#ifndef _GRAPH
#define _GRAPH

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

struct _vertex;
struct _edge;

typedef struct _vertex Vertex;
typedef struct _edge Edge;
typedef struct _vertex *Graph;

int createGraph(Graph **g);
int destroyGraph(Graph *g);
void displayGraph(Graph *g);
int insertVertex(Graph *g, int id);
int removeVertex(Graph *g, int id);
int insertEdge(Graph *g, int origin, int destiny);
int removeEdge(Graph *g, int a, int b);
void greedySearch(Graph *g, int id);
#endif
