/**
 * @file main.cpp
 * @Synopsis  InterProcess Communication.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-08-29
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cerrno>
#include <unistd.h>
// 对于 System V 共享内存，主要有以下几个 API：shmget()、shmat()、shmdt() 及 shmctl()
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>		// key_t
#include <iostream>

// Usage：sudo ./test kkk
// 查看：
// $ ipcs -ma    
// $ ipcs -m
// 删除：
// $ ipcrm -m MID

#define MAX_LEN 1024

int32_t main(int32_t argc, char* argv[]) {
	if (argc  != 2) {
		std::cout << "Usage: " << argv[0] << " str" << std::endl;
		exit(EXIT_FAILURE);
	}

	int32_t shmid = 0;
	char *p_addr = NULL, *c_addr = NULL;

	// 首先要用的函数是shmget，它获得一个共享存储标识符。
	// 这个函数有点类似大家熟悉的malloc函数，系统按照请求分配size大小的内存用作共享内存。
	// 获得共享内存区域的ID，如果不存在指定的共享区域就创建相应的区域
	//  IPC_CREAT   如果共享内存不存在，则创建一个共享内存，否则打开操作
	//  IPC_EXCL    只有在共享内存不存在的时候，新的共享内存才建立，否则就产生错误
	if ((shmid = shmget(IPC_PRIVATE, MAX_LEN, IPC_CREAT)) < 0) {
		std::cerr << "shmget error: " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE); 
	}

	printf("fork()\n");
	if (fork() > 0) {
		printf("Father process.\n");
		if ((p_addr = (char*)shmat(shmid, 0, 0)) == (void*)(-1)) {
			printf("shmat error:%s\n", strerror(errno));
			return -1;
		}

		memset(p_addr, 0, MAX_LEN);
		strncpy(p_addr, argv[1], MAX_LEN);
		printf("child:pid %d, share memory from %lx to %lx, content:%s\n",\
				getpid(), (unsigned long)p_addr, (unsigned long)(p_addr + MAX_LEN), p_addr);

		// 使共享内存区脱离映射的进程的地址空间
		if (shmdt(p_addr) < 0) {
			printf("shmdt error:%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("child process sleep 3 seconds\n");
		sleep(3);

		// 若子进程先于父进程结束时，父进程调用 wait() 函数和不调用 wait() 函数会产生两种不同的结果：
		// --如果父进程没有调用 wait() 和 waitpid() 函数，子进程就会进入僵死状态。
		// --如果父进程调用了 wait() 和 waitpid() 函数，就不会使子进程变为僵尸进程。
		
		// wait() 要与 fork() 配套出现,如果在使用 fork() 之前调用 wait(), wait() 的返回值则为 -1, 正常情况
		// 下 wait() 的返回值为子进程的 PID.
		
		// wait() 函数使父进程暫停执行，直到它的一个子进程结束为止，该函数的返回值是终止运行的子进程的PID. 
		// 参数 status 所指向的变量存放子进程的退出码，即从子进程的 main 函数返回的值或子进程中 exit() 函数
		// 的参数。如果 status 不是一个空指针，状态信息将被写入它指向的变量。
		pid_t child;
		if ((child = wait(NULL)) < 0) {
			printf("wait error:%s\n", strerror(errno));
		} else {
			printf("wait for child pid:%d and close\n", child);
		}
	} else {
		// 子进程从内存中读取数据
		// 获取内存起始地址
		// 当共享内存创建后，其余进程可以调用shmat（）将其连接到自身的地址空间中。
		c_addr = (char*)shmat(shmid, 0, 0);
		sleep(4);
		printf("Child get %s\n", c_addr);
		shmdt(c_addr);

		// 删除共享内存
		printf("Clean SM.\n");
		// void shmctl(int shmid, int cmd, struct shmid_ds *buf)；
		// shmid：通过shmget获取
		// cmd：控制命令，如下：
		//		IPC_STAT	：获取内存状态
		//		IPC_SET		：改变内存状态
		//		IPC_RMID	：删除内存
		// buf：结构体指针，用于存放共享内存状态
		// 返回：成功返回0，错误返回-1
#if 1
		if (shmctl(shmid, IPC_RMID, NULL) < 0) {
			printf("shmat error:%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
#endif
	}
	
	exit(EXIT_SUCCESS);
}

