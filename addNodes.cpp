#include <iostream>
#include <cstdlib>
#include <ctime>

typedef struct _ll {
	int data;
	_ll *next;
}ll;

ll *add(ll *l, int num) {
	if(l == NULL) {
		ll *list = (ll*)malloc(sizeof(ll));
		list->data = num;
		list->next = NULL;
		return list;
	}

	ll* temp;
	temp = l;

	while(temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = (ll*)malloc(sizeof(ll));
	temp->next->data = num;
	temp->next->next = NULL;

	return l;
}

ll *addTo(ll *a, ll *b) {
	ll *adds;
	adds = NULL;
	ll *temp1, *temp2;
	temp1 = a;
	temp2 = b;

	while(temp1->next != NULL && temp2->next != NULL) {
		adds = add(adds, (temp1->data+temp2->data));
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	adds = add(adds, (temp1->data+temp2->data));

	return adds;
}

void del(ll **a, int num) {
	ll *temp = *a, *prev;

	if(temp != NULL && temp->data == num) {
		*a = temp->next;
		free(temp);
		return;
	}

	while(temp->next != NULL && temp->data != num) {
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL) { return; }

	prev->next = temp->next;
	free(temp);
}

void print(ll *l) {
	ll* temp;
	temp = l;
	int i=1;
	std::cout<<i++<<". indis >> "<<l->data<<std::endl;

	while(temp->next != NULL) {
		std::cout<<i++<<". indis >> "<<temp->data<<std::endl;
		temp = temp->next;
	}

	std::cout<<std::endl;
}

int main() {
	srand(time(NULL));

	ll *root1, *root2, *maxRoot;
	maxRoot = NULL;
	root1 = NULL;
	root2 = NULL;

	for(int i=0;i<=10;i++) {
		root1 = add(root1, rand()%99+1);
		root2 = add(root2, rand()%99+2);
	}

	maxRoot = addTo(root1, root2);

	print(root1);
	print(root2);
	print(maxRoot);
	del(&root1, 25);
	print(root1);
}
