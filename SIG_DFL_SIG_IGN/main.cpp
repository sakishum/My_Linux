#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

#define SIG_DFL ((void(*)(int))0)
#define SIG_IGN ((void(*)(int))1)

int main(void) {
	int a = (int)SIG_DFL;
	int b = (int)SIG_IGN;
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	exit(EXIT_SUCCESS);
}
