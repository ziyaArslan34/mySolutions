#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 7
#define COL 7

struct city {
	char name[30];
	int row, col;
	struct city *north, *south, *west, *east; // bune
};

struct country {
	struct city **cities;
};

typedef struct city city_t;
typedef struct country country_t;

int myRand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

const char *randomCity() {
	static const int len = 5;

	static const char *name[] = {
		"city1", "city2", "city3", "city4", "city5"
	};

	return name[myRand(0,len-1)];
}

void print(const country_t *ctr) {
	printf("\n\n");
	for(size_t start=0;start<ROW;start++)
		printf("\e[91m_________________");
	printf("\n\n");

	for(size_t i=0;i<ROW;i++) {
		for(size_t j=0;j<COL;j++) {
			printf("\e[90m| \e[91m[ \e[90m%s %d %d \e[91m] ", ctr->cities[i][j].name, ctr->cities[i][j].row, ctr->cities[i][j].col);
		}
		printf("\n");
		for(size_t ptr = 0;ptr<ROW;ptr++)
			printf("\e[91m_________________");
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

	for(int i=0, r=-3;i<ROW;i++, r++) {
		for(int j=0, c=4;j<COL;j++, c--) {
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

			ctr.cities[j][i].row = r;
			ctr.cities[j][i].col = c;
			strcpy(ctr.cities[j][i].name, randomCity());
		}
	}

	print(&ctr);

	printf("\n[ %s  %d  %d ]\n\n", ctr.cities[1][1].south->name, ctr.cities[1][1].south->row, ctr.cities[1][1].south->col);

	destroy(&ctr);
}
