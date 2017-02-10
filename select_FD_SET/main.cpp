#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>	// FD_SET, FD_SETSIZE, FD_CLR, FD_ISSET
#include <unistd.h>
// /Users/sakishum1118/MyLinux/select_dx
// int select(int maxfd,fd_set *rdset,fd_set *wrset,fd_set *exset,struct timeval *timeout); 

int main(int, char**) {
	fd_set rfds;
	struct timeval tv;
	int reval;

	/* watch stdin (fd 0) to see when it has input */
	// readfds、writefds、exceptfds：
	// 表示需要关注的读、写、错误事件的文件描述符位数组，这些参数即是输入参数也是输出参数，
	// 可能会被内核修改用于标示哪些描述符上发生了关注的事件。所以每次调用 select 前都需要
	// 重新初始化 fdset。
	
	// FD_ZERO: 将指定的文件描述符集清空，在对文件描述符集合进行设置前，必须对其进行初始化，如果不清空，
	// 由于在系统分配内存空间后，通常并不作清空处理，所以结果是不可知的。
	FD_ZERO(&rfds);
	// FD_SET: 用于在文件描述符集合中增加一个新的文件描述符。
	FD_SET(0, &rfds);	// stdin (fd 0) 

	/* wait up to five seconds. */ 
	// NULL		阻塞，直到有 IO 事件触发
	// 0		非阻塞，仅检测描述符集合的状态，立即返回，并不等待外部事件 
	// timeout	阻塞，等待固定时间：如果在指定的时间段里有事件发生或者时间耗尽，函数均返回
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	// 为最 fdset 集合中最大描述符值加 1， fdset 是一个位数组，其大小限制为__FD_SETSIZE(1024), 
	// 注意fd的最大值必须<FD_SETSIZE。
	// 位数组的每一位代表其对应的描述符是否需要被检查。
	reval = select(1, &rfds, NULL, NULL, &tv);	// 注意第一个参数是 1，原因是检测的 stdin 描述符值是 0，需要设置最大描述符值 + 1
	/* don't relay on the value of tv now */
	// 返回值：
	// 负值： select 错误
	// 0：	  等待超时
	// 正值： 某些文件可读可写或出错
	// 超时时间内有事件到来就返回，否者在超时后不管怎样一定返回，返回值同上。
	if (reval == -1) {
		perror("select");
	} else if (reval) {
		printf("\ndata is available now.\n");
		/* FD_ISSET(0, &rfds) will be true. */
	} else {
		printf("\nNo data within five seconds.\n");
	}
	//pause();	// 挂起进程
	getchar();
	exit(EXIT_SUCCESS);
}

