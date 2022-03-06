#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int main() {
	srand((unsigned)time(NULL));

	int randomNumber = my_rand(100,999), result;
	const char *mood = "*+-";
	size_t cnt=0;

	do {
		result=1;

		int array[6];
		size_t idx=0;
		array[0] = my_rand(10,99);

		for(size_t i=1;i<6;i++) {
			array[i] = my_rand(1,9);
		}

		for(size_t i=0;i<6;i++) {
			if(idx >= 3)
				idx=0;
			if(*(mood+idx) == '*')
				result *= array[i];
			else if(*(mood+idx) == '+')
				result += array[i];
			else if(*(mood+idx) == '-')
				result -= array[i];
			idx++;

		}
		cnt++;
		printf("[%d]*[%d]+[%d]-[%d]*[%d]+[%d] = %d\n", array[0], array[1],array[2],array[3],array[4],array[5],result);

	} while(result != randomNumber);

	printf("%zu. deneme dogru sayi: %d\n", cnt, randomNumber);
}
