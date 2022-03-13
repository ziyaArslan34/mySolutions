#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>

#define SIZE 15

typedef struct {
	int x,y;
}point_t;

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int kbhit() {
	struct termios old_, new_;
	int ch;

	tcgetattr(STDIN_FILENO, &old_);
	new_ = old_;

	new_.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_);

	return ch;
}

void point_gold(int (*array)[][SIZE], point_t *gold) {
	(*array)[my_rand(0, SIZE-1)][my_rand(0,SIZE-1)] = 1;
	for(size_t i=0;i<SIZE;i++) {
		for(size_t j=0;j<SIZE;j++) {
			if((*array)[i][j]) {
				gold->x = (int)i;
				gold->y = (int)j;
				break;
			}
		}
	}
}

double distance_calc(const point_t *p1, const point_t *p2) {
	return (sqrt(pow((p1->x-p2->x),2) + pow((p1->y-p2->y),2)));
}

void advance_right(point_t *dedector) {
	if(dedector->y == SIZE-1)
		dedector->y = 0;
	else
		dedector->y++;
}

void advance_left(point_t *dedector) {
	if(dedector->y == 0)
		dedector->y = SIZE-1;
	else
		dedector->y--;
}

void advance_up(point_t *dedector) {
    if(dedector->x == 0)
        dedector->x = SIZE-1;
    else
        dedector->x--;
}

void advance_down(point_t *dedector) {
    if(dedector->x == SIZE-1)
        dedector->x = 0;
    else
        dedector->x++;
}

int equal(const point_t *p1, const point_t *p2) {
	return (p1->x == p2->x) && (p1->y == p2->y);
}

int main() {
	srand((unsigned)time(NULL));
	int array[SIZE][SIZE] = {0};

	point_t gold, dedector = {my_rand(0,SIZE-1),my_rand(0,SIZE-1)};

	point_gold(&array, &gold);

	if(equal(&gold, &dedector)) {
		printf("zaten ikisi ayni yerde :D\n");
		return 0;
	}

	double oldDistance, newDistance=0;
	size_t move=0;

	printf("ilerlemek icin a,d,s,w tuslarini kullan\n\n");

	do {
		oldDistance = newDistance;

		printf("suanki konum: [%d][%d]\n", dedector.x, dedector.y);
		char road = (char)kbhit();
		move++;
		switch(road) {
			case 'a':
				advance_left(&dedector);
				break;
			case 'd':
				advance_right(&dedector);
				break;
			case 'w':
				advance_up(&dedector);
				break;
			case 's':
				advance_down(&dedector);
				break;
			default:
				printf("Hatali yon!..\n");
				move--;
		}

		newDistance = distance_calc(&gold, &dedector);

		if(oldDistance > newDistance)
			printf("yakinlasiyo.. mesafe: %.3lf\n", newDistance);
		else
			printf("uzaklasiyo..  mesafe: %.3lf\n", newDistance);

	}while(!equal(&gold, &dedector));

	printf("%zu. hamlede [%d][%d] konumunda aranan bulundu...\n", move, gold.x, gold.y);
}
