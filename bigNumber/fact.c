#include <stdio.h>
#include "big_number.h"

bignum_t n_factorial(const char *n) {
	bignum_t fact = init_initValue("1"), i;
	bignum_t cnt = init_initValue(n);

	for(i=init_initValue("1");data_less(&i, &cnt);operator_plus(&i, "1")) {
		multiplication(&fact, fact.data, i.data);
	}

	destroy(&cnt);
	destroy(&i);

	return fact;
}

int main(void) {
	char n[50];
	printf("n!: ");
	scanf("%s", n);

	bignum_t result = n_factorial(n);
	printf("%s! -> ", n);
	print_bignum(&result);
	destroy(&result);
}
