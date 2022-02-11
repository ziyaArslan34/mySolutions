#ifndef _SPLIT_H_
#define _SPLIT_H_
#include <stddef.h>

typedef struct {
	char **array;
	size_t size, cap;
}type_t;

type_t       init(size_t);
int          is_alpha(char);
int          expr_find(const char*, char);
int          search(const type_t*, const char*);
const char*  return_ip(const type_t*);
void         push_back_split(type_t*, const char*);
type_t       split_str(const char*, const char*);
void         print_split(const type_t*);
void         destroy_split(type_t*);

#endif
