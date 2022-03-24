#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "big_number.h"
#define SIZE 5

int main() {
	srand((unsigned)time(NULL));

	bignum_t array[SIZE];

	for(size_t i=0;i<SIZE;i++) {
		array[i] = random_big_number();
		printf("%s\n", array[i].data);
	}

	qsort(array, SIZE, sizeof(bignum_t), data_less);

	printf("\n\n");

	for(size_t i=0;i<SIZE;i++)
		print_bignum(array+i);

	for(size_t i=0;i<SIZE;i++)
		destroy(array+i);
}
