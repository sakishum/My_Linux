#include <cstdio>
#include <cstdlib>

// 标准输入的文件标识符为 0

int main(void) {
	char str[10];
	scanf("%s", str);			// 调用 scanf 函数接受用户输入内容，即从终端设备输入内容 
	fscanf(stdin, "%s", str);	// 也可以从 fscanf 指明 stdin 接收内容。
	exit(EXIT_SUCCESS);
}

