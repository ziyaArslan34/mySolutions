#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"
#include <stdlib.h>
#include <string.h>

struct data {
	int flag;
	char name[15];
};

int main(int argc, char **argv) {
	if(argc != 2) {
		fprintf(stderr, "usage: { a.out <filename> }\n");
		return 255;
	}

	struct data flag;
	flag.flag = 0;
	strcpy(flag.name, argv[1]);

	pthread_t th1, th2;

	pthread_create(&th1, NULL, play_efect, &flag);
	pthread_create(&th2, NULL, play_song, &flag);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
}
