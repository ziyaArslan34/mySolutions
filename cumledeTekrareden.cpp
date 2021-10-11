#include <iostream>
#include <fstream>

std::string *my(std::string *arr, int len) {
	std::string *newArr = new std::string[len];

	for(int i=0;i<len/2;i++)
		newArr[i] = arr[i];

	delete [] arr;
	return newArr;
}

void writesArr(std::string *arr, int len) {
	for(int i=0;i<len;i++) {
		std::cout<<arr[i]<<std::endl;
	}
}

std::pair<int, std::string> maxTry(std::string *words, int len) {
	std::string maxTmp = words[0];
	int max=0;

	for(int i=0;i<len;i++) {
		int count=0;
		std::string tmp = words[i];

		for(int j=0;j<len;j++)
			if(words[j] == tmp)
				count++;

		if(count > max) {
			max = count;
			maxTmp = words[i];
		}
	}

	if(max == 1) {
		return std::make_pair(max, "hepsinden 1 tane :)");
	}

	return std::make_pair(max, maxTmp);
}

int main() {
	int SIZE = 10;
	std::string *words = new std::string[SIZE];
	std::string str="";

/*
	std::ifstream reads("kelime.txt");
	std::string line;
*/
	int index=0;

	while(str != "exit") {
		std::cout<<"\nKelime gir: ";
		std::cin>>str;

		if(index == SIZE) {
			words = my(words, SIZE*2);
			SIZE *= 2;
		}
		words[index++] = str;
	}

	writesArr(words, SIZE);
	words[index-1] = "";

	std::pair<int, std::string> returnValue = maxTry(words, index);

	std::cout<<"\nEn cok tekrar eden kelime: "<<returnValue.second<<std::endl;
	std::cout<<"Tekrar sayisi: "<<returnValue.first<<std::endl;

	writesArr(words, SIZE);

	delete [] words;
	return 0;
}
