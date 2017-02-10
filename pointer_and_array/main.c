#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char a[] = "Hello";		// “” 内的内容位于静态存储区
	a[0] = 'X';
	printf("%s\n", a);
	char *p = "world";
	//p[0] = 'X';				// 该语句试图修改常量字符串的内容而导致运行错误
	printf("%s\n", p);
	exit(EXIT_SUCCESS);
}
