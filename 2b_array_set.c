#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char **data;
	size_t size, cap;
}two_array_t;

void destroy(two_array_t*);

two_array_t init(size_t capacity) {
	two_array_t array;
	array.size = 0;
	array.cap = capacity;

	if((array.data = (char**)malloc(sizeof(char*)*capacity)) == NULL) {
		fprintf(stderr, "memory error\n");
		exit(1);
	}

	return array;
}

int empty(two_array_t *array) {
	return array->size == 0;
}

int push_back(two_array_t *array, const char *src) {
	if(array->size >= array->cap) {
		array->cap *= 2;
		if((array->data = (char**)realloc(array->data, sizeof(char*)*array->cap)) == NULL) {
			destroy(array);
			fprintf(stderr, "memory error\n");
			return 0;
		}
	}

	array->data[array->size] = (char*)malloc(sizeof(char)*strlen(src)+1);
	if(array->data[array->size] == NULL) {
		destroy(array);
		return 0;
	}

	strcpy(array->data[array->size++], src);
	return 1;
}

void display(two_array_t *array) {
	printf("\n");
	for(size_t i=0;i<array->size;i++)
		printf("%s\n", array->data[i]);
	printf("\n");
}

void destroy(two_array_t *array) {
	for(size_t i=0;i<array->size;i++)
		free(array->data[i]);
	free(array->data);
}

two_array_t word_set(two_array_t *arr1, two_array_t *arr2) {
	two_array_t new_array = init(arr1->size+arr2->size);

	if(empty(arr1) || empty(arr2))
		return new_array;

	two_array_t *max_data = arr1->size > arr2->size ? arr1 : arr2;
	two_array_t *min_data = arr1->size < arr2->size ? arr1 : arr2;

	for(size_t i=0;i<max_data->size;i++) {
		int flag1 = 1, flag2 = 1;
		for(size_t j=0;j<min_data->size;j++)
			if(strcmp(max_data->data[i], min_data->data[j]) == 0)
				flag1 = 0;
		if(flag1) {
			for(size_t m=0;m<new_array.size;m++)
				if(strcmp(max_data->data[i], new_array.data[m]) == 0)
					flag2 = 0;

			if(flag2) {
				if(!push_back(&new_array, max_data->data[i])) {
					destroy(arr1);
					destroy(arr2);
					destroy(&new_array);
					exit(1);
				}
			}
		}
	}

	return new_array;
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

const char *random_name(void) {
	static const char *names[] = {
		"bir", "iki", "uc", "dort", "bes",
		"alti", "yedi", "sekiz", "dokuz", "on",
		"onbir", "oniki", "onuc", "ondort", "onbes"
	};

	return names[my_rand(0,9)];
}

int main(void) {
	srand((unsigned)time(NULL));

	two_array_t array1 = init(10);
	two_array_t array2 = init(20);

	for(size_t i=0;i<10;i++)
		push_back(&array1, random_name());
	for(size_t i=0;i<20;i++)
		push_back(&array2, random_name());

	two_array_t new_array = word_set(&array1, &array2);

	display(&array1);
	display(&array2);
	display(&new_array);

	destroy(&array1);
	destroy(&array2);
	destroy(&new_array);
}
