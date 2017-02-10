#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>		// strerror
#include <iostream>		// cout, right
#include <iomanip>		// setw

#define ERROR_NUM 150

auto main(int32_t, char**) -> int32_t {
	for (int32_t i = 0; i != ERROR_NUM; ++i) {
		//std::cout << "errno: " << std::right << std::setw(3) << i << ", means: " << strerror(i) << std::endl;
		std::cout << "errno: " << std::left << std::setw(3) << i << ", means: " << strerror(i) << std::endl;
	}
	exit(EXIT_SUCCESS);
}
