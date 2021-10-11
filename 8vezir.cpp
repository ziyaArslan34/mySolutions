#include <iostream>
#include <cstdlib>
#include <ctime>

template <class TYPE>
class Chess {
	private:
		static constexpr size_t size = 8;
		TYPE **arr;
		TYPE value;

	public:
		Chess(TYPE value) {
			this->value = value;

			arr = new TYPE*[size];
			for(size_t i=0;i<size;i++)
				arr[i] = new TYPE[size];

			for(size_t i=0;i<size;i++)
				for(size_t j=0;j<size;j++)
					arr[i][j] = '\x2b';
		}

		~Chess() {
			for(size_t i=0;i<size;i++)
				delete [] arr[i];
			delete [] arr;
		}

		bool ctrlDuz(const int row, const int col) {
			for(size_t i=0;i<size;i++)
				if(arr[row][i] == value || arr[i][col] == value)
					return false;
			return true;
		}

		bool ctrlCapraz(const int row, const int col) {
			for(int i=0;i<size;i++) {
				/*sag ust*/
				if(arr[(row-i) < 0 ? row : row-i][(col+i) > size-1 ? col : col+i] == value)
					return false;

				/*sol ust*/
				if(arr[(row-i) < 0 ? row : row-i][(col-i) < 0 ? col : col-i] == value)
					return false;

				/*sag alt*/
				if(arr[(row+i) > size-1 ? row : row+i][(col+i) > size-1 ? col : col+i] == value)
					return false;

				/*sol alt*/
				if(arr[(row+i) > size-1 ? row : row+i][(col-i) < 0 ? col : col-i] == value)
					return false;
			}
			return true;
		}

		void add() {
			for(size_t i=0;i<size;i++)
				for(size_t j=0;j<size;j++) {
					int rnd1 = rand()%(size-1+1)+0;
					int rnd2 = rand()%(size-1+1)+0;

					if(ctrlDuz(rnd1,rnd2) && ctrlCapraz(rnd1,rnd2))
						arr[rnd1][rnd2] = value;
				}
		}

		void print() {
			std::cout<<'\n';
			for(size_t i=0;i<size;i++) {
				for(size_t j=0;j<size;j++) {
					if(arr[i][j] == value)
						std::cout<<"\e[93m"<<arr[i][j]<<"  ";
					else
						std::cout<<"\e[91m"<<arr[i][j]<<"  ";
				}
				std::cout<<'\n';
			}
			std::cout<<'\n';
		}
};

int main() {
	srand(time(nullptr));

	Chess<char>bt('V');

	bt.add();
	bt.print();

	return 0;
}
