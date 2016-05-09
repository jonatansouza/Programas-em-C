/**
   *@author Jonatan Souza
 */

#include "index.h"

#define MAX_WORD_SIZE 17;

struct index {
        char key;
        char value[17];
        struct index* next;
};



//AUXILIAR FUNCTIONS
static int hash(int key);
//AUXILIAR FUNCTIONS


int index_createfrom(const char *key_file, const char *text_file, Index **idx){
        int lines = 0;
        int wordSizeControl = 0;
        char test[17];
        int c = 0;
        FILE* fp;
        fp = fopen("keys","rt");
        if (fp == NULL) {
                fprintf(stderr, "Erro na abertura do arquivo!\n");
                return 1;
        }

        while ((c = fgetc(fp)) != EOF) {
                if(c == '\n') {
                        lines++;
                        test[wordSizeControl] = '\0';
                        break;
                }else{
                        test[wordSizeControl++] = c;
                }
        }

        fclose(fp);
        printf("%s\n", test);
        return 0;
}
int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences ){

        //TODO
        return 0;
}
int index_put( Index *idx, const char *key ){

        //TODO
        return 0;
}
int index_print( const Index *idx ){

        //TODO
        return 0;
}


//********************//
// AUXILIAR FUNCTIONS //
//********************//

static int hash(int key){
        return key % M;
}
