#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc > 2 || argc == 1){
		printf("wrong number of args!\n");
		return 0;
	}
	int i, result = 1;
	int val = atoi(argv[1]);
	//calcular fatorial
	for(i=val; i > 0; i--){
		result *= i;
	}	
	
	printf("O fatorial de %d é: %d\n", val, result);
}


