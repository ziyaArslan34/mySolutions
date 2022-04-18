#include <iostream>
#include <string>
#include <cstring>
#include <bitset>
#include <type_traits>
#include <vector>
#include <algorithm>

template <typename T>
std::string to_string(const T &arg) {
	return arg;
}

template <>
std::string to_string<int>(const int& arg) {
    char s[10];
    std::sprintf(s, "%d", arg);
    return s;
}

template <>
std::string to_string<double>(const double& arg) {
	char s[10];
	std::sprintf(s, "%.1lf", arg);
	return s;
}

template <>
std::string to_string<std::bitset<8>>(const std::bitset<8>&arg) {
	return arg.to_string();
}

template <typename ...Args>
std::string comb_norm(Args &&... args) {
	std::string str{""};
	std::vector<std::string> vec{((void)"", to_string(args))...};

	for(const auto &i : vec)
		str += i;
	return str;
}

template <typename ...Args>
std::string comb_rev(Args &&... args) {
	std::vector<std::string> vec {(((void)""), to_string(args))...};
	reverse(vec.begin(), vec.end());

	std::string str{""};
	for(const auto &i : vec)
		str += i;
	return str;
}

int main() {
	std::string str{"test"};
	std::bitset<8> bs{'a'};

	std::cout<<comb_norm(1, str, "hii", bs, "\n");
	std::cout<<comb_rev(1, str, "hii", bs, "\n");
}
