//TODO
//
//TODO


/**
   *@author Jonatan Souza
 */
#include "index.h"

#define MAX_WORD_SIZE 17;

//global variables
char TEXT[TEXT_SIZE];
Idx* ROOT = NULL;

struct index {
	char key[17];
	int *value;
	int n;
	struct index* next;
	struct index* list;
};

//AUXILIAR FUNCTIONS
static int hash(const char *key);
int getKeyWordsFromFile(const char* keys, const char* text, Index **idx);
Idx* checkOccurrencesOnText(const char *key, FILE *fp);
int validateSearch(int n, char* text);
int setLowerCase(int c);
void pushLinkedList(Idx* list, Idx* node);
void colisionHandler(Idx* list, Idx* node);

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
	int i;
	char k[17];

	if(strlen(key) > 17) {
		printf("A palavra %s possui mais de 16 chars\n", key);
		return 1;
	}

	for(i=0; i<=strlen(key); i++ )
		k[i] = setLowerCase(key[i]);

	int addr = hash(k);
	Idx *node = (*idx)[addr];
	if(node == NULL) {
		return 1;
	}else{
		do {
			if (!strcmp(node->key, k)) {
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
	int i;
	char k[17];

	if(strlen(key) > 17) {
		printf("A palavra %s possui mais de 16 chars\n", key);
		return 1;
	}

	for(i=0; i<=strlen(key); i++ )
		k[i] = setLowerCase(key[i]);


	int addr = hash(k);
	FILE *fp;
	fp = fopen (TEXT,"r");
	if (fp==NULL)
	{
		return 1;
	}
	node = checkOccurrencesOnText(k, fp);
	if(node == NULL) {
		printf("nenhuma ocorrencia de %s no texto\n", key);
	}else{
		pushLinkedList(ROOT, node);
		if((*idx)[addr] == NULL) {
			(*idx)[addr] = node;
		}else{
			colisionHandler((*idx)[addr], node);
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

		printf("%d.\n", tmp->value[tmp->n-1]);
		tmp = tmp->list;
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

	while ((c = setLowerCase(fgetc(fk))) != EOF) {
		if (c == '\n') {
			str[wordSizeControl] = '\0';
			wordSizeControl = 0;
			node = checkOccurrencesOnText(str, ft);
			if(node == NULL) {
				printf("nenhuma ocorrencia no texto da chave\n");
			}else{

				if(ROOT == NULL) {
					ROOT = node;
					ROOT->list = NULL;
				}else{
					pushLinkedList(ROOT, node);
				}

				if((**idx)[hash(str)] == NULL) {
					(**idx)[hash(str)] = node;
				}else{
					colisionHandler((**idx)[hash(str)], node);
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
	Idx* current = list;
	while(current != NULL) {
		if(!strcmp(node->key, current->key)) {
			printf("A palavra ja existe no indice, as informações estão sendo atualizadas\n");
			return;
		}
		current = current->list;
	}
	current = list;
	if(strcmp(node->key, list->key) < strcmp(list->key, node->key)) {
		ROOT = node;
		node->list = list;

	} else{
		current = list;
		do {
			current = list;
			if(current->list == NULL) {
				current->list = node;
				break;
			}
			list = list->list;
			if(strcmp(node->key, list->key) < strcmp(list->key, node->key)) {
				current->list = node;
				node->list=list;
				break;
			}
		} while(list != NULL);
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
	char text[MAX_TEXT_BUFFER];
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
		node->list = NULL;
		rewind(fp);
		return node;
	}
	rewind(fp);
	return NULL;
}

void colisionHandler(Idx* list, Idx* node){
	while(list->next != NULL) {
		if(!strcmp(list->key, node->key)) {
			list->value = node->value;
			list->n = node->n;
			return;
		}
		list = list->next;
	}
	if(!strcmp(list->key, node->key)) {
		list->value = node->value;
		return;
	}
	list->next = node;
}
