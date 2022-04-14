#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"
//#include "../GenericDynamicArray/dynamic_array.h"

linkedList *create_node(const void *src, size_t typeSize) {
	linkedList *root;

	if((root = (linkedList*)malloc(sizeof(linkedList))) == NULL) {
		perror("");
		return NULL;
	}
	root->typeSize = typeSize;
	root->next = NULL;

	if((root->data = malloc(typeSize)) == NULL) {
		perror("");
		free(root);
		return NULL;
	}
	memcpy(root->data, src, typeSize);

	return root;
}

linkedList *init_root(const void *src, size_t typeSize) {
	return create_node(src, typeSize);
}

linkedList *get_node_index(linkedList **list, size_t idx) {
	if(idx > list_size(list)) {
		fprintf(stderr, "invalid index\n");
		return NULL;
	}

	linkedList *tmp = *list;
	for(size_t i=0;i<idx;i++)
		tmp = tmp->next;

	return tmp->next;
}

linkedList *add_to_end(linkedList **list, const void *src) {
	linkedList *tmp = create_node(src, (*list)->typeSize);

	linkedList *iter = *list;

	while(iter->next != NULL)
		iter = iter->next;
	iter->next = tmp;

	return *list;
}

linkedList *add_to_sort(linkedList **list, const void *src, int (*cmp)(const void*, const void*)) {
	if(cmp(src, (*list)->data)) {
		linkedList *tmp = create_node(src, (*list)->typeSize);

		tmp->next = *list;
		*list = tmp;
		return *list;
	} else {
		linkedList *tmp = create_node(src, (*list)->typeSize);

		linkedList *iter = *list;
		while(iter->next != NULL && cmp(iter->next->data, src))
			iter = iter->next;
		tmp->next = iter->next;
		iter->next = tmp;
	}

	return *list;
}

linkedList *add_to_index(linkedList **list, const void *src, size_t idx) {
	if(idx == 0) {
		if(*list == NULL) {
			fprintf(stderr, "list is null\n");
			return NULL;
		}

		linkedList *newNode = init_root(src, (*list)->typeSize);
		linkedList *tmp = *list;

		*list = newNode;
		(*list)->next = tmp;
		return *list;
	}

	linkedList *tmp = create_node(src, (*list)->typeSize);
	linkedList *iter = *list;

	for(size_t i=0;i<idx-1;i++)
		iter = iter->next;

	tmp->next = iter->next;
	iter->next = tmp;

	return *list;
}

linkedList *del_to_end(linkedList **list) {
	if(*list == NULL)
		return *list;

	linkedList *iter = *list;

	while(iter->next->next != NULL)
		iter = iter->next;

	free(iter->next);
	iter->next = NULL;

	return *list;
}

linkedList *del_to_index(linkedList **list, size_t idx) {
	if(*list == NULL) {
		fprintf(stderr, "list is null\n");
		return *list;
	}

	if(idx == 0) {
		linkedList *tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return *list;
	}

	linkedList *iter = *list;

	for(size_t i=0;i<idx-1;i++)
		iter = iter->next;

	linkedList *tmp = iter->next;
	iter->next = iter->next->next;
	free(tmp);

	return *list;
}
/*
void sort_list(linkedList **list, int (*comp)(const void*, const void*)) {
	dynamicArray_t array = init((*list)->typeSize, list_size(list)+1);

	linkedList *iter = *list;

	while(iter->next != NULL) {
		add_element(&array, iter->data);
		iter = iter->next;
	}

	add_element(&array, iter->data);

	sort_array(&array, comp);

	linkedList *newList = init_root(get_index_element(&array, 0), (*list)->typeSize);

	for(size_t i=1;i<array.size;i++)
		add_to_end(&newList, get_index_element(&array, i));

	destroy(&array);
	destroy_list(list);

	*list = newList;
}
*/
size_t list_size(linkedList **list) {
	size_t cnt = 0;

	linkedList *iter = *list;
	while(iter->next != NULL) {
		iter = iter->next;
		cnt++;
	}

	return cnt;
}

void print_list(linkedList **list, void (*print)(const void*)) {
	if(*list == NULL) {
		fprintf(stderr, "list is null\n");
		return;
	}

	linkedList *tmp = *list;
	printf("\n");
	while(tmp->next != NULL) {
		print(tmp->data);
		tmp = tmp->next;
	}
	print(tmp->data);

	printf("\n");
}

void destroy_list(linkedList **list) {
	if(*list == NULL)
		return;

	linkedList *iter = *list;
	while(iter->next != NULL) {
		free(iter->data);
		iter->data = NULL;
		free(iter);
		iter = iter->next;
	}

	free(iter->data);
	free(iter);

	free(*list);
	*list = NULL;
}
