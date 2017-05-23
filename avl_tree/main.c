#include <stdio.h>
#include <string.h>
#include "tree.h"

int main(int argc, char const *argv[]) {
	Tree* root = createTree();
	int a;
	while (1) {
		printf("digite um valor\n");
		scanf("%d", &a);
		if (a == 'q') {
			return 1;
		}
		insertTree(root, a);
		printf("arvore avl\n");
		printTree(root);
	}
	destroyTree(root);
	return 0;
}
