#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define NAMELEN 31
#define SENDLEN 201
#define MSGLEN 101
#define PORT 19073
#define KEY 7

void strTrimLF(char *arr, int len) {
    int i;
    for(i=0;i<len;i++) {
        if(arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

void strOverWrites() {
    printf("\r%s", "> ");
    fflush(stdout);
}

char *encode(char *buffer, int len) {
    char *temp = (char*)malloc(sizeof(char)*len);

    for(size_t i=0;i<len;i++) {
        temp[i] = buffer[i] + KEY;
    }

    return temp;
}

char *decode(char *buffer, int len) {
    char *temp = (char*)malloc(sizeof(char)*len);

    for(size_t i=0;i<len;i++) {
        temp[i] = buffer[i] - KEY;
    }

    return temp;
}

typedef struct ClientNode {
    int data;
    struct ClientNode *prev;
    struct ClientNode *link;
    char ip[16];
    char name[35];
}CliList;

CliList *newCli(int sockFd, char *ip) {
    CliList *tmp = (CliList*)malloc(sizeof(CliList));

    tmp->data = sockFd;
    tmp->prev = NULL;
    tmp->link = NULL;
    strncpy(tmp->ip, ip, 16);
    strncpy(tmp->name, "NULL", 5);

    return tmp;
}


int serverFd = 0;
int clientFd = 0;

CliList *root, *current;

FILE *file;

void initFile() {
	file = fopen("userInfo.txt", "w+");
}

void writesFile(char *name, char *ip, int data) {
	static int user = 1;

	if(file != NULL) {
		fprintf(file, "USER %d >> %s  %s  %d\n", user++, name, ip, data);
	} else {
		printf("\nFile is error!\n");
	}
}

void ctrlExit(int sig) {
	CliList *tmp;

	while(root != NULL) {
		printf("\nClose socketfd: %d\n", root->data);

		close(root->data);
		tmp = root;
		root = root->link;
		free(tmp);
	}

	printf("\nBye :)\n\n");
	exit(EXIT_SUCCESS);
}

void sendToAll(CliList *cli, char *buffer) {
	CliList *tmp = root->link;

	while(tmp != NULL) {
		if(cli->data != tmp->data) {
			printf("\nSend to sockfd %d: \"%s\" \n", tmp->data,buffer);
			send(tmp->data, buffer, SENDLEN, 0);
		}
		tmp = tmp->link;
	}
}

void cliHandler(void *cli) {
	int leaveFlag = 0;

	char nickName[NAMELEN] = {};
	char recvBuffer[MSGLEN] = {};
	char sendBuffer[SENDLEN] = {};

	char color[10];
	sprintf(color, "\e[%dm", (int)rand()%(37-30)-30);

	CliList *tmp = (CliList*)cli;


	if(recv(tmp->data, nickName, NAMELEN, 0) <= 0 ||
		strlen(nickName) < 2 || strlen(nickName) >= NAMELEN-1) {
			printf("\n%s ismini girmedi.\n", tmp->ip);
			leaveFlag = 1;
	} else {
		strncpy(tmp->name, nickName, NAMELEN);
		printf("\e[93m[++] \e[92m%s(%s)(%d) \e[94mSohbete katildi.\n\n", tmp->name, tmp->ip, tmp->data);
		writesFile(tmp->name, tmp->ip, tmp->data);
		sprintf(sendBuffer, "%s(%s) Sohbete katildi.", tmp->name, tmp->ip);

		sendToAll(tmp, sendBuffer);
	}

	while(1) {
		if(leaveFlag) { break; }

		int receive = recv(tmp->data, recvBuffer, MSGLEN, 0);

		if(receive > 0) {
			if(strlen(recvBuffer) == 0) {
				continue;
			}

			sprintf(sendBuffer, "%s: %s from %s", tmp->name, recvBuffer, tmp->ip);
		} else if(receive == 0 || strcmp(recvBuffer, "exit") == 0) {
			printf("\e[92m%s(%s)(%d) \e[91mSohbetten ayrildi.\n\n", tmp->name, tmp->ip, tmp->data);
			sprintf(sendBuffer,"\e[92m%s(%s) \e[91mSohbetten ayrildi.", tmp->name, tmp->ip);
			leaveFlag = 1;
		} else {
			printf("\nFatal error : -1\n");
			leaveFlag = 1;
		}

		sendToAll(tmp, sendBuffer);
	}

	close(tmp->data);

	if(tmp == current) {
		current = tmp->prev;
		current->link = NULL;
	} else {
		tmp->prev->link = tmp->link;
		tmp->link->prev = tmp->prev;
	}

	free(tmp);
}

int main() {
	signal(SIGINT, ctrlExit);

	serverFd = socket(AF_INET, SOCK_STREAM, 0);

	if(serverFd == -1) {
		printf("\nFail to create a socket.\n");
		exit(EXIT_FAILURE);
	}

	initFile();

	struct sockaddr_in serverInfo, clientInfo;

	int addrlenServ = sizeof(serverInfo);
	int addrlenCli = sizeof(clientInfo);

	memset(&serverInfo, 0, addrlenServ);
	memset(&clientInfo, 0, addrlenCli);

	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(PORT);

	/* LISTEN */
	bind(serverFd, (struct sockaddr*)&serverInfo, addrlenServ);
	listen(serverFd, 5);

	getsockname(serverFd, (struct sockaddr*)&serverInfo, (socklen_t*)&addrlenServ);

	printf("\nStart server on: %s:%d\n", inet_ntoa(serverInfo.sin_addr), ntohs(serverInfo.sin_port));

	root = newCli(serverFd, inet_ntoa(serverInfo.sin_addr));
	current = root;

	while(1) {
		clientFd = accept(serverFd, (struct sockaddr*)&clientInfo, (socklen_t*)&addrlenCli);

		getpeername(clientFd, (struct sockaddr*)&clientInfo, (socklen_t*)&addrlenCli);

		printf("\n\e[90m[*CLIENT*] \e[92m%s:%d \e[93mKATILDI.\n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));

		CliList *cmp = newCli(clientFd, inet_ntoa(clientInfo.sin_addr));

		cmp->prev = current;
		current->link = cmp;
		current = cmp;

		pthread_t id;

		if(pthread_create(&id, NULL, (void*)cliHandler, (void*)cmp) != 0) {
			perror("\nCreate pthread error!\n");
			exit(EXIT_FAILURE);
		}
	}

	fclose(file);
	return 0;
}
