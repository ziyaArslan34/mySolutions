#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EQUAL -1

typedef struct {
	int hour, min, sec;
}mytime_t;

int          my_rand(int,int);
mytime_t     random_clock();
int          comp_less(const mytime_t*, const mytime_t*);
size_t       clock_to_second(const mytime_t*);
void         clock_sort(mytime_t **, size_t, int(*)(const mytime_t*, const mytime_t*));
mytime_t     get_difference_time(const mytime_t*, const mytime_t*);
const char*  get_current_time();
mytime_t     get_current_clock(const char*);
void         print_clock(const mytime_t*);


int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

mytime_t random_clock() {
	mytime_t tm_ = {my_rand(1,24),my_rand(1,59), my_rand(1,59)};
	return tm_;
}

int comp_less(const mytime_t *t1, const mytime_t *t2) {
	if(t1->hour == t2->hour && t1->min == t2->min && t1->sec == t2->sec)
		return EQUAL;

	if(t1->hour < t2->hour)
		return 1;

	if(t1->hour == t2->hour) {
		if(t1->min < t2->min)
			return 1;
		else if(t1->min == t2->min) {
			if(t1->sec < t2->sec)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}

	return 0;
}

size_t clock_to_second(const mytime_t *mytime) {
	size_t second=0;

	second += (size_t)mytime->sec;
	second += (size_t)mytime->min*60;
	second += (size_t)mytime->hour*60*60;

	return second;
}

void clock_sort(mytime_t **array, size_t size, int (*comp)(const mytime_t*, const mytime_t*)) {
	for(size_t i=0;i<size;i++) {
		for(size_t j=0;j<size;j++) {
			if(comp(&((*array)[i]), &((*array)[j]))) {
				mytime_t temp = (*array)[i];
				(*array)[i] = (*array)[j];
				(*array)[j] = temp;
			}
		}
	}
}

mytime_t get_difference_time(const mytime_t *t1, const mytime_t *t2) {
	mytime_t dftime = {0,0,0};
	mytime_t maxClock = {0,0,0};

	if(comp_less(t1, t2) == EQUAL)
		return dftime;

	if(comp_less(t1, t2)) {
		maxClock = *t2;
		dftime = *t1;
	} else {
		maxClock = *t1;
		dftime = *t2;
	}

	int res = 0;

	while(comp_less(&dftime, &maxClock) != EQUAL) {
		res++;
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

	dftime.hour = res / (60*60);
	dftime.min = (res/60)%60;
	dftime.sec = res % 60;

	return dftime;
}

const char *get_current_time() {
	time_t start = time(NULL);
	const char *get = ctime(&start);
	return get;
}

mytime_t get_current_clock(const char *time) {
        mytime_t tm = {0,0,0};
        char s[10];
        size_t idx = 0;
        int cnt = 0;

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
	printf("\n\n[ ");

	if(myTime->hour <= 9) printf(" 0%d:", myTime->hour);
	else printf(" %d:", myTime->hour);

	if(myTime->min <= 9) printf("0%d:", myTime->min);
	else printf("%d:", myTime->min);

	if(myTime->sec <= 9) printf("0%d ", myTime->sec);
	else printf("%d ", myTime->sec);

	printf(" ]\n\n");
}

int main() {
	srand((unsigned)time(NULL));

	const char* currentTime = get_current_time();
	printf("\n%s\n\n", currentTime);

	mytime_t systemClock = get_current_clock(currentTime);
	print_clock(&systemClock);

	getchar();
	mytime_t *array = (mytime_t*)malloc(sizeof(mytime_t)*10);
	size_t idx=0;

	for(size_t i=0;i<10;i++)
		array[idx++] = random_clock();

	for(size_t i=0;i<idx;i++)
		print_clock(&array[i]);
	clock_sort(&array, idx, comp_less);
	printf("\n\nSiralamadan sonra\n\n");

	for(size_t i=0;i<idx;i++)
		print_clock(&array[i]);

	free(array);
	return 0;
}
