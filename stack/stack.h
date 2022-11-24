#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

struct Stack {
	void *data;
	size_t size, cap;
	size_t type;
};

typedef struct Stack stack_t;

stack_t   init_stack(size_t, size_t);
int       empty_stack(const stack_t*);
void      push_stack(stack_t *, const void *);
void*     pop_stack(stack_t *);
void      destroy_stack(stack_t*);

#endif /* stack.h */
