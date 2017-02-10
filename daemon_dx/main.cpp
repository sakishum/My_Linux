#include <cstdio>
#include <cstdlib>
#include <sys/syslog.h>

void process(void) {
	syslog(LOG_NOTICE, "Writing to my Syslog.");
}

int main(void) {
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog("testd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	process();
	closelog();
	printf("--Done.--");
	exit(EXIT_SUCCESS);
}
