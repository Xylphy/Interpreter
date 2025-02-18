#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

#include "Headers/AstPrinter.hpp"
#include "Headers/Expr.hpp"
#include "Headers/Parser.hpp"
#include "Headers/Scanner.hpp"
#include "Headers/Token.hpp"

namespace BisayaPP {

const int FILE_OPEN_ERROR = 74;
const int RUNTIME_ERROR = 70;

bool hadError = false;

void run(const std::string& source) {
  std::print("Running {}\n", source);

  auto* scanner = new Scanner(source);
  std::vector<Token> tokens = scanner->scanTokens();
  auto* parser = new Parser(tokens);
  Expr* expr = parser->parse();

  for (Token token : tokens) {
    std::print("{}\n", token);
  }

  if (hadError) {
    return;
  }
  auto* printer = new AstPrinter();
  printer->setPrintResult(expr);

  std::print("{}\n", printer->get());
}

void runFile(const char* path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Could not open file " << path << '\n';
    exit(FILE_OPEN_ERROR);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  run(buffer.str());

  if (hadError) {
    exit(RUNTIME_ERROR);
  }
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
  std::cerr << "[line " << line << "] Error" << where << ": " << message
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

}  // namespace BisayaPP
