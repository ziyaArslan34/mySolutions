/*
  - Author : Ziya Arslan
  - Date   : 30 12 2020
  - Detay  : Oyunun amaci harita uzerinde Dikey L harfini cizmektir harf cizilirken harfin son parcasini ekliyen oyuncu oyunu kazanir :))

*/

#include <stdio.h>
#include <string.h>

int ctrl(int arr[][4]) {
	/* ben ornek olaral bitane L harfi bulabildim bitmap uzerinde bulmak icin tekrar fomksiyonu guncelleyecegim*/
	if(arr[0][0] == arr[1][0] && arr[2][0] == arr[3][0] && arr[3][0] == arr[3][1] && arr[3][0] != 0) {
		return 1;
	}
	return 0;
}

void printBoard(int arr[][4]) {
	printf("\n");
	for(int i=0;i<7;i++) {
		printf("%d :   ", i+1);
		for(int j=0;j<4;j++) {
			printf("|%d|", arr[i][j]);
		}
		printf("\n");
	}
	printf("      ************\n");
	printf("      ************\n");
	printf("\n       1  2  3  4\n");
	printf("\n");
}

int main() {
	int array[7][4]={0};
	char Player[2][20];

	printf("\n1. Oyuncu: ");
	scanf("%s", Player[0]);
	printf("\n2. Oyuncu: ");
	scanf("%s", Player[1]);

	char win[20];
	int arr, index, num, queue;
	int x=0;

	int playSize = 28;
	while(1) {
		strcpy(win, Player[x++]);
		printf("\nSiradaki oyuncu: %s\n\n", win);
		printBoard(array);
		if(x == 2) { x = 0; }

		do {
			printf("\nLutfen belirlenen sayilar arasindan giris yapiniz.\n\n");
			printf("Dizi sec(1-4): ");
			scanf("%d", &arr);
			printf("\nindex sec(1-7): ");
			scanf("%d", &index);
		} while(!(arr > 0 && arr <= 4) || !(index > 0 && index <= 7));

		printf("\nNumara gir: ");
		scanf("%d", &num);

		array[index-1][arr-1] = num;
		playSize--;

		if(ctrl(array)) {
			printf("\nOyun bitti\n");
			printf("\nKazanan >> %s\n\n", win);
			break;
		}
		if(playSize == 0) {
			printf("\nTum diziler doldu ve Kazanan olmadi :(\n\n");
			break;
		}
	}
	return 0;
}
