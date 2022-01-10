#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW 4
#define COL 4
#define CITYSIZE 56

struct city {
	char name[10];
	size_t row, col;
	struct city *north, *south, *west, *east;
};

struct country {
	struct city **cities;
};

typedef struct city city_t;
typedef struct country country_t;

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

const char *makeCity() {
	static size_t idx=0;

	static const char *allCities[CITYSIZE] = {
		"istanbul", "izmir", "antalya", "erzurum", "igdir", "van", "ankara",
		"elazig", "hakkari", "sirnak", "bitlis", "bayburt", "agri", "mus",
		"siirt", "urfa", "antep", "eskisehir", "adiyaman", "kilis", "adana",
		"hatay", "mersin", "burdur", "aksaray", "maras", "osmaniye", "malatya",
		"kirsehir", "sivas", "tekirdag", "edirne", "mugla", "kutahya", "usak",
		"aydin", "isparta", "kirklareli", "bursa", "izmit", "sakarya", "trabzon",
		"rize", "samsun", "sinop", "giresun", "zonguldak", "yozgat", "ardahan",
		"artvin", "duzce", "bolu", "corum", "balikesir", "canakkale", "batman"
	};

	if(idx >= CITYSIZE)
		return NULL;

	return allCities[idx++];
}

int isNull(const city_t *road) {
	return road == NULL;
}

void printAllInfo(const country_t *ctr) {
	printf("\n\n");
	for(size_t i=0;i<ROW;i++) {
		for(size_t j=0;j<COL;j++) {
			printf("\n\n====================================\n\n");
			printf("[ %s ] sehrinin komsulari\n\n", ctr->cities[i][j].name);
			if(!isNull(ctr->cities[i][j].west)) // Bati
				printf("\nBati [ %s ]\n", ctr->cities[i][j].west->name /*, ctr->cities[i][j].west->row, ctr->cities[i][j].west->col*/);
			//else printf("\nBati komsusu yok\n");

			if(!isNull(ctr->cities[i][j].east)) // Dogu
				printf("\nDogu [ %s ]\n", ctr->cities[i][j].east->name /*, ctr->cities[i][j].east->row, ctr->cities[i][j].east->col*/);
			//else printf("\nDogu komsusu yok\n");

			if(!isNull(ctr->cities[i][j].south)) // Guney
				printf("\nGuney [ %s ]\n", ctr->cities[i][j].south->name /*, ctr->cities[i][j].south->row, ctr->cities[i][j].south->col*/);
			//else printf("\nGuney komsusu yok\n");

			if(!isNull(ctr->cities[i][j].north)) // Kuzey
				printf("\nKuzey [ %s ]\n", ctr->cities[i][j].north->name /*, ctr->cities[i][j].north->row, ctr->cities[i][j].north->col*/);
			//else printf("\nKuzey komsusu yok\n");
			printf("\n\n");
		}
	}
}

void print(const country_t *ctr) {
	printf("\n\n");
	for(size_t start=0;start<ROW;start++)
		printf("_________________");
	printf("\n\n");

	for(size_t i=0;i<ROW;i++) {
		for(size_t j=0;j<COL;j++) {
			printf("| [ %s ] ", ctr->cities[i][j].name);
		}
		printf("\n");
		for(size_t ptr = 0;ptr<ROW;ptr++)
			printf("_________________");
		printf("\n");
	}
	printf("\n\n");
}

void destroy(country_t *ctr) {
	for(size_t i=0;i<COL;i++)
		free(ctr->cities[i]);
	free(ctr->cities);
}

int main() {
	srand((unsigned)time(NULL));

	country_t ctr;

	ctr.cities = (city_t**)malloc(sizeof(city_t*)*ROW);
	for(size_t i=0;i<ROW;i++)
		ctr.cities[i] = (city_t*)malloc(sizeof(city_t)*COL);

	for(size_t i=0;i<ROW;i++) {
		for(size_t j=0;j<COL;j++) {
			if(j == 0)
				ctr.cities[i][j].west = NULL;
			else
				ctr.cities[i][j].west = &ctr.cities[i][j-1];
			if(j == COL-1)
				ctr.cities[i][j].east = NULL;
			else
				ctr.cities[i][j].east = &ctr.cities[i][j+1];

			if(i == 0)
				ctr.cities[i][j].north = NULL;
			else
				ctr.cities[i][j].north = &ctr.cities[i-1][j];
			if(i == ROW-1)
				ctr.cities[i][j].south = NULL;
			else
				ctr.cities[i][j].south = &ctr.cities[i+1][j];

			ctr.cities[j][i].row = i;
			ctr.cities[j][i].col = j;
			const char *cityName = makeCity();
			strcpy(ctr.cities[j][i].name, cityName);
		}
	}

	print(&ctr);

	printAllInfo(&ctr);

	destroy(&ctr);
}
