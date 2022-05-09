#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#include "../include/efect.h"

uint8_t my_rand(uint8_t min, uint8_t max) {
	return (uint8_t)rand()%(max-min+1)+min;
}

void set(uint8_t **array, size_t row, size_t col) {
	for(uint8_t i=0;i<row;i++)
		for(uint8_t j=0;j<col;j++)
			array[i][j] = ' ';

	for(uint8_t i=0;i<col;i++) {
		for(uint8_t j=0;j<my_rand(0,row);j++)
			array[j][i] = my_rand(' ', 'z');
	}
}

void print(uint8_t **array, size_t row, size_t col) {
	for(uint8_t i=0;i<row;i++) {
		printf("  ");
		for(uint8_t j=0;j<col;j++)
			printf("%c", array[i][j]);
		printf("\n");
	}
}

void* play_efect(void* data) {
	system("clear");
	srand((unsigned)time(NULL));
	size_t row = 20, col;
	FILE *p = popen("tput cols", "r");
	if(!p)
		col = 20;

	char width[4];
	fgets(width, 4, p);
	col = (size_t)atoi(width) - 4;
	pclose(p);

	uint8_t **array = (uint8_t**)malloc(sizeof(uint8_t*)*row);
	if(!array)
		exit(1);

	for(size_t i=0;i<row;i++) {
		if((array[i] = (uint8_t*)malloc(sizeof(uint8_t)*col)) == NULL) {
			free(array);
			exit(1);
		}
	}

	int *flag = (int*)data;

	while(!*flag) {
		//printf("play_efect -> [%d][%d]\n", *(int*)data,  *flag);
		set(array, row, col);
		print(array, row, col);
		usleep(MILLISECOND);
	}

	for(size_t i=0;i<row;i++)
		free(array[i]);
	free(array);

	return NULL;
}
