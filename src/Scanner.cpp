#include "Scanner.h"

#include <sstream>

Scanner::Scanner(const std::string &source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}
}

bool Scanner::isAtEnd() { return current >= source.length(); }