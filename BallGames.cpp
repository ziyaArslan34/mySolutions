#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cstring>

namespace Game {
	class Stack {
		public:
			int *arr, top;

			Stack() {
				arr = new int[4];
				top = 0;
			}

			~Stack() {
				delete [] arr;
			}

			bool push(int num) {
				if(top==4) { return false; }
				arr[top++] = num;
				return true;
			}

			int pop() {
				if(top==0) { return EXIT_FAILURE; }
				return arr[--top];
			}
	};

	void print(Stack *s) {
		int len=0;
		while(1) {
			if(len == 9) { break; }
			std::cout<<"\e[92m"<<len+1<<". kutu >> ";

			for(int i=0;i<4;i++) {
				if(s[len].arr[i] == 0) {
					std::cout<<"\e[94m"<<s[len].arr[i]<<"  ";
				} else {
					std::cout<<"\e[93m"<<s[len].arr[i]<<"  ";
				}
			}
			std::cout<<"\n\n";
			len++;
		}
	}

	bool ctrl(Stack *s) {
		int mood=0;
		int j=8;
		//std::cout<<"\nYapilan kutu >> "<<mood<<std::endl;
		while(j>=0) {
			if((s[j].arr[0] == s[j].arr[1]) && (s[j].arr[0] == s[j].arr[2]) && (s[j].arr[0] == s[j].arr[3])) {
				mood++;
			}
			j--;
		}
		std::cout<<"\e[92mTamamlanan kutu : "<<mood<<std::endl;
		if(mood >= 5) { return false; }
		return true;
	}

	void second(Stack *s) {
		int tmp[8][4] = {
			{1,2,8,3},
			{2,2,1,2},
			{3,1,3,4},
			{4,5,3,4},
			{5,6,4,5},
			{7,6,5,6},
			{7,8,6,7},
			{8,7,8,1}
		};
		for(int i=0;i<8;i++) {
			for(int j=0;j<4;j++) {
				s[i].push(tmp[i][j]);
			}
		}
	}

	void ilk(Stack *s) {
		int num=1;
		for(int i=0;i<8;i++) {
			for(int j=0;j<4;j++) {
				if(s[rand()%8+0].push(num)) {}
				else { continue; }
			}
			num++;
		}
	}

	bool numCtrl(std::string num) {
		for(int i=0;i<num.size();i++) {
			if(num[i] >= 49 && num[i] <= 57) {}
			else { return false; }
		}
		return true;
	}
};

int main() {
tekrar:
	srand((unsigned)time(0));

	clock_t start, finish;
	start = clock();

	Game::Stack s[9];
	//Game::ilk(s);
	Game::ilk(s);

	int y;
	std::string x;
	std::cout<<"\n\e[90mMerhaba ben ziya arslan bi oyun kodladim.Lutfen deneyin.\n";
	std::cout<<"\nOyuna hosgeldiniz.\nOyunun amaci 5 tane kutuyu ayni sayilarlar doldurmaktir.\nKolay gelsin :)\n\n";

	while(ctrl(s)) {
		Game::print(s);

		std::cout<<"\n\e[90mHangi kutudaki sayiyi alacaksin(1-9): ";
		std::cin>>x;

		if(Game::numCtrl(x) && (std::stoi(x) > 0 && std::stoi(x) <= 9)) {
			if(s[(std::stoi(x))-1].top == 0) {
				std::cout<<"\n\e[91mSectigin kutu bos!\n";
				continue;
			} else {
				y = s[(std::stoi(x))-1].pop();
				s[(std::stoi(x))-1].arr[(s[(std::stoi(x))-1].top)] = 0;
			}

			std::cout<<"\nEldeki sayi >> "<<y<<"\n";

			std::cout<<"\n\e[90mHangi kutuya koyacaksin(1-9): ";
			std::cin>>x;

			if(Game::numCtrl(x) && (std::stoi(x) <= 9 && std::stoi(x) > 0)) {
				if(s[(std::stoi(x))-1].top < 4) { s[(std::stoi(x))-1].push(y); }
				else { std::cout<<"\n\e[91mSectigin kutu dolu!\n"; }
			} else {
				std::cout<<"\n\e[91mLutfen (1-9) arasinda sayi girin!\n";
				sleep(1);
				continue;
			}
		} else {
			std::cout<<"\n\e[91mLutfen (1-9) arasinda sayi girin!\n";
			sleep(1);
			continue;
		}
		system("clear");
	}

	system("clear");
	std::cout<<"\n\e[94mTEBRIKLER KAZANDINIZ...\n";

	finish = clock();
	std::cout<<"\nOyun suresi >> "<<(float)(finish-start)/CLOCKS_PER_SEC<<". saniyedir.\n";

	char c;
	std::cout<<"\nYeni oyun oynansinmi(e/h): ";
	std::cin>>c;

	if(c == 'e') { goto tekrar; }
	else { std::cout<<"\nBye :)\n\n"; }
	return 0;
}
