#include <initializer_list>
#include <vector>

#include "Expr.hpp"
#include "ParseError.hpp"
#include "Token.hpp"

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  Parser(std::vector<Token>&& tokens);
  auto parse() -> Expr*;

 private:
  auto match(std::initializer_list<TokenType> types) -> bool;
  auto check(TokenType type) -> bool;
  auto isAtEnd() -> bool;
  auto expression() -> Expr*;
  auto equality() -> Expr*;
  auto comparison() -> Expr*;
  auto term() -> Expr*;
  auto factor() -> Expr*;
  auto unary() -> Expr*;
  auto primary() -> Expr*;
  auto advance() -> Token;
  auto peek() -> Token;
  auto previous() -> Token;
  auto consume(TokenType type, const std::string& message) -> Token;
  void synchronize();
  static auto error(const Token& token, const std::string& message)
      -> ParseError;

  std::vector<Token> tokens;
  int current = 0;
};
