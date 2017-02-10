/**
 * @file main.cpp
 * @Synopsis  tail -f /daemon.log 
 *			  kill $(pidof test)
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-07-08
 */


#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/syslog.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <time.h>

#define ERR_EXIT(m) \
do{ \
	perror(m);\
	exit(EXIT_FAILURE);\
} while (0)

void process(void) {
    time_t t;
    int fd = 0;
    fd = open("daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        ERR_EXIT("Open error");
    }
    t = time(0);
    char *buf = asctime(localtime(&t));
    write(fd, (void*)buf, strlen(buf));
    close(fd);
}

void create_daemon(void);
int main(void) {
	// 无法在 mac 中使用 daemon(int, int) 函数。
	// daemon(0, 1) : 就是不关闭标准输入输出结果
	// daemon(1, 0) : 就是不重定向，目标文件没有切换到 / 目录下
	if (daemon(0, 0) == -1) {
		ERR_EXIT("Daemon error.");
	}

	// ===================
	// Main Process
	// ===================
	while (true) {
		process();	// Run our Process
		sleep(10);	// Sleep for 10 seconds
	}

	/*
	 * ps -ef| grep test
	 * root     19638     1  0 20:23 ?        00:00:00 ./test
	 * root     19687  4293  0 20:24 pts/24   00:00:00 grep test
	 * */

	exit(EXIT_SUCCESS);
}
