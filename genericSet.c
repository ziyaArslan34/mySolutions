#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRINT_INT(buffer, idx) printf("%d  ", *(int*)(buffer+idx))
#define PRINT_CHAR(buffer, idx) printf("%c  ", *(char*)(buffer+idx))
#define PRINT_STR(buffer, idx) printf("%s  ", (char*)(buffer+idx))
#define PRINT_ELSE(buffer, idx) printf("istedigin gibi doldur :)\n")

typedef struct {
	void *array;
	size_t cap,size,typeSize;
}array_t;

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

array_t set(const void *buf1, const void *buf2, const size_t size, const size_t typeSize) {
	array_t retVal;

	retVal.cap=4;
	retVal.size=0;
	retVal.array = malloc(typeSize*retVal.cap);
	retVal.typeSize = typeSize;

	for(size_t i=0;i<size;i++) {
		size_t flag=1;

		for(size_t j=0;j<size;j++)
			if(memcmp((char*)buf1+i*typeSize, (char*)buf2+j*typeSize, typeSize) == 0)
				flag=0;
		if(flag) {
			size_t elseFlag = 1;

			if(retVal.size >= retVal.cap) {
				retVal.cap *= 2;
				retVal.array = realloc(retVal.array, typeSize*retVal.cap);
			}

			for(size_t m = 0;m<retVal.size;m++)
				if(memcmp((char*)retVal.array+m*retVal.typeSize, (char*)buf1+i*typeSize, typeSize) == 0)
					elseFlag = 0;

			if(elseFlag) {
				memcpy((char*)retVal.array+retVal.size*retVal.typeSize, (char*)buf1+i*retVal.typeSize, retVal.typeSize);
				++retVal.size;
			}
		}
	}

	return retVal;
}

void printArray(const void *array, size_t size, size_t typeSize) {
	for(size_t i=0;i<size;i++)
		if(typeSize == sizeof(int))
			PRINT_INT((char*)array, i*typeSize);
		// else
	printf("\n");
}

int main() {
	srand((unsigned)time(NULL));

	int a1[9],a2[9];
	array_t val;

	for(size_t i=0;i<9;i++) {
		a1[i] = myRand(1, 10);
		a2[i] = myRand(1, 10);
	}

	val = set(a1, a2, 9,sizeof(int));

	printf("array1 -> "); printArray(a1, 9,sizeof(int));
	printf("array2 -> "); printArray(a2, 9,sizeof(int));
	printf("\narray end -> "); printArray(val.array, val.size, val.typeSize);

	printf("\n");
	free(val.array);
}
