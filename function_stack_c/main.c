// http://www.cnblogs.com/xkfz007/archive/2012/03/27/2420158.html
#include <stdio.h>
#include <stdlib.h>

int g = 100;

void foo(int x, int y, int z) {
	printf("Enter function.\n");
	int l1 = 401;
	int l2 = 402;
	printf("l1= %d at [%X]\n", l1, &l1);
	printf("l2= %d at [%X]\n", l2, &l2);
	printf("x = %d at [%X]\n", x, &x);
	printf("y = %d at [%X]\n", y, &y);
	printf("z = %d at [%X]\n", z, &z);
	printf("g = %d at [%X]\n", g, &g);
	/*
	 * 栈的增长方向 高地址 向 低地址。
	 * 所以压入顺序为 x, y, z
	 * g = 100 at [6555028]
	 * Enter function.
	 * x = 100 at [596AB22C]
	 * y = 200 at [596AB228]
	 * z = 300 at [596AB224]
	 * l = 400 at [596AB23C]	<- 局部变量
	 * g = 100 at [6555028]		<- 全局变量
	 * */
}

int main(void) {
	printf("g = %d at [%X]\n", g, &g);
	foo(100, 200, 300);
	exit(EXIT_SUCCESS);
}
