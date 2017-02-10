#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <math.h>

#define FRAMECOUNTER "/tmp"

auto main(int32_t, char**) -> int32_t {
	int32_t key = 0;
	int32_t sid = 0;
	key = ftok(FRAMECOUNTER, 10);
	if ((sid = semget(key, 1, IPC_CREAT)) < 0) {
		perror("semget");
		exit(EXIT_FAILURE);
	}
	printf("key: %d\tsid: %d\n", key, sid);

	struct sembuf p_op, v_op;
	p_op.sem_num = 0;
	p_op.sem_op = -1;
	if (semop(sid, &p_op, 1) < 0) {
		perror("semgop");
		exit(EXIT_FAILURE);
	}

	printf("father get the semaphore\n");
	sleep(5);
	printf("father release the senphore\n");

	v_op.sem_num = 0;
	v_op.sem_op = 1;
	v_op.sem_flg = 0;
	if (semop(sid, &v_op, 1) < 0) {
		perror("semgop");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
