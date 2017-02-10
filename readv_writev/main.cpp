/**
 * @file main.cpp
 * @Synopsis  散布读、写多个非连续的缓冲区。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-06-02
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <sys/uio.h>	// readv、writev 
#include <unistd.h>		// STDIN_FILENO (0)、STDOUT_FILENO(1)、STDERR_FILENO(2)

// 函数功能：读取多个非连续的缓冲区，或从多个非连续的缓冲区写数据到文件；
// 返回值：若成功返回已读、写的字节数，若出错返回-1；
// 函数原型：
// size_t readv(int filedes, const struct iovec *iov, int iovecnt);
// size_t writev(int filedes, const struct iovec *iov, int iovecnt);
// filedes : 文件描述符
// iov     : 指向 iovec 结构数组的一个指针
// iovecnt : 数组元素的个数
//
// 说明：
// iovec 的指针结构如下：
// struct iovec {
//		void *iov_base;		// starting address of buffer
//		size_t iov_len;		// size of buffer
// }

// writev 以顺序 iov[0], iov[1] 至 iov[iovcnt - 1] 重缓冲区中聚集输出数据。
// writev 返回输出的字节总数。readv 则将读入的数据按照上述同样顺序散布到
// 缓冲区中，readv 总是先填满一个缓冲区，然后再填写下一个。readv 返回读到
// 的总字节数。如果遇到文件结尾，已无数据可读，则返回 0。

int main(void) {
	double x = 1.3f;
	std::cout << floor(x) << std::endl;
	std::cout << ceil(x) << std::endl;

	struct iovec iov[2];
	char *buf1 = (char*)malloc(5);
	char *buf2 = (char*)malloc(1024);

	memset(buf1, 0, 5);
	memset(buf2, 0, 1024);

	iov[0].iov_base = buf1;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf2;
	iov[1].iov_len = 1024;

	ssize_t nread = 0;
	ssize_t nwrite = 0;
	nread = readv(STDIN_FILENO, iov, 2);
	if (nread < 0) {
		perror("readv error.");
	} else {
		printf("readv:\n");
		printf("buf1 is: %s\t length is: %zu\n", buf1, strlen(buf1));
		printf("buf2 is: %s\t length is: %zu\n", buf2, strlen(buf2));
	}

	printf("writev:\n");
	nwrite = writev(STDOUT_FILENO, iov, 2);
	if (nwrite < 0) {
		perror("writev error.");
	}

	free(buf1);
	free(buf2);
	printf("readv and writev example from apue.\n");
	return EXIT_SUCCESS;
}
