#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *substr(const char *str, size_t begin, size_t end, size_t len) {
	size_t sLen = strlen(str);
	if(begin >= sLen || end > sLen || begin < 0 || end < 0)
		return NULL;

	char *newS = (char*)malloc(sizeof(char)*len+1);

	size_t idx=0;
	while(begin != end)
		newS[idx++] = str[begin++];
	newS[idx++] = '\0';

	return newS;
}

void parsing(const char *str, size_t n) {
	if(n == 0 || n == 1) {
		printf("%s\n", str);
		return;
	}

	size_t sLen = strlen(str) / n;
	size_t start=0;

	for(size_t i=0;i<n;i++) {
		size_t begin, end;
		begin = start;
		end = i < n-1 ? sLen+start : strlen(str);
		start += sLen;

		char *s = NULL;

		if((s = substr(str, begin, end, sLen)) != NULL) {
			printf("%s\n", s);
			free(s);
		} else {
			printf("NULL\n");
		}
	}
}

int main() {
	const char *str = "7010987596263049368";
	parsing(str,strlen(str)/3);
}
