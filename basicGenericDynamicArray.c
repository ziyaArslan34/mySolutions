#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PRINTINT(dest, i)      printf("[%d] ", *(int*)(dest+i))
#define PRINTCHAR(dest, i)     printf("[%c] ", *(char*)(dest+i))
#define PRINTSTR(dest, i)      printf("[%s] ", (char*)(dest+i))

typedef struct {
	void *array;
	size_t size;
	size_t cap;
	size_t typeSize;
}type_t;

struct test { int x,y; };

/* prototypes */

type_t*   init(const size_t, const size_t);
type_t*   add(type_t *, const void *);
void*     getIndex(const type_t *const , const size_t);
void*     myCopy(void*, void*, const size_t, size_t);
size_t    compare(const type_t *const, const void *, const void *);
size_t    search(const type_t*const, const void *);
int       elseCompare(const void*, const void*); // int and char vs
int       strCompare(const void*, const void*); // string
int       userCompare(const void*, const void*);
void      sortArray(type_t*);
type_t*   del(type_t*, const void *);
size_t    empty(const type_t *const);
void      print(const type_t *const);
void      printUser(const type_t *const);
void      clear(type_t *);

/*   */


type_t *init(const size_t typeSize, const size_t cap) {
	type_t *retVal = (type_t*)malloc(sizeof(type_t));
	retVal->typeSize = typeSize;
	retVal->cap = cap;
	retVal->size = 0;

	retVal->array = malloc(retVal->cap*retVal->typeSize);

	return retVal;
}

void * myCopy(void *beg, void *destBeg, const size_t typeSize, size_t n) {
        char *db = (char*)destBeg;
        char *b = (char*)beg;

        size_t size=0;

        while(n--) {
                memcpy(db+typeSize*size, b+typeSize*size, typeSize);
                size++;
        }

        return (void*)(db+size-1);
}

int elseCompare(const void* val1, const void* val2) {
	return (*(int*)val1 - *(int*)val2);
}

int strCompare(const void* val1, const void *val2) {
	const char *val1_ = (const char*)val1;
	const char *val2_ = (const char*)val2;
	return (int)strcmp(val1_, val2_);
}

int userCompare(const void* val1, const void* val2) {
	return (((struct test*)val1)->x - ((struct test*)val2)->x);
}
void sortArray(type_t *type) {
	if(type->typeSize == sizeof(int) || type->typeSize == sizeof(char))
		qsort(type->array, type->size, type->typeSize, elseCompare);
	else if(type->typeSize == sizeof(struct test))
		qsort(type->array, type->size, type->typeSize, userCompare);
	else
		qsort(type->array, type->size, type->typeSize, strCompare);
}

size_t empty(const type_t *const type) {
	if(type && type->size)
		return 0;
	return type->size;
}

type_t *add(type_t *type, const void *data) {
	char *dest = (char*)type->array;

	if(type->size >= type->cap) {
		type->cap *= 2;
		type->array = realloc(type->array, type->cap*type->typeSize);

		memcpy(dest+type->size*type->typeSize, data, type->typeSize);
	} else {
		memcpy(dest+type->size*type->typeSize, data, type->typeSize);
	}
	++type->size;

	return type;
}

void *getIndex(const type_t *const type, const size_t idx) {
	if(idx >= type->size)
		return NULL;
	const char *dest = (const char*)type->array;

	return (void*)(dest+idx*type->typeSize);
}

size_t compare(const type_t *const type, const void *data1, const void *data2) {
	return (memcmp(data1, data2, type->typeSize) == 0);
}

size_t search(const type_t *const type, const void *data) {
	if(!type->size)
		return 0;

	const char *dest = (const char*)type->array;

	for(size_t i=0;i<type->size*type->typeSize;i += type->typeSize)
		if(compare(type, (dest+i), data))
			return i;
	return 0;
}

type_t *del(type_t *type, const void *data) {
	size_t src = search(type, data);

	if(src) {
		char *dest = (char*)type->array;
		memcpy(dest+src, 0, type->typeSize);
		return type;
	}

	printf("element not found!\n");
	return NULL;
}

void print(const type_t *const type) {
	printf("\n\n   <<< info >>>\n");
	//printf("type->size     : %zu\n", type->size);
	//printf("type->cap      : %zu\n", type->cap);
	//printf("type->typeSize : %zu\n\n", type->typeSize);

	const char *dest = (const char*)type->array;

	for(size_t i=0;i<type->size*type->typeSize;i += type->typeSize) {
		if(type->typeSize == sizeof(int))
			PRINTINT(dest, i);
		else if(type->typeSize == sizeof(char))
			PRINTCHAR(dest, i);
		else
			PRINTSTR(dest, i);
	}
	printf("\n");
}

void printUser(const type_t *const type) {
	printf("user types\n");
	const char *dest = (const char*)type->array;

	for(size_t i=0;i<type->size*type->typeSize;i += type->typeSize)
		printf("[%d][%d]\n",((struct test*)(dest+i))->x, ((struct test*)(dest+i))->y/*, ((struct test*)(type->array+i))->z*/);
	printf("\n");
}

void clear(type_t *type) {
	type->array = NULL;
	free(type->array);
	type = NULL;
	free(type);
}

int main() {
	srand((unsigned)time(NULL));

	type_t *typeint = init(sizeof(int), 10);
	type_t *typechar = init(sizeof(char), 10);
	type_t *typestr = init(6, 10);
	type_t *typeUser = init(sizeof(struct test), 10);

	for(size_t i=0;i<10;i++) {
		struct test nested;
		nested.x = rand()%99;
		nested.y = rand()%99;

		int ival = rand()%99+1;
		char cval = (char)rand()%(122-97+1)+97;

		(void)add(typeUser, &nested);
		(void)add(typeint, &ival);
		(void)add(typechar, &cval);

		char tmp[6];
		size_t j;
		for(j=0;j<5;j++)
			tmp[j] = (char)rand()%(122-97+1)+97;
		tmp[j] = '\0';
		(void)add(typestr, tmp);
	}

	if(!empty(typeint)) {
		print(typeint);
		sortArray(typeint);
		print(typeint);
	}
	if(!empty(typechar)) {
		print(typechar);
		sortArray(typechar);
		print(typechar);
	}

	if(!empty(typestr)) {
		print(typestr);
		sortArray(typestr);
		print(typestr);
	}

	if(!empty(typeUser)) {
		printUser(typeUser);
		sortArray(typeUser);
		printUser(typeUser);
	}


	clear(typeint);
	clear(typechar);
	clear(typestr);
	clear(typeUser);

	return 0;
}
