#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stddef.h>

struct Node {
	void *data;
	size_t typeSize;
	struct Node *next;
};

typedef struct Node linkedList;

linkedList*  init_root(const void *, size_t);
linkedList*  create_node(const void*, size_t);

linkedList*  add_to_end(linkedList**, const void*);
linkedList*  add_to_idx(linkedList**, const void*, size_t);
linkedList*  del_to_end(linkedList**);
linkedList*  del_to_idx(linkedList**, size_t);

linkedList*  get_node_idx(linkedList**, size_t);
void         sort_list(linkedList**, int (*)(const void*, const void*));

size_t       list_size(linkedList**);
void         print_list(linkedList**, void (*)(const void*));
void         destroy_list(linkedList**);


#endif /* linkedlist.h */
