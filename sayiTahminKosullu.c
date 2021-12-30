#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define arrSize 4

typedef struct {
	char name[30];
	int arr[arrSize];
	size_t idx;
	int score;

	size_t plus,minus;
}player_t;

int ctrl(const int*, int);

player_t createPlayer() {
	player_t ptr;
	strcpy(ptr.name, "username");

	ptr.idx=0;
	ptr.plus=0;
	ptr.minus=0;
	ptr.score=0;

	return ptr;
}

int updatingArray(int *ptr, int num) {
	size_t idx=0;

	while(num) {
		ptr[idx++] = num%10;
		num /= 10;
	}

	return ctrl(ptr, idx) && ptr[arrSize-1] != 0;
}

int ctrl(const int *arr, int idx) {
	if(idx < arrSize || idx > arrSize)
		return 0;

	for(size_t i=0;i<idx;i++) {
		int flag = 0;

		for(size_t j=0;j<idx;j++)
			if(arr[i] == arr[j])
				flag++;
		if(flag > 1)
			return 0;
	}

	return 1;
}

void foo(const int *array, player_t *ptr) {
	ptr->plus = 0;
	ptr->minus = 0;

	for(size_t i=0, j=arrSize-1;i<arrSize;i++, j--) {
		if(array[i] == ptr->arr[j])
			ptr->plus++;
		else
			ptr->minus++;
	}
}

int compArray(const int *arr1, const int *arr2) {
	for(size_t i=0, j=arrSize-1;i<arrSize;i++, j--)
		if(arr1[i] != arr2[j])
			return 0;
	return 1;
}

int main() {
	srand((unsigned)time(NULL));

	player_t ptr = createPlayer();

	int arr[arrSize];
	int randomNum;

	do {
		randomNum = (int)rand()%(9999-1000+1)+1000;
	}while(!updatingArray(arr, randomNum));

	int n = 10, win=0;

	for(size_t i=0;i<arrSize;i++)
		printf("%d ", arr[i]);
	printf("\n");

	while(n--) {
		int num;
		printf("tahmin: ");
		scanf("%d", &num);

		if(!updatingArray(ptr.arr, num)) {
			printf("Yanlis sayi girildi tekrar dene\n");
			n++;
			continue;
		} else {
			if(compArray(arr, ptr.arr)) {
				ptr.score = (n+1)*10;
				win=1;
				printf("tebrikler kazandiniz  puan : %d\n", ptr.score);
				break;
			} else {
				foo(arr, &ptr);
				printf("Bilinen hane    : %zu\n", ptr.plus);
				printf("Bilinmeyen hane : %zu\n", ptr.minus);
			}
		}
	}

	if(!win)
		printf("\nBilemedinnn\n");

}
