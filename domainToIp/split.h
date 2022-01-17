#ifndef _SPLIT_H_
#define _SPLIT_H_
#include <stddef.h>

typedef struct {
	char **array;
	size_t size, cap;
}type_t;

type_t    init(size_t);
int       isAlpha(char);
int       exprFind(const char*, char);
int       search(const type_t*, const char*);
void      push_back(type_t*, const char*);
type_t    createWord(const char*, const char*);
void      printArray(const type_t*);
void      destroy(type_t*);

#endif
