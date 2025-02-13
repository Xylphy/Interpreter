#pragma once

#include <string>

void run(const std::string &source);
void runFile(const char *path);
void runPrompt();
void error(int line, const std::string &message);
void report(int line, const std::string &where, const std::string &message);