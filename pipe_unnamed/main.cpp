/**
 * @file main.cpp
 * @Synopsis  Unname pipe.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-09
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <unistd.h>		// pipe

// 管道是进程间通信中最古老的方式，它包括无名管道和有名管道两种，
// 前者用于父进程和子进程间的通信，后者用于运行于同一台机器上的任
// 意两个进程间的通信。

#define INPUT 0 
#define OUTPUT 1 

auto main(int32_t, char**) -> int32_t {
	int32_t pfd[2];
	/*定义子进程号 */ 
	pid_t pid;
	char buf[100];
	int32_t num = 0;
	memset(buf, 0, sizeof(buf));

	// 无名管道由pipe（）函数创建:
	// int pipe(int fd[2]); 创建无名管道。
	// fd[2]：管道两个文件描述符，
	//		fd[0]代表读端（管道头），
	//		fd[1]代表写端（管道尾）。 
	// 创建成功返回0，失败返回-1。
	/*创建无名管道*/ 
	if (pipe(pfd) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// 创建成功之后可以像操作普通文件一样使用read、write进行读写操作。

	/*执行子进程*/ 
	if ((pid = fork()) == 0) {
		sleep(1);
		/*子进程从父进程读数据*/ 
		if ((num = read(pfd[INPUT], buf, 100) > 0)) {
			printf("%d numbers read, %s\n", num, buf);
		}
	/*执行父进程*/ 
	} else if (pid > 0) {
		/*父进程向子进程写数据*/ 
		if (write(pfd[OUTPUT], "Hello", 5) < 0) {
			perror("write 1");
		}
		if (write(pfd[OUTPUT], " Pipe", 5) < 0) {
			perror("write 2");
		}
		waitpid(pid, NULL, 0);
	}

	/*关闭管道的读端*/
	close(pfd[INPUT]);
	/*关闭管道的写端*/
	close(pfd[OUTPUT]);

	exit(EXIT_SUCCESS);
}
