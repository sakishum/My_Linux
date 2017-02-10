/**
 * @file main.cpp
 * @Synopsis  使用信号量进行进程通信——进程1。
 *			  该进程用于创建信号量。
 *			  信号量是一个计数器，它用来记录对某个资源（如共享内存）的存取状况。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-02
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <sys/types.h>	// key_t
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>		// sleep, fork
#include <errno.h>
#include <math.h>
#include <iostream>

#define FRAMECOUNTER "/tmp"
// 执行：
// $ sudo ./test
// 查看：
// $ ipcs -s
// 删除：
// $ ipcrm -s SID
// 注意：信号量一旦创建就会一直存在系统中，直到手动删除或者重启系统。
// 可以使用ipcs -s命令来查看系统存在的信号量。

auto main(int, char**) -> int32_t {
	int32_t key = 0;
	int32_t sid = 0;
	union semun val;
	val.val = 1024;

	// 函数： key_t ftok(const char *filename, int proj_id);
	// 通过文件名和项目号获得 System V IPC 键值（用于创建消息队列、共享内存所用）
	// proj_id	：	项目号，不为0即可
	// 返回		：	成功则返回键值，失败则返回-1
	key = ftok(FRAMECOUNTER, 10);

	/* 要调用的第一个函数是semget，用以获 得一个信号量ID */ 
	// 函数： int semget(key_t key, int nsems, int msgflg)；
	// key		：键值，IPC 结构的关键字, 当为 IPC_PRIVATE 时新建。	
	// nsems	：信号个数, 是该集合中的信号量数。
	// msgflg	：标志, 创建新的信号量集合，还是引用一个现有的信号量集合。
	//		IPC_CREAT	：不存在则新建，否则打开；
	//		IPC_EXCL	：与IPC_CREAT一同使用时，只有在不存在时才创建，否则出错。
	// 返回		：成功则返回IPC标识符，出错返回-1
	// 如果是创建新 集合（一般在服务器中），则必须指定nsems；如果是引用一个现有的信号量集合（一般在客户机中）则将nsems指定为 0。
	if ((sid = semget(key, 1, IPC_CREAT)) < 0) {
		perror("semget");
		exit(EXIT_FAILURE);
	}
	printf("key: %d\tsid: %d\n", key, sid);

	// semctl 函数用来对信号量进行操作:
	// 函数： void semctl(int semid, int semnum, int cmd, union semun arg)；
	// semid	：通过semget获取
	// semnum	：操作的信号灯编号
	//		cmd		：控制命令，如下：
	//			GETPID		：获取sempid
	//			GETVAL		：获取semval
	//			SETVAL		：设置semval
	//			IPC_RMID	：删除信号灯
	// arg		：各个量使用与cmd设置有关
	// 返回		：成功返回与cmd相关的正数，错误返回-1
	if ((semctl(sid, 0, SETVAL, val)) < 0) {
		perror("semctl");
		exit(EXIT_FAILURE);
	}

	if (semctl(sid, 0, GETVAL, val) < 0) {
		perror("semctl");
		exit(EXIT_FAILURE);
	}
	printf("sem_val: %d\n", val.val);

	struct sembuf p_op, v_op;
	p_op.sem_num = 0;
	p_op.sem_op = -1;

	// semop函数自动执行信号量集合上的操作数组:
	// 函数： int semop(int semid, struct sembuf *sops, unsigned nsops)；
	// semid	：通过semget获取
	// sops		：指向待操作的信号灯结构体，原型如下：
	//	struct sembuf {
	//		unsigned short sem_num; //信号灯编号，从0开始
	//		short sem_op;			//为正数代表释放信号；为负代表获取信号
	//		Short sem_flg;			//操作的标识；IPC_NOWAIT：不阻塞；IPC_UNDO：程序结束时释放信号量
	//	};
	// nsops	：要操作的信号量数
	// 返回		：成功则返回共享内存起始地址，失败返回-1
	if (semop(sid, &p_op, 1) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
	printf("father get the semaphore\n");
	sleep(5);
	printf("father release the senaphore\n");
	v_op.sem_num = 0;
	v_op.sem_op = 1;
	v_op.sem_flg = 0;
	
	if (semop(sid, &v_op, 1) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
