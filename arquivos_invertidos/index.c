//TODO
//  colocar a lista pra imprimir em ordem alfabetica
//TODO


/**
   *@author Jonatan Souza
 */
#include "index.h"

#define MAX_WORD_SIZE 17;

//global variables
char TEXT[50];
Idx* ROOT = NULL;

struct index {
        char key[17];
        int *value;
        int n;
        struct index* next;
        struct index* listRight;
        struct index* listLeft;
};

//AUXILIAR FUNCTIONS
static int hash(const char *key);
int getKeyWordsFromFile(const char* keys, const char* text, Index **idx);
Idx* checkOccurrencesOnText(const char *key, FILE *fp);
int validateSearch(int n, char* text);
int setLowerCase(int c);
void pushLinkedList(Idx* list, Idx* node);

//AUXILIAR FUNCTIONS

int index_createfrom(const char *key_file, const char *text_file, Index **idx){
        int i;
        (*idx) = malloc(sizeof(Index));
        if((*idx) == NULL) {
                return 1;
        }
        if (getKeyWordsFromFile(key_file, text_file, idx)) {
                return 1;
        }

        return 0;
}

int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences ){
        int addr = hash(key);
        Idx *node = (*idx)[addr];
        if(node == NULL) {
                return 1;
        }else{
                do {
                        if (!strcmp(node->key, key)) {
                                (*occurrences) = node->value;
                                *num_occurrences = node->n;
                                return 0;
                        }
                        node = node->next;
                } while(node->next != NULL);
        }

        return 1;
}
int index_put( Index *idx, const char *key ){
        Idx* node;
        int addr = hash(key);
        FILE *fp;
        fp = fopen (TEXT,"r");
        if (fp==NULL)
        {
                return 1;
        }
        node = checkOccurrencesOnText(key, fp);
        if(node == NULL) {
                printf("nenhuma ocorrencia de %s no texto\n", key);
        }else{
                pushLinkedList(ROOT, node);
                if((*idx)[addr] == NULL) {
                        (*idx)[addr] = node;
                }else{
                        node->next = (*idx)[addr]->next;
                        (*idx)[addr]->next = node;
                }
        }
        fclose (fp);
        return 0;
}
int index_print( const Index *idx ){

        Idx *head = NULL, *list = NULL, *tmp = NULL;
        int i;
        tmp = ROOT;
        while(tmp != NULL) {
                char occurrences[tmp->n];
                printf("%s: ", tmp->key);
                for(i = 0; i < (tmp->n-1); i++)
                        printf("%d, ", tmp->value[i]);

                printf("%d\n", tmp->value[tmp->n-1]);
                tmp = tmp->listRight;
        }
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

        strcpy(TEXT, text);

        while ((c = fgetc(fk)) != EOF) {
                if (c == '\n') {
                        str[wordSizeControl] = '\0';
                        wordSizeControl = 0;
                        node = checkOccurrencesOnText(str, ft);
                        if(node == NULL) {
                                printf("nenhuma ocorrencia no texto da chave\n");
                        }else{

                                if(ROOT == NULL) {
                                        ROOT = node;
                                        ROOT->listLeft = NULL;
                                        ROOT->listRight = NULL;
                                }else{
                                        pushLinkedList(ROOT, node);
                                }

                                if((**idx)[hash(str)] == NULL) {
                                        (**idx)[hash(str)] = node;
                                }else{
                                        node->next = (**idx)[hash(str)]->next;
                                        (**idx)[hash(str)]->next = node;
                                }
                        }
                } else if(wordSizeControl < 16) {
                        str[wordSizeControl++] = setLowerCase(c);
                }
        }
        fclose(ft);
        fclose(fk);
        return 0;
}

void pushLinkedList(Idx* list, Idx* node){
        Idx* aux;
        while(list->listRight != NULL) {
                if(strcmp(node->key, list->key) < strcmp(list->key, node->key)) {
                        if (list->listLeft == NULL) {
                                ROOT = node;
                        }
                        aux = list->listLeft;
                        list->listLeft = node;
                        node->listRight = list;
                        if(aux != NULL) {
                                node->listLeft = aux;
                                aux->listRight = node;
                        }

                        return;
                }else if(strcmp(node->key, list->key) == strcmp(list->key, node->key)) {
                        return;
                }
                list= list->listRight;
        }

        if (list->listLeft == NULL) {
                ROOT = node;
        }
        aux = list->listLeft;
        list->listLeft = node;
        node->listRight = list;
        if(aux != NULL) {
                aux->listRight = node;
                node->listLeft = aux;
        }
}

int validateSearch(int n, char* text){
        if(text[-1] < 'A'  ||  text[-1] > 'z')
                if (text[n] < 'A'  ||  text[n] > 'z')
                        return 1;
        return 0;
}

int setLowerCase(int c){
        if ((c >= 'A') && (c <= 'Z'))
                c = c + 32;
        return c;
}

Idx* checkOccurrencesOnText(const char *key, FILE *fp){
        Idx *node;
        int *val = NULL;
        int c, line = 1, lineDelimiter = 0, occurrences = 0;
        char text[10000];
        char *position;
        while ((c = setLowerCase(fgetc(fp))) != EOF) {
                if(c == '\n') {
                        text[lineDelimiter] = '\0';
                        position = strstr(text, key);
                        if(position != NULL) {
                                if(validateSearch((int)strlen(key), position)) {
                                        if(val == NULL) {
                                                val = malloc(sizeof(int));
                                        }else{
                                                if(realloc(val, (occurrences+1)*sizeof(int)) == NULL) {
                                                        printf("memoria cheia\n");
                                                }
                                        }
                                        val[occurrences] = line;
                                        occurrences++;
                                }
                        }
                        position = NULL;
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
                node->listRight = NULL;
                node->listLeft = NULL;
                rewind(fp);
                return node;
        }
        rewind(fp);
        return NULL;
}
