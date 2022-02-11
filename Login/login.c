#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "split.h"

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

void debug(size_t x) { printf("debug: %zu\n", x); }

void sing_in() {
	user_t user;
	size_t flag=0;

	printf("username: ");
	scanf("%s", user.username);
	printf("password: ");
	scanf("%s", user.password);

	FILE *rFile = fopen("users.txt", "r");

	while(!feof(rFile)) {
		char line[1024];
		fgets(line, sizeof(line), rFile);
		line[strlen(line)-1] = '\0';
		type_t split = split_str(line, " {");
		if(search(&split, user.username)) {
			hash_t hash = init_hash();
			type_t pass = split_str(line, "[]");
			hash.size--;

			for(size_t i=0;i<pass.size-1;i++)
				push_back_hash(&hash, atoi(pass.array[i]));
			hash.key = atoi(split_str(line, "()").array[1]);
			char *passw = decrypt(&hash);

			if(strcmp(passw, user.password) == 0)
				flag = 1;

			free(passw);
			destroy_hash(&hash);
			destroy_split(&pass);
			destroy_split(&split);

			break;
		}
		destroy_split(&split);
	}

	fclose(rFile);

	if(!flag) {
		printf("login failure!\n");
		return;
	} else {
		printf("login succcess\n");
	}
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
	fprintf(fptr, "}(%d)\n\n", hash.key);

	printf("\nadded new user\n");
	destroy_hash(&hash);
}

int main() {
	//FILE *users = fopen("users.txt", "w+");

	int choice;
	menu();
	printf("choice: ");
	scanf("%d",&choice);

	switch(choice) {
		case 0:
			//fclose(users);
			exit(0);
			break;
		case 1:
			sing_in();
			break;
		case 2:
			//sing_up(users);
			break;
		default:
			printf("invalid choice!\n");
			break;
	}

	//fclose(users);
}
