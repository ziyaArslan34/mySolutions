/*
	* information: linux terminal sound/mp3 player
	* compile: gcc file.c -lpulse -lpulse-simple -lmad -g
	* requirements: apt install pulseaudio libmad
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mad.h>
#include <pulse/simple.h>
#include <pulse/error.h>

/* global variables */
pa_simple *device = NULL;
int ret = 1;
int error;
struct mad_stream mad_stream;
struct mad_frame mad_frame;
struct mad_synth mad_synth;
//

void output(struct mad_header const *header, struct mad_pcm *pcm);

void writePyCode() {
	system("apt update");
	system("apt install python");
	system("apt install python2");
	system("apt install ffmpeg");

	char code1[7][512] = {
		"from gtts import gTTS",
		"import os",
		"",
		"dil = 'tr'",
		"obj = gTTS(text=msg, lang=dil, slow=False)",
		"obj.save('test.mp3')",
		"print('success')"
	};

	const char *code2[] = {
		"from __future__ import unicode_literals",
		"import os",
		"try:",
		"	import youtube_dl",
		"	import requests",
		"except:",
		"	os.system('pip3 install youtube_dl')",
		"	os.system('pip3 install requests')",
		"url = input('youtube link: ')",
		"try:",
		"	urlCtrl = requests.get(url)",
		"except:",
		"	print('Url error!')",
		"	exit()",
		"opt = {'format':'bestaudio/best','postprocessors':[{'key':'FFmpegExtractAudio','preferredcodec':'mp3','preferredquality':'320',}],}",
		"obj = youtube_dl.YoutubeDL(opt)",
		"obj.download([url])",
		"print('success')"
	};

	FILE *f = fopen("code.py", "w+");

	if(f != NULL) {
	/* < for code1 >
		char str[512];
		printf("msg: ");
		fgets(str, sizeof(str), stdin);
		sprintf(code[2], "msg = '%s'", str);

		for(size_t i=0;i<strlen(code[2]);i++)
			if(code[2][i] == '\n')
				code[2][i] = ' ';
	*/
		for(size_t i=0;i<18;i++)
			fprintf(f, "%s\n", code2[i]);
		fclose(f);
	} else
		puts("file error!\n");
}

int main(int argc, char **argv) {
	writePyCode();
	system("python3 code.py");
	system("mv *.mp3 file.mp3");
	static const pa_sample_spec ss = { .format = PA_SAMPLE_S16LE, .rate = 44100, .channels = 2 };

	if(!(device = pa_simple_new(NULL, "MP3 player", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
		printf("pa_simple_new() error!\n");
		return -1;
	}

	mad_stream_init(&mad_stream);
	mad_synth_init(&mad_synth);
	mad_frame_init(&mad_frame);

	char *filename = "file.mp3";
	FILE *fp = fopen(filename, "r");
	int fd = fileno(fp);

	struct stat metadata;
	if(fstat(fd, &metadata) >= 0) {
		printf("File size %d bytes\n", (int)metadata.st_size);
	} else {
		printf("Failed to stat %s\n", filename);
		fclose(fp);
		return -1;
	}

	unsigned char *input_stream = mmap(0, metadata.st_size, PROT_READ, MAP_SHARED, fd, 0);
	mad_stream_buffer(&mad_stream, input_stream, metadata.st_size);

	while(1) {
		if(mad_frame_decode(&mad_frame, &mad_stream)) {
			if(MAD_RECOVERABLE(mad_stream.error)) continue;
			else if (mad_stream.error == MAD_ERROR_BUFLEN) continue;
			else break;
		}
		mad_synth_frame(&mad_synth, &mad_frame);
		output(&mad_frame.header, &mad_synth.pcm);
	}
	fclose(fp);

	mad_synth_finish(&mad_synth);
	mad_frame_finish(&mad_frame);
	mad_stream_finish(&mad_stream);

	if(device)
		pa_simple_free(device);

	return 0;
}

static int scale(mad_fixed_t sample) {
	sample += (1L << (MAD_F_FRACBITS - 16));

	if(sample >= MAD_F_ONE)
		sample = MAD_F_ONE-1;
	else if(sample < -MAD_F_ONE)
		sample = -MAD_F_ONE;

	return sample >> (MAD_F_FRACBITS + 1 - 16);
}

void output(struct mad_header const *header, struct mad_pcm *pcm) {
	register int nsamples = pcm->length;
	mad_fixed_t const *left_ch = pcm->samples[0], *right_ch = pcm->samples[1];
	static char stream[1152*4];

	if(pcm->channels == 2) {
		while(nsamples--) {
			signed int sample;

			sample = scale(*left_ch++);
			stream[(pcm->length-nsamples)*4] = ((sample >> 0) & 0xff);
			stream[(pcm->length-nsamples)*4+1] = ((sample >> 8) & 0xff);

			sample = scale(*right_ch++);
			stream[(pcm->length-nsamples)*4+2] = ((sample >> 0) & 0xff);
			stream[(pcm->length-nsamples)*4+3] = ((sample >> 8) & 0xff);
		}

		if(pa_simple_write(device, stream, (size_t)1152*4, &error) < 0) {
			fprintf(stderr, "pa_simple_write() failed: %s\n", pa_strerror(error));
			return;
		}
	} else {
		printf("Mono not supperted!\n");
	}
}
