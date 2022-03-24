#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "big_number.h"

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int main() {
	srand((unsigned)time(NULL));

	bignum_t array[10];

	for(size_t i=0;i<10;i++) {
		array[i] = init(10);
		char n[10]={0};
		sprintf(n, "%d", my_rand(10000,1000000));
		operator_plus(array+i, n);
		printf("%s\n", array[i].data);
	}

	qsort(array, 10, sizeof(bignum_t), data_less);

	printf("\n\n");

	for(size_t i=0;i<10;i++)
		printf("%s\n", array[i].data);
}
