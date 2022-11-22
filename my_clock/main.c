#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>

#include "clock.h"

#define SIZE 10

void print_array(const mytime_t *array) {
	for(size_t i=0;i<SIZE;i++) {
		print_clock(array + i);
	}
}

int main(void) {
	srand((unsigned)time(NULL));

	mytime_t current_time = get_current_clock(get_current_time());

	printf("system clock: ");
	print_clock(&current_time);

	//
	mytime_t array[SIZE];
	for(size_t i=0;i<SIZE;i++) {
		array[i] = random_clock();
	}

	printf("\n--------- normal ---------\n\n");
	print_array(array);

	printf("\n--------- comp_less ---------\n\n");
	clock_sort(array, SIZE, time_cmp);
	print_array(array);
}
