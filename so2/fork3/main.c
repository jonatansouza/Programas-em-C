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
	int m, p1 = -1, p2 = -1, p3 = -1;
	int fd[2];
	char str[25];
	m = getpid();

	pipe(fd);
	p1 = fork();
	if(m == getpid()) {
		p2 = fork();
	}
	if(m == getpid()) {
		p3 = fork();
	}
	if(p1 == 0) {
		printf("sou um processo filho id %d\n", getpid());
		int n = fork();
		if(n == 0)
			printf("sou um processo neto id %d\n", getpid());
	}
	if(p2 == 0) {
		printf("Sou um processo filho id %d\n", getpid());
	}
	if(p3 == 0) {
		printf("Sou um processo filho id %d\n", getpid());
	}

	if(m == getpid()) {
		sprintf(str, "%s", "Sou o pai dos processos!");
		write(fd[1], str, 25);
	}
	if (p2 == 0) {
		read(fd[0], str, 25);
		printf("Messagem do pai [%s]\n", str);
	}


	return 0;
}
