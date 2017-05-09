#include "rpn-utils.h"


/**
        AUXILIAR FUNCTIONS

 **/

double rpnResolve(double x1, double x2, char op);

/**
        AUXILIAR FUNCTIONS
        END
 **/

int isOperator(char input){
	int i = 0;
	char options[4] = {'+', '-', '*', '/'};
	for (i = 0; i < 4; i++) {
		if(input == options[i]) {
			return 1;
		}
	}
	return 0;
}

int isDigit(char input){

	if(input > 47 && input < 58) {
		return 1;
	}
	return 0;
}

int isUnary(char input){
	return 0;
}

int rpnDecode(char *input){
	Stack *s = NULL;
	int i = 0;
	double val1, val2;
	char *aft;
	while(i < strlen(input)) {
		if(isDigit(input[i])) {
			push(&s, strtod(&input[i > 0 ? (i-1) : i], &aft));
			i = (strlen(input)-strlen(aft));
			continue;
		}else if (isOperator(input[i]) && !isDigit(input[i+1])) {
			pop(&s, &val1);
			pop(&s, &val2);
			push(&s, rpnResolve(val1, val2, input[i]));
		}
		i++;
	}
	printf("***************\n");
	printStack(s);
	return 0;
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
	default:
		return -1;
	}
}
