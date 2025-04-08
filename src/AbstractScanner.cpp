#include "Headers/AbstractScanner.hpp"

AbstractScanner::AbstractScanner(std::string source, size_t line)
    : source(std::move(source)), line(line) {}

auto AbstractScanner::scanTokens() -> std::vector<Token> {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(END_OF_FILE, "", "", line);
  return tokens;
}

void AbstractScanner::addToken(TokenType type, const std::any& literal) {
  tokens.emplace_back(type, source.substr(start, current - start), literal,
                      line);
}

void AbstractScanner::addToken(TokenType type) { addToken(type, ""); }

auto AbstractScanner::match(char&& expected) -> bool {
  if (isAtEnd() || source[current] != expected) {
    return false;
  }

  advance();
  return true;
}

auto AbstractScanner::isAtEnd() const -> bool {
  return current >= source.length();
}

auto AbstractScanner::peek() const -> char {
  return isAtEnd() ? '\0' : source[current];
}

auto AbstractScanner::peekNext() const -> char {
  return current + 1 >= source.length() ? '\0' : source[current + 1];
}

auto AbstractScanner::advance() -> char { return source[current++]; }
