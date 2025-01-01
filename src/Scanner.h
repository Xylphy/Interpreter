#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Scanner {
   public:
	Scanner(const std::string &source);

	std::vector<Token> scanTokens();

   private:
	bool isAtEnd();
	void scanToken();
	bool match(char expected);
	char advance();
	void addToken(TokenType type, std::string literal);
	void addToken(TokenType type);

	int start = 0;
	int current = 0;
	int line = 1;
	std::string source;
	std::vector<Token> tokens;
};
