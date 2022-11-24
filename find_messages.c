/* input.txt

6220    1       there were various Grubbs, and various Chubbs;
1498    6       Where many paths and errands meet.
1498    7       And whither then? I cannot say.
5181    0       There was plenty of everything left for Frodo.
6220    3       Some of these were only connected with Bilbo, and some
6220    5       The Sackville-Bagginses were not forgotten
1996    2       ziya
1498    1       Down from the door where it began.
5181    2       There was, however, no sign nor mention of money or jewellery:
1498    2       Now far ahead the Road has gone,
6220    6       They disliked Bilbo and detested Frodo,
5181    3       not a penny-piece or a glass bead was given away.
6220    7       written in golden ink.
1498    4       Pursuing it with eager feet,
1996    0       merhaba
1498    3       And I must follow, if I can,
5181    1       as well as the books, pictures were left in his possession.
1996    3       arslan
6220    0       There were many Bagginses and Boffins,
1498    5       Until it joins some larger way
6220    4       of them had hardly ever been in Hobbiton before.
1498    0       The Road goes ever on and on
6220    2       and a selection of Burrowses, Brockhouses and Proudfoots
1996    1       ben

	* ./a.out input.txt *
*/

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
