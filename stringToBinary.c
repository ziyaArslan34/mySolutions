#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *makeBinary(const char *str) {
	size_t index=0, cap=8;

	char *newStr = (char*)malloc(sizeof(char)*cap);

	for(int i=0;i<strlen(str);i++) {
		if(str[i] != '\x20') {
			for(int j=7;j>=0;j--) {
				if(str[i] & (1U << j)) {
					if(index >= cap) {
						cap *= 2;
						newStr = (char*)realloc(newStr, sizeof(char)*cap);
					}
					newStr[index++] = '1';
				} else {
					if(index >= cap) {
						cap *= 2;
						newStr = (char*)realloc(newStr, sizeof(char)*cap);
					}
					newStr[index++] = '0';
				}
			}

			if(index >= cap) {
				cap *= 2;
				newStr = (char*)realloc(newStr, sizeof(char)*cap);
			}
			newStr[index++] = '\x20';
		}
	}

	return newStr;
}

int main() {
	char str[1024];

	printf("yaz: ");
	fgets(str, sizeof(str), stdin);
	str[strlen(str)-1] = '\0';


	printf("%s\n", makeBinary(str));
	return 0;
}
