/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define qtdProcess 3

int main(int argc, char *argv[]){
	int m, p1 = -1, p2 = -1;
	int fd[2];
	char str[25];
	m = getpid();

	/* abrindo o canal de comunicacao */
	pipe(fd);

	p1 = fork();
	if(m == getpid()) {
		p2 = fork();
	}
	if(p1 == 0) {
		printf("sou um processo filho remetente da mensagem,  id %d\n", getpid());
		sprintf(str, "%s", "enviada via pipe!");
		write(fd[1], str, 25);
	}
	if(p2 == 0) {
		printf("Sou um processo filho destinatario da mensagem, id %d\n", getpid());
		read(fd[0], str, 25);
		printf("Messagem [%s]\n", str);

	}


	return 0;
}
