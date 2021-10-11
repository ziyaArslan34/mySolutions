#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	void *array;
	size_t size, cap;
}nums_t;

nums_t makeNumber(const char *str, const size_t index) {
	nums_t nums;
	nums.size = 0;
	nums.cap = 4;

	nums.array = (int*)malloc(sizeof(int)*nums.cap);

	for(int i=strlen(str)-1;i>=0;) {
		int flag = i, ind=0;
		char *temp = (char*)malloc(sizeof(char)*index+1);

		for(int j=i;j<index+flag;j++)
			temp[ind++] = str[i--];
		temp[ind++] = '\0';

		if(nums.size >= nums.cap) {
			nums.cap *= 2;
			nums.array = (int*)realloc(nums.array, sizeof(int)*nums.cap);
		}

		nums.array[nums.size++] = atoi(temp);
	}

	return nums;
}

int main() {
	long int num = 123456789101112;
	char str[50];
	snprintf(str, sizeof(str), "%ld", num);

	nums_t val = makeNumber(str, 3);

	for(size_t i=0;i<val.size;i++)
		printf("%zu. value: %d\n", i+1, val.array[i]);

	free(val.array);
}
