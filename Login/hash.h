#ifndef _HASH_H_
#define _HASH_H_

#define get_min(m1, m2) ((m1) < (m2) ? (m1) : (m2))

#include <stddef.h>

struct hash {
	int *data;
	size_t cap;
	size_t size;
	int key;
};

struct array {
	int *data;
	size_t cap, size;
};

typedef struct array array_t;
typedef struct hash hash_t;

int      my_rand(int, int);
hash_t   init_hash();
array_t  init_array(size_t);
void     push_back(array_t*, int);
void     push_back_hash(hash_t *, int);
int      comp_hash(const hash_t*, const hash_t*);
void     swap(void*, void*, size_t);
void     reverse_array(int*, size_t);
void     encrypt(hash_t*, const char*);
char*    decrypt(const hash_t *);
void     print_hash(const hash_t*);
void     print_array(const array_t*);
void     destroy_hash(hash_t*);
void     destroy_array(array_t*);

#endif
