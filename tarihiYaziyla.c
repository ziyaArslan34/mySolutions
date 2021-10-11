/*
  * girilen tarihi yaziyla ekrana gosteren program *
  * 06.02.2021 seklinde input verilebilir.         *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

void printDate(char date[][SIZE]) {
	printf("\nDate Format: ");
	for(size_t i=0;i<SIZE;i++)
		if(!(strcmp(date[i], " ") == 0))
			printf("%s ", date[i]);

	printf("\n");
}

void init(char date[][SIZE]) {
	for(size_t i=0;i<SIZE;i++) {
		strcpy(date[i], "");
	}
}

char **dateFormat(char *date) {
	int len = strlen(date);

	for(size_t i=0;i<len;i++)
		if(!(date[i] >= 48 && date[i] <= 57) && !(date[i] == '.'))
			return NULL;

	if((date[len-4] > '2' && date[len-3] > '0' && date[len-2] > '2') || (date[0] >= '3' && date[1] > '1') || date[2] != '.' || date[5] != '.' || date[3] > '1' || (date[3] == '1' && date[4] > '2') || len < 10 || len >= 11)
		return NULL;

	char ones[SIZE][SIZE] = {
		" ", "bir", "iki", "uc", "dort", "bes",
		"alti", "yedi", "sekiz", "dokuz"
	};

	char tens[SIZE][SIZE] = {
		" ", "on", "yirmi", "otuz", "kirk", "elli",
		"altmis", "yetmis", "seksen", "doksan"
	};

	char faces[SIZE][SIZE] = {
		" ", "yuz", "ikiyuz", "ucyuz", "dortyuz", "besyuz",
		"altiyuz", "yediyuz", "sekizyuz", "dokuzyuz"
	};

	char thousand[SIZE][SIZE] = {
		" ", "bin", "ikibin", "ucbin", "dortbin", "besbin",
		"altibin", "yedibin", "sekizbin", "dokuzbin"
	};

	char month[13][SIZE] = {
		" ", "ocak", "subat", "mart", "nisan", "mayis", "haziran",
		"temmuz", "agustos", "eylul", "ekim", "kasim", "aralik"
	};

	char returnDate[SIZE][SIZE];
	init(returnDate);

	int cast;

	cast = date[len-len] - '0';
	strcpy(returnDate[len-len], tens[cast]);

	cast = date[len-len+1] - '0';
	strcpy(returnDate[len-len+1], ones[cast]);

	if(date[len-len+3] == '1' && date[len-len+4] == '2') {
		strcpy(returnDate[len-len+3], month[0]);
		strcpy(returnDate[len-len+4], month[12]);
	} else if(date[len-len+3] == '1' && date[len-len+4] == '1') {
		strcpy(returnDate[len-len+3], month[0]);
		strcpy(returnDate[len-len+4], month[11]);
	} else {
		cast = date[len-len+3] - '0';
		strcpy(returnDate[len-len+3], month[cast]);

		cast = date[len-len+4] - '0';
		strcpy(returnDate[len-len+4], month[cast]);
	}

	cast = date[len-4] - '0';
	strcpy(returnDate[len-4], thousand[cast]);

	cast = date[len-3] - '0';
	strcpy(returnDate[len-3], faces[cast]);

	cast = date[len-2] - '0';
	strcpy(returnDate[len-2], tens[cast]);

	cast = date[len-1] - '0';
	strcpy(returnDate[len-1], ones[cast]);

	return returnDate;
}

int main() {
	char date[15];

	printf("\nTarih yaz(gg.aa.yy): ");
	scanf("%s", date);

	printf("Tarih: %s\n", date);

	if(dateFormat(date) != NULL) {
		char **newDate = dateFormat(date);
		printDate(newDate);
	} else {
		printf("\nLutfen tarihi gg.aa.yy seklinde ve olmayan gunleri, aylari, yillari girerek girmeyiniz\n");
		return -1;
	}

	return 0;
}
