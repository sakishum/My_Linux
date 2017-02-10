#include <cstdio>
#include <cstdlib>

// 标准输出的文件标识符为 1

int main(void) {
	printf("%s\n", "hello");			// 调用 printf 函数将内容输出到终端上
	fprintf(stdout, "%s\n", "hello");	// 使用 fprintf 指明 stdout 把内容输出到终端上
	exit(EXIT_SUCCESS);
}
