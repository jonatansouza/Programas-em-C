/**
*@author Jonatan Souza
*/

#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int validatorSentence(char *sentence);
int decodeNumber(int c);
int isNumber(int c);
int isOperator(int c);
int isBracket(int c);


#endif /* VALIDATOR_H_ */