#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct HASH {
	int *data;
	size_t cap;
	size_t size;
	size_t key;
};

struct ARRAY {
	struct HASH *data;
	size_t size;
	size_t cap;
};

typedef struct ARRAY array_t;
typedef struct HASH hash_t;


char*     decrypt(hash_t);
array_t*  init(size_t);
int       compareData(const hash_t*, const hash_t*);
int       compareKey(size_t, size_t);
int       search(const array_t*, size_t);
int       push(array_t*, const hash_t);
char*     getKeyElement(const array_t*, size_t);
char*     getValueElement(const array_t*, const char*);
void      initHash(hash_t*);
hash_t    encrypt(const char*);
char*     decrypt(hash_t);
void      printHash(hash_t);
void      printKey(const array_t*);
void      printValue(const array_t *);
void      clear(array_t*);

void clear(array_t *array) {
	for(size_t i=0;i<array->size;i++) {
		array->data[i].data = NULL;
		free(array->data[i].data);
	}

	array->data = NULL;
	free(array->data);
	array = NULL;
	free(array);
}

array_t *initArray(size_t n) {
	array_t *array = (array_t*)malloc(sizeof(array_t));

	array->cap = n;
	array->size = 0;
	array->data = (hash_t*)malloc(sizeof(hash_t)*array->cap);

	return array;
}

int compareData(const hash_t *val1, const hash_t *val2) {
	size_t cnt=0;
	if(val1->size != val2->size)
		return 0;

	for(size_t i=0;i<val1->size;i++)
		if(val1->data[i] == val2->data[i])
			cnt++;
	return cnt == val1->size;
}

int compareKey(size_t key1, size_t key2) {
	return key1 == key2;
}

int search(const array_t *array, size_t key) {
	for(size_t i=0;i<array->size;i++)
		if(array->data[i].key == key)
			return (int)i;
	return -1;
}

int push(array_t *array, const hash_t data) {
	if(array == NULL || array->data == NULL)
		return 0;
	if(array->size >= array->cap) {
		array->cap *= 2;
		array->data = (hash_t*)realloc(array->data, sizeof(hash_t)*array->cap);
	}

	int flag=1;

	for(size_t i=0;i<array->size;i++)
		if(compareKey(array->data[i].key, data.key))
			flag=0;

	if(flag)
		array->data[array->size++] = data;
	else
		return 0;
	return 1;
}

char *getKeyElement(const array_t *array, size_t key) {
	int idx = search(array, key);

	if(idx != -1)
		return decrypt(array->data[idx]);
	return NULL;
}

void initHash(hash_t *hash) {
	hash->size = 0;
	hash->cap = 4;
	hash->key = (size_t)(rand()%(10-2+1)+2);

	hash->data = (int*)malloc(sizeof(int)*hash->cap);
}

hash_t encrypt(const char *value) {
	hash_t hash;
	initHash(&hash);

	for(size_t i=0;i<strlen(value);i++) {
		int num = value[i];
		while(num) {
			if(hash.size >= hash.cap) {
				hash.cap *= 2;
				hash.data = (int*)realloc(hash.data, sizeof(int)*hash.cap);
			}
			hash.data[hash.size++] = (num%10)+(int)hash.key;
			num /= 10;
		}
		hash.data[hash.size++] = -1;
	}

	return hash;
}

char *decrypt(hash_t hash) {
	size_t index=0, cap=4;
	int *nums = (int*)malloc(sizeof(int)*cap);

	int steps[] = {0,1,10,100,1000,10000,100000,1000000};

	for(size_t i=0;i<hash.size;) {
		size_t count=0, j;
		int step;
		for(j=i;hash.data[i++] != -1 && j < hash.size;j++)
			count++;

		step = steps[count];

		int num = 0;
		for(int m=(int)j-1;hash.data[m] != -1 && m >= 0;m--) {
			num += (hash.data[m]-(int)hash.key)*step;
			step /= 10;
		}

		if(index >= cap) {
			cap *= 2;
			nums = (int*)realloc(nums, sizeof(int)*cap);
		}

		nums[index++] = num;
	}

	char *str = (char*)malloc(sizeof(char)*index+2);
	size_t i=0;

	for(;i<index;i++)
		str[i] = (char)nums[i];
	str[i] = '\0';

	free(nums);
	return str;
}

void printHash(hash_t hash) {
	for(size_t i=0;i<hash.size;i++)
		printf("%d", hash.data[i]);
	printf("\n");
}

void printKey(const array_t *array) {
	for(size_t i=0;i<array->size;i++) {
		printf("%zu  ", array->data[i].key);
		printHash(array->data[i]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	srand((unsigned)time(NULL));

	array_t *array = initArray(10);

	for(size_t i=0;i<7;i++) {
		char str[100];
		printf("str: ");
		scanf("%s", str);
		if(!push(array, encrypt(str)))
			printf("key cakismasi nedeniyle %s eklenmedi\n", str);
	}

	printKey(array);

	while(1) {
		size_t key;
		printf("key gir: ");
		scanf("%zu", &key);

		char *str = getKeyElement(array, key);
		if(str)
			printf("%s\n", str);
		else
			printf("key not found\n");
		free(str);
	}

	clear(array);
	return 0;
}
