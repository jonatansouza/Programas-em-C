/**
   @author Jonatan Souza
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>

int main(int argc, char **args){

	int fd[2], pid;

	char *paginator[2] = {"/bin/more", NULL};
	pipe(fd);

	if ((pid = fork()) == 0) {
		close(STDIN_FILENO);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execv(paginator[0], paginator);

	}else{
		close(STDOUT_FILENO);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		char c;
		FILE *file;
		file = fopen("main.c", "r");
		if (file) {
			while ((c = (char) getc(file)) != EOF)
				write(1, &c, sizeof(c));
			fclose(file);
		}
		close(1);
	}
	waitpid(pid, NULL, 0);
	
	return 0;
}
