#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"

int main() {
	pthread_t th1, th2;

	int eof = 0;

	pthread_create(&th1, NULL, play_song, &eof);
	pthread_create(&th2, NULL, play_efect, &eof);

	sleep(255);
}
