#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 10

int comp(const void *val1, const void *val2) {
	const char* val1_ = (const char*)val1;
	const char* val2_ = (const char*)val2;
	return strcmp(val1_, val2_);
}

void print(const char str[][STRSIZE], const size_t size) {
	printf("\n");
	for(size_t i=0;i<size;i++)
		printf("%s\n", str[i]);
	printf("\n");
}

int main() {
	char str[10][STRSIZE] = {
		"bir","iki", "uc", "dort", "bes",
		"alti", "yedi", "sekiz", "dokuz", "on"
	};

	print(str, 10);

	qsort(str, 10, STRSIZE, comp);

	print(str, 10);
}
