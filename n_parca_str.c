#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *substr(const char *str, size_t begin, size_t end, size_t len) {
	char *newS = (char*)malloc(sizeof(char)*len+1);

	size_t i, idx=0;
	for(i=begin;i<end;i++)
		newS[idx++] = str[i];
	newS[idx++] = '\0';

	return newS;
}

void foo(const char *str, size_t n) {
	if(n == 0 || n == 1 || n >= strlen(str) || (strlen(str)/n) <= n) {
		printf("%s\n", str);
		return;
	}

	size_t sLen = strlen(str) / n;
	size_t start=0;

	for(size_t i=0;i<n;i++) {
		size_t begin, end;
		begin = start;
		end = sLen+start;
		start += sLen;

		//printf("\n\nsLen{ %zu }, begin { %zu }, end { %zu }, start { %zu }\n\n", sLen, begin, end, start);

		char *s = substr(str, begin, end, sLen);

		printf("%s\n", s);
		free(s);
	}
}

int main() {
	const char *str = "ziya arslan learning C++";
	foo(str, 4);
}
