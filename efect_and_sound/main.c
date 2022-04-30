#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"

int main() {
	pthread_t th1, th2;

	pthread_create(&th1, NULL, play_efect, "efect");
	pthread_create(&th2, NULL, play_song, "efect");

	void *res = NULL;
	pthread_join(th2, &res);

	if(res) {
		return 0;
	}
}
