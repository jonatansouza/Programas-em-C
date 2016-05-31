#include <stdio.h>
#include <stdlib.h>

#define M 50

struct pilha {
	int info[M];
	int n;
};
typedef struct pilha Pilha;

Pilha* cria(){
	return (Pilha*) malloc(sizeof(Pilha));;
}

void push(Pilha* p, float v){
	p->info[p->n] = v;
	p->n++;
}

float pop(Pilha* p){
	float v = p->info[p->n-1];
	p->n--;
	return v;
}

void print(Pilha* p){
	int i;
	for(i=p->n-1; i>=0; i--) {
		printf("%d \n", p->info[i]);
	}
}

void concatena_pilhas(Pilha *p1, Pilha *p2){
	if(p2->n > 0) {
		push(p1, pop(p2));
		concatena_pilhas(p1,p2);
	}
	print(p1);
}

int main(){
	Pilha *p1 = cria();
	push(p1, 10);
	push(p1, 45);
	push(p1, 21);
	print(p1);

	Pilha *p2 = cria();
	push(p2, 98);
	push(p2, 31);
	push(p2, 72);
	print(p2);

	concatena_pilhas(p1, p2);
	printf("#####\n" );
	print(p1);

}
