/**
 * @file main.cpp
 * @Synopsis  获取文件行数
 *		利用fgets。fgets的原型：char *fgets(char *s, int size, FILE *stream);，
 *		fgets最多可以读到size-1个字符，剩下的一个是给 \0 预留的，即总要给 \0 
 *		预留一位。同时还应注意：fgets遇到 \n 时就停止本次读取，如果数组中可以
 *		放下 \n 那么就读 \n ，否则只能下一次读取了，但是可以肯定的是，如果放到
 *		下一次读，那么 \n 肯定是第一个，从而造成下次只能读到 \n ,\0会自动加上。
 *		剩下的内容还得下下次读。这下就找到规律了！即 \n 总是在 \0 的前一位上。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-10-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>

int32_t main(int32_t argc, char *argv[]) {
	FILE *fp;
	int32_t n = 0;
	char buffer[3]; 

	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	// r+ 打开可读写的文件，该文件必须存在
	if ((fp = fopen(argv[1], "r+")) == NULL) {
		fprintf(stderr, "open file %s error. %s\n", argv[1], strerror(errno));
	}

	while ((fgets(buffer, 3, fp)) != NULL) {
		if (buffer[strlen(buffer) - 1] == '\n') {
			++n;
		}
	}

	fclose(fp);
	printf("count %d lines.\n", n);

	exit(EXIT_SUCCESS);
}

