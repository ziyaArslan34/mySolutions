#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "big_number.h"

data_t init_data(const char *s1, const char *s2) {
	data_t data;

	data.carry = 0;
	data.step = 0;
	data.len1 = strlen(s1);
	data.len2 = strlen(s2);
	data.maxLen = MAX_LEN(data.len1, data.len2);
	data.minLen = MIN_LEN(data.len1, data.len2);
	data.sMax = data.maxLen == data.len1 ? s1 : s2;
	data.sMin = data.minLen == data.len2 ? s2 : s1;

	return data;
}

bignum_t init(size_t length) {
	bignum_t bignum;
	bignum.size = 0;
	bignum.cap = length <= 0 ? DEFAULT_SIZE : length;

	if((bignum.data = (char*)malloc(sizeof(char)*bignum.cap)) == NULL) {
		perror("");
		exit(1);
	}

	memset(bignum.data, 0, bignum.cap);

	return bignum;
}

void sort_array(bignum_t *array,size_t size, comp fptr) {
	qsort(array, size, sizeof(bignum_t), fptr);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

bignum_t random_big_number(void) {
	bignum_t number = init(DEFAULT_SIZE);
	int step = my_rand(10,40);
	push_back(&number, (char)my_rand('1', '9'));

	for(int i=1;i<step;i++)
		push_back(&number, (char)my_rand('0', '9'));

	push_back(&number, '\0');
	return number;
}

char *parsing_number(const char *str) {
        size_t len = strlen(str);
        size_t size=0, cap=len+(len/3)+1, cnt=0;

        char *pars = NULL;
        if((pars = (char*)malloc(sizeof(char)*cap)) == NULL) {
                fprintf(stderr, "memory error!\n");
                exit(1);
        }

        for(int i=(int)len-1;i>=0;i--) {
                if(size >= cap) {
                        cap *= 2;
                        if((pars = (char*)realloc(pars, sizeof(char)*cap)) == NULL) {
                                fprintf(stderr, "memory error!\n");
                                exit(1);
                        }
                }

                if(cnt && cnt % 3 == 0)
                        pars[size++] = '.';
                pars[size++] = str[i];
                cnt++;
        }

        pars[size++] = '\0';
        reverse(pars, size-1);
        return pars;
}

void print_bignum(const bignum_t *bignum) {
	char *str = parsing_number(bignum->data);
	printf("%s\n", str);
	free(str);
	printf("\n\n");
}

void prefix_del_zero(size_t typeSize, void *array, size_t size, int counter, const char *direction) {
	if(!strcmp(direction, "right")) {
		for(int i=0;i<counter;i++) {
			void *tmp = malloc(typeSize);
			memcpy(tmp, (char*)array+((size-1)*typeSize), typeSize);
			for(int j=(int)size-1;j>0;j--)
				memcpy((char*)array+(size_t)j*typeSize, (char*)array+((size_t)(j-1)*typeSize), typeSize);
			memcpy((char*)array+0*typeSize, tmp, typeSize);
			free(tmp);
		}
	} else if(!strcmp(direction, "left")) {
		for(int i=0;i<counter;i++) {
			void *tmp = malloc(typeSize);
			memcpy(tmp, (char*)array+0*typeSize, typeSize);
			for(size_t j=0;j<size-1;j++)
				memcpy((char*)array+j*typeSize, (char*)array+((j+1)*typeSize), typeSize);
			memcpy((char*)array+((size-1)*typeSize), tmp, typeSize);
		}
	} else {
		fprintf(stderr, "not direction.!\n");
	}
}

void suffix_del_bad_char(char *array, size_t size) {
	int i;
	for(i=(int)size-1;i >= 0 && !(array[i] >= '0' && array[i] <= '9');i--) {}
	array[i+1] = '\0';
}

int data_less(const void *a1, const void *a2) {
	const bignum_t *x = (const bignum_t*)a1;
	const bignum_t *y = (const bignum_t*)a2;

	if(x->size == y->size)
		return strcmp(x->data, y->data) > 0;
	return x->size > y->size;
}

int data_greater(const void *a1, const void *a2) {
	return !data_less(a1,a2) && !data_equal(a1,a2);
}

int data_equal(const void *a1, const void *a2) {
	const bignum_t *x = (const bignum_t*)a1;
	const bignum_t *y = (const bignum_t*)a2;
	if(x->size != y->size)
		return 0;

	for(size_t i=0;i<x->size;i++)
		if(x->data[i] != y->data[i])
			return 0;
	return 1;
}

void debug_function(int loc) { printf("\ndebug: %d\n", loc); }

bignum_t* addition(bignum_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);
	int i,j;

	for(i=(int)data.maxLen-1, j=(int)data.minLen-1;j>=0;j--,i--) {
		data.step = (data.sMax[i] - '0') + (data.sMin[j] - '0') + data.carry;
		if(i == 0) {
			while(data.step) {
				push_back(result, (char)(data.step%10) + '0');
				data.step /= 10;
			}
		} else {
			push_back(result, (char)(((data.step%10)) + '0'));
			data.carry = (data.step/10)%10;
		}
	}

	for(;i>=0;i--) {
		data.step = (data.sMax[i] - '0') + data.carry;
		if(i != 0) {
			if(data.step >= 10) {
				push_back(result, (char)(data.step%10) + '0');
				data.carry = (data.step/10)%10;
			} else {
				push_back(result, (char)data.step+'0');
				data.carry = (data.step/10)%10;
			}
		} else {
			while(data.step) {
				push_back(result, (char)(data.step%10) + '0');
				data.step /= 10;
			}
		}
	}

	reverse(result->data, result->size);
	push_back(result, '\0');

	return result;
}

