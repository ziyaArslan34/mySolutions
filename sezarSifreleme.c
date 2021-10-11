#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *crypt(char *str, const size_t key, const char type) {
	size_t len = strlen(str), i;

	if(type == 'e') { // encrypt
		char *newStr = (char*)malloc(sizeof(char)*len+1);

		for(i=0;i<len;i++)
			newStr[i] = str[i] + key;

		newStr[i] = '\0';
		return newStr;
	} else if(type == 'd') { // decrypt
		char *newStr = (char*)malloc(sizeof(char)*len+1);

		for(i=0;i<len;i++)
			newStr[i] = str[i] - key;

		newStr[i] = '\0';
		return newStr;
	}

	printf("i dont understand type!\n");
	return NULL;
}

int main() {
	char str[] = "hello", *str1, type='e';
	str1 = crypt(str, 5, type);

	printf("%s\n", str1);
	free(str1);

	printf("%s\n", crypt("test", 5, 't'));

	return 0;
}
