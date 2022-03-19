#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shift_array(size_t typeSize, void *array, size_t size, int counter, const char *direction) {
	if(!strcmp(direction, "right")) {
		for(int i=0;i<counter;i++) {
			void *tmp = malloc(typeSize);
			memcpy(tmp, (char*)array+((size-1)*typeSize), typeSize);

			for(int j=(int)size-1;j>0;j--)
				memcpy((char*)array+(size_t)j*typeSize, (char*)array+((size_t)(j-1)*typeSize), typeSize);
			memcpy((char*)array+0*typeSize, tmp, typeSize);
			free(tmp);
		}
	} else if(!strcmp(direction, "left")) {
		for(int i=0;i<counter;i++) {
			void *tmp = malloc(typeSize);
			memcpy(tmp, (char*)array+0*typeSize, typeSize);

			for(size_t j=0;j<size-1;j++)
				memcpy((char*)array+j*typeSize, (char*)array+((j+1)*typeSize), typeSize);
			memcpy((char*)array+((size-1)*typeSize), tmp, typeSize);
		}
	} else {
		fprintf(stderr, "not direction.!\n");
	}
}

int main() {
	int array[] = {1,2,3,4,5,6,7};

	shift_array(sizeof(int), array, 7, 2, "left");

	for(size_t i=0;i<7;i++)
		printf("%d ", array[i]);
	printf("\n");
}
