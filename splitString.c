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

	return arr;
}

int isAlpha(char ch) {
	return (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90);
}

int exprFind(const char *expr, char ch) {
	for(size_t i=0;i<strlen(expr);i++)
		if(expr[i] == ch)
			return 1;
	return 0;
}

int search(const type_t *type, const char *src) {
	for(size_t i=0;i<type->size;i++)
		if(!strcmp(type->array[i], src))
			return 1;
	return 0;
}

void push_back(type_t *type, const char *src) {
	size_t len = strlen(src)+1;

	if(type->size >= type->cap) {
		type->cap *= 2;
		type->array = (char**)realloc(type->array, sizeof(char*)*type->cap);
	}

	type->array[type->size] = (char*)malloc(sizeof(char)*len);
	strcpy(type->array[type->size++], src);
}

type_t foo(const char *str, const char *expr) {
	type_t arr = init();

	size_t len = strlen(str);

	for(size_t i=0;i<len;) {
		size_t idx=0, cap=50;
		char *tmp = (char*)malloc(sizeof(char)*cap);

		for(size_t j=i; (expr == NULL ? isAlpha(str[i++]) : !exprFind(expr, str[i++])) && j < len;j++) {
			if(idx >= cap) {
				cap *= 2;
				tmp = (char*)realloc(tmp, sizeof(char)*cap);
			}
			tmp[idx++] = str[j];
		}

		tmp[idx++] = '\0';

		if(idx-1) {
			push_back(&arr, tmp);
		}
		free(tmp);
	}

	return arr;
}

void printExpr(type_t *type) {
	printf("\nsize : %zu\n", type->size);
	for(size_t i=0;i<type->size;i++)
		printf("%s ", type->array[i]);
	printf("\n\n");
}


void destroy(type_t *type) {
	for(size_t i=0;i<type->size;i++) {
		type->array[i] = NULL;
		free(type->array[i]);
	}

	type->array = NULL;
	free(type->array);
}

int main() {
	type_t val1 = foo("_exprone22a222exprtwo3exprthree....exprfour=exprfive+exprsix&exprseven(expreight>exprnine[exprten]expreleven-exprtwerty", NULL);
	type_t val2 = foo("bir/iki/uc/pazartesi", "/");
	type_t val3 = foo("pazartesi&sali+carsamba]persembe-cuma<cumartesi", "<-&+]");


	printExpr(&val1);
	printExpr(&val2);
	printExpr(&val3);


	if(search(&val1, "idickc")) {
		printf("bulundu\n");
	}

	destroy(&val1);
	destroy(&val2);
	destroy(&val3);
}
