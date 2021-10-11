#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void *data;
	size_t cap;
	size_t size;
	size_t type;
}GENERIC;

void destroy(GENERIC *array) {
	free(array->data);
	free(array);
}

int init(GENERIC *array, const size_t type) {
	array->size = 0;
	array->cap = 4;
	array->type = type;

	array->data = malloc(array->type*array->cap);

	return (array->data != NULL);
}

int addToEnd(GENERIC *array, const void *data) {
	char *src = (char*)malloc(sizeof(char)*array->type);
	memcpy(src, data, array->type);

	if(array->size >= array->cap) {
		array->cap *= 2;
		array->data = realloc(array->data, array->type*array->cap);
	}

	if(array->data == NULL)
		return 0;

	memcpy(array->data+array->size*array->type, src, array->type);
	array->size++;

	free(src);

	return 1;
}

int delToEnd(GENERIC *array) {
	array->size--;
	return 1;
}

void print(GENERIC *array) {
	printf("\n");

	int cnt=1;

	for(int i=0;i<array->size*array->type;i += array->type)
		printf("%d.  Data >> %s\n", cnt++, (char*)(array->data+i));

	printf("\n");
}

int main() {

	//test

	GENERIC *array = (GENERIC*)malloc(sizeof(GENERIC));

	char str[10];

	if(!init(array, sizeof(str))) {
		printf("memory error!\n");
		return -1;
	}

	for(int i=97;i<=122;i++) {
		int j;

		for(j=0;j<9;j++)
			str[j] = rand()%(122-97+1)+97;
		str[j] = '\0';
		if(!addToEnd(array, str))
			return -1;
	}

	print(array);
	for(int i=0;i<3;i++)
		delToEnd(array);

	print(array);

	destroy(array);

	return 0;
}
