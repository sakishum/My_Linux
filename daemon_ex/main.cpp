/**
 * @file main.cpp
 * @Synopsis  tail -f /var/log/system.log
 *			  kill $(pidof test)
 *			  创建守护进程所需要的步骤，分 5 步。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-07-08
 */

#if __APPLE__
#define daemon yes_we_know_that_daemon_is_depreecated_in_x_10_7_thankyou
#endif

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

#if __APPLE__
#undef daemon
extern int daemon(int, int);
#endif

#define DAEMON_NAME "vdaemon"

#define ERR_EXIT(m) \
do{ \
	perror(m);\
	exit(EXIT_FAILURE);\
} while (0)

void process(void) {
	syslog(LOG_NOTICE, "Writing to my Syslog");
}

void create_daemon(void);
int main(void) {
	// Set our Logging Mask and open the log
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Enter Daemon.");

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

	// Close the log
	closelog();

	exit(EXIT_SUCCESS);
}
