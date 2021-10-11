
#include <stdio.h>
#include <stdlib.h>

int myStrlen(char *str) {
	int size=0;
	for(int i=0;str[i]!='\0';i++) size++;
	return size;
}

char *reverse(char **str, int index) {
	int len = myStrlen(str[index]), x=0;

	char *temp = (char*)malloc(sizeof(char)*len);

	for(int i=len-1;i>=0;i--) { temp[x++] = str[index][i]; }

	return temp;
}

void myStrcpy(char **str1, char *temp, int index) {
	int len = myStrlen(temp), i;

	for(i=0;i<len;i++) { str1[index][i] = temp[i]; }

	str1[index][i] = '\0';
}

char **make() {
	char **arr;
	arr = (char**)malloc(sizeof(char*)*3);
	for(int i=0;i<3;i++) arr[i] = (char*)malloc(sizeof(char)*10);
	return arr;
}

void print(char **arr) {
	for(int i=0;i<3;i++) printf("\n%d. employee: %s\n",i+1,  arr[i]);
}

int main() {
	char **arr1 = make() , **arr2 = make();
	for(int i=0;i<3;i++) scanf("%s", arr1[i]);

	for(int i=0;i<3;i++) {
		char *temp = (char*)malloc(sizeof(char)*myStrlen(arr1[i]));
		temp = reverse(arr1, i);
		myStrcpy(arr2, temp, i);
		free(temp);
	}

	printf("\nBEFORE REVERSE..\n");
	print(arr1);
	printf("\nAFTER REVERSE..\n");
	print(arr2);

	free(arr1);
	free(arr2);
}
