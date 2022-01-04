#include <iostream>
#include <random>

template <typename T>
T myRand(const T &min, const T &max, char ch='u') {
	std::mt19937 rnd{std::random_device{}()};

	std::uniform_int_distribution<T> makeUniform(min, max);
	std::normal_distribution<T> makeNormal(min, max);

	if(ch == 'n')
		return makeNormal(rnd);
	return makeUniform(rnd);
}

int main() {
	for(size_t i=0;i<10;i++)
		std::cout<<myRand('a', 'z')<<"\n";
}
