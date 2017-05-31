#include <stdio.h>
#include <string.h>
#include "graph.h"

#define BUFFER_SIZE 256
int main(int argc, char const *argv[]) {
	Graph *g = NULL;
	createGraph(&g);
	insertVertex(g, 'A', 10);
	return 0;
}
