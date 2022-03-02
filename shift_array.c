#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shift(int *arr, int count, int size, const char *direction) {
	if(!strcmp(direction, "right")) {
		for(int i=0;i<count;i++) {
			int tmp = arr[size-1];
			for(int j=size-1;j>=0;j--)
				arr[j] = arr[j-1];
			arr[0] = tmp;
		}
	} else if(!strcmp(direction, "left")) {
		// todo
		for(int i=0;i<count;i++) {
			int tmp = arr[0];
			for(int j=0;j<size-1;j++)
				arr[j] = arr[j+1];
			arr[size-1] = tmp;
		}
	} else {
		puts("cannot direction!..\n");
	}
}

void print(const int *arr, int size) {
	for(int i=0;i<size;i++)
		printf("%d  ", arr[i]);
	printf("\n");
}

int main() {
	int arr[]={2,6,3,9,4};

	print(arr,5);
	shift(arr, 1,5,"left");
	print(arr, 5);

	shift(arr, 4, 5, "right");
	print(arr, 5);
	return 0;
}
