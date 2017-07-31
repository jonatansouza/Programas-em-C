
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define vetorSize 1000
#define qtdProcess 2

int main(int argc, char *argv[]){

	int total = 0;
	int auxI = -1;
	int principal = getpid();
	int result;
	int i, j;
	int process[qtdProcess];


	//abrindo os processos

	for(i=0; i < qtdProcess; i++) {
		if(getpid() == principal) {
			process[i] = fork();
			auxI++;
		}
	}

	//INICIANDO O VETOR
	int vetor[vetorSize];
	for(i=0; i<vetorSize; i++) {
		vetor[i] = i;
	}

	//executando nos processos filhos
	for(i=0; i<qtdProcess; i++) {
		if(getpid()!=principal) {
			int els = 0;
			int count = 0;
			for(j=(auxI*(vetorSize/qtdProcess));
			    j < ((auxI+1)*(vetorSize/qtdProcess));
			    j++) {
				count += vetor[j];
				els++;
			}
			count = (count/els);
			exit(count);
		}
	}
	//pai esperando resultados

	if(getpid()==principal) {
		for(i=0; i<qtdProcess; i++) {
			waitpid(process[i], &result, 0);
			printf("%d\n", WEXITSTATUS(result));
		}
		total = (int)total/qtdProcess;
		printf("************************************\n\n");
		printf("a media de elementos - %d é -> %d\n\n", vetorSize, total);
		printf("***********************************\n\n");
	}

}
