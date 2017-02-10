#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 函数 ouch 通过 sig 传进来的信号作做出响应。
void ouch(int sig) {
	printf("OUCH! - I got singnal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);	
	//(void) signal(SIGINT, ouch);			// terminated by signal SIGTERM (Polite quit request) $kill $(pidof test)
	// SIG_IGN 忽略  (SIGSTOP、SIGLKILL 这两个信号无法忽略)
	// SIG_DFL 默认
	// 以上两个宏，可以作为信号处理函数。
	// 经过试验证明，signal 会祖塞当前正在处理的 signal，但是没有
	// 办法祖塞其他 signal。
}

// main 函数的做能用是，截取被按下 ctrl+c 组合键产生的 SIGINT 信号。
// 没有信号就无限循环中每隔一秒打印一条消息。
int main(void) {
	// 实际运用中，需要对不同的的 signal 设定不同的信号处理函数
	(void) signal(SIGINT, ouch);
	while (1) {
		printf("hello world\n");
		sleep(1);
	}
	return EXIT_SUCCESS;
}
