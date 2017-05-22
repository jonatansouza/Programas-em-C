#include <stdio.h>
#include <string.h>
#include "tree.h"

int main(int argc, char const *argv[]) {
	Tree* root = createTree();
	insertTree(root, 10);
	insertTree(root, 20);
	insertTree(root, 30);
	insertTree(root, 40);
	removeTree(root, 10);

	printf("%i\n", (*root)->info);
	return 0;
}
