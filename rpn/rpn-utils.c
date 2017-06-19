/**
   @author Jonatan Souza
 */
#include "rpn-utils.h"


/**
 *      AUXILIAR FUNCTIONS
 **/
int isOperator(char input);
int isDigit(char input);
int operatorPriority(char operator);
double rpnResolve(double x1, double x2, char op);
void concatRpnPostfix(char *postfix, char operator);
/**
 *        AUXILIAR FUNCTIONS END
 **/

int isOperator(char input){
	int i = 0;
	char options[7] = {'+', '-', '*', '/', '(', ')', 's'};
	for (i = 0; i < 7; i++) {
		if(input == options[i]) {
			return 1;
		}
	}
	return 0;
}

int isDigit(char input){
	return (input > 47 && input < 58) ? 1 : 0;
}

int isUnary(char *infix, int infixSize){
	int i;
	if (infixSize == 0 && infix[infixSize] == '-')
		return 1;
	if(isDigit(infix[infixSize+1]) && infix[infixSize] == '-') {
		for(i = (infixSize-1); i >= 0; i--) {
			if(isDigit(infix[i]))
				return 0;
			if(isOperator(infix[i]))
				return 1;
		}
	}
	return 0;
}


int operatorPriority(char operator){
	switch (operator) {
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case 's':
		return 3;
	case ')':
		return 0;
	case '(':
		return 4;
	default:
		return -1;
	}
}

int rpnParse(char *infix, char *postfix){
	int i=0;
	char * aft;
	char subs[16];
	char operator;
	Stackc *ops = NULL;

	while ( i < strlen(infix)) {
		if(isDigit(infix[i])) {
			sprintf(subs, "%5.2f", strtod(&infix[isUnary(infix, (i-1)) ? i-1 : i], &aft));
			strcat(postfix, subs);
			strcat(postfix, " ");
			i = (aft - infix);
			continue;
		}else if(isOperator(infix[i]) && !isUnary(infix, i)) {
			if(infix[i] == 's' && (infix[i+1] != 'q' || infix[i+2] != 'r' || infix[i+3] != 't')) {
				printf("Operador nao permitido! Utilize \'sqrt\'\n");
				return 1;
			}else{
				if (pickTop(ops, &operator)) {
					if(operatorPriority(operator) >= operatorPriority(infix[i]) && operator != '(') {
						while (operatorPriority(operator) >= operatorPriority(infix[i])) {
							if(!popc(&ops, &operator) || operator == '(') {
								break;
							}
							concatRpnPostfix(postfix, operator);
						}
						pushc(&ops, infix[i]);
						pickTop(ops, &operator);
					}else{
						pushc(&ops, infix[i]);
						pickTop(ops, &operator);
					}
				}else{
					pushc(&ops, infix[i]);
				}
			}
		}
		i++;
	}

	while(popc(&ops, &operator)) {
		concatRpnPostfix(postfix, operator);
	}
	return 0;
}

void concatRpnPostfix(char *postfix, char operator){
	if(operator != '(' && operator != ')') {
		strncat(postfix, &operator, 1);
		strcat(postfix, " ");
	}
}

int rpnPrint(char * rpnString){
	int i;
	for(i=0; i<strlen(rpnString); i++) {
		printf("%c", rpnString[i]);
		if(rpnString[i] == 's')
			printf("qrt");
	}
	printf("\n");
	return 0;
}


/**
 * Concat Double values on string
 */
int rpnCalc(char *input, double *result){
	Stack *s = NULL;
	int i = 0;
	double val1 = 0, val2 = 0;
	char *aft;
	while(i < strlen(input)) {
		if(isDigit(input[i])) {
			push(&s, strtod(&input[i > 0 ? i-1 : i], &aft));
			i = (aft - input);
			continue;
		}else if (isOperator(input[i]) && !isUnary(input, i)) {
			pop(&s, &val1);
			if(input[i] != 's')
				pop(&s, &val2);
			push(&s, rpnResolve(val1, val2, input[i]));
		}
		i++;
	}
	pop(&s, result);
	return (s != NULL) ? 1 : 0;
}

double rpnResolve(double x1, double x2, char op){
	switch (op) {
	case '+':
		return x1 + x2;
	case '-':
		return x2 - x1;
	case '*':
		return x1 * x2;
	case '/':
		return x2 / x1;
	case 's':
		return sqrt(x1);
	default:
		return -1;
	}
}
