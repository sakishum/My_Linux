#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFER_SIZE 100

auto main(int32_t argc, char* argv[]) -> int32_t {
	if (argc < 2) {
		exit(EXIT_FAILURE);
	}
	
	int fd;
	struct stat sb;
	char *mapped;

	// 打开文件
	if ((fd = open(argv[1], O_RDWR)) < 0) {
		perror("open");
	}

	// 获取文件属性
	if ((fstat(fd, &sb)) == -1) {
		perror("fstat");
	}

	// 将文件或其他对象映射至进程的地址空间
	// 文件被映射到多个页上，如果文件的大小不是所有页的大小之和，最后一个页不被使用的空间将会被释放。
	// void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset)
	//
	// mmap 的作用就是映射文件描述符fd指定文件的[offset, offset + len] 区域至调用进程的 [addr, addr+len]的内存区域。
	// fd 为即将映射到进程空间的文件描述符，一般由 open() 返回，同时，fd 可以指定为 -1，此时必须指定 flag 为 MAP_ANON，表明进行的是
	// 匿名映射（不涉及具体的文件名，避免了文件的创建及打开，很显然只能用于相关联的进程间通信）。
	// len参数: 是映射到调用进程地址空间的字节数，它从映射文件开头 offset 个字节开始。
	// prot参数 :指定共享内存的范文权限可取以下值的或：PROT_READ（可读）、PROT_WRITE（可写）、PROT_EXEC（可执行）、PROT_NONE（不可访问） 
	// flag参数: 由以下几个常值指定： MAP_SHARED、MAP_PRIVATE、MAP_FIXED，其中MAP_SHARED、MAP_PRIVATE 必选其一，MAP_FIXED 则不推荐使用
	// offset 参数：一般设为 0，表示从头文件开始映射。
	// addr 参数：指定文件应该被映射到进程空间的起始地址，一般被指定为一个空指针（NULL），此时选择骑士地址的任务留给内核来完成。
	if ((mapped = (char*)mmap(NULL, sb.st_size, PROT_READ|
					PROT_WRITE, MAP_SHARED, fd, 0)) == (void*)-1) {
		perror("mmap");
	}

	/* 注意：私有映射无法修改文件 */
	//if ((mapped = (char*)mmap(NULL, sb.st_size, PROT_READ|
					//PROT_WRITE, MAP_PRIVATE, fd, 0)) == (void*)-1) {
		//perror("mmap");
	//}
	
	// 映射完毕，关闭文件
	close(fd);

	// 直接操作文件映射
	printf("%s", mapped);

	// 修改一个字符，同步到磁盘文件
	mapped[20] = '7';
	if ((msync((void*)mapped, sb.st_size, MS_SYNC)) == -1) {
		perror("msync");
	}

	// 释放特定地址区域的对象映射
	if ((munmap((void*)mapped, sb.st_size)) == -1) {
		perror("munmap");
	}

	exit(EXIT_SUCCESS);
}
