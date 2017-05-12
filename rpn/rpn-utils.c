#include "rpn-utils.h"


/**
        AUXILIAR FUNCTIONS

 **/

double rpnResolve(double x1, double x2, char op);
void insertSpaceRpnPostfix(char *postfix);
int rpnConvert(Queue **digits, QueueC **operators, char *postfix);
void concatRpnPostfix(char *postfix, char operator);
/**
        AUXILIAR FUNCTIONS
        END
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
	if(input > 47 && input < 58) {
		return 1;
	}
	return 0;
}


int operatorPriority(char operator){
	switch (operator) {
	case '#':
		return -10;
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

int rpnCollect(char *infix, char *postfix){
	int i=0;
	char * aft;
	char subs[16];
	char operator;
	Stackc *ops = NULL;

	while ( i < strlen(infix)) {
		if(isDigit(infix[i])) {
			sprintf(subs, "%5.2f", strtod(&infix[i], &aft));
			strcat(postfix, subs);
			strcat(postfix, " ");
			i = (aft - infix);
			continue;
		}else if(isOperator(infix[i])) {
			if(infix[i] == 's' && infix[i+3] != 't') {
				printf("Bad operator! Use \'sqrt\'\n");
				return 1;
			}else{
				if (getTop(ops, &operator)) {
					if(operatorPriority(operator) >= operatorPriority(infix[i]) && operator != '(') {
						while (operatorPriority(operator) > operatorPriority(infix[i])) {
							if(!popc(&ops, &operator) || operator == '(') {
								break;
							}
							concatRpnPostfix(postfix, operator);
						}
						pushc(&ops, infix[i]);
						getTop(ops, &operator);
					}else{
						pushc(&ops, infix[i]);
						getTop(ops, &operator);
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
	printf("%s\n", postfix);
	rpnDecode(postfix);
	return 0;
}

void concatRpnPostfix(char *postfix, char operator){
	if(operator != '(' && operator != ')') {
		strncat(postfix, &operator, 1);
		strcat(postfix, " ");
	}
}


/**
 * Concat Double values on string
 */
int rpnDecode(char *input){
	Stack *s = NULL;
	int i = 0;
	double val1, val2;
	char *aft;
	while(i < strlen(input)) {
		if(isDigit(input[i])) {
			push(&s, strtod(&input[i > 0 ? (i-1) : i], &aft));
			i = (aft - input);
			continue;
		}else if (isOperator(input[i]) && !isDigit(input[i+1])) {
			pop(&s, &val1);
			if(input[i] != 's')
				pop(&s, &val2);
			push(&s, rpnResolve(val1, val2, input[i]));
		}
		i++;
	}
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
	case 's':
		return sqrt(x1);
	default:
		return -1;
	}
}
