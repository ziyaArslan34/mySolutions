#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

template <typename T>
T myRand(const T& min, const T& max) {
	std::mt19937 eng{std::random_device{}()};

	std::uniform_int_distribution<T> rnd(min, max);

	return rnd(eng);
}

template <typename B> void myPrint(B&) {}
template <typename B, typename T, typename ...Args>
void myPrint(B &buffer, const T& val, Args&&...args) {
	buffer<<val<<"  ";
	myPrint(buffer, args...);
}

class Date {
public:
	Date() : day{1}, mon{1}, year{1907} {}

	Date(int d, int m, int y) : day{d}, mon{m}, year{y} {
		if(isLeapYear()) {
			days[1] = 29;
			if(mon == 2 && day > 29)
				day = days[1];
		} else if(mon == 2 && day > 28)
			day = days[1];
	}

	Date(const Date& other) : day{other.day}, mon{other.mon}, year{other.year}, mons{other.mons}, days{other.days} {}
	Date(Date&& other) : day{other.day}, mon{other.day}, year{other.year}, mons{std::move(other.mons)}, days{std::move(other.days)} {
		other.day = 1;
		other.mon = 1;
		other.year = 1907;
	}

	Date &operator =(const Date&) = default;
	Date &operator =(Date&&) = default;

	friend std::ostream& operator <<(std::ostream& out, const Date &date) {
		out<<"[ ";
		out<<date.day<<" "<<date.mons[static_cast<size_t>(date.mon-1)]<<" "<<date.year;
		out<<" ]\n";

		return out;
	}

	friend std::istream& operator >>(std::istream& in, Date &date) {
		in>>date.day>>date.mon>>date.year;
		return in;
	}

	bool isLeapYear() const {
		return (year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0);
	}

	bool operator ==(const Date &date) const {
		return date.day == day && date.mon == mon && date.year == year;
	}

	bool operator !=(const Date& date) const {
		return !(*this == date);
	}

	bool operator >(const Date &date) const {
		if(year > date.year)
			return true;

		if(year == date.year) {
			if(mon > date.mon)
				return true;
			else if(mon == date.mon) {
				if(day > date.day)
					return true;
				else
					return false;
			} else
				return false;
		}

		return false;
	}

	bool operator <(const Date &date) const {
		return *this > date;
	}

	Date& operator ++() {
		return *this;
	}

	Date& operator --() {
		return *this;
	}

	static Date randomDate() {
		return Date{myRand(1,30), myRand(1,12), myRand(1907, 2022)};
	}

	friend void getDifferenceDate(const Date&, const Date&);

private:
	int day, mon, year;

	std::vector<std::string> mons = {
		"ocak", "subat", "mart", "nisan", "mayis", "haziran",
		"temmuz", "agustos", "eylul", "ekim", "kasim", "aralik"
	};

	std::vector<int> days{31,28,30,31,30,31,30,31,30,31,30,31};
};

#include <unistd.h>

void getDifferenceDate(const Date &d1, const Date &d2) {
	Date dfDate;
	Date maxDate;

	if(d1 == d2)
		return;

	if(d1 > d2) {
		dfDate = d2;
		maxDate = d1;
	} else {
		dfDate = d1;
		maxDate = d2;
	}

    int res = 0;

	while(!(dfDate == maxDate)) {
		res++;
		dfDate.day++;

		if(dfDate.day == 31) {
			dfDate.day = 1;
			dfDate.mon++;
			if(dfDate.mon == 13) {
				dfDate.mon = 1;
				dfDate.year++;
			}
		}
	}

	dfDate.year = res / (12*30);
	dfDate.mon = (res/30)%12;
	dfDate.day = res % 30;

	std::cout<<"\n"<<dfDate.day<<" gun "<<dfDate.mon<<" ay "<<dfDate.year<<" yil var\n";
}

int main() {
	getDifferenceDate(Date{3, 1, 2022}, Date{2, 7, 2022});
}
