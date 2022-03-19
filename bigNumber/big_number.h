#ifndef _BIG_NUMBER_H_
#define _BIG_NUMBER_H_

#include <stddef.h>

#define MAX_LEN(x,y) ((x) > (y) ? (x) : (y))
#define MIN_LEN(x,y) ((x) < (y) ? (x) : (y))

typedef struct {
        char *data;
        size_t size, cap;
}array_t;

typedef struct {
        int carry, step;
        size_t len1, len2;
        size_t maxLen, minLen;
        const char *sMax, *sMin;
}data_t;

array_t  init(size_t);
data_t   init_data(const char*, const char*);

void     push_back(array_t *, char);
void     destroy(array_t*);
void     swap(char*, char*);
void     reverse(char*, size_t);

void     addition(array_t*, const char*, const char*);
void     multiplication(array_t*, const char*, const char*);
void     subtraction(array_t*, const char*, const char*);
void     division(array_t*, const char*, const char*);

int      input_control(const char*);
int      data_equal(const array_t*, const array_t*);
int      data_less(const array_t*, const array_t*);
int      data_greater(const array_t*, const array_t*);

void     operator_plus_plus(array_t *);
void     operator_mines_mines(array_t*);

void     debug_function(int);

#endif /* big_number.h */
