#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>

struct Tree {
	void *data;
	struct Tree *left, *right;
};

typedef struct Tree binary_t;
typedef int (*Compare)(const void*, const void*);

binary_t *min_value_tree(binary_t *root) {
	binary_t *current = root;

	while(current && current->left != NULL)
		current = current->left;

	return current;
}

void inorder(binary_t *root, void(*p)(const void*)) {
	if(!root)
		return;

	inorder(root->left, p);
	printf("alloc -> %p [", root);
	p(root->data);
	inorder(root->right, p);
}

binary_t *new_tree(const void *data, size_t type) {
	binary_t *new_tr = (binary_t*)malloc(sizeof(binary_t));
	new_tr->data = malloc(type);

	if(!new_tr || !new_tr->data)
		return NULL;

	memcpy(new_tr->data, data, type);
	new_tr->left = NULL;
	new_tr->right = NULL;

	return new_tr;
}

binary_t *insert_node(binary_t *root, const void *data, size_t type, Compare cmp) {
	if(!root)
		return new_tree(data, type);

	if(cmp(data, root->data) < 0)
		root->left = insert_node(root->left, data, type, cmp);
	else
		root->right = insert_node(root->right, data, type, cmp);

	return root;
}

binary_t *delete_node(binary_t *root, const void *data, size_t type, Compare cmp) {
	if(!root)
		return root;

	if(cmp(data, root->data) < 0)
		root->left = delete_node(root->left, data, type, cmp);
	else if(cmp(data, root->data) > 0)
		root->right = delete_node(root->right, data, type, cmp);
	else {
		if(!root->left) {
			binary_t *tmp = root->right;
			free(root->data);
			free(root);
			return tmp;
		} else if(!root->right) {
			binary_t *tmp = root->left;
			free(root->data);
			free(root);
			return tmp;
		}

		binary_t *tmp = min_value_tree(root->right);
		memcpy(root->data, tmp->data, type);

		root->right = delete_node(root->right, tmp->data, type, cmp);
	}
	return root;
}

void print(const void *data) {
	printf("%d ->  %p]\n", *(int*)data, data);
}

int comp(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

void destroy_tree(binary_t *root) {
	if(root) {
		destroy_tree(root->right);
		destroy_tree(root->left);
		printf("free -> %p [", root);
		print(root->data);
		free(root->data);
		free(root);
	}
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int main(void) {
	srand((unsigned)time(NULL));

	binary_t *root = NULL;

	for(int i=0;i<10;i++) {
		int val = my_rand(10,99);
		root = insert_node(root, &val, sizeof(val), comp);
	}

	inorder(root, print);
	printf("\n");

	destroy_tree(root);
}
