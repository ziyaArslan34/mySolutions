#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char **array;
	size_t size, cap;
}type_t;

type_t init() {
	type_t arr;
	arr.size = 0;
	arr.cap = 10;

	arr.array = (char**)malloc(sizeof(char*)*arr.cap);

	for(size_t i=0;i<arr.cap;i++)
		arr.array[i] = (char*)malloc(sizeof(char)*30);

	return arr;
}

int isAlpha(char ch) {
	return (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90);
}

type_t foo(const char *str) {
	type_t arr = init();

	size_t len = strlen(str);

	for(size_t i=0;i<len;) {
		char tmp[30];
		size_t idx=0;

		for(size_t j=i;isAlpha(str[i++]) && j < len;j++)
			tmp[idx++] = str[j];

		tmp[idx++] = '\0';

		if(arr.size >= arr.cap) {
			arr.cap *= 2;
			arr.array = (char**)realloc(arr.array, sizeof(char**)*arr.cap);

			for(size_t m=arr.cap/2;m<arr.cap;m++)
				arr.array[m] = (char*)malloc(sizeof(char)*30);
		}

		strcpy(arr.array[arr.size++], tmp);
	}

	return arr;
}

void destroy(type_t *type) {
	for(size_t i=0;i<type->size;i++) {
		type->array[i] = NULL;
		free(type->array[i]);
	}

	free(type->array);
}

int main() {
	type_t val = foo("exprone2exprtwo3exprthree.exprfour=exprfive+exprsix&exprseven(expreight>");


	printf("size: %zu\n", val.size);

	for(size_t i=0;i<val.size;i++)
		printf("%s\n", val.array[i]);

	destroy(&val);
}
