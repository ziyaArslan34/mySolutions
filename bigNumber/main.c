#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	char num1[50]={0}, num2[50]={0};
	bignum_t result = init(50);

	do {
		printf("1. sayi: ");
		scanf("%s", num1);
	}while(!input_control(num1));

	do {
		printf("2. sayi: ");
		scanf("%s", num2);
	}while(!input_control(num2));

	int islem=0;

	printf("\nToplama [1]\nCikarma [2]\nCarpma  [3]\nBolme   [4]\n\n");
	printf("islem sec: ");
	scanf("%d", &islem);

	clock_t start = clock();

	switch(islem) {
		case 1:
			addition(&result, num1, num2);
			printf("toplama sonucu: ");
			print_bignum(&result);
			break;
		case 2:
			subtraction(&result, num1, num2);
			printf("cikarma sonucu: ");
			print_bignum(&result);
			break;
		case 3:
			multiplication(&result, num1, num2);
			printf("carpma sonucu: ");
			print_bignum(&result);
			break;
		case 4:
			division(&result, num1, num2);
			printf("bolme sonucu: ");
			print_bignum(&result);
			break;
		default:
			printf("hatali islem!\n");
	}

	destroy(&result);

	printf("\ntoplam gecen sure: %.8lf\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
