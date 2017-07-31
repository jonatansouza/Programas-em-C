/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/shm.h>


int main(int argc, char *argv[]){
	int m, p1 = -1, p2 = -1;
	int id;
	id = shmget(IPC_PRIVATE,(sizeof(char) * 40),0600);
	m = getpid();
	char *msg = (char *)shmat(id, 0,0);
	p1 = fork();
	if(m == getpid()) {
		p2 = fork();
	}
	if(p1 == 0) {
		printf("sou um processo filho remetente da mensagem,  id %d\n", getpid());
		strcpy( msg, "enviada via memoria compartilhada!");
		exit(NULL);
	}
	if(p2 == 0) {
		printf("Sou um processo filho destinatario da mensagem, id %d\n", getpid());
		wait(NULL);
		printf("Messagem [%s]\n", msg);
	}


	return 0;
}
