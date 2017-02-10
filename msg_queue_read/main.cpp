#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

//$ sudo ./test

#define FRAMECOUNTER "/tmp"
#define MAX_BUF_LEN 100

typedef struct _msg_buf {
	long type;
	char buf[MAX_BUF_LEN];
} msg_buf;

auto main(int, char**) -> int32_t {
	int32_t key = 0;
	int32_t qid = 0;
	msg_buf buf;
	key = ftok(FRAMECOUNTER, 10);
	if (key < 0) {
		perror("ftok return faile.\n"); 
		exit(EXIT_FAILURE);
	}

	qid = msgget(key, IPC_CREAT);
	printf("key: %d\nqid: %d\n", key, qid);
	while (1) {
		// msgrcv: Permission denied
		// 该系统调用从msgid代表的消息队列中读取一个消息，并把消息存储在msgp指向的msgbuf结构中。
		if (msgrcv(qid, (void*)&buf, MAX_BUF_LEN, 0, 0) < 0) {
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		printf("type:%ld\nget:%s\n", buf.type, buf.buf);
	}
	exit(EXIT_SUCCESS);
}
