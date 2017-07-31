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
	int m, p1 = -1, p2 = -1, p3 = -1;
	int id;
	m = getpid();
	id = shmget(IPC_PRIVATE,(sizeof(char) * 30),0600);
	p1 = fork();
	if(m == getpid()){
		p2 = fork();
	}
	if(m == getpid()){
		p3 = fork();
	}

	char *msg = shmat(id, 0,0);
	if(p1 == 0){
		pthread_t t1, t2;
		pthread_create(&t1, NULL, myThread, NULL);
		pthread_create(&t2, NULL, myThread, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		printf("processo %d\n", getpid());
	}
	if(p2 == 0){
		printf("remetente messagem id %d\n", getpid());
		strcpy( msg, "memoria compartilhada em SO2");
		exit(NULL);
	}
	if(p3 == 0){
		wait(NULL);
		printf("destinatario da mensagem id %d\n", getpid());
		printf("A mensagem compartilhada e [%s]\n", msg);
	}

	return 0;
}
