/**
*@author Jonatan Souza
*/
#ifndef _RpnUtils
#define _RpnUtils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"




int rpnCalc(char *input, double *result);
int rpnParse(char *infix, char *postfix);
int rpnPrint(char * rpnString);

#endif
