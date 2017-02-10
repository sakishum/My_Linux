#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	fork();
	printf("step 1\n");
#if 0
	fork() && fork() || fork();
#endif
	fork();
	printf("step 2\n");
	sleep(20);
	return EXIT_SUCCESS;
}
