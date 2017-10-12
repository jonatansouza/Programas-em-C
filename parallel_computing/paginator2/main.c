/**
*   Trabalho da disciplina Programação Concorrente e Sistemas Operacionais
* 	Professora Raquel
*
*	@author Jonatan Souza
*   
*   Este programa recebe como argumento o path de um arquivo 
*   e repassa linha a linha para um processo filho 
*   que executa o paginador more
*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>

 #define N_ARGS 2

void help_messages(){
    printf("Failed: incorrect number of args\n");
    printf("Usage: ./paginator <path_file> \n");
    exit(-1);
}

void error_message(){
    perror("error: ");
    exit(-1);
}

int main(int argc, char **argv){

	int fd[2], pid;
	FILE *file;

  	if(argc != N_ARGS){
    		help_messages();
  	}

	file = fopen(argv[1], "r");

	if(file == NULL){
		error_message();
	}

	char *paginator[2] = {"/bin/more", NULL};
	
	pipe(fd);

	if ((pid = fork()) == 0) {
		
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execv(paginator[0], paginator);

  	}else if(pid < 0){
    
		error_message();
  	
	}else{

		char c;
	
		while ((c = (char) getc(file)) != EOF)
			write(fd[1], &c, sizeof(c));
		
		fclose(file);
		close(fd[0]);
		close(fd[1]);
	}
	
	waitpid(pid, NULL, 0);

	return 0;
}
