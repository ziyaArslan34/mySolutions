#include <stdio.h>

int myStrlen(char *str) {
	int len=0;
	for(int i=0;str[i] != '\0';i++) { len++; }
	return len;
}

int numWord(char *text) {
	int len=0;
	for(int i=0;i<myStrlen(text);i++) {
		if(text[i] == ' ') { len++; }
	}
	return len;
}

void info(char *text, char *word) {
	int flag=0;
	int count = myStrlen(word)-1;

	for(int i=0;i<myStrlen(text);i++) {
		if(text[i] == word[count-count] && text[i+1] == word[count-(count-1)] && text[i+2] && word[count-(count-2)]) {
			flag = 1;
		}
	}

	if(flag) { printf("Found [++] \n"); }
	else { printf("Not found!!\n"); }
}

int main() {
	char text[50];
	gets(text, 50);

	char word[10];
	scanf("%s",word);

	info(text, word);
}
