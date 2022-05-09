#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"
#include <stdlib.h>

int main(void) {
	pthread_t th1, th2;

	int flag = 0;

	pthread_create(&th1, NULL, play_efect, &flag);
	pthread_create(&th2, NULL, play_song, &flag);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
}
