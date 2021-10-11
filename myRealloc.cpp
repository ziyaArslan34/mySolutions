#include <iostream>
#include <cstdlib>
#include <cstring>

int *myReallocC(int *arr, int *len, char *str) {
	if(strcmp(str, "genislet") == 0) {
		int *newArr = (int*)malloc(sizeof(int)*2*(*len));

		for(int i=0;i<(*len);i++) { newArr[i] = arr[i]; }

		free(arr);
		(*len) *= 2;

		return newArr;
	} else if(strcmp(str, "daralt") == 0) {
		int *newArr = (int*)malloc(sizeof(int)*((*len)/2));

		for(int i=0;i<(*len)/2;i++) { newArr[i] = arr[i]; }

		free(arr);
		(*len) /= 2;

		return newArr;
	}

	return NULL;
}

template <typename T>
T *myReallocCpp(T *arr, int *len, char *str) {
	if(strcmp(str, "genislet") == 0) {
		T *newArr = new T[(*len)*2];

		for(int i=0;i<(*len);i++) { newArr[i] = arr[i]; }

		delete [] arr;
		(*len) *= 2;

		return newArr;
	} else if(strcmp(str, "daralt") == 0) {
		T *newArr = new T[((*len)/2)];

		for(int i=0;i<(*len)/2;i++) { newArr[i] = arr[i]; }

		delete [] arr;
		(*len) /= 2;

		return newArr;
	}

	return NULL;
}

int main() {
	char azalt[] = "daralt";
	char arttir[] = "genislet";
	int lenC=2;
	int lenCpp=2;

	int *arrC = (int*)malloc(sizeof(int)*lenC);
	int *arrCpp = new int[lenCpp];

	// now add an element to the array until a negative number is entered

	int i=0;
	int num;

	while(1) {
		if(i==lenC) { arrC = myReallocC(arrC, &lenC, arttir); }
		if(i==lenCpp) { arrCpp = myReallocCpp(arrCpp, &lenCpp, arttir); }

		std::cout<<"num: ";
		std::cin>>num;
		if(num <= 0) { break; }

		arrC[i] = num;
		arrCpp[i] = num;

		i++;
	}

	std::cout<<"\nC arr >> ";
	for(int z=0;z<lenC;z++) { std::cout<<arrC[z]<<"  "; }

	std::cout<<"\nCpp arr >> ";
	for(int z=0;z<lenCpp;z++) { std::cout<<arrCpp[z]<<"  "; }

	arrC = myReallocC(arrC, &lenC, azalt);
	arrCpp = myReallocCpp(arrCpp, &lenCpp, azalt);

	std::cout<<"\nAfter arrC >> ";
	for(int i=0;i<lenC;i++) { std::cout<<arrC[i]<<"  "; }

	std::cout<<"\nAfter arrCpp >> ";
	for(int i=0;i<lenCpp;i++) { std::cout<<arrCpp[i]<<"  "; }

	std::cout<<"\n";

	return 0;
}
