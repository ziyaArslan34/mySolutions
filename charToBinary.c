#include <stdio.h>

int main() {
	for(int i=97;i<=122;i++) {
		printf("%c  >> ", i);
		for(int j=7;j>=0;j--) {
			if((char)i & (1u << j))
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}

	return 0;
}
