#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Scanner.h"

bool hadError = false;

void run(const std::string &source) {
	std::cout << "Running: " << source << '\n';
	Scanner *scanner = new Scanner(source);
	std::vector<Token> tokens = scanner->scanTokens();

	for (Token token : tokens) std::cout << token << '\n';
}

void runFile(const char *path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "Could not open file " << path << '\n';
		exit(74);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	run(buffer.str());

	if (hadError) exit(65);
}

void runPrompt() {
	std::string line;
	std::getline(std::cin, line);

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
