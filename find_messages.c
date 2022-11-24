#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id, num;
	char msg[256];
}data_t;

data_t *get_data(FILE *file, size_t *size) {
	if(!file) {
		fprintf(stderr, "cannot open file\n");
		return NULL;
	}

	size_t cap=10;
	*size = 0;
	data_t *array = (data_t*)malloc(sizeof(data_t)*cap);

	if(!array)
		return NULL;

	data_t tmp;
	while(fscanf(file, "%d%d\t%[^\n]s", &tmp.id, &tmp.num, tmp.msg) != EOF) {
		if(*size >= cap) {
			cap *= 2;
			if((array = (data_t*)realloc(array, sizeof(data_t)*cap)) == NULL)
				return NULL;
		}
		array[(*size)++] = tmp;
	}

	fclose(file);
	return array;
}

int is_less_id(const data_t *x, const data_t *y) { return x->id < y->id; }
int is_less_num(const data_t *x, const data_t *y) { return x->num < y->num; }

void swap(data_t *x, data_t *y) {
	data_t tmp = *x;
	*x = *y;
	*y = tmp;
}

void sort_array(data_t *array, size_t x, size_t y, int cmp(const data_t*, const data_t*)) {
	for(size_t i=x;i<y;i++)
		for(size_t j=x;j<y-1;j++)
			if(cmp(array+i, array+j))
				swap(array+i, array+j);
}

void print_data(const data_t *array, size_t start, size_t end) {
	printf("\n");
	for(size_t i=start;i<end;i++)
		printf("%d %d %s\n", array[i].id, array[i].num, array[i].msg);
	printf("\n");
}

size_t n_difference(const data_t *array, size_t size) {
	size_t n = 1;
	int id = array[0].id;

	for(size_t i=0;i<size;i++) {
		if(id != array[i].id) {
			n++;
			id = array[i].id;
		}
	}
	return n;
}

void print_messages(data_t *array, size_t size) {
	size_t n = n_difference(array, size);

	int *cnts = (int*)malloc(sizeof(int)*n);
	cnts[n-1] = size;
	size_t idx=0;
	int id = array[0].id;

	for(size_t i=0;i<size;i++) {
		if(id != array[i].id) {
			id = array[i].id;
			cnts[idx++] = i;
		}
	}

	printf("\n----------------  message 1 ----------------\n");
	sort_array(array, 0, cnts[0], is_less_num);
	print_data(array, 0, cnts[0]);
	printf("\n--------------------------------------------\n");

	for(size_t i=0;i<n-1;i++) {
		printf("\n---------------- message %zu ----------------\n", i+2);
		sort_array(array, cnts[i], cnts[i+1], is_less_num);
		print_data(array, cnts[i], cnts[i+1]);
		printf("\n---------------------------------------------\n");
	}

	free(cnts);
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "usage: { ./a.out <filename> }\n");
		return -1;
	}

	size_t size = 0;
	data_t *array = get_data(fopen(argv[1], "r"), &size);
	if(!array) {
		fprintf(stderr, "memory error\n");
		return -2;
	}

	sort_array(array, 0, size, is_less_id);
	print_messages(array, size);
	free(array);
}
