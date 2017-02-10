/**
 * @file main.cpp
 * @Synopsis  
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-06-04
 */

#include <cstdio>
#include <cstdlib>

#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

/*
// timeval 的结构如下
struct timeval {
	long tv_sec;	// seconds
	long tv_usec;	// microseconds
};
// 注意：timeval 结构体中虽然指定了一个微秒级别的分辨率，但内核支持的分辨率往往没有那么高，
// 很多 unix 内核将超时的值向上舍入(ceil)成10ms 的倍数。此外，加上了内核调度延时现象，即
// 定时器时间到后，内核往往需要话一定时间调度相应进程的运行。因此，定时器的精度，最终还是由
// 内核支持的分别率决定。
*/

/*
select 函数原型:
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
参数说明:
	nfds ：		为最 fdset 集合中最大描述符值加1， fdset 是一个位数组，其大小限制为__FD_SETSIZE(1024), 
				位数组的每一位代表其对应的描述符是否需要被检查。
	readfds、writefds、exceptfds：
				表示需要关注的读、写、错误事件的文件描述符位数组，这些参数即是输入参数也是输出参数，
				可能会被内核修改用于标示哪些描述符上发生了关注的事件。所以每次调用 select 前都需要
				重新初始化 fdset。
	timeout：	超时时间，该结构会被内核修改，其值为超时剩余的时间。

返回值：
	若有就绪描述符则为其数目，若超时则为 0， 若出错则为 -1.

使用 select 实现定时器，需要利用 timeout 参数，注意：
	1）select 函数用了一个结构体 timeval 作为其参数。
	2）select 函数会更新 timeval 的值，timeval 保持的值为剩余时间。
*/

// 秒级定时器
void seconds_sleep(unsigned seconds) {
	struct timeval tv;
	tv.tv_sec = seconds;
	// 如果不初始化赋值给tv.tv_usec 会报错
	// Syscall param select(timeout) points to uninitialised byte(s)
	tv.tv_usec = 0;
	int err = 0;
	do {
		err = select(0, NULL, NULL, NULL, &tv);
	} while (err < 0 && err == EINTR);
}

// 毫秒级定时器
void milliseconds_sleep(unsigned long mSec) {
	struct timeval tv;
	tv.tv_sec = mSec/1000;
	tv.tv_usec = (mSec%1000)*1000;
	int err = 0;
	do {
		err = select(0, NULL, NULL, NULL, &tv);
	} while (err < 0 && err == EINTR);
}

// 微秒级定时器
void microsecond_sleep(unsigned long uSec) {
	struct timeval tv;
	tv.tv_sec = uSec/1000000;
	tv.tv_usec = uSec%1000000;
	int err = 0;
	do {
		err = select(0, NULL, NULL, NULL, &tv);
	} while(err < 0 && err == EINTR);
}

int main(void) {
	printf("Start.\n");
	seconds_sleep(5);				// 5s
	milliseconds_sleep(1500);		// 1.5s
	microsecond_sleep(1900000);		// 1.9s
	printf("end\n");				// Total: 8.4s
	return EXIT_SUCCESS;
}

