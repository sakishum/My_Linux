#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_t ntid;

pid_t gettid(void) {
	return syscall(SYS_gettid);
}

void printids(const char *s) {
	pid_t	pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %lu (0x%lX)\n", s, (uint32_t)pid, 
			(unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void*) {
	printids("new  thread: ");
	return((void*)0);
}

int32_t main(int32_t, char**) {
	int32_t err = 0;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0) {
		perror("can\' create thread\n");
	}
	printids("main thread: ");
	sleep(1);
	exit(EXIT_SUCCESS);
}

/*
 * 在 Mac OS Lion 上运行的结果：
 * main thread:  pid 18419 tid 140735132543328 (0x7FFF73952960)
 * new  thread:  pid 18419 tid 4366798848 (0x104481000)
 *
 * 两个进程具有相同的进程 ID ，期望是主线程 ID 与新线程 ID 所指向的
 * 内存单元在相同的地址范围内，但事实是两者并不在相同的地址范围内。
 *
 * Ubuntu 12.04 LTS
 * main thread:  pid 6036 tid 140229738960640 (0x7F89C7C71700)
 * new  thread:  pid 6036 tid 140229730682624 (0x7F89C748C700)
 * 两个线程具有相同的进程 ID，是否跟 FreeBSD 一样，使用指向线程数据
 * 结构的指针作为他的线程 ID 。
 * */
