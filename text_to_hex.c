#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *data;
	size_t size, cap;
}data_t;

data_t init(size_t);
void   push_back_s(data_t*, const char*, size_t);
void   push_back_c(data_t*,char);
void   swap(char*, char*);
void   reverse(char*, size_t);
data_t text_to_hex(const char*);


data_t init(size_t n) {
	data_t dt;
	dt.size = 0;
	dt.cap = n;

	dt.data = (char*)malloc(sizeof(char)*dt.cap);
	return dt;
}

void push_back_s(data_t *dt, const char *src, size_t len) {
	for(size_t i=0;i<len;i++)
		push_back_c(dt, src[i]);
}

void swap(char *c1, char *c2) {
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void reverse(char *s, size_t size) {
	for(int i=0, j=(int)size-1;i<(int)(size/2) && j >= 0;i++, j--)
		swap(&s[i], &s[j]);
}

void push_back_c(data_t *s, char ch) {
	if(s->size >= s->cap) {
		s->cap *= 2;
		s->data = (char*)realloc(s->data, sizeof(char)*s->cap);
	}
	s->data[s->size++] = ch;
}

data_t text_to_hex(const char *text) {
	data_t data = init(16);

	for(size_t i=0;i<strlen(text);i++) {
		data_t s = init(4);

		int decimal = (int)text[i];

		while(decimal) {
			int digit = decimal%16;
			char ch;
			if(digit < 10)
				ch = (char)(48+digit);
			else
				ch = (char)(87+digit);
			push_back_c(&s,ch);
			decimal /= 16;
		}

		push_back_c(&s,'x');
		push_back_c(&s,'\x5c');

		reverse(s.data,s.size);
		//printf("str: %s\n", s);
		push_back_s(&data, s.data, s.size);
		free(s.data);
	}

	push_back_s(&data, " \0", 3);
	return data;
}

int main() {
	char str[1024];
	printf("enter text: ");
	fgets(str, 1024, stdin);

	data_t dt = text_to_hex(str);

	printf("%s\n", dt.data);
	free(dt.data);
}
