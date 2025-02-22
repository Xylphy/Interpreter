#include <initializer_list>
#include <vector>

#include "Errors.hpp"
#include "Stmt.hpp"

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  Parser(std::vector<Token>&& tokens);
  auto parse() -> std::vector<Stmt*>;

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
  auto synchronize() -> void;

  auto declaration() -> Stmt*;
  auto varDeclaration() -> Stmt*;

  auto statement() -> Stmt*;
  auto printStatement() -> Stmt*;
  auto expressionStatement() -> Stmt*;
  static auto error(const Token& token, const std::string& message)
      -> ParseError;

  std::vector<Token> tokens;
  int current = 0;
};
