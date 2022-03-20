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

array_t init(size_t lenght) {
	array_t res;
	res.size = 0;
	res.cap = lenght <= 0 ? 10 : lenght;

	if((res.data = (char*)malloc(sizeof(char)*res.cap)) == NULL) {
		perror("");
		exit(1);
	}

	memset(res.data, 0, res.cap);

	return res;
}

int data_less(const array_t *a1, const array_t *a2) {
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

int data_greater(const array_t *a1, const array_t *a2) {
	return !data_less(a1,a2) && !data_equal(a1,a2);
}

int data_equal(const array_t *a1, const array_t *a2) {
	if(a1->size != a2->size)
		return 0;

	for(size_t i=0;i<a1->size;i++)
		if(a1->data[i] != a2->data[i])
			return 0;
	return 1;
}

void debug_function(int loc) { printf("\ndebug: %d\n", loc); }

void addition(array_t *result, const char *num1, const char *num2) {
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

void subtraction(array_t *result, const char *num1, const char *num2) {
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
			if(sMax[i] == 48) {
				data.step = sMax[i] - sMax[j];
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

	free(sMax);
	free(sMin);
}

void division(array_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);

	array_t cnt = init(15);
	array_t tmp = init(15);

	addition(result, data.sMax, "0");

	while(data_less(&tmp, result)) {
		array_t res = init(15);

		operator_plus_plus(&cnt);
		addition(&res, tmp.data, data.sMin);
		destroy(&tmp);
		tmp = res;
	}

	destroy(result);
	*result = cnt;
}

void multiplication(array_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);

	array_t *adds = NULL;

	if((adds = (array_t*)malloc(sizeof(array_t)*data.minLen)) == NULL) {
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
		array_t sum = init(15);
		addition(&sum, result->data, adds[i].data);
		destroy(result);
		*result = sum;
	}

	for(size_t i=0;i<data.minLen;i++)
		destroy(&adds[i]);
	free(adds);
}

void push_back(array_t *arr, char ch) {
	if(arr->data == NULL) {
		arr->cap = 18;
		if((arr->data = (char*)malloc(sizeof(char)*arr->cap)) == NULL) {
			perror("");
			exit(1);
		}
	}

	if(arr->size >= arr->cap) {
		arr->cap *= 2;
		if((arr->data = (char*)realloc(arr->data, sizeof(char)*arr->cap)) == NULL) {
			perror("");
			exit(1);
		}
	}

	arr->data[arr->size++] = ch;
}

void operator_plus_plus(array_t *arr) {
	array_t tmp = init(15);
	addition(&tmp, arr->data, "1");
	destroy(arr);
	*arr = tmp;
}

void operator_mines_mines(array_t *arr) {
	array_t tmp = init(15);
	subtraction(&tmp, arr->data, "1");
	destroy(arr);
	*arr = tmp;
}

void destroy(array_t *arr) {
	arr->size = 0;
	arr->cap = 0;
	arr->data = NULL;
	free(arr->data);
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
	return s[0] != 48 && strlen(s) >= 1;
}
