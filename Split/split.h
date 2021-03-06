#ifndef _SPLIT_H_
#define _SPLIT_H_
#include <stddef.h>

typedef struct {
	char **array;
	size_t size, cap;
}split_t;

split_t      init_split(size_t);
int          is_alpha(char);
int          expr_find(const char*, char);
int          search_split(const split_t*, const char*);
void         push_back_split(split_t*, const char*);
split_t*     str_split(split_t *, const char*, const char*);
void         print_split(const split_t*);
void         destroy_split(split_t*);

#endif
