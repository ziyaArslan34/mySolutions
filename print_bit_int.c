#include <stdio.h>

#define IS_LITTLE_ENDIAN ((97 == 0b01100001))

void print_bit(int value) {
	printf("\n[ ");
#if IS_LITTLE_ENDIAN
	for(int i=((int)sizeof(value)*8)-1;i >= 0;i--) {
		if(value & 1 << i)
			printf("1");
		else
			printf("0");
	}
#else
	for(int i=0;i<(int)sizeof(value)*8;i++) {
        if(value & 1 << i)
            printf("1");
        else
            printf("0");
    }
#endif
	printf(" ]\n");
}

int main() {
	//0b01100001 -> 97;

	print_bit(97);
}
