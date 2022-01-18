#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int hex_to_dec(const char *num) {
	size_t size = strlen(num);
	int idx=0;

	int *array = (int*)malloc(sizeof(int)*size);

	for(size_t i=0;i<size;i++) {
		switch(num[i]) {
			case 97:  array[idx] = 10; break;
			case 98:  array[idx] = 11; break;
			case 99:  array[idx] = 12; break;
			case 100: array[idx] = 13; break;
			case 101: array[idx] = 14; break;
			case 102: array[idx] = 15; break;
			case 103: array[idx] = 16; break;

			case 65:  array[idx] = 10; break;
			case 66:  array[idx] = 11; break;
			case 67:  array[idx] = 12; break;
			case 68:  array[idx] = 13; break;
			case 69:  array[idx] = 14; break;
			case 70:  array[idx] = 15; break;
			case 71:  array[idx] = 16; break;

			default:
				array[idx] = num[i] - '0';
				break;
		}
		idx++;
	}

	int res = 0;

	for(int i=0,j=(int)size-1;i<(int)size;i++, j--)
		res += (int) (array[i] * pow(16, j));

	free(array);
	return res;
}

int main() {
	printf("%d\n", hex_to_dec("123"));
	printf("%d\n", hex_to_dec("7a"));
	printf("%d\n", hex_to_dec("7A"));
	printf("%d\n", hex_to_dec("36F"));
	printf("%d\n", hex_to_dec("65"));
}
