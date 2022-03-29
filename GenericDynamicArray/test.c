#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "dynamic_array.h"

int comp(const void *a, const void *b) {
	return strcmp((const char*)a, (const char*)b) < 0;
}

void print(const void *val) {
	printf("%s ", (char*)val);
}

int main() {
	srand((unsigned)time(NULL));

	dynamicArray_t array = init(5, 10);

	const char *str[] = {"abcd", "absh", "bdnd", "jsjj", NULL};

	for(size_t i=0;str[i] != NULL;i++) {
		add_element(&array, str[i]);
	}

	sort_array(&array, comp);
	print_array(&array, print);

	destroy(&array);
}
