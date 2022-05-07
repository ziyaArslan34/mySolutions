/* date: 08.03.2021
   author: ziya arslan
   copyright: NONE
   update: continues
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAPSIZE 7
#define TANKSIZE 15

typedef struct _ENEMYTANK {
	char name[5];
	size_t row, col;
	int hp, gun;
}enemyTank;

typedef struct _PLAYERTANK {
	char name[5];
	size_t row, col;
	int hp, gun;
}playerTank;

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

void initPCTank(enemyTank (*enemyTanks)[]) {
	for(size_t i=0;i<TANKSIZE;i++) {
		char name[4];
		memset(name, ' ', sizeof(name));
		for(size_t j=0;j<3;j++)
			name[j] = (char)my_rand('a', 'z');
		name[3] = '\0';
		strcpy((*enemyTanks)[i].name, name);
		(*enemyTanks)[i].hp = 10;
		(*enemyTanks)[i].gun = 10;
	}
}

void initPlayerTank(playerTank (*playerTanks)[]) {
	for(size_t i=0;i<TANKSIZE;i++) {
		char name[4] = {0};
		for(size_t j=0;j<3;j++)
			name[j] = (char)my_rand('a','z');
		name[3] = '\0';
		strcpy((*playerTanks)[i].name, name);
		(*playerTanks)[i].hp = 10;
		(*playerTanks)[i].gun = 10;
	}
}

void initMain(char (*tankMap)[][MAPSIZE][MAPSIZE], char (*playerMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[], playerTank (*playerTanks)[]) {
	size_t index=0;

	for(size_t i=0;i<MAPSIZE;i++) {
		for(size_t j=0;j<MAPSIZE;j++) {
			strcpy((*tankMap)[i][j], "   ");
			strcpy((*playerMap)[i][j], "   ");
		}
	}

	int flag=TANKSIZE;
	while(flag--) {
		strcpy((*tankMap)[my_rand(0,MAPSIZE-1)][my_rand(0,MAPSIZE-1)], (*enemyTanks)[index].name);
		strcpy((*playerMap)[my_rand(0,MAPSIZE-1)][my_rand(0,MAPSIZE-1)], (*playerTanks)[index].name);
		index++;
	}
}

void printEnemyMap(const char (*map)[][MAPSIZE][MAPSIZE]) {
	printf("    ");
	for(size_t i=0;i<MAPSIZE;i++)
		printf("  %zu  |", i);
	printf("\n");
	printf("______________________________________________\n");
	for(size_t i=0;i<MAPSIZE;i++) {
		printf("%zu ->", i);
		for(size_t j=0;j<MAPSIZE;j++)
			printf(" xxx |"/*, (*map)[i][j]*/);
		printf("\n");
	}
	printf("______________________________________________\n");
}

void printYourMap(const char (*map)[][MAPSIZE][MAPSIZE]) {
	printf("    ");
	for(size_t i=0;i<MAPSIZE;i++)
		printf("  %zu  |", i);
	printf("\n");
	printf("______________________________________________\n");
	for(size_t i=0;i<MAPSIZE;i++) {
		printf("%zu ->", i);
		for(size_t j=0;j<MAPSIZE;j++)
			printf(" %s |", (*map)[i][j]);
		printf("\n");
	}
	printf("______________________________________________\n");
}

static int deadTank(char (*tankMap)[][MAPSIZE][MAPSIZE], size_t row, size_t col, enemyTank (*enemyTanks)[]) {
	size_t i;

	for(i=0;i<TANKSIZE;i++) {
		if(strcmp((*enemyTanks)[i].name, (*tankMap)[row][col]) == 0) {
			(*enemyTanks)[i].hp -= 5;
			break;
		}
	}

	if((*enemyTanks)[i].hp <= 0) {
		strcpy((*tankMap)[row][col], "---");
		return 1;
	}

	return 0;
}

static int ctrlGunEnemy(enemyTank (*enemyTanks)[], char (*enemyMap)[][MAPSIZE][MAPSIZE], const size_t row, const size_t col) {
	for(size_t i=0;i<TANKSIZE;i++) {
		if(strcmp((*enemyTanks)[i].name, (*enemyMap)[row][col]) == 0) {
			if((*enemyTanks)[i].gun <= 0) {
				//strcpy((*enemyTanks)[i].name, "null");
				strcpy((*enemyMap)[row][col], "nul");
				return 1;
			}
		}
	}
	return 0;
}

