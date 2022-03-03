#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "info.h"

typedef struct {
	char name[30];
	int hour, minute;
	char inOut;
	int time;
}person_t;

void differenceTime(person_t *per) {
	int h = per->hour;
	int m = per->minute;

	int hour = 17;
	int minute = 1;
	int totalTime = 0;

	while(h < hour) {
		if(m == 59) {
			h++;
			m=0;
		}
		m++;
		++totalTime;
	}

	printf("%d\n", totalTime/60);
}


int comp(person_t per1, person_t per2) {
	if(per1.hour > per2.hour)
		return 1;

	if(per1.hour == per2.hour) {
		if(per1.minute > per2.minute)
			return 1;
		return 0;
	}

	if(per1.hour == per2.hour && per1.minute == per2.minute)
		return 0;
	return 0;
}

void bubbleSortPerson(person_t *per, size_t size) {
	for(size_t i=0;i<size;i++) {
		for(size_t j=0;j<size;j++) {
			if(comp(per[i], per[j])) {
				person_t temp = per[i];
				per[i] = per[j];
				per[j] = temp;
			}
		}
	}
}

void myCopy(person_t *per, char **array, size_t idx) {
	strcpy(per[idx].name, array[0]);
	per[idx].hour = atoi(array[1]);
	per[idx].minute = atoi(array[2]);
	per[idx].inOut = array[3][0];
}

void printPerson(const person_t *info, size_t size) {
	printf("\n\n");

	for(size_t i=0;i<size;i++)
		printf("%s  %d:%d %c\n", info[i].name, info[i].hour, info[i].minute, info[i].inOut);
	printf("\n\n");

}

int main() {
	FILE *file = fopen("person.txt", "r");

	person_t infoIn[10], infoOut[10];
	size_t inIdx=0, outIdx=0;

	type_t strs = init(15);

	if(!file) {
		perror("Error");
		return -1;
	}

	while(!feof(file)) {
		char str[1024];
		fgets(str, sizeof(str), file);
		str[strlen(str)-1] = '\0';
		size_t sLen = strlen(str);

		if((isAlpha(str[0]) || (str[0] >= 48 && str[0] <= 57)) && (str[sLen-1] == '>' || str[sLen-1] == '<') )
			push_back(&strs, str);
	}

	for(size_t i=0;i<strs.size;i++) {
		type_t temp = init(10);
		splitStr(&temp, strs.array[i], " :");

		//printf("\n\n");
		//printArray(&temp);

		if(inIdx >= 10 || outIdx >= 10) break;

		if(temp.array[3][0] == '>') {
			myCopy(infoIn, temp.array, inIdx);
			inIdx++;

		} else if(temp.array[3][0] == '<') {
			myCopy(infoOut, temp.array, outIdx);
			outIdx++;
		}
		destroy(&temp);
	}

	printf("heh\n");
	bubbleSortPerson(infoIn, inIdx);
	bubbleSortPerson(infoOut, outIdx);

	printPerson(infoIn, inIdx);
	printPerson(infoOut, outIdx);

	differenceTime(&infoIn[0]);
	destroy(&strs);

	return 0;
}
