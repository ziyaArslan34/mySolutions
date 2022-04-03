#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dynamic_array.h"

void print(const void *val) {
	printf("%s ", (char*)val);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int cmp(const void* a, const void* b) {
	return strcmp((const char*)a, (const char*)b);
}

int main() {
	srand((unsigned)time(NULL));

	dynamicArray_t array = init_array(4, 10);

	const char *str[] = {"bir", "iki", "uc1", "dor", "bes", NULL};

	for(int i=0;str[i] != NULL;i++) {
		add_element(&array, str[i]);
	}

	sort_array(&array, cmp);
	print_array(&array, print);

	char s[10];

	printf("\nsil: ");
	scanf("%s", s);

	print_array(del_element(&array, s), print);

	destroy_array(&array);
}
