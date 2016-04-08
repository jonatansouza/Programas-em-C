#ifndef _List
#define _List
#include <stdlib.h>
#include <stdio.h>

struct list{
	int val;
	struct list *next;
};

typedef struct list List;

//functions
List* create_list();
List* destroy_list(List *l);//TODO
List* insert_item(List *l, int val);	
List* remove_item(List *l);
void print_list(List *l);

#endif
