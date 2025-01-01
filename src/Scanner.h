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

	int start = 0;
	int current = 0;
	int line = 1;
	std::string source;
	std::vector<Token> tokens;
};
