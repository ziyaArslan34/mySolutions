#include <stdio.h>

#define make_function(T) void print_##T(T val) {\
	printf("[ ");\
	if(strcmp(#T, "int") == 0) {\
		for(int i=(int)sizeof(val)*8-1;i>=0;i--)\
			putchar(((val & 1 << i) ? '1' : '0'));\
	} else if(strcmp(#T, "short") == 0) {\
		for(int i=(int)sizeof(val)*8-1;i>=0;i--)\
			putchar(((val & 1 << i) ? '1' : '0'));\
	} else if(strcmp(#T, "char") == 0) {\
		for(int i=(int)sizeof(val)*8-1;i>=0;i--)\
			putchar(((val & 1 << i) ? '1' : '0'));\
	}\
	puts(" ]");\
}

make_function(int);
make_function(short);
make_function(char);

int main() {
	int x=97;
	short y=97;
	char z=97;

	print_int(x);
	print_char(z);
	print_short(y);
}
