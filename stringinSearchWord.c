#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search(char *string, char *word) {
	int len = strlen(word);
	int count=0, flag;

	for(int i=0;i<strlen(string)-1;i++) {
		flag=0;

		char *temp = (char*)malloc(sizeof(char)*len+1);

		for(int j=i;j<strlen(string);j++) {
			if(len+1 == flag) { break; }
			temp[flag++] = string[j];

		}
		if(temp[len] == ' ') { temp[len] = '\0'; }
		if(strcmp(temp, word) == 0) { count++; }
		free(temp);
	}

	return count;
}

int main() {
	printf("Bir >> %d\n", search("bir berber bir berbere gel beraber bir berber dukkani acalim demis", "bir"));
	printf("Berber >> %d\n", search("bir berber bir berbere gel beraber bir berber dukkani acalim demis", "berber"));

	return 0;
}
