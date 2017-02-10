/**
 * @file main.cpp
 * @Synopsis  用另一个新程序替换了当前进程的正文、数据、堆和栈段。
 *  当前进程的正文都被替换了，那么execl后的语句，即便execl退出了，都不会被执行。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-09-06
 */

#include <cstdio>
#include <unistd.h>
#include <cstdlib>

// linux IO 涉及终端时（如标准的输入输出），通常使用的是 行缓冲。
// 在这种情况下，当在输入和输出中遇到换行符时，标准 IO 库执行IO
// 操作。(不遇到换行与强制输入输出是不输出的，待到 execl 执行后，
// 创建的进程映像，后面的 printf 也不会打印。)
int main(void) {
	printf("call execl.");		// 不会打印
	sleep(1);
	// 用另一个新程序替换当前进程的正文、数据、堆和栈段。
	// execl("./printhello", "printhello", (char*)0);
	// 当前进程的正文都被替换了，那么 execl 之后的语句，
	// 即便 execl 退出了，都不会被执行。
	
	// int execl(const char *path, const char *arg, ...);
	// execl()用来执行参数path字符串所代表的文件路径, 
	// 接下来的参数代表执行该文件时传递的argv[0],argv[1].....是后一个参数必须用空指针NULL作结束
	// 返回值：成功则不返回值， 失败返回-1， 失败原因存于errno中
	execl("/bin/sh", "", NULL);	// 因为 execl 并不创建新进程，所以前后的进程 ID 并未改变。
	printf("error");			// 不会打印
	return EXIT_SUCCESS;
}
