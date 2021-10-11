#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DA_DEF(TYPE) \
typedef struct _opt { \
        TYPE *arr; \
        size_t capacity; \
        size_t size; \
		char type[10];\
}opt; \
void init(opt *res, char *type) { \
	res->capacity = 2;\
	res->size = 0;\
	res->arr = (TYPE*)malloc(sizeof(TYPE)*res->capacity);\
	strcpy(res->type, type);\
}\
void add(opt * res, TYPE value) {\
	if(!(strcmp(res->type, "string")==0)) {\
		if(res->size >= res->capacity) {\
			res->capacity *= 2;\
			res->arr = (TYPE*)realloc(res->arr, sizeof(TYPE)*res->capacity);\
			memcpy(res->arr+res->size, &value, sizeof(TYPE));\
			res->size++;\
		} else {\
			memcpy(res->arr+res->size, &value, sizeof(TYPE));\
			res->size++;\
		}\
	}\
}\
static int arrayIsEmpty(opt *res) {\
	return (res->size == 0);\
}\
void dell(opt *res) {\
	if(arrayIsEmpty(res)) {\
		printf("Array is empty.\n");\
	}else {\
		res->arr[--res->size];\
	}\
}

DA_DEF(int);

int main() {
	srand((unsigned)time(NULL));
	opt *x = (opt*)malloc(sizeof(opt));
	init(x, "char");

	size_t i,j;
	for(i=97;i<=122;i++) {
	/* < for char* >
		char *str = (char*)malloc(sizeof(char)*5);
		for(j=0;j<5;j++)
			str[j] = rand()%(122-97+1)+97;
		printf("%s\n", str);
	*/

		add(x, i);
		//free(str); <for char* >
	}

	for(size_t i=0;i<x->size;i++)
		printf("%zu: %d\n",i, x->arr[i]);

	free(x->arr);
	free(x);

	return 0;
}
