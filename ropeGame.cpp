#include <iostream>
#include <cstdlib>

typedef struct _ll {
	int data;
	_ll *next;
}ll;

void arrSave(int arr[][5]) {
	for(int i=0;i<5;i += 2) {
		arr[0][i] = 1;
		arr[4][i] = 1;
	}
}

void printLL(ll *l) {
	ll *tmp = l;
	while(tmp->next != nullptr) {
		std::cout<<" > "<<tmp->data;
		tmp = tmp->next;
	}
	std::cout<<"\n\n";
}

ll *insert(ll *l, int data) {
	if(l == nullptr) {
		ll* temp = new ll;
		temp->data = data;
		temp->next = nullptr;
		return temp;
	}

	ll *tmp = l;

	while(tmp->next != nullptr) { tmp = tmp->next; }

	tmp->next = new ll;
	tmp->next->data = data;
	tmp->next->next = nullptr;

	return l;
}

void printArr(int arr[][5]) {
	for(int i=0;i<5;i++) {
		for(int j=0;j<5;j++) {
			if(arr[i][j] == 1) {
				std::cout<<"\e[93m"<<arr[i][j]<<"  ";
			} else {
				std::cout<<"\e[90m"<<arr[i][j]<<"  ";
			}
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

int main() {
	ll *r1, *r2, *r3;
	r1 = r2 = r3 = nullptr;

	int Arr[5][5] = {0};
	arrSave(Arr);

	for(int i=0;i<9;i++) {
		r1 = insert(r1, i+1);
		r2 = insert(r2, i+1);
		r3 = insert(r3, i+1);
	}

	r1 = insert(r1, 1);
	r2 = insert(r2, 1);
	r3 = insert(r3, 1);

	printLL(r1);
	printArr(Arr);

	std::cout<<"\n\e[91m\n\nDevami yakinda... :) \n\n";

	return 0;
}
