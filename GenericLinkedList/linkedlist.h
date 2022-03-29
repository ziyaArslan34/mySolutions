#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stddef.h>

struct Node {
	void *data;
	size_t typeSize;
	struct Node *next;
};

typedef struct Node linkedList;

linkedList*  init(const void *, size_t);
linkedList*  create_node(const void*, size_t);
linkedList*  add_to_end(linkedList**, const void*);
linkedList*  del_to_end(linkedList**);

size_t       list_size(linkedList**);
void         print_list(linkedList**, void (*)(const void*));
void         destroy(linkedList**);


#endif /* linkedlist.h */
