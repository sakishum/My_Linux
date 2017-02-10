/**
 * @file main.cpp
 * @Synopsis  等待2秒后向进程本身传送一个SIGALRM信号。
 *			  设置信号处理。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-02
 */

#include <signal.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

#ifndef USE_RAISE 
#define USE_RAISE false
#endif

void func(int32_t sig_no) {
	if (sig_no == SIGALRM) {
		printf("get SIGALRM\n");
	}
}

auto main(int32_t, char**) -> int32_t {
	printf("%d watting for signal..\n", getpid());
	alarm(2);
	// 函数：signal 设置某一信号对应的动作
	// 头文件		： #include <signal.h>
	// 函数原型		： void (signal(int signum, void (handler) (int))) (int)；
	// signal		：信号编号
	// handler		：信号处理函数，若该参数不是函数指针则必须为以下两个常数之一：
	//		SIG_IGN		：忽略信号
	//		SIG_DFL		：重设为预设的处理方式
	// 返回：成功则返回先前的信号处理函数指针，错误则返回SIG_ERR(-1)
	signal(SIGALRM, func);

	// kill 函数与 raise 函数的区别:
	// kill 函数将信号发送给进程或进程组。raise 函数则允许进程向自身发送信号。
	
	// 函数： kill 传送信号
	// 头文件：
	// #include <signal.h>
	// #include <sys/types.h>
	// 函数原型		： int kill(pid_t pid, int sig)；
	// pid			：接收信号的进程号；当pid=0时为相同进程组的所有进程；
	//				  当pid=-1时为系统内所有进程；当pid>0时为指定进程；
	//				  当pid<-1时为进程组识别码为pid绝对值的所有进程。
	// sig			：要传送的信号
	// 返回			：成功返回0，错误返回-1
#if USE_RAISE
	printf("Use raise().\n");
	raise(SIGALRM);
#else
	printf("Use kill().\n");
	kill(getpid(), SIGALRM);
#endif
	
	// 函数：pause 让进程暂停直到信号出现
	// 头文件		：#include <unistd.h>
	// 函数原型		： int pause(void)；
	// 只返回-1
	pause();
	exit(EXIT_SUCCESS);
}
