/**
 * @file main.cpp
 * @Synopsis  管道是进程间通信中最古老的方式。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-09
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
// 无名管道只能用于父子进程通信，而有名管道可以用于任意进程间通信。
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
// 创建成功之后可以像操作普通文件一样使用read、write进行读写操作。
// 先运行写进程再运行读进程.
// 读进程：
// /Users/sakishum1118/MyLinux/pipe_named_read

// 在Linux系统下，有名管道可由两种方式创建：
// 命令行方式 mknod 系统调用和函数 mkfifo。

#define FIFO "/tmp/myfifo"

auto main(int32_t, char**) -> int32_t {
	int32_t num = 0;
	int32_t fd = 0;
	char buf[100];

	unlink(FIFO);
	
	// int mkfifo(const char *filename, mode_t mode);
	// 创建有名管道对应的实名文件，该文件必须事先不存在。
	// filename	：文件路径
	// mode		：文件权限
	// 返回0代表创建成功，否则返回-1。
	// 生成了有名管道后，就可以使用一般的文件 I/O 函数如 open、close、read、write 等来对它进行操作。
	if ((mkfifo(FIFO, O_CREAT|O_EXCL|O_RDWR) < 0) && (errno != EEXIST)) {
			perror("mkfifo");
	}

	fd = open(FIFO, O_WRONLY);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	while (1) {
		scanf("%s", buf);
		if ((num = write(fd, buf, 100)) < 0) {
			if (errno == EEXIST) {
				printf("FIFO has not been read yet.\n");
			}
		}
	}

	close(fd);

	exit(EXIT_SUCCESS);
}
