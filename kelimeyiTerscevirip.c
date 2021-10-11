#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#define swapInit(TYPE) \
void swap(TYPE *val1, TYPE *val2) {\
	TYPE tmp = *val1;\
	*val1 = *val2;\
	*val2 = tmp;\
}
swapInit(char);
*/

void swap(void *val1, void *val2, const size_t size) {
	void *temp = malloc(size+1);

	memcpy(temp, val1, size);
	memcpy(val1, val2, size);
	memcpy(val2, temp, size);

	free(temp);
}

typedef unsigned int uint;
static uint findWord(const char *str) {
	uint size = 1;

	for(int i=0;i<strlen(str);i++)
		if(str[i] == '\x20' && (str[i+1] >= 33 && str[i+1] <= 126))
			size++;

	return size;
}

static char **make(const int strSize, const int wordSize) {
	char **res = (char**)malloc(sizeof(char*)*wordSize);
	for(int i=0;i<wordSize;i++)
		res[i] = (char*)malloc(sizeof(char)*strSize);

	return res;
}

static uint sizeChars(char **arr, const int wordSize) {
	uint size=0;

	for(int i=0;i<wordSize;i++)
		for(int j=0;arr[i][j] != '\0';j++)
			size++;

	return size;
}

static void myMemset(char **arr, const char *str, size_t size) {
	for(int i=0;i<size;i++)
		strcpy(arr[i], str);
}

char *apply(const char *str) {
	char **arr = NULL;
	const int wordSize = findWord(str);

	arr = make(1024, wordSize);
	myMemset(arr, "", wordSize);
	int arrIndex=0;

	for(int i=0;i<strlen(str);) {
		char *tmp;
		int index=0, j;

		for(j=i;str[j] != ' ';j++);
		tmp = (char*)malloc(sizeof(char)*j+1);

		for(j=i;str[i++] != ' ';j++)
			tmp[index++] = str[j];
		tmp[index] = '\0';

		int size=strlen(tmp)-1;
		for(int m=0;m<strlen(tmp)/2;m++)
			swap(&tmp[m], &tmp[size--], sizeof(tmp[m]));

		if(arrIndex < wordSize)
			strcpy(arr[arrIndex++], tmp);

		memset(tmp, 0, strlen(tmp));
		free(tmp);
	}

	int size = sizeChars(arr, wordSize), newStrIndex=0;
	char *newStr = (char*)malloc(sizeof(char)*size+wordSize+1);

	for(int i=0;i<wordSize;i++) {
		for(int j=0;arr[i][j] != '\0';j++)
			newStr[newStrIndex++] = arr[i][j];
		newStr[newStrIndex++] = ' ';
	}

	newStr[newStrIndex] = '\0';
	printf("index: %d\n", newStrIndex);

	for(int i=0;i<wordSize;i++)
		free(arr[i]);
	free(arr);

	return newStr;
}

int main() {
	char str[1024]={0};

	printf("str: ");
	fgets(str, sizeof(str), stdin);
	str[strlen(str)-1] = '\0';

	char *newStr = apply(str);

	printf("oldStr: %s\n", str);
	printf("newStr: %s\n", newStr);

	free(newStr);
	return 0;
}
