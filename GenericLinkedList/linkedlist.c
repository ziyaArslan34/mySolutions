#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

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

linkedList *init(const void *src, size_t typeSize) {
	return create_node(src, typeSize);
}

linkedList *add_to_end(linkedList **list, const void *src) {
	linkedList *tmp = create_node(src, (*list)->typeSize);

	linkedList *iter = *list;

	while(iter->next != NULL)
		iter = iter->next;
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

	printf("\n");
}

void destroy(linkedList **list) {
	if(*list == NULL)
		return;

	linkedList *iter = *list;
	while(iter->next != NULL) {
		free(iter);
		iter = iter->next;
	}

	free(*list);
	*list = NULL;
}
