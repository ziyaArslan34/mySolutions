#include <stdio.h>

#include "linkedlist.h"

void print(const void *data) {
	printf("%d ", *(int*)data);
}

int main() {
	int val = 500;

	linkedList *root = init(&val, sizeof(int));

	for(int i=100;i<110;i++)
		add_to_end(&root, &i);

	print_list(&root, print);

	for(int i=0;i<5;i++)
		del_to_end(&root);
	print_list(&root, print);
	destroy(&root);
}
