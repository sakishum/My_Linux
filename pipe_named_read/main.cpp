#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <unistd.h>		// read, sleep
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define FIFO "/tmp/myfifo"

auto main(int32_t, char**) -> int32_t {
	int32_t num = 0;
	int32_t fd = 0;
	char buf[100] = {0};

	fd = open(FIFO, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	while (1) {
		memset(buf, 0, sizeof(buf));
		if ((num = read(fd, buf, 100)) < 0) {
			if (errno == EAGAIN) {
				printf("no data yet\n");
			}
			sleep(1);
			continue;
		}
		printf("read %s from fifo\n", buf);
		sleep(1);
	}

	exit(EXIT_SUCCESS);
}
