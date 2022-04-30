#include <stdio.h>
#include "include/efect.h"
#include <pthread.h>
#include <unistd.h>
#include "include/song.h"

#include <sys/stat.h>
#include <sys/mman.h>
#include <mad.h>
#include <pulse/simple.h>
#include <pulse/error.h>


int main() {
	pthread_t th1, th2;

	pthread_create(&th1, NULL, play_efect, "efect");
	pthread_create(&th2, NULL, play_song, "song");
	sleep(240);
}
