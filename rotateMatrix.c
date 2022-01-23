#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROW 29
#define COL 29

void print(char array[][COL]) {
	printf("\n\n");

	for(size_t i=0;i<ROW;i++) {
		//printf("\t\t");
		for(size_t j=0;j<COL;j++)
			printf("%c", array[i][j]);

		printf("\n");
	}

	printf("\n\n");
}


void rotate(char array[][COL]) {
	int newA[COL][ROW];

	for(int i=ROW-1;i >= 0;i--)
		for(int j=0;j<COL;j++)
			newA[j][ROW-i-1] = array[i][j];

	for(size_t i=0;i<ROW;i++)
		for(size_t j=0;j<COL;j++)
			array[i][j] = newA[i][j];

}

int main() {
/*
	char array[ROW][COL] = {
{",,,,,,,,,,*****,,,,,,,,,,,,,,,*****,,,,,,,,,,"},
{",,,,,,,***********,,,,,,,,,***********,,,,,,,"},
{",,,,,***************,,,,,***************,,,,,"},
{",,,*******************,*******************,,,"},
{",*******************************************,"},
{",*******************************************,"},
{",*******************************************,"},
{",*******************************************,"},
{",,,***************************************,,,"},
{",,,,,***********************************,,,,,"},
{",,,,,,,*******************************,,,,,,,"},
{",,,,,,,,,***************************,,,,,,,,,"},
{",,,,,,,,,,,***********************,,,,,,,,,,,"},
{",,,,,,,,,,,,,*******************,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,***************,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,***********,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,*******,,,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,,,***,,,,,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,,,,*,,,,,,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"},
{",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"}
};
*/

char array[ROW][COL] = {
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMyyyyyyyMMMMMyyyyyyyMMMMM",
"MMMmhyyyyyyyyyyyyyyyyyyyhmMMM",
"MMhyyyyyyyyyyyyyyyyyyyyyyydMM",
"MhyyyyyyyyyyyyyyyyyyyyyyyyyhM",
"dyyyyyyyyyyyyyyyyyyyyyyyyyyym",
"yyyyyyyyyyyyyyyyyyyyyyyyyyyyh",
"yyyyyyyyyyyyyyyyyyyyyyyyyyyyh",
"hyyyyyyyyyyyyyyyyyyyyyyyyyyyd",
"myyyyyyyyyyyyyyyyyyyyyyyyyyyN",
"MdyyyyyyyyyyyyyyyyyyyyyyyyymM",
"MMmyyyyyyyyyyyyyyyyyyyyyyhmMM",
"MMMNdyyyyyyyyyyyyyyyyyyydMMMM",
"MMMMMNdyyyyyyyyyyyyyyydMMMMMM",
"MMMMMMMNdyyyyyyyyyyydMMMMMMMM",
"MMMMMMMMMNdyyyyyyydMMMMMMMMMM",
"MMMMMMMMMMMNdyyyyMMMMMMMMMMMM",
"MMMMMMMMMMMMMNyMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMM"
};

/*
	int array[6][6] = {
		{10,11,12,13,14,15},
		{16,17,18,19,20,21},
		{22,23,24,25,26,27},
		{28,29,30,31,32,33},
		{34,35,36,37,38,39},
		{40,41,42,43,44,45}
	};

*/
	print(array);
	rotate(array);
	print(array);
	rotate(array);
	print(array);
}
