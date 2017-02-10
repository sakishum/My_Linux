#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include <errno.h>

class Trace {
public:
	Trace(void) : notify_(0), f_(NULL) {
	}
	Trace(FILE *ff) : notify_(0), f_(ff) {
	}
	void print(const char *s) {
		if (notify_) {
			// printf(args);  等价于 fprintf(stdout, args);
			fprintf(f_, "%s", s);
		}
	}
	void on(void) {
		notify_ = 1;
	}
	void off(void) {
		notify_ = 0;
	}

private:
	int notify_;
	FILE *f_;
};

int main(int, char**) {
	// 但如果用转向标准输出到磁盘文件，则可看出两者区别。stdout输出到磁盘文件，stderr在屏幕。
	// ./test >temp.txt
	// strerr是作为程序运行过程中的错误显示出来的，若想将它重写向到某文件中，需要运行如下命令：
	// ./test 2>temp.txt
	fprintf(stderr,"1 can't open it!\n");     // 标准错误输出设备 两者默认向屏幕输出。
	fprintf(stdout,"2 can't open it !\n");	// 标准输出设备 (printf("..")) 同 stdout。
	printf("3 can't open it!\n");

	Trace trace(stdout);
	trace.on();
	trace.print("begin main()\n");
	// main 函数主体
	trace.print("end main()\n");
	exit(EXIT_SUCCESS);
}
