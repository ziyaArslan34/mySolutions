#include <stdio.h>
#include "clock.h"

#define SIZE (10)

int main(void) {
	mytime_t system_clock = get_current_clock(get_current_time());
	printf("system clock: ");
	print_clock(&system_clock);

	mytime_t array[10];
	for(size_t i=0;i<SIZE;i++)
		array[i] = random_clock();

	for(size_t i=0;i<SIZE;i++)
		print_clock(array + i);

	printf("\n--------After sort--------\n\n");
	clock_sort(array, SIZE, comp_less);
	for(size_t i=0;i<SIZE;i++)
		print_clock(array + i);
}
