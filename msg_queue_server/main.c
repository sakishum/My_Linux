/**
 * @file main.c
 * @Synopsis  ./test &  后台运行
 *		发送信息的程序源文件。	
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-07-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512

// 消息的数据结构体
struct msg_st {
	long int msg_type;		// 一个长整型的成员变量开始的结构体，用以确定消息的类型
	char text[MAX_TEXT];
};

int main(void) {
	int running = 1;
	struct msg_st data;
	char buffer[BUFSIZ];
	int msgid = -1;

	// msgget 用来创建和访问一个消息队列。原型为：
	// int msgget(key_t key, int msgflg);
	// 与其他 IPC 机制一样，程序必须提供一个键来命名某个特定的消息队列。msgflg 是一个权限标志
	// 表示消息队列的访问权限，他与文件的访问权限一样。msgflg 可与 IPC_CREATE 做或操作，表示
	// 当 key 所命名的消息队列不存在时创建一个消息队列，如果 key 所命名的消息队列存在时，
	// IPC_CREATE 标志会被忽略，而只返回一个标识符。
	// 返回：返回一个以 key 命名的消息队列的标识符（非零整数），失败返回 -1。
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while (running) {
		printf("Enter some text: \n");
		fgets(buffer, BUFSIZ, stdin);
		data.msg_type = 1;
		strncpy(data.text, buffer, sizeof(data.text));
		// msgsnd 该函数用于把消息添加到消息队列中。
		// 原型： msgsnd(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);
		// msgid 是由 msgget 函数返回的消息队列标识符
		// msg_ptr 是一个指向准备发送消息的指针，但是消息的数据结构是有一定的要求，指针
		// msg_ptr 所指向的消息结构一定要是以一个长整型成员变量开始的结构体，接收函数将
		// 用这个成员来确定消息的类型。
		// msg_sz 是 msg_ptr 指向的消息的长度，注意是消息的长度，而不是整个结构体的长度，
		// 也就是说 msg_sz 不包括长整型消息类型成员变量的长度。
		// msgflg 用于控制当前消息队列满或队列消息到达系统范围的限制时将要发生的事情。
		// 返回:  如果调用成功，消息数据的一份副本将被放到消息队列中，并返回0，失败返回-1.
		if (msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1) {
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
