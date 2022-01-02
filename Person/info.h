#ifndef _INFO_H_
#define _INFO_H_

typedef struct {
	char **array;
	size_t size, cap;
}type_t;

type_t init(size_t);
void   push_back(type_t *, const char*);
void   destroy(type_t *);
void   splitStr(type_t *, const char*, const char *);
void   printArray(const type_t *);
int    isAlpha(char);
int    findExpr(const char *, char);

#endif
