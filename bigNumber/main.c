#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
        char num1[25]={0}, num2[25]={0};
        array_t result = init(18);

        do {
                printf("1. sayi: ");
                scanf("%s", num1);
        }while(!input_control(num1));

        do {
                printf("2. sayi: ");
                scanf("%s", num2);
        }while(!input_control(num2));

        clock_t start = clock();

        subtraction(&result, num1, num2);
        printf("cikarma: %s\n", result.data);

		destroy(&result);
        clock_t end = clock();
        printf("\ntoplam gecen sure: %.8lf\n", (double)(end-start)/CLOCKS_PER_SEC);
}
