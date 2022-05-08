#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#include "../include/efect.h"

uint8_t my_rand(uint8_t min, uint8_t max) {
	return (uint8_t)rand()%(max-min+1)+min;
}

void set(uint8_t array[][COL]) {
	for(uint8_t i=0;i<ROW;i++)
		for(uint8_t j=0;j<COL;j++)
			array[i][j] = my_rand(' ', 'z');

	size_t n = COL-1;
	while(n--)
		array[my_rand(0,ROW-1)][my_rand(0,COL-1)] = ' ';
}

void print(const uint8_t array[][COL]) {
	for(uint8_t i=0;i<ROW;i++) {
		printf("\t");
		for(uint8_t j=0;j<COL;j++)
			printf("%c ", array[i][j]);
		printf("\n");
	}
}

void* play_efect(void* data) {
	srand((unsigned)time(NULL));

	uint8_t array[ROW][COL];
	while(!(*(int*)data)) {
		//system("clear");
		set(array);
		print(array);
		usleep(400000);
	}

	return NULL;
}
