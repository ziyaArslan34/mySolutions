#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <stddef.h>

struct Clock {
	int hour, min, sec;
};

typedef struct Clock mytime_t;

int          my_rand(int,int);
mytime_t     random_clock(void);
int          time_cmp(const void*, const void*);
size_t       clock_to_second(const mytime_t*);
mytime_t     second_to_clock(size_t);
void         clock_sort(mytime_t *, size_t, int(*)(const void*, const void*));
mytime_t     get_difference_time(const mytime_t*, const mytime_t*);
const char*  get_current_time(void);
mytime_t     get_current_clock(const char*);
void         print_clock(const mytime_t*);

#endif /* clock.h */
