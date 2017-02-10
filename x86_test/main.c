#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a[5] = {1,2,3,4,5};
	int *ptr1 = (int*)(&a+1);
	int *ptr2 = (int*)((int*)a+1);
	printf("ptr1: %X, ptr2: %X\n", ptr1[-1], *ptr2);	// 5, 2
	exit(0);
}
