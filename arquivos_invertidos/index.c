/**
   *@author Jonatan Souza
 */

#include "index.h"

#define MAX_WORD_SIZE 17;

struct index {
        char key[17];
        int *value;
        int n;
        struct index* next;
};

typedef struct found {
        int *occurrences;
        int n;
}Found;



//AUXILIAR FUNCTIONS
static int hash(const char *key);
int getKeyWordsFromFile(const char* keys, const char* text, Index **idx);
Idx* checkOccurrencesOnText(const char *key, FILE *fp);
//AUXILIAR FUNCTIONS


int index_createfrom(const char *key_file, const char *text_file, Index **idx){
        (*idx) = malloc(sizeof(Index));
        if((*idx) == NULL)
                return 1;

        if (getKeyWordsFromFile(key_file, text_file, idx)) {
                return 1;
        }

        return 0;
}

int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences ){
        Idx *node = (*idx)[hash(key)];
        if(node == NULL) {
            return 1;
        }else{
            (*occurrences) = node->value;
            *num_occurrences = node->n;
        }

        return 0;
}
int index_put( Index *idx, const char *key ){
        int address = hash(key);
        if(idx[address] == NULL) {
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
        Idx* node;
        FILE *fk, *ft;
        char str[17];
        int c, wordSizeControl = 0;
        fk = fopen(keys, "r");
        if(fk == NULL) {
                printf("Erro ao abrir o arquivo de chaves\n");
                return 1;
        }
        ft = fopen(text, "r");
        if(ft == NULL) {
                printf("Erro ao abrir o arquivo de texto\n");
                return 1;
        }
        while ((c = fgetc(fk)) != EOF) {
                if (c == '\n') {
                        str[wordSizeControl] = '\0';
                        wordSizeControl = 0;
                        node = checkOccurrencesOnText(str, ft);
                        if(node == NULL) {
                                printf("nenhuma ocorrencia no texto da chave\n");
                        }else{
                                if((**idx)[hash(str)] == NULL) {
                                        (**idx)[hash(str)] = node;
                                }else{
                                        printf("tratar colisao de hash!\n");
                                }
                        }
                } else if(wordSizeControl < 16) {
                        str[wordSizeControl++] = c;
                }
        }
        fclose(ft);
        fclose(fk);
        return 0;
}

Idx* checkOccurrencesOnText(const char *key, FILE *fp){
        Idx *node;
        int *val = NULL;
        int c, line = 1, lineDelimiter = 0, occurrences = 0;
        char text[120];
        while ((c = fgetc(fp)) != EOF) {
                if(c == '\n') {
                        text[lineDelimiter] = '\0';
                        if(strstr(text, key) != NULL) {
                                if(val == NULL) {
                                        val = malloc(sizeof(int));
                                }else{
                                        if(realloc(val, (occurrences+1)*sizeof(int)) == NULL){
                                            printf("memoria cheia\n");
                                        }
                                }
                                val[occurrences] = line;
                                occurrences++;
                        }
                        lineDelimiter = 0;
                        line++;
                }else{
                        text[lineDelimiter++] = c;
                }
        }
        if(val != NULL) {
                node = malloc(sizeof(Idx));
                node->value = val;
                node->n = occurrences;
                strcpy(node->key, key);
                node->next=NULL;
        }
        rewind(fp);
        return node;
}
