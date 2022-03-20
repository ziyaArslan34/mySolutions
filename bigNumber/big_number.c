#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "big_number.h"

data_t init_data(const char*s1, const char *s2) {
	data_t data;

	data.carry = 0;
	data.step=0;
	data.len1 = strlen(s1);
	data.len2 = strlen(s2);
	data.maxLen = MAX_LEN(data.len1, data.len2);
	data.minLen = MIN_LEN(data.len1, data.len2);
	data.sMax = data.maxLen == data.len1 ? s1 : s2;
	data.sMin = data.minLen == data.len2 ? s2 : s1;

	return data;
}

bignum_t init(size_t lenght) {
	bignum_t bignum;
	bignum.size = 0;
	bignum.cap = lenght <= 0 ? 10 : lenght;

	if((bignum.data = (char*)malloc(sizeof(char)*bignum.cap)) == NULL) {
		perror("");
		exit(1);
	}

	memset(bignum.data, 0, bignum.cap);

	return bignum;
}

static void prefix_del_zero(size_t typeSize, void *array, size_t size, int counter, const char *direction) {
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

static void suffix_del_bad_char(char *array, size_t size) {
	int i;
	for(i=(int)size-1;i >= 0 && !(array[i] >= 48 && array[i] <= 57);i--) {}
	array[i+1] = '\0';
}

int data_less(const bignum_t *a1, const bignum_t *a2) {
	if(a1->size < a2->size)
		return 1;
	if(a1->size > a2->size)
		return 0;

	for(size_t i=0;i<a1->size;i++) {
		if(a1->data[i] > a2->data[i])
			return 0;
		else if(a1->data[i] < a2->data[i])
			return 1;
	}

	return 0;
}

int data_greater(const bignum_t *a1, const bignum_t *a2) {
	return !data_less(a1,a2) && !data_equal(a1,a2);
}

int data_equal(const bignum_t *a1, const bignum_t *a2) {
	if(a1->size != a2->size)
		return 0;

	for(size_t i=0;i<a1->size;i++)
		if(a1->data[i] != a2->data[i])
			return 0;
	return 1;
}

void debug_function(int loc) { printf("\ndebug: %d\n", loc); }

void addition(bignum_t *result, const char *num1, const char *num2) {
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
}

void subtraction(bignum_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);
	int i,j, counter=0;

	char *sMax = NULL, *sMin = NULL;
	if((sMax = (char*)malloc(sizeof(char)*data.maxLen+1)) == NULL || (sMin = (char*)malloc(sizeof(char)*data.minLen+1)) == NULL){
		perror("");
		exit(1);
	}

	strcpy(sMax, data.sMax);
	strcpy(sMin, data.sMin);

	for(i=(int)data.maxLen-1, j=(int)data.minLen-1;j>=0;j--, i--) {
		if((sMax[i] + '0') < (sMin[j] + '0')) {
			if(sMax[i] == 48) {
				data.step = ((sMax[i]-'0') + 10) - (sMin[j]-'0');
				int m;
				for(m=i-1;sMax[m] == 48 && m>=0;m--)
					sMax[m] = 57;
				sMax[m]--;
				push_back(result, (char)data.step+'0');
			} else {
				sMax[i-1]--;
				data.step = sMax[i] - sMin[j];
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

	for(size_t i=0;result->data[i] == 48;i++)
		counter++;
	prefix_del_zero(sizeof(char), result->data, result->size, counter, "left");
	suffix_del_bad_char(result->data, result->size);

	free(sMax);
	free(sMin);
}

void division(bignum_t *result, const char *num1, const char *num2) {
	if(!strcmp(num1, "0") || !strcmp(num2, "0")) {
		fprintf(stderr, "zero by division!!.\n");
		return;
	}

	data_t data = init_data(num1, num2);

	bignum_t cnt = init(15);
	bignum_t tmp = init(15);

	addition(result, data.sMax, "0");

	while(data_less(&tmp, result)) {
		bignum_t res = init(15);

		operator_plus_plus(&cnt);
		addition(&res, tmp.data, data.sMin);
		destroy(&tmp);
		tmp = res;
	}

	destroy(result);
	*result = cnt;
}

void multiplication(bignum_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);

	bignum_t *adds = NULL;

	if((adds = (bignum_t*)malloc(sizeof(bignum_t)*data.minLen)) == NULL) {
		perror("");
		exit(1);
	}

	for(size_t i=0;i<data.minLen;i++)
		adds[i] = init(15);
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
		bignum_t sum = init(15);
		addition(&sum, result->data, adds[i].data);
		destroy(result);
		*result = sum;
	}

	for(size_t i=0;i<data.minLen;i++)
		destroy(&adds[i]);
	free(adds);
}

void push_back(bignum_t *bignum, char digit) {
	if(bignum->data == NULL)
		*bignum = init(18);

	if(bignum->size >= bignum->cap) {
		bignum->cap *= 2;
		if((bignum->data = (char*)realloc(bignum->data, sizeof(char)*bignum->cap)) == NULL) {
			perror("");
			exit(1);
		}
	}

	bignum->data[bignum->size++] = digit;
}

void operator_plus_plus(bignum_t *bignum) {
	bignum_t tmp = init(15);
	addition(&tmp, bignum->data, "1");
	destroy(bignum);
	*bignum = tmp;
}

void operator_mines_mines(bignum_t *bignum) {
	bignum_t tmp = init(15);
	subtraction(&tmp, bignum->data, "1");
	destroy(bignum);
	*bignum = tmp;
}

void destroy(bignum_t *bignum) {
	bignum->size = 0;
	bignum->cap = 0;
	bignum->data = NULL;
	free(bignum->data);
}

void swap(char *i, char *j) {
	char temp = *i;
	*i = *j;
	*j = temp;
}

void reverse(char *array, size_t len) {
	for(int i=0, j=(int)len-1;i<(int)len/2;i++, j--)
		swap(&array[i], &array[j]);
}

int input_control(const char *s) {
	for(size_t i=0;i<strlen(s);i++)
		if(!(s[i] >= 48 && s[i] <= 57))
			return 0;
	return strlen(s) == 1 ? 1 : s[0] != 48;
}
