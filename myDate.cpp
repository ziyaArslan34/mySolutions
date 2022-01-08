#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <type_traits>

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

static constexpr const char *mons[] = {"ocak", "subat", "mart", "nisan", "mayis", "haziran", "temmuz", "agustos", "eylul", "ekim", "kasim", "aralik"};
static constexpr const char days[] = {31,28,30,31,30,31,30,31,30,31,30,31};

class Date {
public:
	Date() : day{1}, mon{1}, year{1907} {}

	Date(int d, int m, int y) : day{d}, mon{m}, year{y} {}

	Date(const Date& other) : day{other.day}, mon{other.mon}, year{other.year} {}
	Date(Date&& other) : day{other.day}, mon{other.mon}, year{other.year} {
		other.day = 1;
		other.mon = 1;
		other.year = 1907;
	}

	Date &operator =(const Date&) = default;
	Date &operator =(Date&&) = default;

	friend std::ostream& operator <<(std::ostream& out, const Date &date) {
		out<<std::left;

		out<<std::setw(3)<<"[ ";
		out<<date.day<<" "<<mons[!date.mon ? 0 : date.mon-1]<<" "<<date.year;
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
		return !(*this > date);
	}

	Date& operator ++() {
		day++;
		if(day > days[static_cast<size_t>(mon-1)]) {
			day = 1;
			mon++;
			if(mon > 12) {
				mon = 1;
				year++;
				if(year > 2023)
					year = 1907;
			}
		}

		return *this;
	}

	Date& operator +(size_t n) {
		while(n--)
			++*this;
		return *this;
	}

	Date& operator --() {
		day--;
		if(day == 0) {
			mon--;
			day = days[!mon ? 0 : static_cast<size_t>(mon-1)];
			if(mon == 0) {
				mon = 12;
				year--;
				if(year == 1907)
					year = 2022;
			}
		}

		return *this;
	}

	Date& operator -(size_t n) {
		while(n--)
			--*this;
		return *this;
	}

	static Date randomDate() {
		return Date{myRand(1,30), myRand(1,11), myRand(1907, 2022)};
	}

	friend Date getDifferenceDate(const Date&, const Date&);

/*
	void getInfo() {
		myPrint(std::cout, "Day: ", day, "\n", "Mon: ", mon, "\n", "Year: ", year, "\n", "Vec size: ", mons.size(), "\n\n");
	}
*/

private:
	int day, mon, year;
};

Date getDifferenceDate(const Date &d1, const Date &d2) {
	Date dfDate;
	Date maxDate;

	if(d1 == d2)
		return dfDate;

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

		if(dfDate.day > days[!dfDate.mon ? 0 : static_cast<size_t>(dfDate.mon-1)]) {
			dfDate.day = days[static_cast<size_t>(dfDate.mon-1)];
			dfDate.mon++;
			if(dfDate.mon > 12) {
				dfDate.mon = 1;
				dfDate.year++;
			}
		}
	}

	dfDate.year = res / (12*30);
	dfDate.mon = (res/30)%12;
	dfDate.day = res % 30;

	//std::cout<<"\n"<<dfDate.day<<" gun "<<dfDate.mon<<" ay "<<dfDate.year<<" yil var\n";

	return dfDate;
}

int main() {
	std::vector<Date> vec;

	for(size_t i=0;i<25;i++)
		vec.push_back(Date{Date::randomDate()});

	sort(vec.begin(), vec.end(), std::greater{});

	for(const auto& i : vec) {
		std::cout<<i<<"\n";
	}
}
