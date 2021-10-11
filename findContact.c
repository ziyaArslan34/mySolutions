#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100][30];
	char phoneNumber[100][30];
	size_t size;
}contact_t;

/*
	N:;name;;;
	FN:name surname
	TEL;CELL;PREF:phoneNumber
*/

void init(contact_t *cnt) {
	FILE *file = fopen("persons.txt", "r");

	if(file == NULL) {
		perror("persons.txt is null\n");
		return;
	}

	(*cnt).size = 0;

	while(!feof(file)) {
		fscanf(file, "%s%s", (*cnt).name[(*cnt).size], (*cnt).phoneNumber[(*cnt).size]);
		(*cnt).size++;
	}

	fclose(file);
	puts("persons.txt is read finish\n");
}

int main() {
	contact_t cnt;
	init(&cnt);

	FILE *file1 = fopen("contact.vcf", "rb"); // read file
	FILE *file2 = fopen("newContact.vcf", "wb"); // write file

	if(file1 == NULL || file2 == NULL) {
		printf("file is nulll\n");
		return -1;
	}

	while(!feof(file1)) {
		char line[1024], temp[1024];

		fgets(line, sizeof(line), file1); // get .vcf
		line[strlen(line)-1] = '\0'; // strip '\n'

		if(line[0] == 'N' && line[1] == ':') {
			if(cnt.size >= 0) {
				sprintf(temp, "N:;%s;;;", cnt.name[cnt.size]);
				fprintf(file2, "%s\n", temp);
			} else {
				perror("cnt.size() error!\n");
				fprintf(file2, "N:;errorr;;;\n");
			}
		} else if(line[0] == 'F' && line[1] == 'N') {
			if(cnt.size >= 0) {
				sprintf(temp, "FN%s", cnt.name[cnt.size]);
				fprintf(file2, "%s\n", temp);
			} else {
				perror("cnt.size() error!\n");
				fprintf(file2, "FNerrorr\n");
			}
		} else if(line[0] == 'T' && line[1] == 'E') {
			if(cnt.size >= 0) {
				sprintf(temp, "TELL;CELL;PREF:%s", cnt.phoneNumber[cnt.size]);
				fprintf(file2, "%s\n", temp);
			} else {
				perror("cnt.size() error!\n");
				fprintf(file2, "TELL;CELL;PREF:errorrr\n");
			}
		} else {
			fprintf(file2, "%s\n", line);
		}

		cnt.size++;
	}

	printf("operation is successfully :)\n");

	fclose(file1);
	fclose(file2);

	return 0;
}
