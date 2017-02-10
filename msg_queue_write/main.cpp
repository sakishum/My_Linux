/**
 * @file main.cpp
 * @Synopsis  使用消息队列进行进程通信——写进程.
 *			  该进程用于创建信号量.
 *			  先运行写进程再运行读进程.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-02
 */
#include <cstdio>
#include <cstdlib>
#include <cstdint>
// 系统V消息队列API:
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

// 运行：
// $ sudo ./test
// 开启 ~/MyLinux/msg_queue_read 目录下的查看消息队列的程序
// 查看消息队列：
// $ ipcs
// 删除消息队列：
// $ ipcrm -q QID
// 注意：消息队列一旦创建就会一直存在系统中，直到手动删除或者重启系统。可以使用ipcs -q命令来查看系统存在的消息队列。

#define FRAMECOUNTER "/tmp"
#define MAX_BUF_LEN 100

typedef struct _msg_buf {
	long type;				// 信息种类
	char buf[MAX_BUF_LEN];	// 信息内容，长度由 msgsz 指定
} msg_buf;

auto main(int, char**) -> int32_t {
	int32_t key = 0;
	int32_t qid = 0;
	msg_buf buf;

	// 文件名到键值
	// 函数： key_t ftok(const char* pathname, int proj_id);
	// 通过文件名和项目号获得 System V IPC 键值（用于创建消息队列、共享内存所用）
	// pathname 就时你指定的文件名(该文件必须是存在而且可以访问的);
	// proj_id 是子序号，虽然为 int，但是只有8个比特被使用(0-255)。
	// 返回      ：成功时候返回 key_t 类型的key值，失败返回-1
	// No such file or directory
	key = ftok(FRAMECOUNTER, 10);
	if (key < 0) {
		perror("ftok return faile.\n");
		exit(EXIT_FAILURE);
	}

	// 函数： int msgget(key_t key, int msgflg)；
	// key       ：键值，当为 IPC_PRIVATE 时新建一块共享内存；
	// shmflg    ：标志。
	//		参数 msgflg 可以为以下	：IPC_CREAT、IPC_EXCL、IPC_NOWAIT 或三者的或结果
	//		IPC_CREAT				：内存不存在则新建，否则打开；
	//		IPC_EXCL				：只有在内存不存在时才创建，否则出错。
	// 返回      ：成功则返回标识符，出错返回-1
	qid = msgget(key, IPC_CREAT);
	printf("key: %d\nqid: %d\n", key, qid);

	// msgtyp:  信息类型。 取值如下：
	//   msgtyp = 0 ，不分类型，直接返回消息队列中的第一项.
	//   msgtyp > 0 , 返回第一项 msgtyp 与 msgbuf 结构体中的 mtype 相同的信息.
	//   msgtyp < 0 , 返回第一项 mtype 小于等于 msgtyp 绝对值的信息.
	buf.type = 10;
	while (1) {
		// 定义函数 char* fgets(char* s, int size, FILE* stream);
		// 函数说明 fgets()用来从参数stream所指的文件内读入字符并存到参数s所指的内存空间，
		// 直到出现换行字符、读到文件尾或是已读了size-1个字符为止，最后会加上NULL作为字符串结束。
		fgets(buf.buf, MAX_BUF_LEN, stdin);

		// 向msgid代表的消息队列发送一个消息，即将发送的消息存储在msgp指向的msgbuf结构中，消息的大小由msgze指定。
		// 函数： int msgsnd(int msgid, const void *msgp, size_t sz, int flg)；
		// 向消息队列发送消息
		// msgid ：通过msgget获取
		// msgp  ：指向消息内容的指针
		// sz    ：消息内容的大小
		// flg   ：处理方式;
		//		0，忽略標志位；
		//		IPC_NOWAIT 时表示空间不足时不会阻塞。
		// 返回  ：成功则返回0，失败返回-1
		if (msgsnd(qid, (void*)&buf, MAX_BUF_LEN, 0) < 0) {
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

