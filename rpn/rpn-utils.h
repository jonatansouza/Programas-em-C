/**
*@author Jonatan Souza
*/

#ifndef _RpnUtils
#define _RpnUtils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"


int isOperator(char input);
int isDigit(char input);
int rpnDecode(char *input);
int isUnary(char input);
int rpnCollect(char *infix, char *postfix);
int operatorPriority(char operator);


#endif
