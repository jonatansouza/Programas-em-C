/**
   *@author Jonatan Souza
 */

#include "tree.h"



/**
        AUXILIAR FUNCTIONS
 **/

/**
 * Calcula a altura de um no da arvorer
 */
int nodeHeight(Node *n);
/**
 * Calcula o fator de balanceamento de um no
 */
int balanceFactorTree(Node *n);
/**
 * retorna o maior entre os dois valores passado por parametro
 */
int highestValue(int a, int b);

/* retorn o menor no */
Node* searchLowest(Node *t);

void destroyNode(Node *n);

void printNode(Node *n);

void printNode2(Node *n, int d);

/**
        AUXILIAR FUNCTIONS
                                END
 **/


void printTree(Tree *t){
	printNode(*t);
}

void destroyTree(Tree *t){
	if(t == NULL)
		return;
	destroyNode(*t);
	free(t);
}


int treeHeight(Tree *t){
	int l, r;
	if(t==NULL || *t==NULL)
		return 0;
	l = treeHeight(&((*t)->left));
	r = treeHeight(&((*t)->right));
	return (l > r) ? l+1 : r+1;
}



int insertTree(Tree *t, int info){
	Node *node;
	int res;

	/* Caso a arvore esteja vazia */
	if (*t == NULL) {
		node = (Node *) malloc(sizeof(Node));
		if(node == NULL)
			return 0;
		node->info = info;
		node->height = 0;
		node->left = NULL;
		node->right = NULL;
		*t = node;
		return 1;
	}
	node = *t;
	if(info < node->info) {
		/* verifica se a inserção funcionou e realiza o balanceamento */
		if((res = insertTree(&(node->left), info)) == 1) {
			/* caso seja maior que dois é necessario balancear */
			if(balanceFactorTree(node) >= 2) {
				if(info < (*t)->left->info) {
					rotationLL(t);
				}else{
					rotationLR(t);
				}
			}
		}
	}

	else{
		if(info > node->info) {
			if((res = insertTree(&(node->right), info)) == 1) {
				if(balanceFactorTree(node) >= 2) {
					if((*t)->right->info < info) {
						rotationRR(t);
					}else{
						rotationRL(t);
					}
				}
			}
		}else{
			printf("Valor duplicado\n");
			return 0;
		}
	}
	node->height = highestValue(nodeHeight(node->left), nodeHeight(node->right)) + 1;
	return res;

}

int removeTree(Tree *t, int info){
	int res;
	Node *node;
	if(*t == NULL) {
		printf("valor nao existe\n");
		return 0;
	}
	if(info < (*t)->info) {
		if((res = removeTree(&(*t)->left, info)) == 1) {
			if(balanceFactorTree(*t) >= 2) {
				if(nodeHeight((*t)->right->left) <= nodeHeight((*t)->right->right)) {
					rotationRR(t);
				}else{
					rotationRL(t);
				}
			}
		}
	}
	if((*t)->info < info) {
		if ((res = removeTree(&(*t)->right, info)) == 1) {
			if(balanceFactorTree(*t) >= 2) {
				if(nodeHeight((*t)->left->right) <= nodeHeight((*t)->left->left)) {
					rotationLL(t);
				}else{
					rotationLR(t);
				}
			}
		}
	}
	if((*t)->info == info) {
		if(((*t)->left == NULL || (*t)->right == NULL)) {
			node = *t;
			if((*t)->left != NULL) {
				*t = (*t)->left;
			}else{
				*t = (*t)->right;
			}
			free(node);
		}else{
			node = searchLowest((*t)->right);
			(*t)->info = node->info;
			removeTree(&(*t)->right, (*t)->info);
			if(balanceFactorTree(*t) >= 2) {
				if(nodeHeight((*t)->left->right) <= nodeHeight((*t)->left->left)) {
					rotationLL(t);
				}else{
					rotationLR(t);
				}
			}
		}
		return 1;
	}
	return res;
}

void rotationLL(Tree *t){
	Node *node = (*t)->left;
	(*t)->left = node->right;
	node->right = (*t);
	(*t)->height = highestValue(nodeHeight((*t)->left), nodeHeight((*t)->right)) +1;
	node->height = highestValue(nodeHeight(node->left), (*t)->height)+1;
	(*t) = node;

}

void rotationRR(Tree *t){
	Node *node = (*t)->right;
	(*t)->right = node->left;
	node->left = (*t);
	(*t)->height = highestValue(nodeHeight((*t)->left), nodeHeight((*t)->right)) +1;
	node->height = highestValue(nodeHeight(node->right), (*t)->height)+1;
	(*t) = node;

}

void rotationLR(Tree *t){
	rotationRR(&(*t)->left);
	rotationLL(t);
}

void rotationRL(Tree *t){
	rotationLL(&(*t)->right);
	rotationRR(t);
}

int isEmptyTree(Tree* t){
	return (t == NULL || *t == NULL) ? 1 : 0;
}

Tree* createTree(){
	Tree *root = (Tree *) malloc(sizeof(Tree));
	if(root != NULL)
		*root = NULL;
	return root;
}



/**
 * AUXILIAR FUNCTIONS
 */


int nodeHeight(Node *n){
	if (n == NULL)
		return -1;
	return n->height;
}
int balanceFactorTree(Node *n){
	int bf = nodeHeight(n->left) - nodeHeight(n->right);
	return (bf >= 0 ? bf : bf*(-1));
}
int highestValue(int a, int b){
	return (a > b) ? a : b;
}

Node* searchLowest(Node *t){
	Node *n1 = t;
	Node *n2 = t->left;
	while(n2 != NULL) {
		n1 = n2;
		n2 = n2->left;
	}
	return n1;
}

void destroyNode(Node *n){
	if(n == NULL)
		return;
	destroyNode(n->left);
	destroyNode(n->right);
	free(n);
	n = NULL;
}

void printNode(Node *n){
	printNode2(n, 0);
	/*int i;
	   if(n == NULL)
	        return;
	   printNode(n->left);
	   for (i = 0; i < n->height; i++) {
	        printf("          ");
	   }
	   printf("(%d) %d\n", n->info, n->height);
	   printNode(n->right);*/

}

void printNode2(Node *n, int d){
	int i;
	if(n == NULL)
		return;
	printNode2(n->right, d+1);
	for(i=0; i<d; i++)
		printf("    ");
	printf("(%d)\n", n->info);
	printNode2(n->left, d+1);

}
