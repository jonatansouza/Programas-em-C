/**
   @author Jonatan Souza
 */
#include <stdio.h>
#include "rpn-utils.h"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	char input[BUFFER_SIZE];
	char stRpn[BUFFER_SIZE];
	double result;

	printf("=================================\n");
	printf("||       ");
	printf("RPN CALCULATOR!");

	printf("       ||\n");
	printf("=================================\n");

	printf("Digite a expressao e pressione enter ou q para sair:\n");
	while (1) {
		memset(input, 0, BUFFER_SIZE);
		memset(stRpn, 0, BUFFER_SIZE);
		printf("\n>> ");
		fgets(input, BUFFER_SIZE, stdin);

		if (input[0] == 'q') {
			printf("Ate logo!\n");
			return 0;
		}
		if (rpnParse(input, stRpn)) {
			printf("Ocorreu um erro no parser de \'%s\' por favor verifique a expressao digitada\n", input);
			continue;
		};
		if (rpnPrint(stRpn)) {
			printf("Ocorreu um erro durante o parser!\n" );
			continue;
		}
		if (!rpnCalc(stRpn, &result)) {
			printf("O resultado da expressao e %5.2f\n", result);
		} else {
			printf("Erro: Expressao incorreta!\n");
		}

	}

	return 0;
}
