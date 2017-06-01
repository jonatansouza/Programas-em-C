#include <stdio.h>
#include <string.h>
#include "graph.h"

#define BUFFER_SIZE 256
int main(int argc, char const *argv[]) {
	Graph *g = NULL;
	createGraph(&g);
	insertVertex(g, 'A');
	insertVertex(g, 'B');
	insertEdge(g, 'A', 'B', 10);
	insertEdge(g, 'B', 'A', 20);
	removeVertex(g, 'A');
	displayGraph(g);
	return 0;
}
