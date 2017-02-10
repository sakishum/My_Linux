#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// new 是 C++ 的操作符
// new operator		-> new(operator new)，调用 operator new(size_t)
// operator new		-> 分配内存，失败调用 new_handle, 没有异常继续，有一场抛出 std::bad_alloc
// placement new	-> 在申请的对内存上调用对象的 构造函数 constructor, 不担心申请的内存是否成功
//
// 可以利用malloc+placement new来构建自己的内存管理模块，创建对象时，通过 malloc 申请一块内存，
// 然后调用 placement new 来完成对象的初始化；释放对象时，首先调用对象的析构函数，然后通过 free
// 释放空间。
//
// 将 malloc/free 使用 new/delete 替换
// #define malloc(s) ((void*)new unsigned char[s])
// #define free(p) (delete [](char*)(p))

class A {
public:
	A(void) {
		std::cout << "Call A constructor." << std::endl;
	}
	~A(void) {
		std::cout << "Call A destructor." << std::endl;
	}

	// 利用自定义参数获取更多的信息
	// 添加两个参数:char* file, int line,这两个参数记录new运算符的位置
	// 在new时将文件名和行号传入，这样我们就能在分配内存失败时给出提示：输出文件名和行号
	// 第一个参数必须是 size_t 类型的，返回值必须是 void *
	void *operator new(size_t size, const char *file, int line) {
		if (0 == size) {
			return NULL;
		}
		std::cout << "Call A::operator new on file:" << file << " line:" << line << std::endl;
		return malloc(size);
	}

	void *operator new[](size_t size) {
		return operator new(size, __FILE__, __LINE__);
	}

	// 只能由一个参数
	// 参数类型必须是 void*
	void operator delete(void *pointer) {
		if (NULL != pointer) {
			std::cout << "Call A::operarot delete on file:" << __FILE__ << " line:" << __LINE__ << std::endl;
			return free(pointer);
		}
	}

	void operator delete[](void *pointer) {
		operator delete(pointer);
	}
};

#define new new(__FILE__, __LINE__)

int main(int, char**) {
	// 需要将类的声明实现与new的使用隔离开来。并且将类头文件放在宏定义之前。否则在类A中的
	// operator new重载中的new会被宏替换，整个函数就变成了： 
	// void* operator new(__FILE__, __LINE__)(size_t size, char* file, int line)
	A *p1 = new A;
	delete p1;

	A *p2 = new A;
	delete p2;

	std::cin.get();
	exit(EXIT_SUCCESS);
}
