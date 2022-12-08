#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>

struct Tree {
	void *data;
	size_t type;
	struct Tree *left, *right;
};

typedef struct Tree binary_t;

void inorder(binary_t *root, void(*p)(const void*)) {
	if(!root)
		return;

	inorder(root->left, p);
	p(root->data);
	inorder(root->right, p);
}

binary_t *new_tree(const void *data, size_t type) {
	binary_t *new_tr = (binary_t*)malloc(sizeof(binary_t));
	new_tr->data = malloc(type);

	if(!new_tr || !new_tr->data)
		return NULL;

	new_tr->type = type;

	memcpy(new_tr->data, data, type);
	new_tr->left = NULL;
	new_tr->right = NULL;

	return new_tr;
}

binary_t *insert(binary_t *root, const void *data, size_t type, int (*cmp)(const void*, const void*)) {
	if(!root)
		return new_tree(data, type);

	if(cmp(data, root->data))
		root->left = insert(root->left, data, type, cmp);
	else if(cmp(root->data, data))
		root->right = insert(root->right, data, type, cmp);

	return root;
}

void print(const void *data) {
	printf("%d ", *(int*)data);
}

int comp(const void *a, const void *b) {
	return *(int*)a < *(int*)b;
}

void destroy_tree(binary_t *root) {
	if(!root)
		return;
	destroy_tree(root->left);
	free(root->data);
	destroy_tree(root->right);
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int main(void) {
	srand((unsigned)time(NULL));

	int val = my_rand(10,99);

	binary_t *root = new_tree(&val, sizeof(int));

	for(int i=0;i<10;i++) {
		val = my_rand(10,99);
		insert(root, &val, sizeof(val), comp);
	}

	inorder(root, print);
	destroy_tree(root);

}
