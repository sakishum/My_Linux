/**
 * @file main.cpp
 * @Synopsis  tail -f /var/log/system.log
 *			  kill $(pidof test)
 *			  创建守护进程所需要的步骤，分 5 步。
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

#define DAEMON_NAME "vdaemon"

#define ERR_EXIT(m) \
do{ \
	perror(m);\
	exit(EXIT_FAILURE);\
} while (0)

void process(void) {
	syslog(LOG_NOTICE, "Writing to my Syslog");
}

int main(void) {
	// Set our Logging Mask and open the log
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

	syslog(LOG_INFO, "Enter Daemon.");

	pid_t pid, sid;

	// Fork the Parent Process
	// fork 创建一个新进程。
	// 返回：子进程中返回 0，父进程中返回子进程 ID，出错返回 -1.
	pid = fork();
	if (pid < 0) {
		ERR_EXIT("Create Process Fail.");
		//perror("Create Process Fail.");
		//exit(EXIT_FAILURE);
	}

	// We got a good pid, Close the Parent Process
	// fork 返回给父进程子进程的 ID，子进程的 ID > 0
	// 1) 在父进程中执行 fork(), 并调用 exit() 退出；(目的是让 Daemon 在后台运行)
	if (pid > 0) {
		printf("Close Parent Process, PID: %d\n", pid);
		exit(EXIT_SUCCESS);
	}

	// Change the mask
	// 2) 在子进程中，调用 umask()，设置进程的 umask 为 0；
	// 当用户在 Linux 下创建目录或者文件的时候，会有一个预设的权限，这个权限再减去 umask 
	// 的权限，就是新建的目录或文件的实际权限。
	// 目录默认权限： 0777
	// 文件默认权限： 0666
	// $ umask ==>  0022 最前面的一个0是SUID， SGID 和 Sticky Bits 的特殊权限的设置
	// 新建一个目录 $ mkdir test || ll -d test ==> drwxr-xr-x  2 sakishum1118  staff    68B  7  9 19:33 test
	// 按照 umask 的设定，目录的权限应当等于 0777 - 0022, 就是 drwx-xr-x, 和上面输出的一致.
	// 新创建一个文件 $ touch test.txt || ll text.txt ==> -rw-r--r--  1 sakishum1118  staff     0B  7  9 19:37 test/test.txt
	// 按照 umask 的设定，目录的权限应当等于 0666 = 0022, 就是 -rw-r--r--, 和上面输出的一致
	// 计算过程：umask 先取反，然后和预设权限求与(计算需要吧每个权限数字分开来计算，不能当做一个值，实际结果一样)：
	//    000 010 010
	// ~
	// ----------------
	//    111 101 101
	// &  110 110 110
	// ----------------
	//    110 100 100
	//    rw- r-- r--
	umask(0);

	// Create a new Sinature ID for our child
	// 3) 在子进程中调用 setsid() 创建新的会话；(目的是脱离控制终端，登陆会话层和进程组)
	// 创建一个对话期(session), 如果，调用 setsid 不是一个进程组的组长，
	// 此函数创建一个对话期(session)
	sid = setsid();
	if (sid < 0) {
		ERR_EXIT("SETSID ERROR");
		perror("Call setsid() Fail.");
		exit(EXIT_FAILURE);
	}

	// Change Directory
	// If we can't find the directory we exit with failure
	// 4) 在子进程中调用 chdir()，让根目录"/"成为子进程的工作目录；(进程活动时，其工作
	// 目录所在文件系统不能卸下。一般需要将工作目录改变到根目录。对于需要转储核心，写
	// 运行日志的进程，需要将工作目录改变到特定的目录 /tempchild("/"))
	// 更改当前工作目录，成功返回0， 失败返回 -1
	if (chdir("/") < 0) {
		exit(EXIT_FAILURE);
	}

	// Close Standard File Descriptors
	// 5) 在子进程中关闭任何不必要的文件描述符。(进程会从父进程继承打开了的文件描述符，
	// 如不关闭，将会浪费系统资源，造成进程所在的文件系统无法卸下以及引起无法预料的错误)
	close(STDIN_FILENO);	// 标准输入(standard input, FD : 0)
	close(STDOUT_FILENO);	// 标准输出(standard output, FD : 1)
	close(STDERR_FILENO);	// 标准错误输出(standrand error, FD : 2)

	// ===================
	// Main Process
	// ===================
	while (true) {
		process();	// Run our Process
		sleep(10);	// Sleep for 10 seconds
	}

	// Close the log
	closelog();

	exit(EXIT_SUCCESS);
}
