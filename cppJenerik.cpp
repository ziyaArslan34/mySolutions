#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename TYPE>
class ARRAY {
	private:
		int cap,size;
		TYPE *array;

	public:
		ARRAY(int cap) {
			this->cap = cap;
			size = 0;
			array = new TYPE[cap];
		}

		~ARRAY() { delete [] array; }

		void myRealloc() {
			cap *= 2;
			TYPE *newarray = new TYPE[cap];
			for(int i=0;i<size;i++)
				newarray[i] = array[i];
			array = newarray;
		}

		void mySort() {
			for(int i=0;i<size;i++) {
				for(int j=0;j<size;j++) {
					if(array[i] < array[j]) {
						int temp = array[i];
						array[i] = array[j];
						array[j] = temp;
					}
				}
			}
		}

		void push(TYPE value) {
			if(size >= cap)
				myRealloc();
			array[size++] = value;
		}

		TYPE pop() {
			return array[--size];
		}

		void print() {
			std::cout<<'\n';
			for(int i=0;i<size;i++)
				std::cout<<array[i]<<"  ";
			std::cout<<'\n'<<"size: "<<size<<'\n';
		}
};

int main() {
	srand(time(nullptr));

	ARRAY<int>a(5);
	ARRAY<char>b(5);
	ARRAY<double>c(5);
//	ARRAY<char*>d(5);
	ARRAY<std::string>e(5);
	ARRAY<float>f(5);

	for(int i=97;i<122;i++) {
		int val = rand()%(122-97+1)+97;
		a.push(val);
		b.push(val);
		c.push(val);
		f.push(val);
	}

	a.print();
	a.mySort();

	for(int i=0;i<5;i++) {
		std::string tmp;
		for(int j=0;j<5;j++)
			tmp.push_back((rand()%(122-97+1)+97));
		e.push(tmp);
	}


	a.print();
	b.print();
	c.print();
	//d.print();
	e.print();
	f.print();

	return 0;
}
