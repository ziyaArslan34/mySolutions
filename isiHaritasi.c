#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void initialize(int arr1[][SIZE], int arr2[][SIZE]) {
	for(size_t i=0;i<SIZE;i++) {
		for(size_t j=0;j<SIZE;j++) {
			arr1[i][j] = 0;
			arr2[i][j] = rand()%(99-10+1)+10;
		}
	}
}

void printMap(int arr1[][SIZE], int arr2[][SIZE]) {
	printf("\n");
	for(size_t i=0;i<SIZE;i++) {
		for(size_t j=0;j<SIZE;j++) {
			if(arr1[i][j] >= 2 && arr1[i][j] < 3)
				printf("\e[94m%d ", arr2[i][j]);
			else if(arr1[i][j] >= 3 && arr1[i][j] < 5)
				printf("\e[93m%d ", arr2[i][j]);
			else if(arr1[i][j] >= 5)
				printf("\e[91m%d ", arr2[i][j]);
			else
				printf("\e[90m%d ", arr2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void pointMap(int arr1[][SIZE]) {
	size_t row, col;

	char entry='e';

	while(entry != 'h') {
		printf("\e[92mrow col gir(4-4): ");
		scanf("%zu%zu", &row, &col);
		arr1[row][col]++;

		printf("\e[92mdevam(e/h): ");
		scanf(" %c", &entry);
	}
}

int main() {
	int hotMap[SIZE][SIZE], mainMap[SIZE][SIZE];
	initialize(hotMap, mainMap);
	pointMap(hotMap);

	printMap(hotMap, mainMap);

	return 0;
}
