#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *data;
	size_t size, cap;
}data_t;

data_t init(size_t n) {
	data_t dt;
	dt.size = 0;
	dt.cap = n;

	dt.data = (char*)malloc(sizeof(char)*dt.cap);
	return dt;
}

void push_back(data_t *dt, const char *src) {
	for(size_t i=0;i<strlen(src);i++) {
		if(dt->size >= dt->cap) {
			dt->cap *= 2;
			dt->data = (char*)realloc(dt->data, sizeof(char)*dt->cap);
		}

		dt->data[dt->size++] = src[i];
	}
}

void swap(char *c1, char *c2) {
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void reverse_s(char *s, size_t size) {
	for(int i=0, j=(int)size-1;i<(int)(size/2) && j >= 0;i++, j--)
		swap(&s[i], &s[j]);
}

void push_back_s(char *s, size_t *size, size_t *cap, char ch) {
	if(*size >= *cap) {
		*cap *= 2;
		s = (char*)realloc(s, sizeof(char)*(*cap));
	}
	s[(*size)++] = ch;
}

data_t text_to_hex(const char *text) {
	data_t data = init(16);

	for(size_t i=0;i<strlen(text);i++) {
		size_t size=0, cap=4;
		char *s = (char*)malloc(sizeof(char)*cap);
		int decimal = (int)text[i];

        while(decimal) {
			int digit = decimal%16;
			char ch;
			if(digit < 10)
				ch = (char)(48+digit);
			else
				ch = (char)(87+digit);
			push_back_s(s,&size, &cap, ch);
			decimal /= 16;
		}

		push_back_s(s, &size, &cap, 'x');
		push_back_s(s, &size, &cap, '\x5c');

		reverse_s(s,size);
		//printf("str: %s\n", s);
		push_back(&data, s);
		free(s);
	}

	push_back(&data, " \0");
	return data;
}

int main() {
	data_t dt = text_to_hex("ziya arslan");

	printf("%s\n", dt.data);
	free(dt.data);
}
