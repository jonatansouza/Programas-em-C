#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"

#define BUFFER_SIZE 256

int main(int argc, char const *argv[]) {
	int running = 1, cost = 0, i, j;
	char input[BUFFER_SIZE], *aft;
	char vertex, dest, option;
	Graph *g = NULL;
	createGraph(&g);

	#ifdef DEV

	insertVertex(g, 'a');
	insertVertex(g, 'b');
	insertVertex(g, 'c');
	insertVertex(g, 'd');
	insertVertex(g, 'e');
	insertVertex(g, 'f');
	insertEdge(g, 'a', 'b', 100);
	insertEdge(g, 'a', 'c', 300);
	insertEdge(g, 'a', 'a', 100);
	insertEdge(g, 'd', 'b', 70);
	insertEdge(g, 'f', 'c', 10);
	insertEdge(g, 'a', 'f', 10);
	insertEdge(g, 'a', 'f', 20);
	insertEdge(g, 'a', 'a', 100);
	displayGraph(g);
	greedySearch(g, 'a');
	destroyGraph(g);
	#else

        while (running) {
                memset(input, 0, BUFFER_SIZE);
                printf("\n1 - inserir vertice\n");
                printf("2 - inserir aresta\n");
                printf("3 - remover vertice\n");
                printf("4 - remover aresta\n");
                printf("5 - imprimir grafo\n");
                printf("6 - Busca Gulosa\n");
                printf("7 - sair\n");
                printf("\n$");

                scanf(" %c", &option);
                switch (option) {
                case '1':
                        printf("Digite um id para o novo no (apenas um caracter)\n");
                        printf(">>");
                        scanf(" %c", &vertex);
                        if (!insertVertex(g, vertex)) {
                                printf("Vertice inserido!\n");
                                printf("Digite os vizinhos (exemplo:b10 c20 d30) obs: caso o valor nao seja indicado o default sera 0\n");
                                getchar();
                                fgets(input, BUFFER_SIZE, stdin);
                                for(i = 0; i < strlen(input); i++) {
                                        if(isalpha(input[i])) {
                                                dest = input[i];
                                                for(j = i+1; j <= strlen(input); j++) {
                                                        if(isdigit(input[j])) {
                                                                cost = strtod(&input[j], &aft);
                                                                i = (aft - input) -1;
                                                                if(!insertEdge(g, vertex, dest, cost))
                                                                        printf("Aresta inserida [%c] - [%c] com custo %d!\n", vertex, dest, cost);
                                                                break;
                                                        }
                                                        if(isalpha(input[j]) || input[j] == '\0') {
                                                                if(!insertEdge(g, vertex, dest, 0))
                                                                        printf("Aresta inserida [%c] - [%c] com custo 0!\n", vertex, dest);
                                                                break;
                                                        }
                                                }
                                        }
                                }
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
                        printf("Digite um vertice para inicio da busca\n");
                        printf(">>");
                        scanf(" %c", &vertex);
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
