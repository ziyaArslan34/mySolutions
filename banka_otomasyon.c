#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __unix
	#define CLEAR system("clear")
#else
	#define CLEAR system("cls")
#endif

struct User {
	char name[10], surname[15];
	double balance;
	int id;
};

struct Accounts {
	const char *log_file, *log_mode;
	char line_log[1024];
	FILE *log;
	struct User *user;
	size_t size, cap;
};

typedef struct User user_t;
typedef struct Accounts account_t;

void write_log(account_t *account) {
	if((account->log = fopen(account->log_file, account->log_mode)) == NULL) {
		fprintf(stderr, "file error\n");
		exit(2);
	}

	fprintf(account->log, "%s", account->line_log);
	fclose(account->log);
}

user_t create_user(const char *name, const char *surname, int id) {
	user_t user;
	strcpy(user.name, name);
	strcpy(user.surname, surname);
	user.id = id;
	user.balance = 0;

	return user;
}

const char *current_date(void) {
	time_t start = time(NULL);
	return ctime(&start);
}

account_t init_account(size_t sz) {
	account_t account;
	account.size = 0;
	account.cap = sz;

	account.log_file = "logs.txt";
	account.log_mode = "a+";

	if((account.log = fopen("logs.txt", "a+")) == NULL) {
		fprintf(stderr, "file error\n");
		exit(2);
	}

	snprintf(account.line_log, 1024, "\n[Kayit dosyasi olusturuldu.] [%.*s]\n\n", (int)strlen(current_date())-1, current_date());
	write_log(&account);

	if((account.user = (user_t*)malloc(sizeof(user_t)*sz)) == NULL) {
		fprintf(stderr, "memory error\n");
		exit(1);
	}

	return account;
}

void destroy_account(account_t *account) {
	if(account->user) {
		free(account->user);
		account->user = NULL;
	}

	if(account->log) {
		snprintf(account->line_log, 1024, "\nProgram kapatildi. Tum hesaplar silindi. [%.*s]\n", (int)strlen(current_date())-1, current_date());
		write_log(account);
		fclose(account->log);
		account->log = NULL;
	}
}

int find_user_id(const account_t *account, int id) {
	for(size_t i=0;i<account->size;i++)
		if(account->user[i].id == id)
			return 1;
	return 0;
}

size_t find_user(const account_t *account, const user_t *user) {
	for(size_t i=0;i<account->size;i++)
		if(!strcmp(user->name, account->user[i].name)
			&& !strcmp(user->surname, account->user[i].surname)
			&& user->id == account->user[i].id )
			return i;

	return account->size;
}

void add_user(account_t *account, const user_t *user) {
	if(find_user_id(account, user->id)) {
		printf("Bu id kullanilmaktadir.Baska bi id deneyin.\n");
		return;
	}

	if((account->log = fopen(account->log_file, account->log_mode)) == NULL) {
		fprintf(stderr, "file error\n");
		destroy_account(account);
		exit(2);
	}

	snprintf(account->line_log, 1024, "Kullanici eklendi [{%s} {%s} {%d} {%.3lf}] [%.*s]\n",user->name, user->surname, user->id, user->balance, (int)strlen(current_date())-1, current_date());
	write_log(account);

	if(account->size >= account->cap) {
		account->cap *= 2;
		if((account->user = (user_t*)realloc(account->user, sizeof(user_t)*account->cap)) == NULL) {
			fprintf(stderr, "memory error\n");
			destroy_account(account);
			exit(1);
		}
	}

	account->user[account->size++] = *user;
}

static int left_shift(void *array, size_t type, size_t size, int cnt) {
	for(int i=0;i<cnt;i++) {
		void *tmp = malloc(type);
		if(!tmp)
			return 0;
		memcpy(tmp, (char*)array + 0 * type, type);
		for(size_t j=0;j<size-1;j++)
			memcpy((char*)array + j * type, (char*)array + ((j+1) * type), type);
		memcpy((char*)array + ((size-1) * type), tmp, type);
		free(tmp);
	}
	return 1;
}

void del_user(account_t *account, user_t *user) {
	size_t idx = find_user(account, user);
	if(idx == account->size) {
		printf("Kisi kayitlarda yok.\n");
		return;
	}

	if((account->log = fopen(account->log_file, account->log_mode)) == NULL) {
		fprintf(stderr, "file error\n");
		destroy_account(account);
		exit(2);
	}

	snprintf(account->line_log, 1024, "Kullanici silindi [{%s} {%s} {%d} {%.3lf}] [%.*s]\n",user->name, user->surname, user->id, user->balance, (int)strlen(current_date())-1, current_date());
	write_log(account);

	if(!left_shift(account->user, sizeof(user_t), account->size, (int)idx+1)) {
		fprintf(stderr, "memory error\n");
		destroy_account(account);
		exit(1);
	}
	--account->size;
}

