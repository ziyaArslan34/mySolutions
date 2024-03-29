#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clock.h"

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

mytime_t random_clock(void) {
	return (mytime_t){my_rand(1,24), my_rand(1,59), my_rand(1,59)};
}

int time_cmp(const void *tm1, const void *tm2) {
	// /* kotu gozukmesin diye bu iptal :) */return (t1->hour == t2->hour && t1->min == t2->min && t1->sec == t2->sec) ? EQUAL : ((t1->hour < t2->hour) ? 1 : (!(t1->hour == t2->hour) ? 0 : (t1->min < t2->min) ? 1 : (t1->min == t2->min) ? ((t1->sec < t2->sec) ? 1 : 0) : 0));

	const mytime_t *t1 = (const mytime_t*)tm1;
	const mytime_t *t2 = (const mytime_t*)tm2;

	return clock_to_second(t1) - clock_to_second(t2);
}

size_t clock_to_second(const mytime_t *t) {
	return (size_t)(t->sec + (t->min*60) + (t->hour*3600));
}

mytime_t second_to_clock(size_t sec) {
	return (mytime_t){sec / 3600, (sec/60)%60, sec % 60};
}

void clock_sort(mytime_t *array, size_t size, int (*comp)(const void*, const void*)) {
	for(size_t i=0;i<size;i++) {
		for(size_t j=0;j<size-1;j++) {
			if(comp(&array[i], &array[j]) < 0) {
				mytime_t temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

mytime_t get_difference_time(const mytime_t *t1, const mytime_t *t2) {
	mytime_t dftime = {0,0,0};
	mytime_t maxClock = {0,0,0};

	if(!time_cmp(t1, t2))
		return dftime;

	time_cmp(t1, t2) < 0 ? ({maxClock = *t2 ; dftime = *t1;})
							: ({maxClock = *t1 ; dftime = *t2;});

	size_t second = 0;

	while(time_cmp(&dftime, &maxClock) < 0) {
		second++;
		dftime.sec++;

		if(dftime.sec == 60) {
			dftime.sec = 0;
			dftime.min++;
			if(dftime.min == 60) {
				dftime.min = 0;
				dftime.hour++;
			}
		}
	}

	return second_to_clock(second);
}

const char *get_current_time(void) {
	time_t start = time(NULL);
	return ctime(&start);
}

mytime_t get_current_clock(const char *time) {
	mytime_t tm = {0,0,0};
	char s[10];

	size_t idx = 0, cnt = 0;

	for(size_t i=0;i<strlen(time);i++) {
		if(time[i] == ' ')
			cnt++;
		if(cnt == 3) {
			for(size_t j=i+1;time[j] != ' ';j++)
				s[idx++] = time[j];
			break;
		}
	}
	s[idx++] = '\0';

	sscanf(s, "%d:%d:%d", &tm.hour, &tm.min, &tm.sec);
	return tm;
}

void print_clock(const mytime_t *myTime) {
	printf(" [ ");

	if(myTime->hour <= 9) printf(" 0%d:", myTime->hour);
	else printf(" %d:", myTime->hour);

	if(myTime->min <= 9) printf("0%d:", myTime->min);
	else printf("%d:", myTime->min);

	if(myTime->sec <= 9) printf("0%d ", myTime->sec);
	else printf("%d ", myTime->sec);

	printf(" ]\n\n");
}
