#include <stdio.h>
#include <stdlib.h>

int myAtoi(const char *str) {
	int cap=4, size=0, i=0;
	int *array = (int*)malloc(sizeof(int)*cap);

	if(str[i] == '-')
		i++;

	for(;str[i] != '\0';i++) {
		if(str[i] >= 48 && str[i] <= 57) {
			if(size >= cap) {
				cap *= 2;
				array = (int*)realloc(array, sizeof(int)*cap);
			}
			array[size++] = str[i] - '0';
		} else {
			free(array);
			return -1; // wrong string is return exit_failure
		}
	}

	int steps[] = {0,1,10,100,1000,10000,100000,1000000};

	if(size >= (sizeof(steps)/sizeof(steps[0]))) {
		free(array);
		return -1;
	}

	int num=0, step = steps[size];


	for(i=0;i<size;i++) {
		num += array[i]*step;
		step /= 10;
	}

	if(str[0] == '-')
		num = -num;
	free(array);
	return num;
}

int main() {
	//test
	int x = myAtoi("12-3");
	int y = myAtoi("--123");
	int z = myAtoi("100000");
	int q = myAtoi("string");

	printf("%d  %d  %d  %d\n", x, y, z, q);
}
