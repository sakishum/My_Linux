#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>		// getpid
#include <pthread.h>

pthread_t ntid;

void printids(const char *str) {
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", str, (unsigned long)pid,
			(unsigned long)tid, (unsigned long)tid);
}

void * thr_fn(void *) {
	printids("new thread: ");
	return ((void*)0);
}

int main(int, char**) {
	int err;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0) {
		//err_exit(err, "can\'t create thread");
	}
	printids("main thread:");
	sleep(1);
	exit(EXIT_SUCCESS);
}
