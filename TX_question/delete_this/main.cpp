#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Test {
public:
	Test(void) {
		std::cout << "Constructor." << std::endl;
	}
	~Test(void) {
		std::cout << "Destructor." << std::endl;
	}
	void foo(void) {
		std::cout << "Called Test::foo()." << std::endl;
	}
	void test(void) {
		// delete this 指针，
		delete this;
	}
};

int main(int, char**) {
	Test *t2 = NULL;
	t2->foo();
	Test t1;
	t1.test();
	t1.foo();
	exit(EXIT_SUCCESS);
}
