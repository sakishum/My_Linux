#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 1234
#define BACKLOG 5
#define BUF_SIZE 200
int fd_A[BACKLOG];
int conn_amount;

void showclient(void) {
	int i;
	printf("client amount: %d\n", conn_amount);
	for (i = 0; i != BACKLOG; ++i) {
		printf("[%d]:%d ", i, fd_A[i]);
	}
	printf("\n");
}

int32_t main(int argc, char *argv[]) {
	exit(EXIT_SUCCESS);
}
