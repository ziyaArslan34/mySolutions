#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t myRand(int min, int max) {
	return rand()%(max-min+1)+min;
}

void swap(void *val1, void *val2, size_t typeSize) {
	void *temp = malloc(typeSize);
	memcpy(temp, val1, typeSize);
	memcpy(val1, val2, typeSize);
	memcpy(val2, temp, typeSize);
	free(temp);
}

void randomizeArray(void *array, size_t size, size_t typeSize) {
	for(size_t i=0;i<size;i++)
		swap((char*)array+myRand(0,size-1)*typeSize, (char*)array+myRand(0,size-1)*typeSize, typeSize);
}

void printArray(const void *array, size_t size, size_t typeSize, void (*fptr)(const void*)) {
	printf("\n");
	for(size_t i=0;i<size;i++)
		fptr((char*)array+i*typeSize);
	printf("\n");
}

void printInt(const void *dest) {
	printf("%d ", *(int*)dest);
}

void printChar(const void *dest) {
	printf("%c ", *(char*)dest);
}

int main() {
	srand((unsigned)time(NULL));

	char arrChar[11] = "ziyaarslan";
	int arrInt[10] = {1,2,3,4,5,6,7,8,9,10};


	randomizeArray(arrChar, 10, sizeof(char));
	randomizeArray(arrInt, 10, sizeof(int));

	printArray(arrChar, 10, sizeof(char), printChar);
	printArray(arrInt, 10, sizeof(int), printInt);

}
