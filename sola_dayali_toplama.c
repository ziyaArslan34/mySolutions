#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int *data;
	size_t size, cap;
}array_t;

array_t init(size_t cap) {
	array_t array;
	array.size = 0;
	array.cap = cap;
	if((array.data = (int*)malloc(sizeof(int)*cap)) == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	return array;
}

void push_back(array_t *array, int data) {
	if(array->size >= array->cap) {
		array->cap *= 2;
		if((array->data = (int*)realloc(array->data, array->cap*sizeof(int))) == NULL) {
			fprintf(stderr, "malloc error\n");
			free(array->data);
			exit(1);
		}
	}

	array->data[array->size++] = data;
}

void display(const array_t *array) {
	printf("\n");
	for(size_t i=0;i<array->size;i++) {
		printf("%d ", array->data[i]);
	}
	printf("\n");
}

int get_eb_step(const array_t *array) {
	int eb = 0;

	for(size_t i=0;i<array->size;i++) {
		int temp = array->data[i];
		int teb = 0;
		while(temp) {
			temp /= 10;
			teb++;
		}
		if(eb < teb)
			eb = teb;
	}

	return eb;
}

int left_shift(int val, int n) {
	static int ns[] = {1,10,100,1000,10000,100000,1000000};
	return val * ns[n];
}

int get_sum(array_t *array) {
	int eb = get_eb_step(array), result=0;
	for(size_t i=0;i<array->size;i++) {
		int teb=0, temp = array->data[i];
		while(temp) {
			temp /= 10;
			teb++;
		}
		array->data[i] = left_shift(array->data[i], eb-teb);
		result += array->data[i];
	}

	return result;
}

int main(void) {
	array_t array = init(20);
	int val = 1;

	while(val != 0) {
		printf("sayi girin: ");
		scanf("%d", &val);
		push_back(&array, val);
	}
	display(&array);
	printf("toplam: %d\n", get_sum(&array));
	//display(&array);
	free(array.data);
}
