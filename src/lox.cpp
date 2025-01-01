#include <fstream>
#include <iostream>
#include <sstream>

#include "Scanner.h"

bool hadError = false;

void run(const std::string &source) {
	Scanner *scanner = new Scanner(source);
	std::vector<std::string> tokens = scanner->scanTokens();

	for (std::string token : tokens) std::cout << token << std::endl;
}

void runFile(const char *path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "Could not open file " << path << std::endl;
		exit(74);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	run(buffer.str());

	if (hadError) exit(65);
}

void runPrompt() {
	std::string line;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, line) || line.empty()) break;
		run(line);
        hadError = false;
	}
}

void report(int line, const std::string &where, const std::string &message) {
	std::cerr << "[line " << line << "] Error" << where << ": " << message
			  << std::endl;
}

void error(int line, const std::string &message) { report(line, "", message); }
