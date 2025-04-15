#include <fstream>
#include <iostream>
#include <memory>
#include <print>
#include <sstream>

#include "Headers/Interpreter.hpp"
#include "Headers/Parser.hpp"
#include "Headers/Scanner.hpp"

namespace BisayaPP {

Interpreter interpreter;

const int FILE_OPEN_ERROR = 74;
const int RUNTIME_ERROR = 70;
const int SYNTAX_ERROR = 65;

bool hadError = false;
bool hadRuntimeError = false;

void run(const std::string& source) {
  std::vector<std::unique_ptr<Stmt>> statements =
      std::make_unique<Parser>(
          *std::make_unique<std::vector<Token>>(
              std::make_unique<Scanner>(source)->scanTokens()))
          ->parse();

  if (hadError) {
    return;
  }

  interpreter.setInterpretResult(statements);
}

auto runFile(const char* path) -> int {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Could not open file " << path << '\n';
    exit(FILE_OPEN_ERROR);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  run(buffer.str());

  if (hadError) {
    return SYNTAX_ERROR;
  }
  if (hadRuntimeError) {
    return RUNTIME_ERROR;
  }
  return 0;
}

void runPrompt() {
  std::string line;
  std::getline(std::cin, line);

  while (true) {
    std::print("> ");
    if (!std::getline(std::cin, line) || line.empty()) {
      break;
    }

    run(line);
    hadError = false;
  }
}

void report(size_t line, const std::string& where, const std::string& message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message
            << '\n';
}

void error(size_t line, const std::string& message) {
  report(line, "", message);
}

void error(const Token& token, const std::string& message) {
  if (token.type == TokenType::END_OF_FILE) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void runtimeError(const RuntimeError& runtimeError) {
  error(runtimeError.token, runtimeError.what());
  hadRuntimeError = true;
}

void resetInterpreter() { interpreter.resetInterpreter(); }
}  // namespace BisayaPP