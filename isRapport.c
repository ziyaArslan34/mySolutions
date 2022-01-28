#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM(a,b) ((a) > (b) ? (a) : (b)) //for setw
#define MIN_NUM(a,b) ((a) < (b) ? (a) : (b)) //for setw

typedef struct {
	void *array;
	size_t size, cap, typeSize;
}mystack_t;

mystack_t*  init(size_t);
int         empty(const mystack_t*);
void        push(mystack_t*, const void*);
void*       getTop(const mystack_t*);
void*       pop(mystack_t*);
int         isOpen(char);
int         isClose(char);
int         isRapport(const char*);
void        mySetw(size_t);
int         myRand(int, int);
size_t      findMaxSize(const char*[], size_t size);

mystack_t *init(size_t typeSize) {
	mystack_t *st = (mystack_t*)malloc(sizeof(mystack_t));

	st->size = 0;
	st->cap = 4;
	st->typeSize = typeSize;

	st->array = malloc(st->cap*st->typeSize);

	return st;
}

int empty(const mystack_t *stack) {
	return stack->size == 0;
}

void push(mystack_t *st, const void *data) {
	if(st->size >= st->cap) {
		st->cap *= 2;
		st->array = realloc(st->array, st->cap*st->typeSize);
	}

	memcpy((char*)st->array+st->size*st->typeSize, data, st->typeSize);
	++st->size;
}

void *getTop(const mystack_t *st) {
	return ((char*)st->array+(st->size-1)*st->typeSize);
}

void *pop(mystack_t *st) {
	--st->size;
	return ((char*)st->array+st->size*st->typeSize);
}

int isOpen(char ch) {
	return (ch == '(' || ch == '{' || ch == '[' || ch == '<');
}

int isClose(char ch) {
	return (ch == ')' || ch == '}' || ch == ']' || ch == '>');
}

int isRapport(const char *str) {
	const char *chOpen = "({[<";
	const char *chClose = ")}]>";

	size_t idx1=0, idx2=0;

	int flag = 0;
	for(size_t i=0;i<strlen(str);i++)
		if(isOpen(str[i]) || isOpen(str[i]))
			flag = 1;
	if(!flag)
		return 0;

	mystack_t *stack = init(sizeof(char));

	for(size_t i=0;i<strlen(str);i++) {
		if(isOpen(str[i]))
			push(stack, &str[i]);
		else if(isClose(str[i])) {
			char top;
			if(!empty(stack))
				top = *(char*)getTop(stack);
			for(size_t j=0;j<strlen(chOpen);j++)
				if(top == chOpen[j])
					idx1 = j;
			for(size_t j=0;j<strlen(chClose);j++)
				if(str[i] == chClose[j])
					idx2 = j;

			if(idx1 == idx2) {
				if(!empty(stack))
					pop(stack);
				else
					return 0;
			} else {
				push(stack, &str[i]);
			}
		}
	}

	int res = empty(stack);

	free(stack->array);
	free(stack);

	return res;
}

void mySetw(size_t n) {
	while(n--)
		printf(" ");
}

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

size_t findMaxSize(const char *str[], size_t size) {
	size_t maxSize = 0;

	for(size_t i=0;i<size;i++) {
		size_t len = strlen(str[i]);
		if(maxSize < len)
			maxSize = len;
	}

	return maxSize;
}

int main() {
	srand((unsigned)time(NULL));

	const char *str[] = {"({[{{}sifir}][{(<><bir>)}][iki][{uc}]})",
						 "({[{{<}sifir}][{(<><bir>)}][iki][{uc}]})",
						 "{[(<>)]}",
						 "((a[scope1] * b[scope2]) (a[{scope3}{scope4}]))",
						 "{{()[]{}}}",
						 "merhabalar"
	};

	size_t maxSize = findMaxSize(str, 6); //for setw

	for(size_t i=0;i<6;i++) {
		size_t len = strlen(str[i]);

		if(isRapport(str[i])) {
			printf("%s ", str[i]);
			mySetw(((MAX_NUM(len, maxSize) - MIN_NUM(len, maxSize)) + 1));
			printf(" -> true\n");
		} else {
			printf("%s ", str[i]);
			mySetw(((MAX_NUM(len, maxSize) - MIN_NUM(len, maxSize)) + 1));
			printf(" -> false\n");
		}
	}
}
