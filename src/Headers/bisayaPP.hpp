#pragma once

#include <cstddef>
#include <string>

#include "Token.hpp"

namespace BisayaPP {

void run(const std::string& source);
void runFile(const char* path);
void runPrompt();
void error(size_t line, const std::string& message);
void report(size_t line, const std::string& where, const std::string& message);
void error(const Token& token, const std::string& message);

}  // namespace BisayaPP
