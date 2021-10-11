#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>

void watchClock(int hour, int min, int second, char *color) {
	char arr[5][50];

	strcpy(arr[0],  "===================");
	sprintf(arr[1], "| HOUR   >>  %d   |", hour);
	sprintf(arr[2], "| MINUTE >>  %d   |", min);
	sprintf(arr[3], "| SECOND >>  %d   |", second);
	strcpy(arr[4],  "===================");

	if(hour <= 9)
		sprintf(arr[1], "| HOUR   >>  0%d   |", hour);
	if(min <= 9)
		sprintf(arr[2], "| MINUTE >>  0%d   |", min);
	if(second <= 9)
		sprintf(arr[3], "| SECOND >>  0%d   |", second);

	std::cout<<std::endl<<std::endl<<std::endl;

	for(int i=0;i<5;i++)
		std::cout<<color<<"      "<<arr[i]<<std::endl;
}

int main() {
	int hour, min, second=0;
	char color[] = "\e[94m";
	unsigned char c, ch=7;

	std::cout<<"\nHour minute (23:59): ";
	std::cin>>hour>>c>>min;

	while(1) {
		system("clear");

		if(second == 60) {
			min++;
			second=0;
		}

		if(min == 60) {
			hour++;
			min=0;
		}

		if(hour == 24) {
			hour = 0;
		}

		watchClock(hour, min, second, color);
		second++;
		std::cout<<ch;
		sleep(1);
	}
	return 0;
}
