#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct USER {
	char name[15], surname[15];
	long int accountNo;
	double balance;
};

typedef struct _LL {
	struct USER user;
	struct _LL *next;
}LL;

LL *make(char *name, char *surname) {
	LL *newNode = (LL*)malloc(sizeof(LL));
	strcpy(newNode->user.name, name);
	strcpy(newNode->user.surname, surname);

	long int accountNo = rand()%(10000000000-1000000000+1)+1000000000;

	newNode->user.accountNo = accountNo;
	newNode->user.balance = 0.0;

	newNode->next = NULL;

	return newNode;
}

LL *addAccount(LL *account, char *name, char *surname) {
	if(account == NULL) {
		account = make(name, surname);
		return account;
	}

	LL *tmp = account;

	while(tmp->next != NULL) tmp = tmp->next;

	tmp->next = make(name, surname);
	return account;
}

int delAccount(LL **account, long int accountNo) {
	if(*account == NULL) return 0;

	LL *iter = *account;

	int index=1, flag=0;

	while(iter->next != NULL) {
		if(iter->user.accountNo == accountNo) {
			flag = 1;
			break;
		}

		iter = iter->next;
		index++;
	}

	iter = *account;
	for(int i=0;i<index-2;i++)
		iter = iter->next;

	iter->next = iter->next->next;

	if(flag == 0)
		return 0;

	return 1;
}

void printAllAccount(LL *accounts) {
	if(accounts == NULL) {
		printf("\nAccounts is empty.\n");
		return;
	}

	int i=1;

	LL *account = accounts;

	system("clear || cls");
	printf("\n\n");

	while(account->next != NULL) {
		printf("## %d. USER ##\n", i++);
		printf("Name      : %s\n", account->user.name);
		printf("Surname   : %s\n", account->user.surname);
		printf("Account no: %ld\n", account->user.accountNo);
		printf("Balance   : %lf\n\n", account->user.balance);

		account = account->next;
	}
	printf("## %d. USER ##\n", i);
	printf("Name      : %s\n", account->user.name);
	printf("Surname   : %s\n", account->user.surname);
	printf("Account no: %ld\n", account->user.accountNo);
	printf("Balance   : %lf\n\n", account->user.balance);
	printf("\n\n");
}

int searchAccount(LL *account, long int accountNo) {
	if(account == NULL) {
		printf("Not added account.\n");
		return 0;
	}

	LL *tmp = account;

	do {
		if(tmp->user.accountNo == accountNo) {
			printf("\n\n");
			printf("Name      : %s\n", tmp->user.name);
			printf("Surname   : %s\n", tmp->user.surname);
			printf("Account no: %ld\n", tmp->user.accountNo);
			printf("Balance   : %lf\n\n", tmp->user.balance);
			printf("\n\n");
			return 1;
		}
		tmp = tmp->next;
	} while(tmp->next != NULL);

	return 0;
}

void getBalance(LL *account, long int accountNo) { // TODO
	if(account == NULL) {
		printf("\nAccount is empty.\n");
		return;
	}

	LL *tmp = account;
	do {
		if(tmp->user.accountNo == accountNo) {
			printf("\n\n");
			printf("Name      : %s\n", tmp->user.name);
			printf("Surname   : %s\n", tmp->user.surname);
			printf("Account no: %ld\n", tmp->user.accountNo);
			printf("Balance   : %lf\n\n", tmp->user.balance);
			printf("\n\n");
			return /*tmp->user.balance*/;
		}

		tmp = tmp->next;
	} while(tmp->next != NULL);

	printf("\nAccount is empty.\n");
}

void paraYatir(LL *account, long int accountNo) {
	if(account == NULL) {
		printf("\nAccount is empty.\n");
		return;
	}

	double balance;
	printf("\nBalance?: ");
	scanf("%lf", &balance);

	LL *tmp = account;

	do {
		if(tmp->user.accountNo == accountNo) {
			tmp->user.balance += balance;
			getBalance(tmp, accountNo);
			return;
		}
		tmp = tmp->next;
	} while(tmp->next != NULL);

	printf("\n%ld not found.\n", accountNo);
}

void paraCek(LL *account, long int accountNo) {
	if(account == NULL) {
		printf("\nAccount is empty.\n");
		return;
	}

	double balance;
	printf("\nBalance?: ");
	scanf("%lf", &balance);

	LL *tmp = account;

	do {
		if(tmp->user.accountNo == accountNo) {
			if(tmp->user.balance < balance) {
				printf("\n%ld account not %lf balance\n", accountNo, balance);
				return;
			} else {
				tmp->user.balance -= balance;
				getBalance(tmp, accountNo);
				return;
			}
		}

		tmp = tmp->next;
	} while(tmp->next != NULL);

	printf("\n%ld not found.\n", accountNo);
}

void menu1() {
	printf("\nNew account     [1]");
	printf("\nSearch account  [2]");
	printf("\nDel account     [3]");
	printf("\nprintAllAccount [4]");
	printf("\nGet Balance     [5]");
	printf("\nPara yatirma    [6]");
	printf("\nPara cekme      [7]\n");
}

int ctrlCho(char *cho) {
	int flag=0;

	for(size_t i=0;i<strlen(cho);i++)
		if(cho[i] >= 48 && cho[i] <= 57)
			flag++;
	return (flag == 1);
}

int main() {
	srand((unsigned)time(NULL));

	LL *accounts = NULL;

	char cho[10]={0};
	char name[15], surname[15];
	long int accountNo;

	while(!(strcmp(cho, "exit") == 0)) {
		menu1();

		printf("\nCho: ");
		scanf("%s", cho);

		if(ctrlCho(cho)) {
			int choo = atoi(cho);
			switch(choo) {
				case 1:
					printf("\nYour name?: ");
					scanf("%s", name);
					printf("\nYour surname?: ");
					scanf("%s", surname);

					accounts = addAccount(accounts, name, surname);
					break;
				case 2:
					printf("\nAccount no?: ");
					scanf("%ld", &accountNo);

					if(searchAccount(accounts, accountNo)) {}
					else {
						printf("\nSearched account not found.\n");
					}
					break;
				case 3:
					printf("\nAccount no?: ");
					scanf("%ld", &accountNo);

					if(delAccount(&accounts, accountNo)) {
						printf("\n%ld account deleted.\n", accountNo);
					} else {
						printf("\nAccount is not found.\n");
					}
					break;
				case 4:
					printAllAccount(accounts);
					break;
				case 5:
					printf("\nAccount no?: ");
					scanf("%ld", &accountNo);

					getBalance(accounts, accountNo);
					break;
				case 6:
					printf("\nAccount no?: ");
					scanf("%ld", &accountNo);

					paraYatir(accounts, accountNo);
					break;
				case 7:
					printf("\nAccount no?: ");
					scanf("%ld", &accountNo);

					paraCek(accounts, accountNo);
					break;
				default:
					system("clear || cls");
					printf("\nChooice not found.Please try again\n");
					break;
			}
		} else {
			system("clear || cls");
			printf("\nIncorrect entry\n");
		}
	}

	free(accounts);
	return 0;
}
