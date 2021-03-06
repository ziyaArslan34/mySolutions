#ifndef _BIG_NUMBER_H_
#define _BIG_NUMBER_H_

#include <stddef.h>

#define MAX_LEN(x,y) ((x) > (y) ? (x) : (y))
#define MIN_LEN(x,y) ((x) < (y) ? (x) : (y))

#define DEFAULT_SIZE 20

struct Bignum {
	char *data;
	size_t size, cap;
};

struct Data {
	int carry, step;
	size_t len1, len2;
	size_t maxLen, minLen;
	const char *sMax, *sMin;
};

typedef struct Bignum bignum_t;
typedef struct Data   data_t;
typedef int    (*Comp)(const void*, const void*);

bignum_t   init(size_t);
bignum_t   init_initValue(const char *);
data_t     init_data(const char*, const char*);
void       print_bignum(const bignum_t*);
char*      parsing_number(const char*);
void       push_back(bignum_t *, char);
void       destroy(bignum_t*);
void       swap(char*, char*);
void       reverse(char*, size_t);
void       sort_array(bignum_t*, size_t size, Comp);
bignum_t   random_big_number(int, int);
int        my_rand(int, int);

bignum_t*  addition(bignum_t*, const char*, const char*);
bignum_t*  multiplication(bignum_t*, const char*, const char*);
bignum_t*  subtraction(bignum_t*, const char*, const char*);
bignum_t*  division(bignum_t*, const char*, const char*);

int        input_control(const char*);
int        data_equal(const void*, const void*);
int        data_less(const void*, const void*);
int        data_greater(const void*, const void*);
int        for_qsort_compare(const void *, const void *);

bignum_t*  operator_plus(bignum_t *, const char*);
bignum_t*  operator_mines(bignum_t*, const char*);

void       debug_function(int);

#endif /* big_number.h */
