#include "rpn-utils.h"


/**
        AUXILIAR FUNCTIONS

 **/

double rpnResolve(double x1, double x2, char op);
void concatRpnPostfix(char *postfix, double val);
void insertSpaceRpnPostfix(char *postfix);
int rpnConvert(Queue **digits, QueueC **operators, char *postfix);

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
		return 0;
	case ')':
		return 0;
	case '(':
		return 3;

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
			if(infix[i] == 's' && infix[i+3] != 't') {
				printf("Bad operator! Use \'sqrt\'\n");
				return 1;
			}
			queueC(&oq, (char)infix[i]);
		}
		i++;
	}
	queueC(&oq, '#');
	rpnConvert(&q, &oq, postfix);
	return 0;
}
int rpnConvert(Queue **digits, QueueC **operators, char *postfix){
	char c = 'a', ant = 'a';
	char ops[10];
	int opCount=1, i=0, waiting = 0;
	double val;
	dequeueC(operators, &ant);
	while (dequeueC(operators, &c)) {
		if(operatorPriority(ant) >= operatorPriority(c)) {
			if(ant != ')' && ant != '(' ) {
				for(i=0; i<=opCount; i++) {
					dequeue(digits, &val);
					printf("%5.2f\n", val);
				}
				if(ant != ')' && ant != '(')
					printf("%c\n", ant);
				if(waiting) {
					for(i=waiting-1; i>=0; i--)
						printf("%c\n", ops[i]);
				}
				waiting = 0;
				opCount = 0;
			}
		}else{
			if(ant != ')' && ant != '(' ) {
				if (ant != 's') {
					opCount++;
				}
				ops[waiting++] = ant;
			}
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
	char *stringVal = malloc(sizeof(char) * 6);
	sprintf(stringVal,"%5.2f",val);
	strcat(postfix, " ");
	strcat(postfix, stringVal);
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