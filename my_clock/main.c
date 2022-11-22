#include <stdio.h>

#include "clock.h"

int main(void) {
	mytime_t current_time = get_current_clock(get_current_time());

	printf("system clock: ");
	print_clock(&current_time);
}
