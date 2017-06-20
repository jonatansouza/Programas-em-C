#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"

#define BUFFER_SIZE 256

int main(int argc, char const *argv[]) {
	int running = 1, vertex = 0, dest;
	char option;
	Graph *g = NULL;

	printf("+++++++++++++++++++++++++++++++++\n");
	printf("+     Grafos e Busca Gulosa     +\n");
	printf("+++++++++++++++++++++++++++++++++\n");

	createGraph(&g);

	#ifdef DEV

	insertVertex(g, 10);
	insertVertex(g, 20);
	insertVertex(g, 30);
	insertVertex(g, 90);
	insertVertex(g, 50);
	insertVertex(g, 15);
	insertEdge(g, 10, 20);
	insertEdge(g, 30, 20);
	insertEdge(g, 15, 50);
	insertEdge(g, 90, 50);
	insertEdge(g, 50, 10);
	displayGraph(g);
	greedySearch(g, 90);
	destroyGraph(g);
	#else

	while (running) {
		printf("\n1 - inserir vertice\n");
		printf("2 - inserir aresta\n");
		printf("3 - remover vertice\n");
		printf("4 - remover aresta\n");
		printf("5 - imprimir grafo\n");
		printf("6 - Busca Gulosa\n");
		printf("7 - sair\n");
		printf("\n>>");
		scanf(" %c", &option);
		switch (option) {
		case '1':
			printf("Digite um id para o novo no (um numero inteiro)\n");
			printf(">>");
			if (scanf(" %d", &vertex) == 1)
			if (!insertVertex(g, vertex)) {
				printf("Vertice inserido!\n");
				printf("Digite os vizinhos ou \'q\' para continuar\n");
				printf(">>");
				while (scanf("%d", &dest)==1) {
					if(!insertEdge(g, vertex, dest))
						printf("Aresta inserida!\n");
				}
			}
			getchar();
			break;
		case '2':
			printf("Digite um par de vertices para a nova aresta (exemplo: 10 20)\n");
			printf(">>");
			scanf(" %d %d", &vertex, &dest);
			if(!insertEdge(g, vertex, dest))
				printf("Aresta inserida!\n");
			break;
		case '3':
			printf("Digite o id do vertice a ser deletado\n");
			printf(">>");
			scanf(" %d", &vertex);
			if(!removeVertex(g, vertex))
				printf("vertice removido!\n");
			break;
		case '4':
			printf("Digite o par de vertices que compoem a aresta (exemplo: 10 20)\n");
			printf(">>");
			scanf(" %d %d", &vertex, &dest);
			if(!removeEdge(g, vertex, dest))
				printf("aresta removida!\n");
			break;
		case '5':
			displayGraph(g);
			break;
		case '6':
			printf("Digite um vertice para inicio da busca\n");
			printf(">>");
			scanf(" %d", &vertex);
			greedySearch(g, vertex);
			break;

		case '7':
			printf("Ate logo\n");
			running = 0;
			destroyGraph(g);
			break;
		default:
			printf("Opcao invalida\n");
			break;
		}
	}
	#endif
	return 0;
}
