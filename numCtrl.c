#include <stdio.h>
#include <string.h>

#define true 1
#define false 0

typedef int bool;

bool ctrl(const char *data) {
	for(int i=0;i<strlen(data);i++)
		if(!((data[i] >= 48 && data[i] <= 57) || data[0] == '-'))
			return false;
	return true;
}

int main() {
	while(1) {
		char num[10];

		printf("sayi gir: ");
		fgets(num, sizeof(num), stdin);
		num[strlen(num)-1] = '\0';

		if(ctrl(num)) {
			printf("Sayi girisi basarili :)\n");
			printf("Sayi: %d\n", atoi(num));
			break;
		}

		printf("Yanlis sayi girisi. Tekrar dene\n");
	}

	return 0;
}
