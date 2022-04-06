#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dynamic_array.h"

void print(const void *val) {
	printf("%d ", *(int*)val);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int cmp(const void* a, const void* b) {
	return *(int*)a < *(int*)b;
}

int main() {
	srand((unsigned)time(NULL));

	dynamicArray_t array = init_array(sizeof(int), 10);

	for(int i=100;i<115;i++) {
		int val = my_rand(10, 100);
		add_element(&array, &val);
	}

	print_array(&array, print);
	sort_array(&array, cmp);
	print_array(&array, print);

	destroy_array(&array);
}
