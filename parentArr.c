#include <stdio.h>
#include <stdlib.h>

int *firstArr;

void make() {
	firstArr = (int*)malloc(sizeof(int)*64);
}

void rowColumnMake(int **matris, int num) {
	static int index=0;
	for(int z=0;z<8;z++) {
		firstArr[index++] = matris[z][num];
	}
}

void arrMake(int **matris) {
	for(int z=0;z<8;z++) {
		rowColumnMake(matris, z);
	}
}

int **doubleArrMake() {
	int **arr;
	arr = (int**)malloc(sizeof(int*)*8);
	for(int i=0;i<8;i++) arr[i] = (int*)malloc(sizeof(int)*8);
	return arr;
}

int **endMake() {
	int **newArr;
	newArr = doubleArrMake();

	int x=0;

	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			newArr[i][j] = firstArr[x++];
		}
	}

	return newArr;
}

void writes(int **arr) {
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int **matris, **endArr;

	matris = doubleArrMake();

	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			matris[i][j] = rand()%50+11;
		}
	}

	make();
	writes(matris);
	arrMake(matris);
	endArr = endMake();
	printf("\n\n");
	writes(endArr);

	free(endArr);
	free(matris);
	free(firstArr);

	return 0;
}
