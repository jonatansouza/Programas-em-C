#include <stdio.h>
void inverteSeq(int *seq, int n);

int main(int argc, char *argv[]){
	int seq[argc-1];
	int i;
	for(i=1; i<argc; i++){
		seq[i-1] = atoi(argv[i]);
	}	
	printf("Sequencia digitada!\n");	

	for(i=1; i<argc; i++){
		printf("%d,", seq[i-1]);
	}
	printf("\n");	
	inverteSeq((int *)&seq, argc-1);
}

void inverteSeq(int *seq, int n){
	int i, temp;
	
	for(i=0; i < n/2; i++){
		temp = seq[i];
		seq[i] = seq[(n-1)-i];
		seq[(n-1)-i]  = temp;
	}
	printf("\nSequencia inversa!\n");	
	for(i=0; i<n; i++){
		printf("%d,", seq[i]);
	}
	printf("\n");	
}
