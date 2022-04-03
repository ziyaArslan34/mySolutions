#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"
#include "../split/split.h"

typedef struct {
	char username[30];
	char password[30];
}user_t;

void menu() {
	printf("\nWELCOME\n");
	printf("sing in [1]\n");
	printf("sing up [2]\n");
	printf("\nexit  [0]\n");
}

void debug(const char *dbg) { printf("debug: %s\n", dbg); }

void sing_in() {
	user_t user;
	size_t flag=0;

	FILE *fptr = fopen("users.txt", "r");

	printf("username: ");
	scanf("%s", user.username);
	printf("password: ");
	scanf("%s", user.password);

	while(!feof(fptr)) {
		char line[1024] = {0};

		fgets(line, sizeof(line), fptr);
		line[strlen(line)-1] = '\0';

		split_t spl1 = init_split(10);
		str_split(&spl1, line, NULL);
		if(search_split(&spl1, user.username)) {
			hash_t passw = init_hash();
			split_t psw = init_split(10);
			str_split(&psw, line, "{[]}()");

			for(size_t i=1;i<psw.size-1;i++) {
				push_back_hash(&passw, (int)atoi(psw.array[i]));
			}
			passw.key = atoi(psw.array[psw.size-1]);
			char *str = decrypt(&passw);

			if(strcmp(user.password, str) == 0) {
				flag = 1;
				destroy_split(&spl1);
				destroy_split(&psw);

				break;
			}
			free(str);
			destroy_split(&psw);
			destroy_hash(&passw);
		}
		destroy_split(&spl1);
	}

	if(!flag) {
		printf("login failure!\n");
		fclose(fptr);
		return;
	} else {
		printf("login succcess\n");
	}
	fclose(fptr);
}

void sing_up(FILE *fptr) {
	static int cnt=1;
	user_t user;

	printf("username: ");
	scanf("%s", user.username);
	printf("password: ");
	scanf("%s", user.password);

	fprintf(fptr, "user%d: %s{", cnt++, user.username);
	hash_t hash = init_hash();

	encrypt(&hash, user.password);
	for(size_t i=0;i<hash.size;i++)
		fprintf(fptr, "[%d]",hash.data[i]);
	fprintf(fptr, "}(%d)\n", hash.key);

	printf("\nadded new user\n");
	destroy_hash(&hash);
}

int main() {
	srand((unsigned)time(NULL));

	FILE *users = fopen("users.txt", "a+");
/*while(1) {*/
	int choice;
	menu();
	printf("choice: ");
	scanf("%d",&choice);

	switch(choice) {
		case 0:
			fclose(users);
			exit(0);
			break;
		case 1:
			sing_in();
			break;
		case 2:
			sing_up(users);
			break;
		default:
			printf("invalid choice!\n");
			break;
	}
	fclose(users);
}
