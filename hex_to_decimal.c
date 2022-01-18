#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int hex_to_dec(const char *hex) {
	int size = (int)strlen(hex);
	int decimal=0, base=1;

	for(int i=size-1;i>=0;i--) {
		if(hex[i] >= '0' && hex[i] <= '9') {
			decimal += (int)(hex[i] - 48) * base;
			base *= 16;
		} else if(hex[i] >= 'a' && hex[i] <= 'f') {
			decimal += (int)(hex[i] - 87) * base;
			base *= 16;
		} else if(hex[i] >= 'A' && hex[i] <= 'F') {
			decimal += (int)(hex[i] - 55) * base;
			base *= 16;
		} else {
			printf("undefined hexdecimal\n");
			return 0;
		}
	}

	return decimal;
}

int main() {
	printf("123 -> %d\n", hex_to_dec("123"));
	printf("7a  -> %d\n", hex_to_dec("7a"));
	printf("7A  -> %d\n", hex_to_dec("7A"));
	printf("36F -> %d\n", hex_to_dec("36F"));
	printf("65  -> %d\n", hex_to_dec("65"));
	printf("1A  -> %d\n", hex_to_dec("1A"));
	printf("6fz -> %d\n", hex_to_dec("6fz"));
}
