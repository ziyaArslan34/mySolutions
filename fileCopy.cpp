/*
 - Komut satirindan girilen 1. dosyayi 2. dosyaya kopyalayan kod
 - calistirilma sekli soyle olmalidir;
	- ./fileCopy file1.txt file2.txt
*/

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cerr<<"\nArgv not enter!\n";
		return -1;
	} else {
		std::string fileName1(argv[1]);
		std::ifstream reads(fileName1);
		std::string line;

		if(reads.is_open()) {
			std::string fileName2(argv[2]);
			std::ofstream writes;
			writes.open(fileName2);

			while(!reads.eof()) {
				getline(reads, line);
				writes<<line<<std::endl;
			}
		} else {
			std::cerr<<"\nFile not found!\n";
			return -1;
		}
	}

	return 0;
}
