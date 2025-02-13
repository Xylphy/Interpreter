#include <cstdlib>
#include <iostream>

#include "interpreter.hpp"

int main() {
	int choice;
	std::cout << "Enter 1 to run file or 2 to run prompt: ";
	std::cin >> choice;
	std::string path;

	switch (choice){
		case 1:
			std::cout << "Enter path to file: ";
			std::cin >> path;
			runFile(path.c_str());
			break;
		case 2:
			runPrompt();
			break;
	}
	return 0;
}