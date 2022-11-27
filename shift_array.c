#include <stdio.h>
#include <stdlib.h>

void left_shift(void *array, size_t type, size_t size, int cnt) {
	for(int i=0;i<cnt;i++) {
		void *tmp = malloc(type);
		if(!tmp)
			return;
		memcpy(tmp, (char*)array + 0 * type, type);
		for(size_t j=0;j<size-1;j++)
			memcpy((char*)array + j * type, (char*)array + ((j+1) * type), type);
		memcpy((char*)array + ((size-1) * type), tmp, type);
		free(tmp);
	}
}

void left_right(void *array, size_t type, size_t size, int cnt) {
	for(int i=0;i<cnt;i++) {
		void *tmp = malloc(type);
		if(!tmp)
			return;
		memcpy(tmp, (char*)array + ((size-1) * type), type);
		for(int j=(int)size-1;j>0;j--)
			memcpy((char*)array + (size_t)j * type, (char*)array + ((size_t)(j-1) * type), type);
		memcpy((char*)array + 0 * type, tmp, type);
		free(tmp);
	}
}

int main(void) {
	int array[] = {1,2,3,4,5};
	left_shift(array, sizeof(int), 5, 2);

	for(size_t i=0;i<5;i++)
		printf("%d ", array[i]);
}
