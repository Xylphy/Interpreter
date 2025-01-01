#pragma once

#include <string>
#include <vector>

class Scanner {
   public:
	Scanner(const std::string &source) : source(source) {}

	std::vector<std::string> scanTokens();

   private:
	std::string source;
};
