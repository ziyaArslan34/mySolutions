#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	void *data;
	void *begin;
	void *end;

	size_t cap,size, typeSize;
}queue_t;


queue_t*    init(size_t);
int         empty(const queue_t*);
void        enqueue(queue_t*, const void*);
void        dequeue(queue_t*);
void*       display(const queue_t*);
int         myRand(int, int);
const char* rName(void);

queue_t *init(size_t typeSize) {
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));

	queue->cap = 10;
	queue->size = 0;
	queue->typeSize = typeSize;

	queue->data = malloc(queue->cap*queue->typeSize);
	queue->begin = ((char*)queue->data)+queue->size*queue->typeSize;
	queue->end = ((char*)queue->data)+queue->size*queue->typeSize;

	return queue;
}

int empty(const queue_t *qu) { return qu->size == 0; }

void enqueue(queue_t *qu, const void *data) {
	if(qu->size >= qu->cap) {
		qu->cap *= 2;
		qu->data = realloc(qu->data, qu->cap*qu->typeSize);
	}

	memcpy((char*)qu->data+qu->size*qu->typeSize, data, qu->typeSize);
	qu->end = (char*)qu->data+qu->size*qu->typeSize;

	++qu->size;
}

void dequeue(queue_t *qu) {
	if(empty(qu)) {
		perror("queue is empty!\n");
		return;
	}

	for(size_t i=0;i<qu->size; i++)
		memcpy((char*)qu->data+i*qu->typeSize, (char*)qu->data+(i+1)*qu->typeSize, qu->typeSize);

	--qu->size;

	qu->end = (char*)qu->data+qu->size*qu->typeSize;
	qu->begin = display(qu);
}

void *display(const queue_t *qu) {
	if(empty(qu))
		return NULL;

	return (char*)qu->data+0*qu->typeSize;
}

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

const char *rName() {
	static const char *name[] = {
		"ziya", "enes", "emir", "ahmet", "burak",
		"ilayda", "didem", "aycan", "ismihan", "sila",
		"emre", "mert", "sinem", "ebru", "bilmemne"
	};

	return name[myRand(0, 15-1)];
}

int main() {
	srand((unsigned)time(NULL));

	queue_t *qu = init(10);

	for(int i=1;i<10;i++) {
		enqueue(qu, rName());
		printf("begin : %s   end : %s\n", (char*)qu->begin, (char*)qu->end);
	}


	for(size_t i=0;i<5;i++) {
		printf("kuyruktan cikan : %s\n", (char*)display(qu));
		dequeue(qu);

		printf("siradaki        : %s\n", (char*)display(qu));
	}

	qu->data = NULL;
	qu->begin = NULL;
	qu->end = NULL;

	free(qu->data);
	qu = NULL;
	free(qu);
}
