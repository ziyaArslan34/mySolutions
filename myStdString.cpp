#include <iostream>

namespace myStd {
	class string {
		public:
			char str[1024];
			int num;

			string() { num = 0; str[0] = '\0'; }

			int size() {
				num=0;
				for(int i=0;str[i] != '\0';i++) {
					num++;
				}
				return num;
			}

			void push_back(char a) {
				str[size()] = a;
			}

	};
};

std::istream &operator >>(std::istream &i, myStd::string &s) {
	return i>>s.str;
}

std::ostream &operator <<(std::ostream &i, myStd::string &s) {
	return i<<s.str;
}

int main() {
	myStd::string str;

	std::cin>>str;
	str.push_back('x');

	std::cout<<"\n"<<str<<"\n";
}
