#include <iostream>
#include <cstdlib>
#include <ctime>

void first(int *arr, int len) {
	for(int i=0;i<len;i++) {
		arr[i] = rand()%(77-(-50)+1)+(-50);
	}
}

void printCard(int *arr, int len) {
	std::cout<<"\e[90m**************";

	if(arr[len-1] < 0) {
		std::cout<<"\e[91m"<<arr[len-1]<<"\n";
	} else {
		std::cout<<"\e[94m"<<arr[len-1]<<"\n";
	}

	std::cout<<"\e[90m**************";

	if(arr[len-2] < 0) {
		std::cout<<"\e[91m"<<arr[len-2]<<"\n";
	} else {
		std::cout<<"\e[94m"<<arr[len-2]<<"\n";
	}
}

int *collapse(int *arr, int *len) {
	int *newArr = new int[(*len)-1];

	for(int i=0;i<(*len)-1;i++) {
		newArr[i] = arr[i];
	}
	delete [] arr;
	(*len)--;
	return newArr;
}

int main() {
	srand((unsigned)time(nullptr));

	int *array = new int[100];
	int len=100;
	int tp=0;
	int num;

	first(array, len);

	while(1) {
		if(len==2) { break; }

		system("clear");
		printCard(array, len);

		std::cout<<"\n\n"<<tp<<"\n\n";

		std::cout<<"\n\e[92mChoice is number: ";
		std::cin>>num;
		if(num == array[len-1]) { tp += array[len-1]; }
		else if(num == array[len-2]) { tp += array[len-2]; }
		else { std::cout<<"\n\e[91mNumber not found!\n"; continue; }
		array = collapse(array, &len);
	}
}
