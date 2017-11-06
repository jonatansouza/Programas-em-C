#include <stdio.h>
#include <stdlib.h>

int getrand(int min,int max){
  return(rand()%(max-min)+min);
}

int main(int argc, char const *argv[]) {
	FILE *f = fopen("matrix.out", "w");
  int i, j;
  int rows, cols;

  if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


  rows = atoi(argv[1]);
  cols = atoi(argv[2]);

  fprintf(f, "%d %d\n\n", rows, cols);

  for(i = 0; i<rows; i++){
    for ( j = 0; j < cols; j++) {
      fprintf(f, "%d ", getrand(-1, j+i));
    }
    fprintf(f, "\n");
  }


  printf("matrix %d x %d has been writed\n", rows, cols);

	fclose(f);
	return 0;
}