void print_function(const user_t *user) {
	printf("\nIsim    : %s\n", user->name);
	printf("Soyisim : %s\n", user->surname);
	printf("Id      : %d\n", user->id);
	printf("Bakiye  : %.3lf\n", user->balance);
}

void print_user(const account_t *account, size_t idx) {
	print_function(account->user + idx);
}

void print_all_user(const account_t *account) {
	for(size_t i=0;i<account->size;i++)
		print_function(account->user + i);
}

double add_balance(account_t *account, const user_t *user, double balance) {
	size_t res = find_user(account, user);
	if(res != account->size) {
		account->user[res].balance += balance;
		snprintf(account->line_log, 1024, "Kullanici[{%s} {%s} {%d} {%.3lf}] hesaba %.3lf tl para yatirdi.[%.*s]\n", user->name, user->surname, user->id, user->balance, balance, (int)strlen(current_date())-1, current_date());
		write_log(account);
	} else {
		return 0.0;
	}
	return balance;
}

double sub_balance(account_t *account, const user_t *user, double balance) {
	size_t res = find_user(account, user);
	if(res != account->size) {
		if(account->user[res].balance < balance)
			return 0.0;
		account->user[res].balance -= balance;
		snprintf(account->line_log, 1024, "Kullanici[{%s} {%s} {%d} {%.3lf}] hesaptan %.3lf tl para cekti.[%.*s]\n", user->name, user->surname, user->id, user->balance, balance, (int)strlen(current_date())-1, current_date());
		write_log(account);
	} else {
		return 0.0;
	}
	return balance;
}

int money_transfer(account_t *account) {
	user_t u1, u2;
	double balance;
	printf("Kaynak hesap girin(ad, soyad, id): ");
	scanf("%s%s%d", u1.name, u1.surname, &u1.id);

	if(find_user(account, &u1) == account->size) {
		printf("Kaynak hesap bulunamadi\n");
		return -1;
	}

	printf("Aktarmak istediginiz miktar: ");
	scanf("%lf", &balance);

	printf("Aktarmak istediginiz hesap(ad, soyad, id): ");
	scanf("%s%s%d", u2.name, u2.surname, &u2.id);

	if(find_user(account, &u2) == account->size) {
		printf("Hedef hesap bulunamadi\n");
		return -1;
	}

	if(add_balance(account, &u2, sub_balance(account, &u1, balance)) == balance) {
		snprintf(account->line_log, 1024, "[{%s} {%s} {%d}] -> [{%s} {%s} {%d}] -> %.3lf [%.*s]\n", u1.name, u1.surname, u1.id, u2.name, u2.surname, u2.id, balance, (int)strlen(current_date())-1, current_date());
		write_log(account);
		return 1;
	}
	return 0;
}

void menu(void) {
	printf("\nHesap ekle           [1]");
	printf("\nHesap sil            [2]");
	printf("\nHesap ara            [3]");
	printf("\nPara cek             [4]");
	printf("\nPara yatir           [5]");
	printf("\nTum hesaplari goster [6]");
	printf("\nPara transferi       [7]\n");
	printf("\nExit                 [0]\n\n");
}

int main(void) {
	account_t account = init_account(10);

	while(1) {
		user_t user;
		int choice;
		size_t idx;
		double balance;

		menu();
		printf("Secim: ");
		scanf("%d", &choice);

		switch(choice) {
			case 0:
				destroy_account(&account);
				return 0;
			case 1:
				CLEAR;
				printf("Ad soyad ve id girin: ");
				scanf("%s%s%d", user.name, user.surname, &user.id);
				add_user(&account, &user);
				break;
			case 2:
				CLEAR;
				printf("Ad soyad ve id girin: ");
				scanf("%s%s%d", user.name, user.surname, &user.id);
				del_user(&account, &user);
				break;
			case 3:
				CLEAR;
				printf("Ad soyad ve id girin: ");
				scanf("%s%s%d", user.name, user.surname, &user.id);
				idx = find_user(&account, &user);
				if(idx == account.size)
					printf("Kullanici bulunamadi.\n");
				else
					print_user(&account, idx);
				break;
			case 4:
				printf("Ad soyad ve id girin: ");
				scanf("%s%s%d", user.name, user.surname, &user.id);
				printf("Cekeceginiz tutari girin: ");
				scanf("%lf", &balance);
				sub_balance(&account, &user, balance);
				break;
			case 5:
				printf("Ad soyad ve id girin: ");
				scanf("%s%s%d", user.name, user.surname, &user.id);
				printf("Yatiracaginiz tutari girin: ");
				scanf("%lf", &balance);
				add_balance(&account, &user, balance);
				break;
			case 6:
				CLEAR;
				print_all_user(&account);
				break;
			case 7:
				money_transfer(&account);
				break;
			default:
				printf("Yanlis secim.\n");
		}
	}
}
