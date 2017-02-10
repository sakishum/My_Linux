/**
 * @file main.cpp
 * @Synopsis   Ashmem(Anonymous Shared Memory), UNIX 的匿名共享内存. 
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-09
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <boost/interprocess/anonymous_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

auto main(int32_t, char**) -> int32_t {
	// 一旦片段建立，可以使用fork()调用以便内存区域能够被用于通信两个相关进程
	try {
		// Create an anonymous shared memory segmaent with size 1000
		boost::interprocess::mapped_region region(boost::interprocess::anonymous_shared_memory(1000));

		// Write all the memory to 1
		std::memset(region.get_address(), 1, region.get_size());

		// The segment is unmapped when "region" goes out of scope
	} catch (boost::interprocess::interprocess_exception &ex) {
		std::cout << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
