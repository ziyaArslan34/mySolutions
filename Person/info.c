#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

type_t init(size_t defaultCap) {
	type_t arr;

	arr.cap = defaultCap;

	if(defaultCap <= 0)
		arr.cap = 10;

	arr.size = 0;
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

void splitStr(type_t *type, const char *str, const char *expr) {
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
			push_back(type, tmp);
		}
		free(tmp);
	}
}

void push_back(type_t *type, const char *str) {
	if(type->size >= type->cap) {
		type->cap *= 2;
		type->array = (char**)realloc(type->array, sizeof(char*)*type->cap);
	}

	size_t sLen = strlen(str);
	type->array[type->size] = (char*)malloc(sizeof(char)*sLen+1);
	strcpy(type->array[type->size++], str);
}

void printArray(const type_t *type) {
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
