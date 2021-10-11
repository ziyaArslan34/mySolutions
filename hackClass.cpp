/*
Pointerlar ile sinifin private uyelerinin degerini degistirme
*/


#include <iostream>
#include <string>

class Myobj {
    private:
        int data;
		char name[15];
    public:
        Myobj(int data, char *name) {
            this->data = data;
			strcpy(this->name, name);
        }

        void print() {
			std::cout<<data<<std::endl;
			std::cout<<name<<std::endl;
		}
};

int main() {
    Myobj obj(5, "str");
    obj.print();
    int *ptr = (int*)(&obj); // sinifin adresini int tipinden bi pointera atiyoruz
    *ptr = 100; // pointerin degerini degistirdigimizde gosterdigi adreste otomatik olarak degisiyo :)

	char *Cptr = (char*)(&obj);
	strcpy((char*)&*(Cptr+4), "hiii");
	obj.print();

	return 0;
}
