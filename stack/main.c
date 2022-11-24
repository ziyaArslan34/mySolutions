#include <stdio.h>

#include "stack.h"

int main(void) {
	stack_t st = init_stack(10, sizeof(int));

	for(int i=10;i<25;i++)
		push_stack(&st, &i);

	for(size_t i=0;i<10;i++)
		printf("%d\n", *(int*)pop_stack(&st));
	destroy_stack(&st);
}
