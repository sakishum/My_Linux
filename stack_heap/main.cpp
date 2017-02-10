/**
 * @file main.cpp
 * @Synopsis  堆栈申请空间的申请与释放。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-05
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

void foo(int a) {
	printf("a = %d\n", a);
	char *pBuffer = nullptr;
	// <--nothing allocated yet (excluding the pointer itself, which is allocated here on the stack).
	bool b = true;
	// Allocated on the stack
	if (b) {
	// Create 500 bytes on the stack
		char buffer[500];
	// Create 500 bytes on the heap
		pBuffer = new char[500];
	}
	// <--buffer is deallocated here, pBuffer is not
}
	// <--oops there's a memory leak, I should have called delete[] pBuffer;

auto main(int32_t, char**) -> int32_t {
	int a = 10;
	foo(a);
	exit(EXIT_SUCCESS);
}
