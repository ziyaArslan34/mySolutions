#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print() {
	const char *man[] = {
		" ____       ",
		" |   |      ",
		" |   O      ",
		" |  /|\\     ",
		" | _/ \\_    ",
		" |          ",
		"=========== "
		};

	for(int i=0;i<7;i++)
		printf("%s\n", man[i]);
	printf("\n");
}

int foo(char *myWord, const char *str, const char ch, const int len) {
	int flag=0;

	for(int i=0;i<len;i++) {
		if(str[i] == ch) {
			myWord[i] = ch;
			flag=1;
		}
	}
	return flag;
}

int main() {
	int hang=29;

	const char *kelime = "adamasmaca";
	int len = strlen(kelime);

	char *myWord = (char*)malloc(sizeof(char)*len);
	memset(myWord, '_', len);

	while(hang) {
		char ch;
		printf("tahmini harf: ");
		scanf(" %c", &ch);

		if(!foo(myWord, kelime, ch, len)) {
			printf("hatali harf.\n");
			hang--;
		}

		printf("%s\n", myWord);

		if(strcmp(myWord, kelime) == 0) {
			printf("tebrikler.\n");
			break;
		}
	}

	if(hang==0) {
		printf("you lose\n");
		print();
	}

	free(myWord);

	return 0;
}
