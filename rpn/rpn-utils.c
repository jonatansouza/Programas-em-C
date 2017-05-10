#include "rpn-utils.h"


/**
        AUXILIAR FUNCTIONS

 **/

double rpnResolve(double x1, double x2, char op);
void concatRpnPostfix(char *postfix, double val);
void insertSpaceRpnPostfix(char *postfix);
int rpnConvert(Queue **digits, QueueC **operators);

/**
        AUXILIAR FUNCTIONS
        END
 **/

int isOperator(char input){
	int i = 0;
	char options[5] = {'+', '-', '*', '/', ')'};
	for (i = 0; i < 5; i++) {
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
	case ')':
		return 4;
	default:
		return -1;
	}
}

int rpnCollect(char *infix, char *postfix){
	int i=0;
	char * aft;
	Queue *q = NULL;
	QueueC *oq = NULL;
	printf("Colecting infix -> %s to postfix\n", infix );

	while ( i < strlen(infix)) {
		if(isDigit(infix[i])) {
			queue(&q, strtod(&infix[i], &aft));
			i = (aft - infix);
			continue;
		}else if(isOperator(infix[i])) {
			queueC(&oq, (char)infix[i]);
		}
		i++;
	}
	rpnConvert(&q, &oq);
	return 0;
}
/**
   TODO ALGORITMO PARA dequeue
 */
int rpnConvert(Queue **digits, QueueC **operators){
	char postfix[256];
	char c = 'a', ant = 'a';
	double val1, val2;
	postfix[0] = '\0';
	dequeueC(operators, &ant);
	while (dequeueC(operators, &c)) {
		if(operatorPriority(ant) >= operatorPriority(c)) {

		}else{

		}
		ant = c;
	}
	return 0;
}

void insertSpaceRpnPostfix(char *postfix){
	postfix[strlen(postfix)+1] = ' ';
	postfix[strlen(postfix)+2] = '\0';
}
/**
 * Concat Double values on string
 */
void concatRpnPostfix(char *postfix, double val){
	char *stringVal = malloc(4);
	sprintf(stringVal,"%f",val);
	strcat(postfix, " ");
	strcat(postfix, stringVal);
	strcat(postfix, " ");
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
