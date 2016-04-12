#include "list.h"

int main(int argc, char *argv[]){
	List *l = create_list();
	insert_item(l, 10);
	insert_item(l, 20);
	insert_item(l, 70);
	insert_item(l, 40);
	insert_item(l, 50);
	print_list(l);
	return 0;
}
