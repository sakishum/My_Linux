#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 僵尸进程(zombie process)就是死掉的进程。产生的原因就是父进程产生子进程后，
// 子进程先于父进程退出，但是父进程出于种种原因，并没有处理子进程的退出信号，
// 那么这个子进程就会成为僵尸进程。

int main(void) {
	pid_t pid;
	pid = fork();
	if (pid < 0) {				// 如果出错
		printf("error occurrend!\n");
	} else if (pid == 0) {		// 如果是子进程
		// exit(EXIT_SUCCESS);	// 子进程退出
	} else {					// 如果是父进程
		sleep(60);				// 休眠60 秒
		wait(NULL);				// 收集僵尸进程/ Ubuntu 12.04 LTS wait();
		// 使用 kill 命令也无法杀死僵尸进程。只能通过杀死父进程或者等待
		// 父进程运行运行结束退出来清除僵尸进程。
		// 在父进程中加上 wait() 方法，就是用于通知父进程子进程的结束，
		// 子进程结束时要处理子进程的数据。
	}
	return EXIT_SUCCESS;
}

/*
  $pstree -p test
  21737 pts/17   S+     0:00 ./test                                                                 
  21738 pts/17   Z+     0:00 [test] <defunct>	
  产生僵尸进程是由于子进程先于父进程退出，那么如果父进程先于子进程退出，会发生什么情况？
  子进程会被 init (PID 1) 这个进程接管，执行结束后，会被自动回收。
*/
