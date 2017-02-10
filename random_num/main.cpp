#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

int main(void) {
	srand((int32_t)time(NULL));
	int32_t random = rand();
	std::cout << "random: " << random << std::endl;
	exit(EXIT_SUCCESS);
}
