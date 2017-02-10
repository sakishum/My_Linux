/**
 * @file main.cpp
 * @Synopsis  通过匿名映射实现父子进程通信。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-17
 */
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

#define BUFFER_SIZE 100

auto main(int32_t, char**) -> int32_t {
	char *p_map = nullptr;

	p_map = (char*)mmap(nullptr, BUFFER_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
	if (fork() == 0) {
		sleep(1);
		printf("Child got a message: %s\n", p_map);
		sprintf(p_map, "%s", "hi, parent, this is child");
		munmap(p_map, BUFFER_SIZE);	// 实际上，进程终止时，会自动解除映射
		exit(EXIT_SUCCESS);
	} else {
		sprintf(p_map, "%s", "hi, child, this is parent");
		sleep(2);
		printf("parent got a message: %s\n", p_map);
	}
	exit(EXIT_SUCCESS);
}


