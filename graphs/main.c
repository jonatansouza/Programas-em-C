#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(int argc, char const *argv[]) {
	int running = 1, cost = 0;
	char vertex, dest, option;
	Graph *g = NULL;
	createGraph(&g);

	while (running) {
		printf("\n1 - inserir vertice\n");
		printf("2 - inserir aresta\n");
		printf("3 - remover vertice\n");
		printf("4 - remover aresta\n");
		printf("5 - imprimir grafo\n");
		printf("6 - sair\n");
		printf("\n$");

		scanf(" %c", &option);
		switch (option) {
		case '1':
			printf("Digite um id para o novo nó (apenas um caracter)\n");
			printf(">>");
			scanf(" %c", &vertex);
			if (!insertVertex(g, vertex)) {
				printf("Vertice inserido!\n");
			}
			break;
		case '2':
			printf("Digite um par de vertices e um custo para a nova aresta (exemplo: A B 100)\n");
			printf(">>");
			scanf(" %c %c %d", &vertex, &dest, &cost);
			if(!insertEdge(g, vertex, dest, cost))
				printf("Aresta inserida!\n");
			break;
		case '3':
			printf("Digite o id do vertice a ser deletado\n");
			printf(">>");
			scanf(" %c", &vertex);
			if(!removeVertex(g, vertex))
				printf("vertice removido\n");
			break;
		case '4':
			printf("Digite o par de vertices e o custo da aresta (exemplo: A B 100)\n");
			printf(">>");
			scanf(" %c %c %d", &vertex, &dest, &cost);
			if(!removeEdge(g, vertex, dest, cost))
				printf("aresta removida!\n");
			break;
		case '5':
			displayGraph(g);
			break;
		case '6':
			printf("Até logo\n");
			running = 0;
			break;
		default:
			printf("Opção inválida\n");
			break;
		}
	}
	return 0;
}
