#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <unistd.h>

#define START_PARSE_CODE 500

struct Clock {
	int hour, minute, second;
	friend std::ostream& operator<<(std::ostream& out, const Clock &cl) {
		out<<"\n[ "<<cl.hour<<" "<<cl.minute<<" "<<cl.second<<" ]\n";
		return out;
	}
};

std::string parseTime(const std::string &buffer) {
	size_t cnt{};
	std::string time;
	size_t len = buffer.size();

	size_t flag = 0;

	for(size_t i=0;i<len;i++) {
		if(flag == 0) {
			if(buffer[i] >= 48 && buffer[i] <= 57) {
				for(size_t m=i;buffer[i++] != ' ' && m < len;m++) {}
				flag = START_PARSE_CODE;
			}
		}

		if(flag == START_PARSE_CODE) {
			for(size_t j=i;buffer[i++] != ' ' && j < buffer.size();j++) {
				//std::cout<<"buffer["<<j<<"] : "<<buffer[j]<<"\n";
				time.push_back(buffer[j]);
			}
		}
	}

	for(size_t i=0;i<4;i++)
		time.pop_back();
	return time;
}

Clock getCurrent(const std::string &currentTime) {
	std::vector<int>vec;

	for(size_t i=0;i<currentTime.size();) {
		std::string tmp;

		for(size_t j=i;currentTime[i++] != ':' && j < currentTime.size();j++)
			tmp.push_back(currentTime[j]);
		vec.push_back(std::atoi(tmp.data()));
		//vec.push_back(std::stoi(tmp));
	}

	Clock res;

	res.hour = vec[0];
	res.minute = vec[1];
	res.second = vec[2];

	return res;
}

int main() {

	auto date = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(date);

	std::time_t ttm = std::time(0);
	std::tm *now = std::localtime(&ttm);

	std::string buffer{std::ctime(&time)};
	std::string currentTime = parseTime(buffer);

	Clock clock = getCurrent(currentTime);


	std::cout<<buffer<<"\n";
	std::cout<<currentTime<<"\n";
	std::cout<<clock<<"\n";

	if(((now->tm_year+1900) == 2022 &&
		(now->tm_mon+1) == 1 && now->tm_mday == 1) &&
	(clock.hour == 0 && clock.minute == 0 && clock.second == 0)) {
		std::cout<<"\n\n"<<buffer<<"\n\n";
		std::cout<<"Mutlu yillar\n\n";

		return 0;
	}
/*

	while(1) {
		main();
	}
*/
}
