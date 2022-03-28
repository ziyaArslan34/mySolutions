#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dynamic_array.h"

struct test { int x,y; };

void print(const void *val) {
	struct test tmp = *(struct test*)val;

	printf("[%d][%d] ", tmp.x, tmp.y);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int f(const void* a, const void* b) {
	return ((struct test*)a)->x < ((struct test*)b)->x;
}

int main() {
	srand((unsigned)time(NULL));

	dynamicArray_t array = init(sizeof(struct test), 10);

	for(int i=0;i<15;i++) {
		struct test t = {my_rand(0,100), my_rand(0,100)};
		add_element(&array, &t);
	}

	sort_array(&array, f);
	print_array(&array, print);

	struct test del;

	printf("\nsil: ");
	scanf("%d%d", &del.x, &del.y);

	del_element(&array, &del);
	print_array(&array,print);
	destroy(&array);
}