bignum_t* subtraction(bignum_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);
	int i,j;

	char *sMax = NULL, *sMin = NULL;
	if((sMax = (char*)malloc(sizeof(char)*data.maxLen+1)) == NULL || (sMin = (char*)malloc(sizeof(char)*data.minLen+1)) == NULL){
		perror("");
		exit(1);
	}

	strcpy(sMax, data.sMax);
	strcpy(sMin, data.sMin);

	for(i=(int)data.maxLen-1, j=(int)data.minLen-1;j>=0;j--, i--) {
		if((sMax[i] + '0') < (sMin[j] + '0')) {
			if(sMax[i] == '0') {
				data.step = ((sMax[i]-'0') + 10) - (sMin[j]-'0');
				int m;
				for(m=i-1;sMax[m] == '0' && m>=0;m--)
					sMax[m] = '9';
				sMax[m]--;
				push_back(result, (char)data.step+'0');
			} else {
				sMax[i-1]--;
				data.step = ((sMax[i]-'0')+10) - (sMin[j]-'0');
				push_back(result, (char)data.step+'0');
			}
		} else {
			data.step = sMax[i] - sMin[j];
			push_back(result, (char)data.step+'0');
		}
	}

	for(;i>=0;i--)
		push_back(result, sMax[i]);

	reverse(result->data, result->size);
	push_back(result, '\0');

	int counter = 0;
	for(size_t i=0;result->data[i] == '0';i++)
		counter++;
	prefix_del_zero(sizeof(char), result->data, result->size, counter-1, "left");
	//suffix_del_bad_char(result->data, result->size);

	free(sMax);
	free(sMin);

	return result;
}

bignum_t* division(bignum_t *result, const char *num1, const char *num2) {
	if(!strcmp(num1, "0") || !strcmp(num2, "0")) {
		fprintf(stderr, "zero by division!!.\n");
		return NULL;
	}

	data_t data = init_data(num1, num2);

	bignum_t max = init(10), cnt = init(10), min = init(10);

	for(size_t i=0;i<data.maxLen;i++)
		push_back(&max, data.sMax[i]);
	push_back(&max, '\0');

	while(data_less(&min, &max) || data_equal(&max, &min)) {
		operator_plus(&min, data.sMin);
		operator_plus(&cnt, "1");
	}

	operator_mines(&cnt, "1");
	destroy(result);
	destroy(&max);
	destroy(&min);

	*result = cnt;

	return result;
}

bignum_t* multiplication(bignum_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);

	bignum_t *adds = NULL;

	if((adds = (bignum_t*)malloc(sizeof(bignum_t)*data.minLen)) == NULL) {
		perror("");
		exit(1);
	}

	for(size_t i=0;i<data.minLen;i++)
		adds[i] = init(DEFAULT_SIZE);
	size_t idx=0;

	for(int i=(int)data.minLen-1;i>=0;i--) {
		for(size_t m=0;m<idx;m++)
			push_back(&adds[idx], '0');
		data.carry = 0;

		for(int j=(int)data.maxLen-1;j>=0;j--) {
			data.step = ((data.sMax[j] - '0') * (data.sMin[i] - '0')) + data.carry;
			if(j) {
				push_back(&adds[idx], (char)(data.step%10) + '0');
				data.carry = (data.step/10)%10;
			} else {
				while(data.step) {
					push_back(&adds[idx], (char)(data.step%10) + '0');
					data.step /= 10;
				}
			}
		}
		reverse(adds[idx].data, adds[idx].size);
		push_back(&adds[idx++], '\0');
	}

	for(size_t i=0;i<idx;i++) {
		operator_plus(result, adds[i].data);
	}

	for(size_t i=0;i<data.minLen;i++)
		destroy(adds+i);
	free(adds);

	return result;
}

void push_back(bignum_t *bignum, char digit) {
	if(bignum->data == NULL)
		*bignum = init(DEFAULT_SIZE);

	if(bignum->size >= bignum->cap) {
		bignum->cap *= 2;
		if((bignum->data = (char*)realloc(bignum->data, sizeof(char)*bignum->cap)) == NULL) {
			perror("");
			exit(1);
		}
	}

	bignum->data[bignum->size++] = digit;
}

bignum_t *operator_plus(bignum_t *bignum, const char *n) {
	bignum_t tmp = init(DEFAULT_SIZE);
	addition(&tmp, bignum->data, n);
	destroy(bignum);
	*bignum = tmp;

	return bignum;
}

bignum_t *operator_mines(bignum_t *bignum, const char *n) {
	bignum_t tmp = init(DEFAULT_SIZE);
	subtraction(&tmp, bignum->data, n);
	destroy(bignum);
	*bignum = tmp;

	return bignum;
}

void destroy(bignum_t *bignum) {
	bignum->size = 0;
	bignum->cap = 0;
	free(bignum->data);
	bignum->data = NULL;
}

void swap(char *i, char *j) {
	char temp = *i;
	*i = *j;
	*j = temp;
}

void reverse(char *array, size_t len) {
	char *pend = array+len;

	while(array < pend)
		swap(array++, --pend);
}

int input_control(const char *s) {
	for(size_t i=0;i<strlen(s);i++)
		if(!(s[i] >= '0' && s[i] <= '9'))
			return 0;
	return strlen(s) == 1 ? 1 : s[0] != '0';
}
