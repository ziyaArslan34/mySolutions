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
#define MSGLEN 101
#define SENDLEN 201
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
    printf("\r\e[90m%s", "> ");
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

volatile sig_atomic_t flag = 0;

int sockfd = 0;
char nickName[NAMELEN] = {};

void ctrlExit(int sig) { flag = 1; }

void recvMsgHandler() {
	char receiveMessage[SENDLEN] = {};

	while(1) {
		int receive = recv(sockfd, receiveMessage, SENDLEN, 0);

		if(receive > 0) {
			printf("\r\e[94m%s\n", receiveMessage);
			strOverWrites();
		} else if(receive == 0) {
			break;
		} else {
			/* -1 */
		}
	}
}

void sendMsgHandler() {
	char message[MSGLEN] = {};

	while(1) {
		strOverWrites();

		while(fgets(message, MSGLEN, stdin) != NULL) {
			strTrimLF(message, MSGLEN);

			if(strlen(message) == 0) {
				strOverWrites();
			} else {
				break;
			}
		}

		send(sockfd, message, MSGLEN, 0);
		if(strcmp(message, "exit") == 0) {
			break;
		}
	}
	ctrlExit(2);
}

int main() {
	signal(SIGINT, ctrlExit);

	printf("\nEnter your name: ");
	if(fgets(nickName, NAMELEN, stdin) != NULL) {
		strTrimLF(nickName, NAMELEN);
	}

	if(strlen(nickName) < 2 || strlen(nickName) >= NAMELEN-1) {
		printf("\nName must be more than one and less than thirty charectes.\n");
		exit(EXIT_FAILURE);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == -1) {
		printf("\nFail to create a socket.\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serverInfo, clientInfo;

	int addrlenServ = sizeof(serverInfo);
	int addrlenCli = sizeof(clientInfo);

	memset(&serverInfo, 0, addrlenServ);
	memset(&clientInfo, 0, addrlenCli);

	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverInfo.sin_port = htons(PORT);

	int error = connect(sockfd, (struct sockaddr*)&serverInfo, addrlenServ);

	if(error == -1) {
		printf("\nConnection to server error!\n");
		exit(EXIT_FAILURE);
	}

	getsockname(sockfd, (struct sockaddr*)&clientInfo, (socklen_t*)&addrlenServ);
	getpeername(sockfd, (struct sockaddr*)&serverInfo, (socklen_t*)&addrlenServ);

	printf("\n\e[93m[++]Connect to server: %s:%d\n", inet_ntoa(serverInfo.sin_addr), ntohs(serverInfo.sin_port));
	printf("\nYou are: %s:%d\n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));

	send(sockfd, nickName, NAMELEN, 0);

	pthread_t sendMsgth;
	pthread_t recvMsgth;

	if(pthread_create(&sendMsgth, NULL, (void*)sendMsgHandler,NULL) != 0) {
		printf("\nCreate pthread error!\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&recvMsgth, NULL, (void*)recvMsgHandler, NULL) != 0) {
		printf("\nCreate pthread error!\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		if(flag) {
			printf("\nBye :)\n");
			break;
		}
	}

	close(sockfd);

	return 0;
}
