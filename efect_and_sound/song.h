#ifndef _SONG_H_
#define _SONG_H_

#include <sys/stat.h>
#include <sys/mman.h>
#include <mad.h>
#include <pulse/simple.h>
#include <pulse/error.h>

void  output(struct mad_header const *, struct mad_pcm *, int*, pa_simple*);
void* play_song(void*);


#endif /* song.h */
