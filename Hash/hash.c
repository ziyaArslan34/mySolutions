#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"
#include "../GenericDynamicArray/dynamic_array.h"

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

hash_t init_hash() {
	hash_t hash;

	hash.size = 0;
	hash.cap = 16;
	hash.key = my_rand(2,9);

	if((hash.data = (int*)malloc(sizeof(int)*hash.cap)) == NULL) {
		perror("");
		exit(1);
	}

	return hash;
}

void push_back_hash(hash_t *hash, int val) {
	if(hash->size >= hash->cap) {
		hash->cap *= 2;
		if((hash->data = (int*)realloc(hash->data, sizeof(int)*hash->cap)) == NULL) {
			perror("");
			free(hash->data);
			exit(1);
		}
	}
	hash->data[hash->size++] = val;
}

int comp_hash(const hash_t *h1, const hash_t *h2) {
	size_t size1 = h1->size;
	size_t size2 = h2->size;

	if(size1 != size2)
		return 0;

	for(size_t i=0;i<size1;i++)
		if(h1->data[i] != h2->data[i])
			return 0;
	return 1;
}

void encrypt(hash_t *hash, const char *value) {
	for(size_t i=0;i<strlen(value);i++) {
		int num = (int)value[i];
		dynamicArray_t array = init_array(sizeof(int), 5);

		while(num) {
			int step = num%10+hash->key;
			add_element(&array, &step);
			num /= 10;
		}

		for(size_t idx=0;idx<array.size;idx++) {
			int val = *(int*)get_index_element(&array, idx);
			push_back_hash(hash, val);
		}

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
		printf("%d", hash->data[i]);
	printf("\n");
}

void destroy_hash(hash_t *hash) {
	free(hash->data);
	hash->data = NULL;
}
