/*

 - Date >> 18 Aralık 2020
 - Copyright o da ne oyle sjjfj
 - author >> Ziya ARSLAN
 - Linked list implementasyonu

*/


#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node *next;
}LL;

LL *make(int num) {
	LL *newNode = (LL*)malloc(sizeof(LL));
	newNode->data = num;
	newNode->next = NULL;

	return newNode;
}

void clearLL(LL *ll) {
        while(ll->next != NULL) {
                free(ll);
                ll = ll->next;
        }
}

int nodesLen(LL *ll) {
	if(ll == NULL) { return -1; }
	LL *iter = ll;
	int len=1;
	while(iter->next != NULL) {
		iter = iter->next;
		len++;
	}

	return len;
}

int clearNodes(LL **ll) {
	free(*ll);
	*ll = NULL;

	if(*ll == NULL) { return 1; }
	return 0;
}

void printNodes(LL *ll) {
	LL *temp = ll;

	if(ll == NULL) {
		printf("\nNodes is NULL.\n");
		return;
	}

	int i=1;
	while(temp->next != NULL) {
		printf("%d. node : %d\n", i,temp->data);
		temp = temp->next;
		i++;
	}
	printf("%d. node : %d\n", i, temp->data);
}

LL *addToEnd(LL *ll, int num) {
	if(ll == NULL) {
		LL *newNode = make(num);
		return newNode;
	}

	LL *temp = ll;

	while(temp->next != NULL) { temp = temp->next; }

	temp->next = make(num);
	return ll;
}

void insertionAdd(LL **buffer, LL *ll, int num, int index) {
	LL *iter = ll;
	LL *temp = make(num);

	if(index == 1) {
		*buffer = temp;
		(*buffer)->next = iter;
	} else {
		for(int i=0;i<index-2;i++) {
			iter = iter->next;
		}

		temp->next = iter->next;
		iter->next = temp;
	}
}

int searchNodes(LL *ll, int src) {
	if(ll == NULL) { return 0; }

	int flag = 0;
	int loc = 0;

	LL *temp = ll;

	while(temp->next != NULL) {
		if(temp->data == src) {
			flag = 1;
			break;
		}
		loc++;
		temp = temp->next;
	}

	if(temp->data == src) { flag = 1; }

	printf("\nYou searching number %d. index in found\n", loc+1);
	return flag;
}

void deleteNodes(LL **ll, int index) {
	LL *iter = (*ll);

	if(index == 1) {
		iter = iter->next;
		free((*ll));
		(*ll) = iter;
		return;
	}

	iter = (*ll);
	for(int i=0;i<index-2;i++) { iter = iter->next; }

	iter->next = iter->next->next;
}

void delToEnd(LL **ll) {
	if(*ll == NULL) { return; }

	LL *iter = *ll;

	while(iter->next->next != NULL) {
		iter = iter->next;
	}
	free(iter->next);
	iter->next = NULL;
}

/*
int removeEnd(LL * ll)
{
    Node * iter = ll->Root;

    while (iter->Next->Next != NULL)
        iter = iter->Next;

    free(iter->Next);
    iter->Next = NULL;

    return EXIT_SUCCESS;
}
*/

void inlineAdd(LL **ll, int num) {
	if(*ll == NULL) {
		*ll = make(num);
		return;
	} else if((*ll)->data > num) {
		LL *temp = make(num);
		temp->next = *ll;
		*ll = temp;
		return;
	} else {
		LL *tmp = make(num);

		LL *iter = *ll;

		while(iter->next != NULL && iter->next->data < num) {
			iter = iter->next;
		}

		tmp->next = iter->next;
		iter->next = tmp;
	}
}

LL *sortNodes(LL *ll, int *arr) {
	if(ll == NULL) { return ll; }

	if(nodesLen(ll) == 1) { return ll; }

	int len = nodesLen(ll);

	LL *tmp = NULL;
	for(int i=0;i<len;i++) {
		inlineAdd(&tmp, arr[i]);
	}

	free(arr);
	return tmp;
}

int *buubleSort(LL *ll) {
	int len = nodesLen(ll);
	int *arr = (int*)malloc(sizeof(int)*len);

	LL *iter = ll;

	for(int i=0;i<len;i++) {
		arr[i] = iter->data;
		iter = iter->next;
	}

	return arr;
}

void choiceMenu() {
	printf("\nEleman ekleme       : [1]");
	printf("\nAraya eleman ekleme : [2]");
	printf("\nSirali eleman ekleme: [3]");
	printf("\nEleman silme        : [4]");
	printf("\nSondan eleman silme : [5]");
	printf("\nEleman arama        : [6]");
	printf("\nSiralama            : [7]");
	printf("\nListeyi yazdirma    : [8]");
	printf("\n\nEXIT                : [0]\n\n");
}

int main() {
	LL *root = NULL;
	int *sortArr = NULL;

	int choice, num, index;

	while(1) {
		//system("cls || clear");
		choiceMenu();
		printf("\nChoice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				printf("\nEnter num: ");
				scanf("%d", &num);
				root = addToEnd(root, num);
				printf("\nSuccess.\n");
				break;
			case 2:
				printf("\nEnter num: ");
				scanf("%d", &num);
				printf("\nEnter index: ");
				scanf("%d", &index);
				if(index > nodesLen(root) || index < 0) {
					printf("\nindex not found!\n");
				} else {
					insertionAdd(&root, root, num, index);
					printf("\nSuccess.\n");
				}
				break;
			case 3:
				printf("\nEnter num: ");
				scanf("%d", &num);
				inlineAdd(&root, num);
				printf("\nSuccess.\n");
				break;
			case 4:
				printf("\nEnter index: ");
				scanf("%d", &index);
				if(index > nodesLen(root) || index < 0) {
					printf("\nindex not found!\n");
				} else {
					deleteNodes(&root, index);
					printf("\nSuccess.\n");
				}
				break;
			case 5:
				delToEnd(&root);
				printf("\nSuccess.\n");
				break;
			case 6:
				printf("\nSearch num: ");
				scanf("%d", &num);
				if(searchNodes(root, num)) {
					printf("\nFound num[+]\n");
				} else {
					printf("\nNum not found[-]\n");
				}
				break;
			case 7:
				if(root == NULL) {
					printf("\nNodes is NULL.\n");
				} else if(root->next == NULL) {
					sortArr[0] = root->data;
				} else {
					sortArr = buubleSort(root);
					root = sortNodes(root, sortArr);
				}
				printf("\nSuccess.\n");
				break;
			case 8:
				system("cls || clear");
				printNodes(root);
				break;
			case 0:
				clearLL(root);
				if(clearNodes(&root)) {
					printf("\nProgram success is exit.\n");
					exit(0);
				} else {
					clearLL(root);
					printf("\nClear nodes is error!!\n");
					exit(1);
				}
				break;

			default:
				printf("\nChoice not found!\n");
				break;
		}
	}

	return 0;
}
