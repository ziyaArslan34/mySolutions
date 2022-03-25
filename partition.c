#include <stdio.h>
#include <stdlib.h>

int compare(const void *p) {
	return *(const int *)p % 2 == 0;
}

void *partition(void *vp, size_t size, size_t width, int (*comp)(const void*)) {
	void *ptr = NULL;

	if((ptr = malloc(size*width+1)) == NULL)
		return NULL;

	size_t idx=0;
	int val = 0;

	for(size_t i=0;i<size*width;i += width) {
		if(comp((char*)vp+i)) {
			memcpy((char*)ptr+idx*width, (char*)vp+i, width);
			idx++;
			memcpy((char*)vp+i, &val, width);
		}
	}

	for(size_t i=0;i<size*width;i += width) {
		if(memcmp((char*)vp+i, &val, width) != 0) {
			memcpy((char*)ptr+idx*width, (char*)vp+i, width);
			++idx;
		}
	}

	return ptr;
}

int main() {
	char arr[] = {97,98,99,100,101,102,103,104,105,106};

	char *ptr = NULL;

	if((ptr = (char*)partition(arr, 10, sizeof(char), compare)) != NULL) {
		for(size_t i=0;i<10;i++)
			printf("%c ", *(ptr+i));
		printf("\n");
		free(ptr);
	} else {
		perror("");
	}
}
