/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include "graphs.h"

int main(int argc, char *argv[]){
	Graph *g = NULL;

	printf("Grafos\n");
	insertVertex(&g, 1);
	insertVertex(&g, 2);
	insertVertex(&g, 3);
	insertEdge(g, 3, 1);
	insertEdge(g, 3, 2);
	insertEdge(g, 3, 3);
	displayGraph(g);
	removeVertex(&g, 1);
	removeVertex(&g, 2);

	removeVertex(&g, 2);
	displayGraph(g);

	return 0;
}
