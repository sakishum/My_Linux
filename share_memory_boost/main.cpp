/**
 * @file main.cpp
 * @Synopsis  一个服务端进程创建了一个共享内存对象，映射它并且初始化所有字节至同一个值。
 *		      之后，客户端进程打开共享内存，映射它并且检查数据是不是被正确的初始化了。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-09
 */

#include <cstdio>
#include <cstdlib>		// system
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

static const std::string Topic = "MySharedMemory";

auto main(int32_t argc, char* argv[]) -> int32_t {
	// Parent process
	if (argc == 1) {
		std::cout << "Parent Process." << std::endl;
		// Remove shared memory on construction and destruction
		// As shared memory has kernel or filesystem persistence, the user must explicitly destroy it. 
		struct shm_remove {
			shm_remove(void) { boost::interprocess::shared_memory_object::remove(Topic.c_str()); }
			~shm_remove(void) { boost::interprocess::shared_memory_object::remove(Topic.c_str()); }
		} remover;

		// Create a shared memory object.
		boost::interprocess::shared_memory_object shm (boost::interprocess::create_only,	// open or crate
				Topic.c_str(),						// name
				boost::interprocess::read_write);	// mode
		
		// Set size
		// When a shared memory object is created, its size is 0. 
		shm.truncate(1000);

		// Map the whole shared memory in this process
		boost::interprocess::mapped_region region(shm, boost::interprocess::read_write);

		// Write all the memory to 1
		// region.get_address() : 取得文件的首地址
		//  region.get_size()   : 取得文件的长度
		std::memset(region.get_address(), 8, region.get_size());

		// Launch child process
		std::string s(argv[0]);
		s += " child ";

		// system() 会调用 fork() 产生子进程，由子进程来调用 /bin/sh -c string 来执行参数 string
		// 字符串所代表的命令，此命令执行完后随机返回原调用的进程。 在调用 system() 期间 SIGCHLD
		// 信号会被暂时搁置，SIGINT 和 SIGQUIT 信号会被忽略。
		if (0 != std::system(s.c_str())) {
			exit(EXIT_SUCCESS);
		}
		std::cout << "Parent Process. End" << std::endl;
	} else {
		std::cout << "Child Process." << std::endl;
		// Open already created shared memory object.
		boost::interprocess::shared_memory_object shm ( boost::interprocess::open_only,
				Topic.c_str(),
				boost::interprocess::read_only);

		// Map the whole shared memory in this process
		boost::interprocess::mapped_region region(shm, boost::interprocess::read_only);

		// Check that memory was initialized to 1
		char *mem = static_cast<char*>(region.get_address());
		for (std::size_t i = 0; i != region.get_size(); ++i) {
			//printf("data: %d\n", *mem);
			if (*mem++ != 8) {
				std::cerr << "Not initiualized all by 1" << std::endl;
				exit(EXIT_FAILURE);		// Error checking memory
			}
		}
		std::cout << "Child Process. End" << std::endl;
	}
	exit(EXIT_SUCCESS);
}

