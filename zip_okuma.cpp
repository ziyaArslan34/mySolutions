#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout<<"usage: { readZip <file.zip> }\n";
		return -1;
	}

	std::ifstream reads{argv[1], std::ios::binary};

	if(!reads) {
		std::cout<<"File failed!\n";
		return -1;
	}

	do {
		char data[5]{0};

		unsigned int fileSize{};
		unsigned short len{}, extlen{};

		reads.read(data, 4);

		if(!(data[0] == 'P' && data[1] == 'K')) {
			break;
		}

		reads.seekg(14,std::ios::cur);
		reads.read((char*)&fileSize, 4);

		std::cout<<"Dosya boyutu: "<<fileSize<<"\n";

		reads.seekg(4, std::ios::cur);
		reads.read((char*)&len, 2);
		std::cout<<"Dosya isim uzunlugu: "<<len<<"\n";
		reads.read((char*)&extlen, 2);
		std::cout<<"Extra bilgi uzunlugu: "<<extlen<<"\n";

		char *filename = new char[len+1];
		reads.read(filename, len);
		filename[len] = 0;

		std::cout<<"Dosya ismi: "<<filename<<"\n\n\n";
		delete [] filename;
		reads.seekg(extlen+fileSize, std::ios::cur);
	} while(!reads.eof());
}
