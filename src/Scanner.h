#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Scanner {
   public:
	Scanner(const std::string &source) : source(source) {}

	std::vector<Token> scanTokens();

   private:
	std::string source;
};
