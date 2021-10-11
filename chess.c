#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP 8

/*
	1 piyon
	2 kale
	3 at
	4 fil
	5 vezir
	6 sah
*/

/* PROTOTYPE */

void myMove(int (*)[][MAP], const char*, const char*);
void init(int (*)[][MAP]);
void printMap(int (*)[][MAP]);
int ctrlRowCol(const char*, const char*);
void choice(int (*)[][MAP]);
int rockCtrl(int (*)[][MAP], const int, const int, const int, const int, const int);
void newRock(int (*)[][MAP], const int, const int);


void init(int (*map)[][MAP]) {
	for(int i=0;i<MAP;i++) {
		(*map)[1][i] = 1;
		(*map)[6][i] = 1;
	}

	(*map)[0][0] = (*map)[0][MAP-1] = 2;
	(*map)[0][1] = (*map)[0][MAP-2] = 3;
	(*map)[0][2] = (*map)[0][MAP-3] = 4;

	(*map)[0][3] = 5;
	(*map)[0][4] = 6;

	(*map)[MAP-1][0] = (*map)[MAP-1][MAP-1] = 2;
	(*map)[MAP-1][1] = (*map)[MAP-1][MAP-2] = 3;
	(*map)[MAP-1][2] = (*map)[MAP-1][MAP-3] = 4;

	(*map)[MAP-1][3] = 5;
	(*map)[MAP-1][4] = 6;
}

void printMap(int (*map)[][MAP]) {
	printf("   ");
	for(int i=1;i<MAP+1;i++)
		printf("%d   ", i);
	printf("\n  ");
	for(int i=0;i<MAP*2;i++)
		printf("\e[91m__");
	printf("\n");

	char chars = 97;
	for(int i=0;i<MAP;i++) {
		printf("\e[91m%c  ", chars++);
		for(int j=0;j<MAP;j++) {
			if((*map)[i][j] == 0)
				printf("\e[90m%d | ", (*map)[i][j]);
			else
				printf("\e[93m%d | ", (*map)[i][j]);
		}
		printf("\n");
	}
	printf("  ");
	for(int i=0;i<MAP*2;i++)
		printf("\e[91m__");
	printf("\n\n");
}

int ctrlRowCol(const char *val1, const char *val2) { return ((strlen(val1) == 2 && strlen(val2) == 2) && ((val1[0] >= 97 && val1[0] <= 104) && (val2[0] >= 97 && val2[0] <= 104)) && ((val1[1] >= 49 && val1[1] <= 56) && (val2[1] >= 49 && val2[1] <= 56))); }

void choice(int (*map)[][MAP]) {
	char first[3], second[3];

	while(1) {
		printf("tas sec: ");
		scanf("%s", first);
		printf("gidcegi yer: ");
		scanf("%s", second);

		if(!ctrlRowCol(first, second))
			printf("Hatali secim\n");
		else
			break;
	}

	myMove(map, first, second);
}

void myMove(int (*map)[][MAP], const char *source, const char *target) {
	int sourceRow = source[0]-(48*2)-1, sourceCol = source[1]-48-1;
	int targetRow = target[0]-(48*2)-1, targetCol = target[1]-48-1;

	if((*map)[sourceRow][sourceCol] == 0) {
		printf("\norda tas yok .d\n");
		return;
	}

	if(!rockCtrl(map,sourceRow, sourceCol, (*map)[sourceRow][sourceCol], targetRow, targetCol)) {
		printf("oraya gidemezsin.\n");
		return;
	}

	(*map)[targetRow][targetCol] = (*map)[sourceRow][sourceCol];
	(*map)[sourceRow][sourceCol] = 0;

	if(targetRow == MAP-1)
		newRock(map, targetRow, targetCol);
}


void newRock(int (*map)[][MAP], const int row, const int col) {
	int flag=1;

	while(flag) {
		char newRc[6];
		printf("new rock(vezir/at/kale/fil): ");
		fgets(newRc, sizeof(newRc), stdin);
		newRc[strlen(newRc)-1] = '\0';

		switch(newRc[0]) {
			case 'f':
				(*map)[row][col] = 4;
				flag=0;
				break;
			case 'v':
				(*map)[row][col] = 5;
				flag=0;
				break;
			case 'k':
				(*map)[row][col] = 2;
				flag=0;
				break;
			case 'a':
				(*map)[row][col] = 3;
				flag=0;
				break;
			default:
				printf("Try again\n");
				break;
		}
	}
}

int rockCtrl(int (*map)[][MAP], const int rockRow, const int rockCol, const int rock, const int row, const int col) {
	if(rock == 1) { // piyon hareketleri
		int flag=1;

		if((rockRow+1 == row && rockCol-1 == col) || (rockRow-1 == row && rockCol+1 == col) || (rockRow+1 == row && rockCol+1 == col) || (rockRow-1 == row && rockCol-1 == col)) {
			if((*map)[row][col] != 0)
				return 1;
			else
				flag=0;
		}

		if((rockCol-col) != 1 || (rockCol-col) != -1)
			flag=0;
		if(rockCol-col == 0)
			flag=1;

		if(((rockRow - row) == -1 || (rockRow - row) == 1) && ((*map)[row][col] == 0))
			return flag;
	}

	else if(rock == 2) { // kale hareketleri
		int flag=1;
		if(rockCol == col) {
			for(int i=1;i<row-1;i++)
				if((*map)[rockRow+i][rockCol] != 0)
					flag=0;
		}
		return flag;
	}

	else if(rock == 4) { // fil hareketleri
		if(rockRow == row || rockCol == col)
			return 0;
		else {
			int flag=1;
			if(rockRow+1 == row && rockCol+1 == col)
				for(int i=1;i<row-1;i++)
					for(int j=1;j<col-1;j++)
						if((*map)[rockRow+i][rockCol+j] != 0)
							flag=0;
			if(rockRow-1 == row && rockCol-1 == col)
				for(int i=1;i<row-1;i++)
					for(int j=1;j<col-1;j++)
						if((*map)[rockRow-i][rockCol-j] != 0)
							flag=0;
			return flag;
		}
	}

	return 0;
}

int main() {
	int map[MAP][MAP]={0};

	init(&map);
	printMap(&map);

	while(1) {
		choice(&map);
		printMap(&map);
	}

	return 0;
}
