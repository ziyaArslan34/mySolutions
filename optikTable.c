#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

#define ROW 10
#define COL 10

void printTable(char code[][COL], int *arr) {
        printf("\n   ");

        for(int i=0;i<ROW;i++) printf("\e[90m%d ", arr[i]);
        printf("\n  ");
        for(int i=0;i<20;i++) printf("\e[90m%c", '_');
        printf("\n");

        for(int i=0;i<ROW;i++) {
                printf("\e[90m%d |", i);

                for(int j=0;j<COL;j++) {
                        if(code[i][j] <= 122 && code[i][j] >= 97) {
                                printf("\e[91m%c\e[90m|", code[i][j]);
                        } else {
                                printf("\e[90m%c\e[90m|", code[i][j]);
                        }
                }

                printf("\n");
        }

        char ch = '\xF8'; /*'¯'*/

        printf("  ");

        for(int i=0;i<20;i++) printf("\e[90m%c", ch);
        printf("\n");
}

int sep(int *arr, long int num) {
        int ln, i=9;

        if(/*num < 100000000 ||*/ num > 9999999999) {
                return 0;
        }

        while(num > 0) {
                ln = num%10;
                num /= 10;
                arr[i--] = ln;
        }
        return 1;
}

void starMap(char code[][COL], int *arr) {
        for(int i=0;i<ROW;i++) {
                for(int j=0;j<COL;j++) {
                        if(arr[j] == i) {
                                code[i][j] = (char)rand()%(122-97)+97;
                        }
                }
        }
}

int main() {
        srand(time(NULL));
        setlocale(LC_ALL, "utf-8");

        //while(1) {
                system("clear");
                int arr[10]={0};

                char code[ROW][COL] = {
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
                };

                long int num;

                printf("\nSayi gir: ");
                scanf("%ld", &num);  // sayilari manuel girmek isterseniz

        //      num = (long int)rand()%(999999999-100000000)+100000000;

                if(sep(arr, num)) {
                        starMap(code, arr);
                        printTable(code, arr);
                } else {
                        printf("\nLutfen 10 basamaktan fazla sayi girmeyin!\n");
                }
        //}

        return 0;
}
