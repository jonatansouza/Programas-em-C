/**
*@author Jonatan Souza
*/
#ifndef _Graph
#define _Graph

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"


struct _vertex;
struct _edge;
struct _graph;
typedef struct _vertex Vertex;
typedef struct _edge Edge;
typedef struct _graph Graph;

int insertVertex(Graph **g, int id);
int insertEdge(Graph *g, int a, int b);
int removeVertex(Graph **g, int id);
int removeEdge(Graph *g, int a, int b);
int greedyLocalSearch(Graph *g);
int greedySearch(Graph *g);
void displayGraph(Graph *g);

#endif
