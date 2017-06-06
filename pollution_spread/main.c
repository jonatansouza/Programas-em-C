#include <stdio.h>
#include <string.h>
#include "matrix.h"

#define BUFFER_SIZE 256
int main(int argc, char const *argv[]) {
	Matrix *m = NULL;
	char input[BUFFER_SIZE];

	printf("*******************************\n" );
	printf("*                             *\n" );
	printf("* POLLUTION SPREAD CALCULATOR *\n" );
	printf("*                             *\n" );
	printf("*******************************\n" );

	/**
	 * Check the user insert the file path from args
	 */
	if(argc > 1) {
		strcpy(input, argv[1]);
	}else{
		memset(input, 0, BUFFER_SIZE);
		printf("Digite o caminho do arquivo >> ");
		fgets(input, BUFFER_SIZE, stdin);
		input[strlen(input)-1] = '\0'; /** remove extra return */
	}
	system("color 70");
	if(PSRegister(&m, input)) {
		PSCompute(m);
		PSMatrixDestroy(m);
	}

	return 0;
}
