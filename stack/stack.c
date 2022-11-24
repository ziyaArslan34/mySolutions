#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

stack_t init_stack(size_t cap, size_t type) {
	stack_t st;
	st.size = 0;
	st.cap = cap;
	st.type = type;

	if((st.data = malloc(type*cap)) == NULL)
		exit(-1);

	return st;
}

int empty_stack(const stack_t *st) {
	return st->size == 0;
}

void push_stack(stack_t *st, const void *data) {
	if(st->size >= st->cap) {
		fprintf(stderr, "stack dolu\n");
		return;
	}

	memcpy((char*)st->data + st->size * st->type, data, st->type);
	++st->size;
}

void *pop_stack(stack_t *st) {
	if(empty_stack(st))
		return NULL;
	--st->size;
	return (char*)st->data + (st->size) * st->type;
}

void destroy_stack(stack_t *st) {
	st->size = 0;
	st->cap = 0;
	free(st->data);
}
