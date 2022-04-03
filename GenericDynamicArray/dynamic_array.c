#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

void debug_function(int val) { printf("debug: %d\n", val); }

dynamicArray_t init_array(size_t typeSize, size_t capacity) {
	dynamicArray_t array;

	array.size = 0;
	array.cap = capacity;
	array.typeSize = typeSize;

	if((array.data = malloc(typeSize*capacity)) == NULL) {
		perror("");
		exit(1);
	}

	return array;
}

size_t search_element(const dynamicArray_t *array, const void *src) {
	if(!array)
		return array->size;

	for(size_t i=0;i<array->size;i++)
		if(memcmp((char*)array->data+i*array->typeSize, src, array->typeSize) == 0)
			return i;
	return array->size;
}

int empty(const dynamicArray_t *array) {
	return array->size == 0;
}

dynamicArray_t* add_element(dynamicArray_t *array, const void *src) {
	if(!array)
		return array;

	if(array->size >= array->cap) {
		array->cap *= 2;
		if((array->data = realloc(array->data, array->typeSize*array->cap)) == NULL) {
			perror("");
			exit(1);
		}
	}

	memcpy((char*)array->data+array->size*array->typeSize, src, array->typeSize);
	array->size++;

	return array;
}

dynamicArray_t* insert_element(dynamicArray_t *array, size_t idx, const void *src) {
	if(idx >= array->size) {
		fprintf(stderr, "invalid index\n");
		return array;
	}

	(void)src;

	return array;
}

dynamicArray_t* del_element(dynamicArray_t *array, const void *src) {
	if(empty(array)) {
		fprintf(stderr, "array is empty\n");
		return array;
	}


	size_t find = search_element(array, src);

	if(find == array->size) {
		fprintf(stderr, "element not found..!\n");
		return array;
	}

	restore_array(array, find);
	--array->size;

	return array;
}

void *get_index_element(const dynamicArray_t *array, size_t idx) {
	if(empty(array) || idx >= array->size)
		return NULL;
	return (char*)array->data+idx*array->typeSize;
}

void print_array(const dynamicArray_t *array, void (*fptr)(const void*)) {
	if(empty(array))
		return;

	printf("\n");
	for(size_t i=0;i<array->size;i++)
		fptr((char*)array->data+i*array->typeSize);
	printf("\n");
}

void sort_array(dynamicArray_t *array, int (*comp)(const void*, const void*)) {
	if(empty(array))
		return;

	for(size_t i=0;i<array->size;i++) {
		for(size_t j=0;j<array->size;j++) {
			if(comp((char*)array->data+i*array->typeSize, (char*)array->data+j*array->typeSize)) {
				void *tmp;
				if((tmp = malloc(array->typeSize)) == NULL) {
					perror("");
					destroy_array(array);
					exit(1);
				}

				memcpy(tmp, (char*)array->data+i*array->typeSize, array->typeSize);
				memcpy((char*)array->data+i*array->typeSize, (char*)array->data+j*array->typeSize, array->typeSize);
				memcpy((char*)array->data+j*array->typeSize, tmp, array->typeSize);
				free(tmp);
			}
		}
	}
}

void restore_array(dynamicArray_t *array, size_t cnt) {
	if(empty(array))
		return;

	for(size_t i=0;i<cnt+1;i++) {
		void *tmp;
		if((tmp = malloc(array->typeSize)) == NULL) {
			perror("");
			destroy_array(array);
			exit(1);
		}

		memcpy(tmp, (char*)array->data+0*array->typeSize, array->typeSize);
		for(size_t j=0;j<array->size-1;j++)
			memcpy((char*)array->data+j*array->typeSize, (char*)array->data+(j+1)*array->typeSize, array->typeSize);
		memcpy((char*)array->data+(array->size-1)*array->typeSize, tmp, array->typeSize);
	}
}

static void swap(void *a, void *b, size_t type) {
	void *tmp;
	if((tmp = malloc(type)) == NULL) {
		perror("");
		exit(1);
	}

	memcpy(tmp, a, type);
	memcpy(a, b, type);
	memcpy(b, tmp, type);
	free(tmp);
}

void reverse_array(dynamicArray_t *array) {
	for(size_t i=0, j=array->size-1;i<array->size/2;i++, j--)
		swap(get_index_element(array, i), get_index_element(array, j), array->typeSize);
}

void destroy_array(dynamicArray_t *array) {
	array->size = 0;
	array->cap = 0;
	array->typeSize = 0;

	free(array->data);
	array->data = NULL;
}
