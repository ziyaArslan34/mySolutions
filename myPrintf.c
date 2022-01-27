#include <stdio.h>
#include <stdarg.h>

void foo(const char *fmt, ...) {
	va_list v;
	va_start(v, fmt);

	for(size_t i=0;i<strlen(fmt);i++) {
		switch(fmt[i]) {
			case 'i':
				printf("%d ", va_arg(v,int));
				break;
			case 'c':
				printf("%c ", va_arg(v,int));
				break;
			case 's':
				printf("%s ", va_arg(v,char*));
				break;
			case 'd':
				printf("%lf ", va_arg(v, double));
				break;
		}
	}

	va_end(v);
}

int main() {
	foo("cidcdsis",'A', 10,2.5, 'B',12.3, "str",34, "\n");
}
