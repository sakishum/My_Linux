#include <cstdio>
#include <cstdlib>

// 标准错误和标准输出一样都是输出到终端上，标准错误输出的文件标识符为 2

int main(void) {
	// 语义上分析： 在程序处理时，正常的信息输出作为标准输出，产生的错误
	// 作为标准错误输出。这样在重定向的时候，就可以将正常的信息和错误信息
	// 重定向到不同的文件。
	printf("%s\n", "hello");			// 标准输出
	perror("hello");					// 用来将上一个函数发生错误的原因输出到标准错误(stderr)
	fprintf(stderr, "%s\n", "error");	// 向 stderr 中输出信息
	exit(EXIT_SUCCESS);
}

/*
 * 执行以下命令，重定向输出：
 * $ ./test  1>log.txt 2>error.txt		// 这样就将标准输出信息保存到了 log.txt, 错误的信息 error 保存到了 error.txt 文件
 * $ cat error.txt
 * hello: Undefined error: 0			// 参数 s 所指向的字符串会首先打印出来，后边再加上错误原因字符串(依照全局变量errno 的值决定输出的字符串)
 * error
 * $ cat log.txt
 * hello
 * */
