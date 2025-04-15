#pragma once

#include <cstddef>
#include <string>

#include "Errors.hpp"

namespace BisayaPP {

void run(const std::string& source);
auto runFile(const char* path) -> int;
void runPrompt();
void error(size_t line, const std::string& message);
void report(size_t line, const std::string& where, const std::string& message);
void error(const Token& token, const std::string& message);
void runtimeError(const RuntimeError& error);

// Resets the interpreter state
// Used especially for test cases
void resetInterpreter();

}  // namespace BisayaPP
