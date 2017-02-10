#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class A {
public:
	A(void) {
		std::cout << "call A constructor." << std::endl;
	};

	~A(void) {
		std::cout << "call A destructor." << std::endl;
	}
};

// 将对象的分配，构造，析构和释放分离开来，这也是new和delete运算符两句就能完成的操作。
// 分别注释掉new(a) A();和a->~A();两句，可以看到对应的构造和析构函数将不会被调用。
int main(int, char**) {
	A *p = (A*)::operator new(sizeof(A));	// 分配
	new(p) A();							// 构造
	p->~A();								// 析构
	::operator delete(p);					// 释放
	exit(EXIT_SUCCESS);
}
