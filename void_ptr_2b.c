#include <stdio.h>

void f(const void *ptr, size_t row, size_t col, size_t type, void (*fptr)(const void*)) {
	for(size_t i=0;i<row*col;i++) {
			int ch = *((char*)ptr+i*type);
			fptr(&ch);
	}

	printf("\n");
}

void p_int(const void *val) { printf(" [%d] ", *(int*)val); }
void p_char(const void *val) { printf(" [%c] ", *(char*)val); }

int main() {
	char str[2][4] = {{'z','i','y','a'}, {'a','r','s','l'}};

	int arr[2][4] = {{1,2,3,4},{6,7,8,9}};

	f(str, 2, 4, sizeof(char), p_char);

	f(arr, 2, 4, sizeof(int), p_int);
}
