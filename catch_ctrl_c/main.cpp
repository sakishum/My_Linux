#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>		// SIGTERM, SIGINT, signal
#include <string.h>		// strerror
#include <unistd.h>		// sleep
#include <errno.h>		
#include <stdint.h>		


bool forever = true;

void sighandler(int32_t sig)
{
	// cleanup and close up stuff here
	std::cout << "Signal " << sig << " caugth..." << std::endl;
	std::cout << "Errno info: " << strerror(errno) << std::endl; 
	forever = false;
}

int32_t main(int32_t, char**)
{
	signal(SIGTERM, &sighandler);	// kill PID	-> 15
	signal(SIGINT, &sighandler);	// ctrl-c	-> 2

	while (forever)
	{
		std::cout << "Going to sleep...." << std::endl;
		sleep(1);
	}

	// terminate program 
	exit(EXIT_SUCCESS);
}
