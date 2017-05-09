/**
*@author Jonatan Souza
*/

#ifndef _RpnUtils
#define _RpnUtils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


int isOperator(char input);
int isDigit(char input);
int rpnDecode(char *input);
int isUnary(char input);


#endif
