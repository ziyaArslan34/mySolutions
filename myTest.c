#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int id;
	char name[20];
	char address[20];
	int mood;
}kargo_t;

typedef struct {
	void *data;
	size_t size,cap;
	size_t typeSize;
}type_t;

type_t *init(const size_t n, const size_t typeSize) {
	type_t *retVal = (type_t*)malloc(sizeof(type_t));
	retVal->size = 0;
	retVal->cap = n;
	retVal->typeSize = typeSize;

	retVal->data = malloc(retVal->cap*retVal->typeSize);
	return retVal;
}

type_t *add(type_t *type, const void *data) {
	if(!type) {
		perror("type is null, please do init\n");
		return NULL;
	}

	if(type->size >= type->cap) {
		type->cap *= 2;
		type->data = realloc(type->data, type->typeSize*type->cap);
	}

	char *dest = (char*)type->data;

	memcpy(dest+type->size*type->typeSize, data, type->typeSize);
	++type->size;
	return type;
}

static int compare(const void *val1, const void *val2) {
	return (((kargo_t*)val1)->id > ((kargo_t*)val2)->id);
}

void mySort(type_t *type) {
	qsort(type->data, type->size, type->typeSize, compare);
}

void print(const type_t *type) {
	printf("\n");
	printf("<<<<<<<info>>>>>>>>\n");

	const char *dest = (const char*)type->data;

	for(size_t i=0;i<type->size*type->typeSize;i += type->typeSize) {
		printf("\nid      : %d\n", ((kargo_t*)(dest+i))->id);
		printf("name    : %s\n", ((kargo_t*)(dest+i))->name);
		printf("address : %s\n", ((kargo_t*)(dest+i))->address);
		printf("mood    : %d\n", ((kargo_t*)(dest+i))->mood);
	}
	printf("\n");
}

void destroy(type_t *type) {
	free(type->data);
	free(type);
}

int main() {
	srand((unsigned)time(NULL));

	type_t *type = init(10, sizeof(kargo_t));

	const char *names[] = {"bir", "iki", "uc","dort", "bes"};
	const char *addreses[] = {"adr1", "adr2", "adr3", "adr4", "adr5"};

	for(size_t i=0;i<5;i++) {
		kargo_t temp;
		temp.id = rand()%95+2;
		strcpy(temp.name, names[i]);
		strcpy(temp.address, addreses[i]);

		(void)add(type, &temp);
	}

	print(type);
	mySort(type);
	print(type);
	destroy(type);

	return 0;
}
