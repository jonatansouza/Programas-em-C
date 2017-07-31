/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/shm.h>

#define qtdProcess 3

void *myThread(){
	printf("thread %d\n", (int)pthread_self());
}


int main(int argc, char *argv[]){
	int i, m, p1, p2, p3;
	m = getpid();
	p1 = fork();
	if(m == getpid()){
		p2 = fork();
	}
	if(m == getpid()){
		p3 = fork();
	}
	if(p1 == 0) {
		printf("processo %d\n", getpid());
	}
	if(p2 == 0) {
		printf("remetente messagem id %d\n", getpid());
	}
	if(p3 == 0) {
		printf("destinatario da mensagem id %d\n", getpid());
	}

	return 0;
}
