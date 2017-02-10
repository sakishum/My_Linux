#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int, char**) {
	for (int i = 0; i != 2; ++i) {
		fork();
		//printf("-");		// -------- -*8
		//printf("-\n");	// ------ -*6
		printf("ppid=%d, pid=%d, i=%d \n", getppid(), getpid(), i);
	}
	//wait(NULL);
	//wait(NULL);
	sleep(10);				// 让进城听令 10 秒，这样便于使用 pstree 查看进程树
	exit(EXIT_SUCCESS);
}
