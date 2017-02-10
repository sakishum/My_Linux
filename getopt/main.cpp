#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
	int input;
	printf("argc: %d\n", argc);
	printf("argv[%d] = \"%s\"", 1, argv[2]);
	while ((input = getopt(argc, argv, "h")) != -1) {
		printf("Enter\n");
		if ( input == 'h' ) {
			printf("%d\n", input);	
			continue;
		}
	}
	exit(EXIT_SUCCESS);
}


