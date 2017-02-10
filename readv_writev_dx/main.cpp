#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/uio.h>
#include <unistd.h>

int main(void) {
	static char part2[] = "THIS IS FROM WRITEV";
	static int part3 = 65;			// 'A''
	static char part1[] = "[";

	struct iovec iov[3];

	iov[0].iov_base = part1;
	iov[0].iov_len = strlen(part1);
	iov[1].iov_base = part2;
	iov[1].iov_len = strlen(part2);
	iov[2].iov_base = &part3;
	iov[2].iov_len = sizeof(part3);

	writev(STDOUT_FILENO, iov, 3);	// [THIS IS FROM WRITEVA

	return EXIT_SUCCESS;
}

