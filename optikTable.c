#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

#define ROW 10
#define COL 10

void swap(void *val1, void *val2, size_t typeSize) {
	void *temp = malloc(typeSize);
	memcpy(temp, val1, typeSize);
	memcpy(val1, val2, typeSize);
	memcpy(val2, temp, typeSize);
	free(temp);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

void randomize_array(void *array, size_t size, size_t typeSize) {
	for(size_t i=0;i<size;i++)
		swap((char*)array+my_rand(0,(int)size-1)*typeSize, (char*)array+my_rand(0,(int)size-1)*typeSize, typeSize);
}

void print_table(char code[][COL], int *arr) {
	printf("\n   ");

	for(int i=0;i<ROW;i++)
		printf("\e[90m%d ", arr[i]);
	printf("\n  ");

	for(int i=0;i<20;i++)
		printf("\e[90m%c", '_');
	printf("\n");

	for(int i=0;i<ROW;i++) {
		printf("\e[90m%d |", i);
		for(int j=0;j<COL;j++) {
			if(code[i][j] <= 122 && code[i][j] >= 97) {
				printf("\e[91m%c\e[90m|", code[i][j]);
			} else {
				printf("\e[90m%c\e[90m|", code[i][j]);
			}
		}
		printf("\n");
	}
	char ch = '\xF8'; /*'¯'*/
	printf("  ");
	for(int i=0;i<20;i++)
		printf("\e[90m%c", ch);
	printf("\n");
}

int sep(int *arr, long int num) {
	int ln, i=9;
	if(/*num < 100000000 ||*/ num > 9999999999)
		return 0;

	while(num > 0) {
		ln = num%10;
		num /= 10;
		arr[i--] = ln;
	}
	return 1;
}

void star_map(char code[][COL], int *arr, const char *text) {
	size_t idx=0;

	for(int i=0;i<ROW;i++) {
		for(int j=0;j<COL;j++) {
			if(arr[j] == i) {
				if(idx >= strlen(text))
					idx=0;
				code[i][j] = text[idx++];
			}
		}
	}
}

int main() {
	srand((unsigned)time(NULL));

	char text[50];
	printf("enter text: ");
	fgets(text, sizeof(text), stdin);
	text[strlen(text)-1] = '\0';

	while(1) {
		system("clear");
		int arr[10]={0};

		char code[ROW][COL] = {
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
		};

		long int num = 1234567891;

		if(sep(arr, num)) {
			randomize_array(arr, 10, sizeof(int));
			star_map(code, arr,text);
			print_table(code, arr);
		} else {
			printf("\nLutfen 10 basamaktan fazla sayi girmeyin!\n");
		}
		sleep(1);
	}
}
