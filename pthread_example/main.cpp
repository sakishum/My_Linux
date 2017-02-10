/**
 * @file main.cpp
 * @Synopsis  多线程编程例子，分离状态与正常启动线程的区别。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-11-03
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// usleep, getpid
#include <pthread.h>


void *work(void *ptr) {
	pthread_t tid;
	tid = pthread_self();
	printf("tid %lu (0x%lx)\n", (unsigned long)tid, (unsigned long)tid);
	for (int i = 0; i != 10; ++i) {
		printf("%d\n", *(reinterpret_cast<int*>(ptr)));
		usleep(1000);
	}
	pthread_exit(0);
}

int main(int, char**) {
	pthread_attr_t attr;
	pthread_attr_init (&attr);	// 初始化, 实现时为属性对象分配了动态内存空间
	// 表示与系统中所有线程一起竞争 CPU 时间
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);				
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);	// 分离，不能使用 pthread_join 来同步

	pthread_attr_t attr1;
	pthread_attr_init (&attr1);
	// 表示仅与同进程中的线程竞争 CPU
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);				
	pthread_attr_setdetachstate (&attr1, PTHREAD_CREATE_JOINABLE);	// 默认

	int a = 0;
	int b = 1;
	pthread_t t0, t1;

	// 一下线程都是 阻塞式的线程

	// 线程一的线程函数一结束就自动释放资源
	int ret = pthread_create(&t0, &attr, &work, reinterpret_cast<void*>(&a));
	if (ret != 0){
		perror("Thread creation failed.\n");
	}
	pthread_attr_destroy(&attr);

	// 线程二就得等到 pthread_join 来释放系统资源
	ret = pthread_create(&t1, &attr1, &work, reinterpret_cast<void*>(&b));
	if (ret != 0){
		perror("Thread creation failed.\n");
	}
	pthread_attr_destroy(&attr1);


	// 调 pthread_join 函数的线程将挂起等待，直到 id 为 thread 的线程终止
	pthread_join(t1, 0);

	//pthread_detach(t0);
	pthread_cancel(t0);

	exit(EXIT_SUCCESS);
}

