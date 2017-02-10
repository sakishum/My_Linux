#include <cstdio>
#include <cstdlib>

int main(void) {
	// 使用 freopen 函数实现重定向输出流
	puts("stdout is printed to console.\n");
	if (freopen("out.txt", "w", stdout) == NULL) {
		perror("freopen fail.\n");
		exit(EXIT_FAILURE);
	}
	puts("stdout is redirected to file.\n");	// 不会在终端输出，万恶是保存在 out.txt 文件
	fclose(stdout);
	exit(EXIT_SUCCESS);
}

/*
 * stdin、stdout 和 stderr 与终端有密切关系，通常在生产环境时，会将这三个流重定向到其他文件。
 * 比如编写守护进程时，因为守护进程和终端无关，所以往往需要将 stdin、stdout 和 stderr 重定向
 * 到 /dev/null 去。
 *
 * */
