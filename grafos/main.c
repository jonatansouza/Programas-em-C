/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include "graphs.h"

int main(int argc, char *argv[]){
	Graph *g = NULL;

	printf("Grafos\n");
	insertVertex(&g, 1);
	insertVertex(&g, 3);
	 insertVertex(&g, 4); 
	insertVertex(&g, 2);
	insertEdge(g, 3, 2);
	insertEdge(g, 3, 3);
	insertEdge(g, 1, 2);

	displayGraph(g);
	greedySearch(g);

	return 0;
}
