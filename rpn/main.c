#include <stdio.h>
#include "rpn-utils.h"

int main(int argc, char *argv[]){
/*	struct stFila stPolonesa;
        char sExpressao[256];
        float fResultado;

        puts("Digite expressão parentizada:");
        gets(sExpressao);
        parser(sExpressao, stPolonesa);
        imprimeFila(stPolonesa);
        fResultado = calcula(stPolonesa);
        printf("O resultado da expressão é %5.2f\n", fResultado);
 */
	/*Stack *calcRPN = NULL; */

	char result[256];
	result[0] = '\0';

	printf("RPN CALCULATOR!\n");
	rpnCollect(argv[1], result);
	/*rpnDecode(argv[1]);*/

	return 0;
}
