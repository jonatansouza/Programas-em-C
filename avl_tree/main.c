#include <stdio.h>
#include <string.h>
#include "tree.h"

int getOneChar(){
	int c,garbage;
	c=garbage=fgetc(stdin);
	while(garbage!='\n'&&garbage!=EOF)
		garbage=fgetc(stdin);
	return c;
}

int main(int argc, char const *argv[]) {
	Tree* root = createTree();
	int sample;
	char c;
	printf("############################## \n");
	printf("#          AVL TREE          # \n");
	printf("############################## \n");
	while (1) {
		printf("\nInserir (i), Remover (r), imprimir(p), sair (q):\n");
		scanf("%c", &c);
		scanf("%*[^\n]%*1[\n]");
		switch (c) {
		case 'i':
		case 'I':
			printf("digite um valor: ");
			scanf("%d", &sample);
			scanf("%*[^\n]%*1[\n]");
			insertTree(root, sample);
			break;
		case 'r':
		case 'R':
			printf("digite um valor: ");
			scanf("%d", &sample);
			scanf("%*[^\n]%*1[\n]");
			removeTree(root, sample);
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
	}
	return 0;
}
