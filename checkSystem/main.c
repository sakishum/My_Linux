#include <stdio.h>
#include <stdlib.h>

// return: 1 小端; 0 大端
int checkSystem(void) {
	if (sizeof(int) != 4) {
		return -1;
	}
	union check {
		int i;
		char c;
	}c;
	c.i = 1;
	// 0x0 0x0 0x0 0x1
	return (c.c == 1);
}

// return: 1 小端; 0 大端
int checkSystem1(void) {
	if (sizeof(short) != 2) {
		return -1;
	}
	union check {
		short s;
		char c[2];
	}c;
	c.s = 0x0102;
	if (c.c[0] == 1 && c.c[1] == 2) {
		printf("B\n");
		return 0;
	} else if (c.c[0] == 2 && c.c[1] == 1) {
		printf("L\n");
		return 1;
	}
	return -1;
}

int main(void) {
	if (0 == checkSystem()) {
		printf("Big-ending.\n");
	} else {
		printf("Little-ending.\n");
	}
	if (0 == checkSystem1()) {
		printf("Big-ending.\n");
	} else {
		printf("Little-ending.\n");
	}
	exit(0);
}
