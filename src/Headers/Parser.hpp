#include <memory>
#include <vector>

#include "Errors.hpp"
#include "Stmt.hpp"
#include "Token.hpp"

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  Parser(std::vector<Token>&& tokens);
  auto parse() -> std::vector<std::unique_ptr<Stmt>>;

  [[nodiscard]] auto getCurrentIndex() const -> size_t { return current; }

 private:
  auto match(std::initializer_list<TokenType> types) -> bool;
  auto check(TokenType type) -> bool;
  auto isAtEnd() -> bool;
  auto expression() -> std::unique_ptr<Expr>;
  auto equality() -> std::unique_ptr<Expr>;
  auto comparison() -> std::unique_ptr<Expr>;
  auto term() -> std::unique_ptr<Expr>;
  auto factor() -> std::unique_ptr<Expr>;
  auto unary() -> std::unique_ptr<Expr>;
  auto primary() -> std::unique_ptr<Expr>;
  auto assignment() -> std::unique_ptr<Expr>;
  auto advance() -> Token;
  auto peek() -> Token;
  auto previous() -> Token&;
  auto consume(TokenType type, const std::string& message) -> Token;
  auto checkTokenType(TokenType type, const std::string& message) -> Token;
  auto synchronize() -> void;
  auto block() -> std::vector<std::unique_ptr<Stmt>>;
  auto orExpression() -> std::unique_ptr<Expr>;
  auto andExpression() -> std::unique_ptr<Expr>;

  auto findStart() -> void;
  auto findEnd() -> void;
  auto skipConsecutiveTokens(TokenType token) -> void;

  auto declaration() -> std::vector<std::unique_ptr<Stmt>>;
  auto varDeclaration(TokenType& type) -> std::unique_ptr<Stmt>;

  auto statement() -> std::unique_ptr<Stmt>;
  auto printStatement() -> std::unique_ptr<Stmt>;
  auto inputStatement() -> std::unique_ptr<Stmt>;
  auto expressionStatement(TokenType endToken) -> std::unique_ptr<Stmt>;
  auto ifStatement() -> std::unique_ptr<Stmt>;
  auto whileStatement() -> std::unique_ptr<Stmt>;
  auto forStatement() -> std::unique_ptr<Stmt>;

  static auto error(const Token& token, const std::string& message)
      -> ParseError;

  std::vector<Token> tokens;
  size_t current = 0;
  bool hadError;
};
