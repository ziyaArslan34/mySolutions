#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	FILE *fptr = fopen("info.txt", "w");

	FILE *domainFile = fopen("domain.txt", "r");
	char line[1024];

	while(!feof(domainFile)) {
		fgets(line, sizeof(line), domainFile);
		line[strlen(line)-1] = '\0';

		char cmd[1024];

		sprintf(cmd, "host %s > temp.txt", line);
		system(cmd);

		FILE *tempFile = fopen("temp.txt", "r");
		char sline[1024];
		fgets(sline, sizeof(sline), tempFile);
		sline[strlen(sline)-1] = '\0';

		//printf("\nsline: %s\n", sline);

		type_t word = createWord(sline, " ");
		//printArray(&word);

		fprintf(fptr, "%s\n", returnIp(&word));
		destroy(&word);
		fclose(tempFile);
	}

	fclose(fptr);
	fclose(domainFile);
}
