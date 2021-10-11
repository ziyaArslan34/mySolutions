#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tr {
	int data;
	struct tr *left;
	struct tr *right;
};

void inorder(struct tr *root) {
	if(root == NULL) {
		return;
	}

	inorder(root->left);
	printf("%d\n", root->data);
	inorder(root->right);
}

struct tr *newTree(int data) {
	struct tr *newTr = (struct tr*)malloc(sizeof(struct tr));

	newTr->data = data;
	newTr->right = NULL;
	newTr->left = NULL;

	return newTr;
}

struct tr *insert(struct tr *root, int data) {
	if(root == NULL) {
		return newTree(data);
	}

	if(data < root->data) {
		root->left = insert(root->left, data);
	} else if(data > root->data) {
		root->right = insert(root->right, data);
	}

	return root;
}

int main() {
	srand(time(NULL));

	struct tr *root = newTree(1);

	for(int i=0;i<30;i++) {
		insert(root, rand()%50+i);
	}

	inorder(root);
}
