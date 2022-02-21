#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN(x,y) ((x) > (y) ? (x) : (y))
#define MIN_LEN(x,y) ((x) < (y) ? (x) : (y))

typedef struct {
	char *data;
	size_t size, cap;
}array_t;

typedef struct {
	int get, step;
	size_t sLen1, sLen2;
	size_t maxLen, minLen;
	const char *sMax, *sMin;
}data_t;

array_t init(size_t);
data_t  init_data(const char*, const char*);
void    push_back(array_t *, char);
void    destroy(array_t*);
void    swap(char*, char*);
void    reverse(char*, size_t);
void    addition(array_t*, const char*, const char*);
void    multiplication(array_t*, const char*, const char*);
void    subtraction(array_t*, const char*, const char*, char);
void    division(array_t*, const char*, const char*);

data_t init_data(const char*s1, const char *s2) {
	data_t data;

	data.get = 0;
	data.step=0;
	data.sLen1 = strlen(s1);
	data.sLen2 = strlen(s2);
	data.maxLen = MAX_LEN(data.sLen1, data.sLen2);
	data.minLen = MIN_LEN(data.sLen1, data.sLen2);
	data.sMax = data.maxLen == data.sLen1 ? s1 : s2;
	data.sMin = data.minLen == data.sLen2 ? s2 : s1;

	return data;
}

void addition(array_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);
	int i,j;

	for(i=(int)data.maxLen-1, j=(int)data.minLen-1;j>=0;j--,i--) {
		data.step = (data.sMax[i] - '0') + (data.sMin[j] - '0') + data.get;
		if(i == 0) {
			while(data.step) {
				push_back(result, (char)(data.step%10)+'0');
				data.step /= 10;
			}
		} else {
			push_back(result, (char)(((data.step%10)) + '0'));
			data.get = (data.step/10)%10;
		}
	}

	for(;i>=0;i--) {
		int temp = (data.sMax[i] - '0') + data.get;
		if(i != 0) {
			if(temp >= 10) {
				push_back(result, (char)(temp%10) + '0');
				data.get = (temp/10)%10;
			} else {
				push_back(result, (char)temp+'0');
				data.get = (temp/10)%10;
			}
		} else {
			while(temp) {
				push_back(result, (char)(temp%10) + '0');
				temp /= 10;
			}
		}
	}

	reverse(result->data, result->size);
	push_back(result, '\0');
}

void debug(int cnt) { printf("debug: %d\n", cnt); }

void multiplication(array_t *result, const char *num1, const char *num2) {
	data_t data = init_data(num1, num2);

	array_t *temp = (array_t*)malloc(sizeof(array_t)*data.minLen);
	for(size_t t=0;t<data.minLen;t++)
		temp[t] = init(18);
	size_t idx=0;

	for(int i=(int)data.minLen-1;i>=0;i--) {
		for(size_t _else=0;_else<idx;_else++)
			push_back(&temp[idx], '0');
		data.get = 0;

		for(int j=(int)data.maxLen-1;j>=0;j--) {
			int step = ((data.sMax[j] - '0') * (data.sMin[i] - '0')) + data.get;
			if(j !=  0) {
				push_back(&temp[idx], (char)(step%10) + '0');
				data.get = (step/10)%10;
			} else {
				while(step) {
					push_back(&temp[idx], (step%10)+'0');
					step /= 10;
				}
			}
		}

		reverse(temp[idx].data, temp[idx].size);
		push_back(&temp[idx++], '\0');
	}

	addition(result, temp[0].data, temp[1].data);
	const char *tmp = result->data;
	destroy(result);

	for(size_t x=2;x<idx;x++) {
		addition(result, tmp, temp[x].data);
		tmp = result->data;
		if(x < idx-1)
			destroy(result);
	}

	for(size_t y=0;y<data.minLen;y++)
		free(temp[y].data);
	push_back(result, '\0');
}

array_t init(size_t cap) {
	array_t res;
	res.size = 0;
	res.cap = cap <= 0 ? 10 : cap;
	res.data = (char*)malloc(sizeof(char)*res.cap);
	return res;
}

void push_back(array_t *arr, char ch) {
	if(arr->data == NULL) {
		arr->cap = 18;
		arr->data = (char*)malloc(sizeof(char)*arr->cap);
	}

	if(arr->size >= arr->cap) {
		arr->cap *= 2;
		arr->data = (char*)realloc(arr->data, sizeof(char)*arr->cap);
	}

	arr->data[arr->size++] = ch;
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

int main() {
	char num1[18]={0}, num2[18]={0};
	array_t result = init(18);
	memset(result.data, '0', 18);

	printf("1. ve 2. numarayi girin: ");
	scanf("%s%s", num1, num2);

	clock_t start = clock();

	multiplication(&result, num1, num2);
	clock_t end = clock();

	printf("%s\n", result.data);
	printf("hesaplama suresi: %.4lf\n", (double)(end-start)/CLOCKS_PER_SEC);
	destroy(&result);
}
