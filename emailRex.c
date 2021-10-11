#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ctrlEt(const char *email) {
	int flag=0;

	for(int i=0;i<strlen(email);i++)
		if(email[i] == '@')
			flag++;

	return (flag == 1);
}

int ctrl(const char *email) {
	const char *domain[] = {
		"gmail",
		"hotmail",
		"yandex",
		"outlook"
	};

	int flag = 0;

	if(ctrlEt(email)) {
		size_t size=0, cap=10;
		char *str = (char*)malloc(sizeof(char)*cap);

		for(int i=0;i<strlen(email);i++) {
			if(email[i] == '@') {
				for(int j=i+1;email[j] != '.' && j < strlen(email);j++) {
					if(size >= cap) {
						cap *= 2;
						str = (char*)realloc(str, sizeof(char)*cap);
					}

					str[size++] = email[j];
				}

				str[size++] = '\0';
			}
		}

		for(int i=0;i<4;i++)
			if(strcmp(domain[i], str) == 0) {
				flag = 1;
				break;
			}

		free(str);
	}

	return flag;
}

int main() {
	if(ctrl("ziya@gmail.com")) {
		printf("dogru\n");
	}
}
