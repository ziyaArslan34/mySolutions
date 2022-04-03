#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <stddef.h>

typedef struct {
	void *data;
	size_t size, cap;
	size_t typeSize;
}dynamicArray_t;


dynamicArray_t   init_array(size_t, size_t);
dynamicArray_t*  add_element(dynamicArray_t*, const void*);
dynamicArray_t*  del_element(dynamicArray_t*, const void*);
dynamicArray_t*  insert_element(dynamicArray_t*, size_t, const void*);

int              empty(const dynamicArray_t*);
size_t           search_element(const dynamicArray_t*, const void*);
void*            get_index_element(const dynamicArray_t*, size_t);
void             print_array(const dynamicArray_t*, void (*)(const void*));
void             destroy_array(dynamicArray_t*);
void             sort_array(dynamicArray_t*, int (*)(const void*, const void*));
void             reverse_array(dynamicArray_t*);
void             restore_array(dynamicArray_t*, size_t);

void             debug_function(int);

#endif /* dynamic_array.h */
