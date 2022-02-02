#include <stdio.h>

void print_2b_array(const void *ptr, size_t row, size_t col,
	size_t type, void (*fptr)(const void*)) {
	for(size_t i=0;i<row*col;i++)
			fptr(&*((char*)ptr+i*type));
	printf("\n");
}

struct test { int x,y; };

void p_int(const void *val) { printf(" [%d] ", *(int*)val); }
void p_char(const void *val) { printf(" [%c] ", *(char*)val); }
void p_str(const void *val) { printf(" [%s] ", (char*)val); }
void p_user(const void *val) { printf(" [%d] [%d] ",((struct test*)val)->x, ((struct test*)val)->y); }

int main() {
	char s[2][3][5] = {
		{"test", "arsl","abcd"},
		{"tset","lsra","dcba"}
	};

	print_2b_array(s,2,3,5,p_str);

	struct test t[2][2] = {
		{{0,1},{2,3}}, {{4,5},{6,7}}
	};

	print_2b_array(t,2,2,sizeof(struct test), p_user);
}
