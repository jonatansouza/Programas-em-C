#include <stdio.h>
#include <string.h>
#include "tree.h"

int main(int argc, char const *argv[]) {
	Tree* root = createTree();
	int rands[10] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, i=0;
	int sample;
	char c;
	printf("############################## \n");
	printf("#          AVL TREE          # \n");
	printf("############################## \n");

	while ( i < 10) {
		getchar();
		insertTree(root, rands[i++]);
		printTree(root);
	}
	while ( i >= 0) {
		getchar();
		removeTree(root, rands[i--]);
		printTree(root);
	}

/*
while (1) {
	        printf("\ni - Inserir\nr - Remover\np - imprimir\nq - sair\n\n");
	        printf(">>");
	        scanf(" %c", &c);
	        switch (c) {
	        case 'i':
	        case 'I':
	                printf("digite um valor: ");
	                scanf(" %d", &sample);
	                getchar();
	                if(insertTree(root, sample)){
	                        printf("valor %d inserido com sucesso!\n", sample);
	                }
	                break;
	        case 'r':
	        case 'R':
	                printf("digite um valor: ");
	                scanf(" %d", &sample);
	                getchar();
	                if(removeTree(root, sample)){
	                        printf("valor %d removido com sucesso!\n", sample);
	                }
	                break;
	        case 'p':
	        case 'P':
	                printTree(root);
	                break;
	        case 'q':
	        case 'Q':
	                destroyTree(root);
	                return 1;
	                break;
	        default:
	                printf("Entrada invalida!\n");
	                break;
	        }
	   }*/
	return 0;
}
