#pragma once
#include <cstddef>
#include <vector>

#include "Token.hpp"

class AbstractScanner {
 public:
  std::string source;
  std::vector<Token> tokens;

  size_t start = 0;
  size_t current = 0;
  size_t line = 1;

  AbstractScanner(std::string source, size_t line);
  virtual ~AbstractScanner() = default;

  virtual auto scanToken() -> void = 0;
  virtual auto identifier() -> void = 0;
  auto scanTokens() -> std::vector<Token>;
  auto addToken(TokenType type, const std::any& literal) -> void;
  auto addToken(TokenType type) -> void;
  auto match(char&& expected) -> bool;
  auto advance() -> char;
  [[nodiscard]] auto isAtEnd() const -> bool;
  [[nodiscard]] auto peek() const -> char;
  [[nodiscard]] auto peekNext() const -> char;
};