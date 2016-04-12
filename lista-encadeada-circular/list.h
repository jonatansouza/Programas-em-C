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
int insert_item(List *l, int val);	
void print_list(List *l);

#endif
