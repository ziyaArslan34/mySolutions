#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

void print(const void *data) {
	printf("%d ", *(int*)data);
}

int cmp(const void *a, const void *b) {
	return (*(int*)a > *(int*)b);
}

int main() {
	srand((unsigned)time(NULL));

	int x = 1;

	linkedList *root = init_root(&x, sizeof(int));

	for(int i=100;i<115;i++) {
		int val = (int)rand()%(100-10+1)+10;
		printf("%d\n", val);

		add_to_sort(&root, &val, cmp);
	}

	print_list(&root, print);
	destroy_list(&root);
}
