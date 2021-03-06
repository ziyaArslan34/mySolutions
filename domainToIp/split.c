#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

type_t init(size_t defaultSize) {
	type_t arr;
	arr.size = 0;
	arr.cap = defaultSize;

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

const char * returnIp(const type_t* type) {
	for(size_t i=0;i<type->size;i++) {
		size_t len = strlen(type->array[i])-1;

		if((type->array[i][0] >= 48 && type->array[i][0] <= 57)
			&& (type->array[i][len] >= 48 && type->array[i][len] <= 57))
			return type->array[i];
	}

	return NULL;
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

type_t createWord(const char *str, const char *expr) {
	type_t arr = init(10);

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
