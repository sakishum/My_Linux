/**
 * @file main.cpp
 * @Synopsis  多进程，fork 与 vfork 的区别。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-02
 */

#include <unistd.h>			// sleep, vfork
//#include <sys/types.h>
#include <sys/wait.h>		// wait
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cerrno>
#include <cmath>
#include <iostream>

#ifndef VFORK_SIGNED
#define VFORK_SIGNED 0
#endif

// 函数：
// pid_t fork();	创建一个子进程，在子进程中返回0，在父进程中返回子进程ID，出错则返回-1。
// pid_t vfor();	创建一个子进程，与fork()相似；区别如下：
// fork() 子进程拷贝父进程数据段、堆栈段，vfork() 则是共享；
// fork() 父子进程执行顺序不确定，vfork() 是先执行完子进程再执行父进程。
//
// pid_t getpid();	返回当前进程ID
// pid_t getppid();	返回父进程ID

auto main(int32_t, char**) -> int32_t {
	pid_t child;
	int32_t i = 0;

	// 创建子进程
#if VFORK_SIGNED
	if ((child = vfork()) < 0) {
#else
	if ((child = fork()) < 0) {
#endif
		printf("Fork Error : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		// 父进程
		if (child > 0) {
			++i;
			printf("I am the father: %d;\ti = %d\n", getpid(), i);

			pid_t child;
			// 函数：
			// pid_t wait(int *status); 等子进程结束之后才运行。
			// status	：接收子进程返回状态
			//
			// pid_t waitpid(pid_t pid, int *status, int options); 与waitpid()相似。
			// pid		：指定的进程号，当pid=-1时等待任何子进程，相当于wait()；
			// status	：用于接收进程返回状态；
			// option	：为WNOHANG时若无任何已结束的子进程则马上返回，不予以等待；为WUNTRACES时若子进程暂停则马上返回，不予以理会结束状态。
			if ((child = wait(NULL)) < 0) {
				printf("wait error:%s\n", strerror(errno));
			} else {
				printf("wait for child pid:%d and close\n", child);
			}

			exit(EXIT_SUCCESS);
		// 子进程
		} else {
			++i;
			printf("I am the child: %d;\ti = %d\n", getpid(), i);
			sleep(1);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
