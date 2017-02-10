#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// 由 fork 创建的新进程被称为 子进程(child process)。fork 函数被抵用一次，但
// 返回两次。两次返回的唯一区别是子进程的返回是 0， 而父进程的返回则是新子进
// 程的进程 ID。

// How many processes are there after the execution of the code shown below:
int main(void) {
	fork();
	fork();
	if (0 == fork()) {
		fork();
	}
	sleep(20);
	return EXIT_SUCCESS;
}

/*
result: 12

test─┬─test─┬─test───test───test                  
     │      └─test───test                         
     ├─test───test───test                         
     └─test───test
*/
