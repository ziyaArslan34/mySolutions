#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

hash_t init_hash() {
	hash_t hash;

	hash.size = 0;
	hash.cap = 16;
	hash.key = my_rand(2,9);

	hash.data = (int*)malloc(sizeof(int)*hash.cap);
	return hash;
}

array_t init_array(size_t capacity) {
	array_t array;
	array.size = 0;
	array.cap = capacity;

	array.data = (int*)malloc(sizeof(int)*array.cap);
	return array;
}

void push_back_array(array_t *arr, int val) {
	if(arr->size >= arr->cap) {
		arr->cap *= 2;
		arr->data = (int*)realloc(arr->data, sizeof(int)*arr->cap);
	}

	arr->data[arr->size++] = val;
}

void push_back_hash(hash_t *hash, int val) {
	if(hash->size >= hash->cap) {
		hash->cap *= 2;
		hash->data = (int*)realloc(hash->data, sizeof(int)*hash->cap);
	}
	hash->data[hash->size++] = val;
}

void swap(void *val1, void *val2, size_t type) {
	void *temp = malloc(type);
	memcpy(temp, val1, type);
	memcpy(val1, val2, type);
	memcpy(val2, temp, type);
}

void reverse_array(int *array, size_t size) {
	if(size < 2)
		return;

	for(int i=0, j=(int)size-1;i<(int)size && j >= 0;j--, i++)
		swap(&array[i], &array[j], sizeof(int));
}

void encrypt(hash_t *hash, const char *value) {
	for(size_t i=0;i<strlen(value);i++) {
		int num = (int)value[i];
		array_t array = init_array(5);

		while(num) {
			push_back_array(&array, num%10+hash->key);
			num /= 10;
		}

		reverse_array(array.data, array.size);

		for(size_t idx=0;idx<array.size;idx++)
			push_back_hash(hash, array.data[idx]);

		push_back_hash(hash, -1);
		destroy_array(&array);
	}
}

char* decrypt(const hash_t *hash) {
	size_t index=0, cap=4;
	int *nums = (int*)malloc(sizeof(int)*cap);

	int steps[] = {0,1,10,100,1000,10000,100000,1000000};

	for(size_t i=0;i<hash->size;) {
		int count=0, step;
		size_t j;
		for(j=i;hash->data[i++] != -1;j++)
			count++;

		step = steps[count];

		int num = 0;
		for(int m=(int)j-1;hash->data[m] != -1;m--) {
			num += (hash->data[m]-hash->key)*step;
			step /= 10;
		}

		if(index >= cap) {
			cap *= 2;
			nums = (int*)realloc(nums, sizeof(int)*cap);
		}

		nums[index++] = num;
	}

	char *str = (char*)malloc(sizeof(char)*index+1);

	for(size_t i=0;i<index;i++)
		str[i] = (char)nums[i];

	str[index++] = '\0';
	free(nums);

	return str;
}

void print_hash(const hash_t *hash) {
	for(size_t i=0;i<hash->size;i++)
		printf(" [%d] ", hash->data[i]);
	printf("\n");
}

void destroy_hash(hash_t *hash) {
	free(hash->data);
}

void destroy_array(array_t *array) {
	free(array->data);
}
