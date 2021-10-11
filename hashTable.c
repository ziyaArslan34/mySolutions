/* string encrypt sample */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct HASH {
	int *array;
	size_t cap;
	size_t size;
	size_t key;
};

typedef struct HASH hash_t;

void init(hash_t **hash) {
	(*hash)->size = 0;
	(*hash)->cap = 4;
	(*hash)->key = rand()%(10-2+1)+2;

	(*hash)->array = (int*)malloc(sizeof(int)*(*hash)->cap);
}

int encrypt(hash_t **hash, const char *value) {
	for(int i=0;i<strlen(value);i++) {
		int num = value[i];
		while(num) {
			if((*hash)->size >= (*hash)->cap) {
				(*hash)->cap *= 2;
				(*hash)->array = (int*)realloc((*hash)->array, sizeof(int)*(*hash)->cap);
			}
			(*hash)->array[(*hash)->size++] = (num%10)+(*hash)->key;
			num /= 10;
		}
		(*hash)->array[(*hash)->size++] = -1;
	}

	return 1;
}

void decrypt(hash_t **hash) {
	int index=0, cap=4;
	int *nums = (int*)malloc(sizeof(int)*cap);

	int steps[] = {0,1,10,100,1000,10000,100000,1000000};

	for(int i=0;i<(*hash)->size;) {
		int count=0, step, j;
		for(j=i;(*hash)->array[i++] != -1;j++)
			count++;

		step = steps[count];

		int num = 0;
		for(int m=j-1;(*hash)->array[m] != -1;m--) {
			num += ((*hash)->array[m]-(*hash)->key)*step;
			step /= 10;
		}

		if(index >= cap) {
			cap *= 2;
			nums = (int*)realloc(nums, sizeof(int)*cap);
		}

		nums[index++] = num;
	}

	char *str = (char*)malloc(sizeof(char)*index+1);

	for(int i=0;i<index;i++)
		str[i] = nums[i];

	printf("\nDecrypt : %s\n", str);

	free(str);
	free(nums);
}

void printHash(hash_t **hash) {
	for(int i=0;i<(*hash)->size;i++)
		printf("%d", (*hash)->array[i]);
	printf("\n");
}

int main() {
	srand((unsigned)time(NULL));

	hash_t *hash = (hash_t*)malloc(sizeof(hash_t));
	init(&hash);

	char str[1024];

	printf("enter of string(1024): ");
	fgets(str, sizeof(str), stdin);
	str[strlen(str)-1] = '\0';


	//encrypt
	encrypt(&hash, str);
	printf("\nEncrypt : ");
	printHash(&hash);

	//decrypt
	decrypt(&hash);

	printf("size: %zu  %zu\n", sizeof(hash), hash->size);
	free(hash->array);
	free(hash);

	return 0;
}
