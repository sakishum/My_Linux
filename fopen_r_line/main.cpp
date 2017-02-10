/**
 * @file main.cpp
 * @Synopsis  获取文件行数
 *		将文件中的字符一个一个读出，然后与 \n 作比较。
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
	int32_t ch = 0;
	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen(argv[1], "r+")) == NULL) {
		fprintf(stderr, "open file %s error. %s\n", argv[1], strerror(errno));
	}

	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			++n;
		}
	}

	fclose(fp);
	printf("count %d lines.\n", n);

	exit(EXIT_SUCCESS);
}
