#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

class Complex {
public:
	Complex (double a, double b): r (a), c (b) {}

private:
	double r; // Real Part
	double c; // Complex Part
};

int main(int, char**) {
	Complex* array[1000];
	// 外层循环的每次迭代都会导致 1000 次分配和释放。5000 次
	// 这样的迭代将导致 10 百万次用户和内核代码之间的切换。
	for (int i = 0;i  <  5000; i++) {
		for (int j = 0; j  <  1000; j++) {
			array[j] = new Complex (i, j);
		}
		for (int j = 0; j  <  1000; j++) {
			delete array[j];
		}
	}
	exit(EXIT_SUCCESS);
}
