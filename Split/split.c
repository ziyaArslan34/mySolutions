#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

split_t init_split(size_t defaultSize) {
	split_t arr;
	arr.size = 0;
	arr.cap = defaultSize;

	if((arr.array = (char**)malloc(sizeof(char*)*arr.cap)) == NULL) {
		perror("");
		exit(1);
	}

	return arr;
}

int is_alpha(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int expr_find(const char *expr, char ch) {
	for(size_t i=0;i<strlen(expr);i++)
		if(expr[i] == ch)
			return 1;
	return 0;
}

int search_split(const split_t *type, const char *src) {
	for(size_t i=0;i<type->size;i++)
		if(!strcmp(type->array[i], src))
			return 1;
	return 0;
}

void push_back_split(split_t *type, const char *src) {
	size_t len = strlen(src)+1;

	if(type->size >= type->cap) {
		type->cap *= 2;
		if((type->array = (char**)realloc(type->array, sizeof(char*)*type->cap)) == NULL) {
			perror("");
			free(type->array);
			exit(1);
		}
	}

	if((type->array[type->size] = (char*)malloc(sizeof(char)*len)) == NULL) {
		perror("");
		free(type->array[type->size]);
		free(type->array);
		exit(1);
	}
	strcpy(type->array[type->size++], src);
}

split_t* str_split(split_t *arr, const char *str, const char *expr) {
	size_t len = strlen(str);

	for(size_t i=0;i<len;) {
		size_t idx=0, cap=50;
		char *tmp;
		if((tmp = (char*)malloc(sizeof(char)*cap)) == NULL) {
			perror("");
			destroy_split(arr);
			exit(1);
		}

		for(size_t j=i; (expr == NULL ? is_alpha(str[i++]) : !expr_find(expr, str[i++])) && j < len;j++) {
			if(idx >= cap) {
				cap *= 2;
				if((tmp = (char*)realloc(tmp, sizeof(char)*cap)) == NULL) {
					perror("");
					destroy_split(arr);
					exit(1);
				}
			}
			tmp[idx++] = str[j];
		}

		tmp[idx++] = '\0';

		if(idx-1) {
			push_back_split(arr, tmp);
		}
		free(tmp);
	}

	return arr;
}

void print_split(const split_t *type) {
	printf("\n\n");

	for(size_t i=0;i<type->size;i++)
		printf(" < %s > ", type->array[i]);

	printf("\n\n");
}

void destroy_split(split_t *type) {
	for(size_t i=0;i<type->size;i++) {
		free(type->array[i]);
		type->array[i] = NULL;
	}

	free(type->array);
	type->array = NULL;
}