static int ctrlGunYour(playerTank (*playerTanks)[], char (*playerMap)[][MAPSIZE][MAPSIZE], const size_t row, const size_t col) {
	return 0;
}

static int ctrlEnemyTank(char (*tankMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[]) {
	for(size_t i=0;i<MAPSIZE;i++)
		for(size_t j=0;j<MAPSIZE;j++)
			for(size_t index=0;index<TANKSIZE;index++)
				if(strcmp((*tankMap)[i][j], (*enemyTanks)[index].name) == 0)
					return 1;
	return 0;
}

static int ctrlYourTank(char (*playerMap)[][MAPSIZE][MAPSIZE], playerTank (*playerTanks)[]) {
	for(size_t i=0;i<MAPSIZE;i++)
		for(size_t j=0;j<MAPSIZE;j++)
			for(size_t index=0;index<TANKSIZE;index++)
				if(strcmp((*playerMap)[i][j], (*playerTanks)[index].name) == 0)
					return 1;
	return 0;
}

static int entryCtrl(const char *row, const char *column) {
	if(strlen(row) != 1 || strlen(column) != 1)
		return 1;
	if(!(row[0] >= '0' && row[0] <= '6') || !(column[0] >= '0' && column[0] <= '6'))
		return 1;
	return 0;
}

static int yourDamaged(char (*playerMap)[][MAPSIZE][MAPSIZE], playerTank (*playerTanks)[], const size_t row, const size_t col) {
	size_t i;

	for(i=0;i<TANKSIZE;i++) {
		if(strcmp((*playerMap)[row][col], (*playerTanks)[i].name) == 0) {
			(*playerTanks)[i].hp -= 5;
			break;
		}
	}

	if((*playerTanks)[i].hp <= 0) {
		strcpy((*playerMap)[row][col], "---");
		return 1;
	}

	return 0;
}

void game(char (*tankMap)[][MAPSIZE][MAPSIZE], char (*playerMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[], playerTank (*playerTanks)[]) {
	while(ctrlEnemyTank(tankMap, enemyTanks)) {
		char row[2], column[2];
		size_t rnd1, rnd2;

		printf("\n\n\t--------[ ENEMY ]----------\n\n");
		printEnemyMap(tankMap);
		printf("\n\n\t--------[ YOUR  ]----------\n\n");
		printYourMap(playerMap);

		printf("\n\nenter row column(0-6): ");
		scanf("%s%s", row, column);

		while(entryCtrl(row, column)) {
			printf("\nHata. lutfen tekrar gir.\n");
			printf("\nenter row column(0-4): ");
			scanf("%s%s", row, column);
		}

		system("clear");

		if(!(strcmp((*tankMap)[atoi(row)][atoi(column)], "   ") == 0) && !(strcmp((*tankMap)[atoi(row)][atoi(column)], "---") == 0)) {
			printf("%s is damaged\n", (*tankMap)[atoi(row)][atoi(column)]);
			if(deadTank(tankMap, atoi(row), atoi(column), enemyTanks))
				printf("%s is dead\n", (*tankMap)[atoi(row)][atoi(column)]);
		} else {
			printf("empty\n");
		}

		rnd1 = rand()%MAPSIZE+0;
		rnd2 = rand()%MAPSIZE+0;

		if(yourDamaged(playerMap, playerTanks, rnd1, rnd2))
			printf("\nyour tank is damaged\n");

		if(!ctrlYourTank(playerMap, playerTanks)) {
			printf("\n\e[91mmission failed!!!\n\n");
			return;
		}
	}

	printf("\nYOU WIN\n\n");
}

int main() {
	srand((unsigned)time(NULL));

	enemyTank enemyTanks[TANKSIZE];
	playerTank playerTanks[TANKSIZE];

	char tankMap[MAPSIZE][MAPSIZE][MAPSIZE];
	char playerMap[MAPSIZE][MAPSIZE][MAPSIZE];

	initPCTank(&enemyTanks); // enemyTank initialize
	initPlayerTank(&playerTanks); // playerTank initialize

	initMain(&tankMap, &playerMap, &enemyTanks, &playerTanks); // map initialize

	system("clear");
/*
	printf("\n-------ENEMYTANKS--------\n");
	printMap(&tankMap);
	printf("\n-------PLAYERTANKS-------\n");
	printMap(&playerMap);
*/

	game(&tankMap, &playerMap, &enemyTanks, &playerTanks); // play game
	return 0;
}
