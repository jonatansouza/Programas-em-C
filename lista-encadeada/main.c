#include "list.h"

int main(int argc, char *argv[]){
	List *l = create_list();
	l = insert_item(l, 10);
	l = insert_item(l, 20);
	l = insert_item(l, 30);
	l = insert_item(l, 40);
	l = insert_item(l, 50);
	l = insert_item(l, 60);
	l = insert_item(l, 70);
	l = remove_item(l);
	l = remove_item(l);
	l = remove_item(l);
	print_list(l);
	l = destroy_list(l);
	return 0;
}
