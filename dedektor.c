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

	new_.c_lflag &= (unsigned)~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_);

	return ch;
}

void point_object(int (*map)[][SIZE], point_t *object) {
	(*map)[my_rand(0, SIZE-1)][my_rand(0,SIZE-1)] = 1;
	for(size_t i=0;i<SIZE;i++) {
		for(size_t j=0;j<SIZE;j++) {
			if((*map)[i][j]) {
				object->x = (int)i;
				object->y = (int)j;
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

int equal_controls(const point_t *p1, const point_t *p2) {
	return (p1->x == p2->x) && (p1->y == p2->y);
}

void print_map(int (*map)[][SIZE], const point_t *dedector) {
	(*map)[dedector->x][dedector->y] = 2;

	printf("\n ");
	for(size_t i=0;i<SIZE*2+1;i++)
		printf("\e[90m_");
	printf("\n");

	for(size_t i=0;i<SIZE;i++) {
		printf("\e[90m |");
		for(size_t j=0;j<SIZE;j++) {
			if((*map)[i][j] == 2) {
				printf("\e[91mx\e[90m|");
			} else {
				printf("\e[91m \e[90m|");
			}
		}
		printf("\n");
	}

	printf(" ");
	for(size_t i=0;i<SIZE*2+1;i++)
		printf("\e[90m_");
	printf("\n");
	(*map)[dedector->x][dedector->y] = 0;
}

int main() {
	srand((unsigned)time(NULL));
	int map[SIZE][SIZE] = {0};

	point_t object, dedector = {my_rand(0,SIZE-1),my_rand(0,SIZE-1)};

	point_object(&map, &object);

	if(equal_controls(&object, &dedector)) {
		printf("zaten ikisi ayni yerde :D\n");
		return 0;
	}

	double oldDistance, newDistance=0;
	size_t move=0;

	printf("ilerlemek icin a,d,s,w tuslarini kullanin..\n\n");

	do {
		oldDistance = newDistance;

		//printf("suanki konum: [%d][%d]\n", dedector.x, dedector.y);
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
				continue;
		}

		newDistance = distance_calc(&object, &dedector);

		system("clear");
		if(oldDistance > newDistance)
			printf("yakinlasiyorsunuz.. mesafe: %.3lf\n", newDistance);
		else
			printf("uzaklasiyorsunuz..  mesafe: %.3lf\n", newDistance);
		print_map(&map, &dedector);
	}while(!equal_controls(&object, &dedector));

	printf("%zu. hamlede [%d][%d] konumunda nesne bulundu...\n", move, object.x, object.y);
}
