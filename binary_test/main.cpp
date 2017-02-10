#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void myswap(int &a, int &b) {
	if (a == b) {
		return;
	}
	a ^= b;
	b ^= a;
	a ^= b;
}

int numOfBit1(int a) {
	int cnt = 0;
	while (a != 0) {
		++cnt;
		a &= a - 1;		// 将最左边的1置为0；正负都可以算，负数是按照补码计算的，最后的符号位也被统计
	}
	return cnt;
}

int myAbs(int a) {
	int sign = a >> 31;		// 取符号位
	return (a^sign) - sign;	// （a^0）- 0 = a, (a^-1)-(-1) = ~a+1 = -a, a^-1 即为 a 取反
}

int main(int, char**) {
	int x = -1025;
	if (x % 2 != 0) {
		// 如果x为负奇数，x%2=-1
		std::cout << "Nagetive." << x % 2 << std::endl;
	}
	if ((x & 0x1) == 0) {
		std::cout << "Not odd." << std::endl;
	}

	int a = 3, b = 4;
	myswap(a, b);
	std::cout << "a: " << a << ", b: " << b << std::endl;

	int c = 0x7;
	std::cout << "c\'s bit 1 count is " << numOfBit1(c) << std::endl;

	int d = 1;
	// 正负转换，不适用正负号。不管正负数，取反后加1即可
	// 0001 ~  1110  -0 +1 -1
	d = ~d + 1;	// d 变为 -1
	std::cout << "d: " << d << std::endl;
	d = ~d + 1;	// d 变为 1
	std::cout << "d: " << d << std::endl;

	// 求绝对值，不判断正负数，不适用正负号，返回绝对值
	int e = -226;
	std::cout << myAbs(e) << std::endl;

	exit(EXIT_SUCCESS);
}
