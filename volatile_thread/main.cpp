
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// 多线程共享变量使用 volatile 修饰
// volatile 的作用是，告诉编译器，不要把变量优化到寄存器里，
// 每次读取变量的时都直接从原始内存地中读取。
//
// 它的效果是让编译器不要对这个变量的读写操作做任何优化，
// 每次读的时候都直接去该变量的内存地址中去读，每次写的
// 时候都直接写到该变量的内存地址中去，即不做任何缓存优化。
volatile bool start = false;

void *thread_run(void *) {
	while (1) {
		if (start) {
			printf("Thread malloc.\n");
			// 申请 1K 空间
			char *buf = new char[1024];
			start = false;
		}
	}
}

int main(void) {
	pthread_t th;
	std::cin.get();
	pthread_create(&th, NULL, thread_run, NULL);

	while (std::cin.get()) {
		start = true;
	}
	return EXIT_SUCCESS;
}

