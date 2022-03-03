#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

void printBit(int value) {
	printf("\nvalue:[%d] [ ", value);

	for(int i=(int)(sizeof(value)*8)-1;i>=0;i--) {
		if(value & 1 << i)
			printf("1");
		else
			printf("0");
	}
	printf(" ]\n\n");
}

int main() {
	srand((unsigned)time(NULL));

	int val = myRand(10, 50);

	printBit(val);

	int setBit, resetBit;
	printf("Hangi bit set edilsin: ");
	scanf("%d", &setBit);

	val |= 1 << setBit;
	printBit(val);

	printf("Hangi bit reset edilsin: ");
	scanf("%d", &resetBit);

	val &= ~(1 << resetBit);
	printBit(val);
}
