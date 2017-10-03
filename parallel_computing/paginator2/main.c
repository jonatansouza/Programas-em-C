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
		printf("paginando\n");
		dup2(fd[0], 0);
		close(fd[1]);
		execv(paginator[0], paginator);

	}else{
		printf("lendo\n");
		dup2(fd[1], 1);
		close(fd[0]);
		int c;
		FILE *file;
		file = fopen("main.c", "r");
		if (file) {
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
	}
	waitpid(pid, NULL, 0);
  return 0;
}
