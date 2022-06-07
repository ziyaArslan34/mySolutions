#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 50

typedef struct {
	char **data;
	size_t size, cap;
}array_t;

void destroy_array(array_t*);

array_t init_array(size_t defaultSize) {
	array_t array;
	array.size = 0;
	array.cap = defaultSize;
	if((array.data = (char**)malloc(sizeof(char*)*defaultSize)) == NULL) {
		fprintf(stderr, "memory error!\n");
		exit(1);
	}

	return array;
}

void push_back_array(array_t *array, const char *word) {
	if(array->size >= array->cap) {
		array->cap *= 2;
		if((array->data = (char**)realloc(array->data, sizeof(char*)*array->cap)) == NULL) {
			fprintf(stderr, "memory error!\n");
			destroy_array(array);
			exit(1);
		}
	}

	if((array->data[array->size] = (char*)malloc(sizeof(char)*WORD_SIZE)) == NULL) {
		fprintf(stderr, "memory error!\n");
		destroy_array(array);
		exit(1);
	}
	strcpy(array->data[array->size++], word);
}

void sort_array(array_t *array) {
	for(size_t i=0;i<array->size;i++) {
		for(size_t j=0;j<array->size;j++) {
			if(strcmp(array->data[i], array->data[j]) < 0) {
				char tmp[WORD_SIZE];
				strcpy(tmp, array->data[i]);
				strcpy(array->data[i], array->data[j]);
				strcpy(array->data[j], tmp);
			}
		}
	}
}

void destroy_array(array_t *array) {
	for(size_t i=0;i<array->size;i++)
		free(array->data[i]);
	free(array->data);
}

void print_array(const array_t *array) {
	printf("\n");
	for(size_t i=0;i<array->size;i++)
		fprintf(stdout, "%s\n", array->data[i]);
	printf("\n");
}

int search_word(char **array, size_t size, const char *word) {
	if(!--size)
		return 0;
	if(!strcmp(array[size], word))
		return 1;
	return search_word(array, size, word);
}

void read_input_file(const char *filename, array_t *array, array_t *ignore_words) {
	FILE *input;
	if((input = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "input file error!\n");
		destroy_array(array);
		exit(1);
	}

	char word[WORD_SIZE];
	while(fscanf(input, "%s", word) != EOF) {
		int flag = 0;
		for(size_t i=0;i<ignore_words->size;i++)
			if(!strcmp(word, ignore_words->data[i]))
				flag = 1;

		if(!flag)
			push_back_array(array, word);
	}
	fclose(input);
}

void write_output_file(array_t *array, array_t *ignore_words) {
	array_t tmp_array = init_array(array->size);
	FILE *output;
	if((output = fopen("output.txt", "w")) == NULL) {
		fprintf(stderr, "output file error\n");
		destroy_array(array);
		destroy_array(&tmp_array);
		exit(1);
	}

	for(size_t i=0;i<array->size;i++) {
		size_t cnt=0;
		for(size_t j=0;j<array->size;j++)
			if(!strcmp(array->data[j], array->data[i]))
				cnt++;
		int flag1=0, flag2=0;
		for(size_t m=0;m<tmp_array.size;m++)
			if(!strcmp(tmp_array.data[m], array->data[i]))
				flag1 = 1;

		for(size_t ig=0;ig<ignore_words->size;ig++)
			if(!strcmp(ignore_words->data[ig], array->data[i]))
				flag2 = 1;

		if(!flag1 && !flag2) {
			fprintf(output, "%s, %zu\n", array->data[i], cnt);
		}
		push_back_array(&tmp_array, array->data[i]);
	}
	destroy_array(&tmp_array);
	fclose(output);
}

array_t get_ignore_list(void) {
	FILE *ignore_file;
	if((ignore_file = fopen("ignore_list.txt", "r")) == NULL) {
		fprintf(stderr, "ignore file error!\n");
		exit(1);
	}

	array_t ignore_list = init_array(20);
	char word[WORD_SIZE];

	while(fscanf(ignore_file, "%s", word) != EOF)
		push_back_array(&ignore_list, word);
	fclose(ignore_file);
	return ignore_list;
}

size_t get_count_word(const array_t *array, const char *word) {
	size_t cnt = 0;
	for(size_t i=0;i<array->size;i++)
		if(!strcmp(array->data[i], word))
			cnt++;
	return cnt;
}

int main(void) {
	array_t array = init_array(10);
	array_t ignore_words = get_ignore_list();

	read_input_file("input.txt", &array, &ignore_words);
	write_output_file(&array, &ignore_words);

	char word[WORD_SIZE];
	printf("Kelime girin: ");
	scanf("%s", word);
	if(search_word(array.data, array.size, word)) {
			fprintf(stdout, "Aradigin kelimenin siklik sayisi: %zu\n", get_count_word(&array, word));
	} else {
		fprintf(stdout, "Aradigin kelime bulunamadi\n");
	}

	sort_array(&array);
	print_array(&array);

	destroy_array(&array);
}
