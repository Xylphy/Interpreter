#include "Headers/Token.hpp"

#include <ostream>

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type(type),
      lexeme(std::move(lexeme)),
      literal(std::move(literal)),
      line(line) {}

Token::Token(const Token& other) {
  if (this != &other) {
    *this = other;
  }
}

auto operator<<(std::ostream& ostream, const Token& token) -> std::ostream& {
  ostream << token.type << " " << token.lexeme << " ";
  return ostream;
}