#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>


int main(int, char**) {
	//signal(SIGINT,  SIG_IGN);
    signal(SIGHUP,  SIG_DFL); // 终端退出，应该也跟着退出
    signal(SIGQUIT, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
    signal(SIGXFSZ, SIG_IGN);
	for (;;) {}
	exit(EXIT_SUCCESS);
}
