#include <stdio.h>
#include "big_number.h"

bignum_t result(const char *start, const char *cnt) {
	bignum_t st = init_initValue(start);

	bignum_t count = init_initValue(cnt);
	bignum_t i = init_initValue("0");

	while(data_less(&i, &count)) {
		const char *value = st.data;
		bignum_t tmp = init(10);
		multiplication(&tmp, value, value);
		destroy(&st);
		st = tmp;
		operator_plus(&i, "1");
	}

	destroy(&i);
	destroy(&count);

	return st;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "usage: ./a.out <start> <power>\n");
		return -1;
	}

	bignum_t res = result(argv[1], argv[2]);
	print_bignum(&res);
	destroy(&res);
}
