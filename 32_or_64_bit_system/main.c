/**
 * @file main.c
 * @Synopsis  用 C 语言写一个程序, 求当前系统的 位数 。 ... 是个问题 ... 
 * @Synopsis  用 C 语言写一个程序, 求当前系统整型字字长(16、32、64位), 不能使用 sizeof() ?
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-05-18
 */

#include <stdio.h>
#include <stdlib.h>

long getSizeOfInt(void) {
	int arr[2];
	return (long)((long)&(arr[1]) - (long)&(arr[0]))<<3;
}

int main(void) {
	// 使用 sizeof()
	// 此种方法只能知道编译器是什么型，不能知道系统是什么型。
	// 因为(int *) 与 sizeof(int) 都是编译器处理的东西，他们的长度由编译器决定，并不受目标系统的影响。
	// 编译器屏蔽了硬件细节。应用层看不出什么内容，从 OS 内部或则驱动去获取。
	// 
	int *pi = NULL;
	union ut {
		short s;
		char c[2];
	} u;

	if (sizeof(pi) == 4) {
		printf("32 bits\n");
	}
	if (sizeof(pi) == 8) {
		printf("64 bits\n");
	}

	// 当前系统整型字长:
	printf("%ld bits.\n", getSizeOfInt());

	// Little ending： 将低字节存储在起始地址
	// Big ending   ： 将高字节存储在起始地址
	if (sizeof(short) == 2) {
		// 十六进制，一个数值占4位
		u.s = 0x0102;
		printf("%X\n", u.s);
		printf("[0]=%X, [1]=%X\n", u.c[0], u.c[1]);
		// 通过 union 将 short (2 字节) 强制转换成两个 char 单字节 
		// 低字节存的是数据的高字节数据
		if (u.c[0] == 1 && u.c[1] == 2) {
			printf("Big-ending.\n");
		}
		// 低字节存的是数据的低字节数据
		if (u.c[0] == 2 && u.c[1] == 1) {
			printf("Little-ending.\n");
		}
	}
}
