/**
   *@author Jonatan Souza
 */

#include "index.h"

#define MAX_WORD_SIZE 17;

struct index {
        char key[17];
        int *value;
        struct index* next;
};



//AUXILIAR FUNCTIONS
static int hash(const char *key);
int getKeyWordsFromFile(const char* keys, const char* text, Index **idx);
//AUXILIAR FUNCTIONS


int index_createfrom(const char *key_file, const char *text_file, Index **idx){
        (*idx) = malloc(sizeof(Index));
        if((*idx) == NULL)
                return 1;
        getKeyWordsFromFile(key_file, text_file, idx);

        /*int lines = 0;
           int wordSizeControl = 0;
           char test[17];
           int c = 0;
           printf("%s\n", test);*/
        return 0;
}
int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences ){
        return 0;
}
int index_put( Index *idx, const char *key ){
        int address = hash(key);
        if(idx[address] == NULL){
            /*idx[address] = malloc(sizeof(Idx));
            if(idx[address] == NULL){
                fprintf( stderr, "Erro: ao alocar memoria\n" );
                return 1;
            }*/
        }
        return 0;
}
int index_print( const Index *idx ){

        //TODO
        return 0;
}


//********************//
// AUXILIAR FUNCTIONS //
//********************//

static int hash(const char *key){
        unsigned int hash = 5183;
        int c;
        while (c = *key++)
                hash = ((hash << 5) + hash) + c;
        return hash % M;
}

int getKeyWordsFromFile(const char* keys, const char* text, Index **idx){
        FILE *fp;
        char str[17];
        int c, wordSizeControl = 0;
        fp = fopen(keys, "r");
        if(fp == NULL) {
                printf("Erro ao abrir o arquivo\n");
        }
        while ((c = fgetc(fp)) != EOF) {
                if (c == '\n') {
                        str[wordSizeControl] = '\0';
                        wordSizeControl = 0;
                        printf("%s\n", str);
                } if(wordSizeControl < 16) {
                        str[wordSizeControl++] = c;
                }
        }
        fclose(fp);
        return 0;
}
