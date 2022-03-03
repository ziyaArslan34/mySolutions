/* SNAKE GAME SAMPLE */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>

#ifdef WIN32
	#include <windows.h>
	#define SLEEP Sleep(1)
	#define CLEAR "cls"
#elif __unix__
	#include <unistd.h>
	#define CLEAR "clear"
	#define SLEEP usleep(90000)
#endif

#define X 20
#define Y 30

typedef struct {
	int x,y;
}snake_t;

int len=4;
int score=0;
int row=5, col=10;

char map[X][Y];

int kbhit() {
    struct termios term;
    tcgetattr(0, &term);

    struct termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

int continues(snake_t *snake) {
	int k1=0, k2=0;

	if(snake[0].x == 0 || snake[0].x == 19 || snake[0].y == 0 || snake[0].y == 39) {
		k1 = 1;
	}

	for(int i=1;i<len;i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			k2 = 1;
			break;
		}
	}

	return (k1 == 1 || k2 == 1);
}

void yemleme() {
	row = rand()%((X-2)-2+1)+2;
	col = rand()%((Y-2)-2+1)+2;
}

void yem(char arr[][Y], snake_t *snake) {
	if(snake[len-1].x == row && snake[len-1].y == col) {
		snake[len].x = row;
		snake[len].y = col;
		len++;
		score += 10;
		yemleme();
		printf("\a");
	}
}

void defend(char arr[][Y]) {
	for(int i=0;i<X;i++) {
		if(i == 0 || i == 19) {
			for(int j=0;j<Y;j++)
				arr[i][j] = '=';
		} else {
			arr[i][0] = '|';
			for(int j=1;j<Y-1;j++)
				arr[i][j] = ' ';
			arr[i][Y-1] = '|';
		}
	}

	map[row][col] = 'x';
}

void print(char arr[][Y]) {
	system(CLEAR);

	printf("score: %d\n", score);

	for(int i=0;i<X;i++) {
		for(int j=0;j<Y;j++) {
			if(arr[i][j] == '*')
				printf("\e[91m%c ", arr[i][j]);
			else if(arr[i][j] == 'x')
				printf("\e[93m%c ", arr[i][j]);
			else
				printf("\e[90m%c ", arr[i][j]);
		}
		printf("\n");
	}
}

void start(snake_t *snake) {
	snake[0].x = 1;
	snake[0].y = 4;

	snake[1].x = 1;
	snake[1].y = 3;

	snake[2].x = 1;
	snake[2].y = 2;

	snake[3].x = 1;
	snake[3].y = 1;
}

void snakeInfo(char arr[][Y], snake_t *snake) {
	yem(map, snake);

	for(int i=0;i<len;i++)
		arr[snake[i].x][snake[i].y] = '*';
}

void fright(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].y++;
}

void fleft(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].y--;
}

void fup(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x--;
}

void fdown(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x++;
}

void ctrlRight(long int *i, int *ctrl, snake_t *snake) {
	while(*i < 100000) {
		if(*i % 2000 == 0) {
			if(continues(snake)) {
				print(map);
				*ctrl = 1;
				break;
			}
			fright(snake, len);
			defend(map);
			snakeInfo(map, snake);
			print(map);
			SLEEP;
		}
		(*i)++;
		if(kbhit()) break;
	}
}

void ctrlLeft(long int *i, int *ctrl, snake_t *snake) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fleft(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			SLEEP;
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void ctrlUp(long int *i, int *ctrl, snake_t *snake) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fup(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			SLEEP;
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void ctrlDown(long int *i, int *ctrl, snake_t *snake) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fdown(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			SLEEP;
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void welcome() {
	printf("Yilan Oyunu\n\n");
	printf("Oyuna baslamak icin yon(a,w,s,d) tusuna basip enter yapin.\n");
	printf("sonrasinda artik a,w,s,d tuslarina basarak(enter yapmadan) hareket edebilirsiniz..\n");
	printf("\nKolay gelsin :)\n");
}

int main() {
	srand((unsigned)time(NULL));

	FILE *file = fopen("snake.txt", "w+");

	char name[30];
	printf("isminiz: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';

	char yon;
	snake_t snake[100];
	long int i;
	int ctrl=0;

	defend(map);
	start(snake);
	snakeInfo(map, snake);
	print(map);

	welcome();

	while(1) {
		yon = getchar();
		i=0;

		if(yon == 'd')
			ctrlRight(&i, &ctrl, snake);
		else if(yon == 'a')
			ctrlLeft(&i, &ctrl, snake);
		else if(yon == 'w')
			ctrlUp(&i, &ctrl, snake);
		else if(yon == 's')
			ctrlDown(&i, &ctrl, snake);
		else
			continue;

		if(ctrl == 1) break;
	}

	printf("Skorunuz: %d\n", score);

	fprintf(file, "isim: %s  >> Skor: %d\n", name, score);
	fclose(file);

	return 0;
}
