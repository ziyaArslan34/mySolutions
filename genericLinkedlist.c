/*
	* generic linked list sample *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _LL {
	void *data;
	struct _LL *next;
}LL;

LL *make(const void *data, const size_t size) {
	LL *ll = (LL*)malloc(sizeof(LL));
	ll->data = malloc(size);

	memcpy(ll->data, data, size);
	ll->next = NULL;

	return ll;
}

LL *add(LL *ll, const void *data, const size_t size) {
	if(ll == NULL) {
		LL *temp = make(data, size);
		return temp;
	}


	LL *tmp = ll;

	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = make(data, size);
	return ll;
}

void destroy(LL *ll) {
	while(ll->next != NULL) {
		free(ll->data);
		free(ll);
		ll = ll->next;
	}

	free(ll);
}

void print(LL *root, const size_t size) {
	LL *tmp = root;

	printf("\n");

	if(size == sizeof(int)) {
		while(tmp->next != NULL) {
			printf("%d ", *(int*)tmp->data);
			tmp = tmp->next;
		}
	} else if(size == sizeof(char)) {
		while(tmp->next != NULL) {
			printf("%c  ", *(char*)tmp->data);
			tmp = tmp->next;
		}
	} else {
		while(tmp->next != NULL) {
			printf("%s\n", (char*)tmp->data);
			tmp =tmp->next;
		}
	}

	printf("\n");
}

int main() {
	srand(time(NULL));

	LL *root1 = NULL;
	LL *root2 = NULL;
	LL *root3 = NULL;

	for(int i=97;i<122;i++) {
		root1 = add(root1, &i, sizeof(int));
		root2 = add(root2, &i, sizeof(char));

		char str[6];
		int j;

		for(j=0;j<5;j++)
			str[j] = rand()%(122-97+1)+97;
		str[j] = '\0';

		root3 = add(root3, str, strlen(str));
	}

	print(root1, sizeof(int));
	print(root2, sizeof(char));
	print(root3, 0);

	destroy(root1);
	destroy(root2);
	destroy(root3);

	return 0;
}
