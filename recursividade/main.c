#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc > 2 || argc == 1){
		printf("wrong number of args!\n");
		return 0;
	}
	
	int x = atoi(argv[1]);
	printf("fatorial de %d e:\n", x);
	int result = fatorial(x);
	printf("%d\n", result);
}

int fatorial(int x){
	if(x)
		return x*fatorial(x-1);
	else
		return 1;	
}

