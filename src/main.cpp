#include <iostream>

#include "cpplox.h"

int main(int argc, char **argv) {
	if (argc > 1) {
		std::cout << "Usage: cpplox [script]" << '\n';
		return 64;
	} else if (argc == 1) {
		runFile(argv[0]);
	} else {
		runPrompt();
	}
	return 0;
}