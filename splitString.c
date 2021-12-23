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

static int isAlpha(char ch) {
	return (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90);
}

int exprFind(const char *expr, char ch) {
	for(size_t i=0;i<strlen(expr);i++)
		if(expr[i] == ch)
			return 1;
	return 0;
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

		if(arr.size >= arr.cap) {
			arr.cap *= 2;
			arr.array = (char**)realloc(arr.array, sizeof(char**)*arr.cap);
		}

		if(idx-1) {
			size_t index;
			arr.array[arr.size] = (char*)malloc(sizeof(char)*idx);
			for(index=0;index<idx;index++)
				arr.array[arr.size][index] = tmp[index];
			arr.array[arr.size++][index++] = '\0';
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
	type_t val3 = foo("pazartesi&sali+carsamba]persembe-cuma<cumartesi", "-&+]");


	printExpr(&val1);
	printExpr(&val2);
	printExpr(&val3);


	destroy(&val1);
	destroy(&val2);
	destroy(&val3);
}
