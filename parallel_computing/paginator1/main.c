/**
   @author Jonatan Souza
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
		close(STDIN_FILENO);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execv(paginator[0], paginator);

  }else if(pid < 0){
    error_message();
  }else{

  	close(STDOUT_FILENO);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		char c;
		while ((c = (char) getc(file)) != EOF)
			write(1, &c, sizeof(c));
		fclose(file);
		close(1);
	}
	waitpid(pid, NULL, 0);

	return 0;
}
