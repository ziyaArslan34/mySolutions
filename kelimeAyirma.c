#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define swapInit(TYPE) \
void swap(TYPE *val1, TYPE *val2) {\
	TYPE tmp = *val1;\
	*val1 = *val2;\
	*val2 = tmp;\
}

swapInit(char);

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

static void print(char **arr, const int wordSize) {
	for(int i=0;i<wordSize;i++)
		printf("%d. Kelime: %s\n",i+1, arr[i]);
	printf("\n");
}

static void myMemset(char **arr, const char *str, size_t size) {
	for(int i=0;i<size;i++)
		strcpy(arr[i], str);
}

void apply(char **arr, const char *str) {
	const int wordSize = findWord(str);
	const int len = strlen(str);

	arr = make(1024, wordSize);
	myMemset(arr, "", wordSize);
	int arrIndex=0;

	for(int i=0;i<len;) {
		char *tmp;
		int index=0, j;

		for(j=i;str[j] != ' ' && j < len;j++);
		tmp = (char*)malloc(sizeof(char)*j-i+1);

		for(j=i;str[i++] != ' ' && j < len;j++)
			tmp[index++] = str[j];
		tmp[j] = '\0';

/*
		int size=strlen(tmp)-1;
		for(int m=0;m<strlen(tmp)/2;m++)
			swap(&tmp[m], &tmp[size--]);
*/

		if(arrIndex < wordSize)
			strcpy(arr[arrIndex++], tmp);

		memset(tmp, 0, strlen(tmp));
		free(tmp);
	}

	print(arr, wordSize);

	for(int i=0;i<wordSize;i++)
		free(arr[i]);
	free(arr);
}

int main() {
	char **wordArray = NULL;
	char str[1024]={0};

	printf("str: ");
	fgets(str, sizeof(str), stdin);
	str[strlen(str)-1] = '\0';

	printf("\nKelimeler ayriliyor...\n");
	sleep(1);

	apply(wordArray, str);
}
