#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#include "efect.h"

uint8_t my_rand(uint8_t min, uint8_t max) {
	return (uint8_t)rand()%(max-min+1)+min;
}

void set(uint8_t array[][COL]) {
	for(uint8_t i=0;i<8;i++)
		for(uint8_t j=0;j<COL;j++)
			array[i][j] = my_rand(0,1);
}

void print(const uint8_t array[][COL]) {
	printf("\n\n");
	for(uint8_t i=0;i<8;i++) {
		printf("\t");
		for(uint8_t j=0;j<COL;j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}
}

void* play_efect(void* name) {
	srand((unsigned)time(NULL));

	uint8_t array[8][COL];

	while(1) {
		system("clear");
		set(array);
		print(array);
		usleep(500000);
	}

	return name;
}
