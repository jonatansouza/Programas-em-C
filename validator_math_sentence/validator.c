#include "validator.h"


int validatorSentence(char *sentence){
    char a;
    int i = 0;
    int openBrackets = 0;
    int closedBrackets = 0;
    int operator = 0;
    a = sentence[i++];  
    while(a != '\0'){
        if(!isNumber(a) && !isOperator(a) && !isBracket(a)){
            printf("invalid chars\n");
            return 0;
        }else if(isOperator(a)){
            if(operator){
                printf("invalid input operators %c\n", a);
                return 0;
            }
            operator++;
        } else if(isNumber(a)){
            operator = 0;
        }else if(isBracket(a)){
            operator = 0;
            if(a == ASC_OPEN_BRACKET){
                openBrackets++;
            }else{
                closedBrackets++;
            }
            if(closedBrackets > openBrackets){
                printf("invalid Brackets\n");
                return 0;
            }
        }
        a = sentence[i++];
    }
    if(openBrackets != closedBrackets){
        printf("invalid Bracket without match\n");
        return 0;
    }else if(operator){
        printf("invalid input operator end of input\n");
        return 0;
    }
    return 1;
}


int decodeNumber(int c){
    if(c > ASC_DIVIDED && c < ASC_COLON){
        return (c-ASC_DEFAULT);
    }else{
        return -1;
    }
}

int isNumber(int c){
    if(c > ASC_DIVIDED && c < ASC_COLON){
        return c;
    }
    return 0;
}

int isOperator(int c){
    if(c == ASC_TIMES || c == ASC_PLUS || c == ASC_MINUS || c == ASC_DIVIDED){
        return c;
    }
    return 0;
}

int isBracket(int c){
    if(c == ASC_OPEN_BRACKET || c == ASC_CLOSED_BRACKET){
            return c;    
    }
    return 0;
}