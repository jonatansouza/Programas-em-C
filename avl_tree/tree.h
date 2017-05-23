/**
   *@author Jonatan Souza
 */

#ifndef _Tree
#define _Tree

#include <stdio.h>
#include <stdlib.h>

struct _node {
	int info;
	int height;
	struct _node *left;
	struct _node *right;
};

typedef struct _node Node;
typedef Node* Tree;

/**
* Aloca espaço na memoria para a raiz da arvore
*/
Tree* createTree();
/**
* Verifica se a arvore esta vazia
*/
int isEmptyTree(Tree *t);


/**
* Rotação simples
* Duas inserções para a esquerda gira pra direita
*/
void rotationLL(Tree *t);

/**
* Rotacao simples
* Duas inserções para a direita gira pra esquerda
*/
void rotationRR(Tree *t);

/**
* Rotação dupla
*/
void rotationLR(Tree *t);

/**
* Rotação dupla
*/
void rotationRL(Tree *t);

/**
* Insere valores na arvore
*/
int insertTree(Tree *t, int info);

/**
* Remove elementos da arvore
*/
int removeTree(Tree *t, int info);

/**
* Altura da arvore binaria
*/
int treeHeight(Tree *t);

/**
* imprime a arvore na tela
*/
void printTree(Tree *t);

/**
*
*/
void destroyTree(Tree *t);

#endif
