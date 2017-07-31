
/**
   *@autor Jonatan Souza
 *
 ***Este programa calcula a qtd de pares em um vetor de n posicoes.
 ***recebe por parametro o numero de threads
 ***o tamanho do vetor pode ser alterado.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

#define vetorSize 1000
#define qtdThreads 2

int vetor[vetorSize];
int job;

void *ant(void *itr){
	int i,  els=0, val, max;
  int count = 0;
  val = (int) itr;
  if(val*job > 0){
    max = vetorSize;
  }else{
    max = vetorSize/2;
  }
	for(i=val*job; i < max; i++) {
		count += vetor[i];
		els++;
	}
  count = (int) count/els;
  printf("%d\n",count );
  pthread_exit((void *)count);
}

int main(int argc, char *argv[]){
	int i;
  int count = 0;
	void *st;
	pthread_t threads[qtdThreads];
	job = vetorSize / qtdThreads;

//INICIANDO O VETOR
	for(i=0; i<vetorSize; i++) {
		vetor[i] = i;
	}


//abrindo threads
	for(i=0; i < qtdThreads; i++) {
		pthread_create(&threads[i], NULL, ant, (void *)i);
	}

	for(i=0; i<qtdThreads; i++) {
		pthread_join(threads[i], &st);
		count += (int) st;
	}
	/* pois sao duas threads */
	count = (int)count/2;
	printf("************************************\n\n");
	printf("a media de elementos - %d é -> %d\n\n", vetorSize, count);
	printf("***********************************\n\n");
}
