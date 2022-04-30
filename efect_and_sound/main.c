#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"

int main() {
	pthread_t th1, th2;

	pthread_create(&th1, NULL, play_efect, "efect");
	pthread_create(&th2, NULL, play_song, "efect");
	sleep(255);

	pthread_join(&th1, NULL);
	pthread_join(&th2, NULL);
}
