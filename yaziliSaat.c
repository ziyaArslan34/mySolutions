#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int clockCtrl(char *clock) {
	if(clock[0] >= 51 || clock[3] > 53 || clock[2] != ':' || strlen(clock) > 5 || (clock[0] == 50 && clock[1] >= 53))
		return 0;

	for(size_t i=0;i<strlen(clock);i++) {
		if((clock[i] >= 48 && clock[i] <= 57) || clock[i] == ':')
			continue;
		else
			return 0;
	}

	return 1;
}

static void init(char str[][8]) {
	for(size_t i=0;i<5;i++)
		strcpy(str[i], " ");
}

static void printClock(char clock[][8]) {
	for(size_t i=0;i<4;i++)
		printf("%s ", clock[i]);
	printf("\n\n");
}

char *endClock(char clock[][8]) {
	char *str;

	int len=0, index=0;

	for(size_t i=0;i<4;i++)
		for(size_t j=0;j<strlen(clock[i]);j++)
			len++;

	str = (char*)malloc(sizeof(char)*len);

	for(size_t i=0;i<4;i++) {
		for(size_t j=0;j<strlen(clock[i]);j++)
			str[index++] = clock[i][j];
		str[index++] = ' ';
	}

	return str;
}

void returnClock(char *clock) {
	if(!clockCtrl(clock)) {
		printf("\nLutfen duzgun giris yapin!\n");
		return;
	}

	char temp1[10][8] = {
		" ", "bir", "iki", "uc", "dort",
		"bes", "alti", "yedi", "sekiz", "dokuz"
	};

	char temp2[10][8] = {
		" ", "on", "yirmi", "otuz", "kirk",
		"elli", "altmis", "yetmis", "seksen", "doksan"
	};

	char returnStr[4][8];
	init(returnStr);
	int cast;

	size_t i,j=0;
	int len = strlen(clock)-1;

	char *clock1 = (char*)malloc(sizeof(char)*len-1);

	for(i=0;i<strlen(clock);i++)
		if(clock[i] >= 48 && clock[i] <= 57)
			clock1[j++] = clock[i];

	cast = clock1[len-len] - '0';
	strcpy(returnStr[0], temp2[cast]);
	//printf("temp2[%d]: %s\n", cast, temp2[cast]);

	cast = clock1[len-len+1] - '0';
	strcpy(returnStr[1], temp1[cast]);
	//printf("temp1[%d]: %s\n", cast, temp1[cast]);

	cast = clock1[len-len+2] - '0';
	strcpy(returnStr[2], temp2[cast]);
	//printf("temp2[%d]: %s\n", cast, temp2[cast]);

	cast = clock1[len-len+3] - '0';
	strcpy(returnStr[3], temp1[cast]);
	//printf("temp1[%d]: %s\n", cast, temp1[cast]);

	free(clock1);

	char *endStr = endClock(returnStr);

	printClock(returnStr);
	printf("\nClock: %s\n", endStr);
	free(endStr);
}

int main() {
	while(1) {
		char clock[10];
		printf("\nsaat(24:00): ");
		scanf("%s", clock);
		returnClock(clock);
	}

	return 0;
}
