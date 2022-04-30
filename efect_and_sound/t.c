#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *file = fopen("song.mp3", "rb");

	while(!feof(file)) {
		char ch;
		fread(&ch, sizeof(ch), 1, file);
	}

	fclose(file);
}
