#include <stdio.h>

#include "stack.h"

int main(void) {
	stack_t st = init_stack(10, sizeof(int));

	for(int i=10;i<20;i++)
		push_stack(&st, &i);

	int result = 0, n = (int)st.size;

	while(!empty_stack(&st))
		result += *(int*)pop_stack(&st);
	printf("%d\n", result/n);

	destroy_stack(&st);
}
