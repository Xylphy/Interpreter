#include <initializer_list>
#include <vector>

#include "Expr.hpp"
#include "ParseError.hpp"
#include "Token.hpp"

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  Parser(std::vector<Token>&& tokens);
  Expr* parse();

 private:
  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  bool isAtEnd();
  Expr* expression();
  Expr* equality();
  Expr* comparison();
  Expr* term();
  Expr* factor();
  Expr* unary();
  Expr* primary();
  Token advance();
  Token peek();
  Token previous();
  Token consume(TokenType type, std::string message);
  void synchronize();
  ParseError error(Token token, std::string message);

  std::vector<Token> tokens;
  int current = 0;
};
