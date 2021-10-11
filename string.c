#include <stdio.h>
#include <stdlib.h>

int myStrlen(char *str) {
	int num=0;
	for(int i=0;str[i] != '\0';i++) num++;
	return num;
}

void myStrcpy(char *str1, char *str2) {
	int len = myStrlen(str2);

	for(int i=0;i<len;i++) {
		str1[i] = str2[i];
	}
}

void print(char str[][10]) {
	for(int i=0;i<5;i++) {
		printf("\n%d word : %s\n", i+1, str[i]);
	}
}

int main() {
	char arr[5][10];
	char str[] = "bir iki uc dort bes";

	int y=0;

	for(int i=0;i<myStrlen(str);) {
		char *temp = (char*)malloc(sizeof(char)*10);
		int x=0;

		for(int j=i;str[i++] != ' ';j++) {
			temp[x++] = str[i-1];
		}

		myStrcpy(arr[y++], temp);
	}

	print(arr);

	return 0;
}
