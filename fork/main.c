/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define nProcess 3

int main(int argc, char *argv[]){
	int i, m;
	m = getpid();
	for (i = 0; i < nProcess; i++) {
		if (getpid() == m) {
			fork();
		}
	}
	if(getpid() == m)
		printf("pai - %d\n", getpid());
	else
		printf("filho - %d\n", getpid());

	return 0;
}
