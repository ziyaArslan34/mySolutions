#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int a,b;
	double c;
	char d[10];
}test_t;

void swap(void *val1, void *val2, size_t size) {
	void *temp = malloc(size);

	memcpy(temp, val1, size);
	memcpy(val1, val2, size);
	memcpy(val2, temp, size);

	free(temp);
}

void print(test_t test) {
	printf("\n\n");
	printf("a: %d  b: %d\n", test.a, test.b);
	printf("c: %lf\n", test.c);
	printf("d: %s\n", test.d);
	printf("\n\n");
}

int main() {
	test_t x,y;

	x.a = 1; x.b = 2; x.c = 1.2; strcpy(x.d, "xinki");
	y.a = 3; y.b = 4; y.c = 3.2; strcpy(y.d, "yninki");

	swap(&x, &y, sizeof(test_t));

	print(x);
	print(y);

	return 0;
}
