#include "Headers/Parser.hpp"

#include <algorithm>

#include "Headers/Expr.hpp"
#include "Headers/Interpreter.hpp"
#include "Headers/Stmt.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

Parser::Parser(std::vector<Token> &&tokens) : tokens(std::move(tokens)) {}

auto Parser::expression() -> Expr * { return assignment(); }

auto Parser::equality() -> Expr * {
  Expr *expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    Token operatorToken = previous();
    Expr *right = comparison();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::match(std::initializer_list<TokenType> types) -> bool {
  if (std::ranges::any_of(
          types, [this](TokenType type) -> bool { return check(type); })) {
    advance();
    return true;
  }
  return false;
}

auto Parser::check(TokenType type) -> bool {
  if (isAtEnd()) {
    return false;
  }
  return peek().type == type;
}

auto Parser::advance() -> Token {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

auto Parser::isAtEnd() -> bool {
  return peek().type == TokenType::END_OF_FILE || peek().type == TokenType::END;
}

auto Parser::peek() -> Token { return tokens[current]; }

auto Parser::previous() -> Token { return tokens[current - 1]; }

auto Parser::comparison() -> Expr * {
  Expr *expr = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                TokenType::LESS_EQUAL})) {
    Token operatorToken = previous();
    Expr *right = term();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::term() -> Expr * {
  Expr *expr = factor();

  while (match({TokenType::MINUS, TokenType::PLUS, TokenType::CONCATENATOR})) {
    Token operatorToken = previous();
    Expr *right = factor();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::factor() -> Expr * {
  Expr *expr = unary();

  while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULO})) {
    Token operatorToken = previous();
    Expr *right = unary();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::unary() -> Expr * {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token operatorToken = previous();
    Expr *right = unary();
    return new Unary(operatorToken, right);
  }

  return primary();
}

auto Parser::primary() -> Expr * {
  if (match({TokenType::BOOL_FALSE})) {
    return new Literal(false, TokenType::BOOL_FALSE);
  }
  if (match({TokenType::BOOL_TRUE})) {
    return new Literal(true, TokenType::BOOL_TRUE);
  }
  /*     if (match({TokenType::NIL}))
      return new Literal(nullptr); */
  if (match({TokenType::NUMBER, TokenType::STRING_LITERAL,
             TokenType::CHARACTER_LITERAL, TokenType::DECIMAL_NUMBER})) {
    return new Literal(previous().literal, previous().type);
  }
  if (match({TokenType::IDENTIFIER})) {
    return new Variable(previous());
  }

  if (match({TokenType::LEFT_PAREN})) {
    Expr *expr = expression();
    if (!match({TokenType::RIGHT_PAREN})) {
      throw std::runtime_error("Expect ')' after expression.");
    }
    return new Grouping(expr);
  }

  throw std::runtime_error("Expect expression.");
}

auto Parser::consume(TokenType type, const std::string &message) -> Token {
  if (check(type)) {
    return advance();
  }

  throw std::runtime_error(message);
}

auto Parser::error(const Token &token, const std::string &message)
    -> ParseError {
  BisayaPP::error(token, message);

  return {token, message};
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOLON) {
      return;
    }

    switch (peek().type) {
      case TokenType::CLASS:
      case TokenType::FUN:
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
      case TokenType::PRINT:
      case TokenType::RETURN:
        return;
      default:;
    }

    advance();
  }
}

auto Parser::varDeclaration() -> Stmt * {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

  Expr *initializer = nullptr;
  if (match({TokenType::EQUAL})) {
    initializer = expression();
  }

  consume(TokenType::SEMICOLON, "Expect newline after variable declaration.");
  return new Var(name, initializer);
}

auto Parser::declaration() -> Stmt * {
  try {
    if (match({TokenType::VAR}) &&
        (peek().type == TokenType::INTEGER ||
         peek().type == TokenType::DECIMAL || peek().type == TokenType::CHAR ||
         peek().type == TokenType::BOOL)) {
      advance();
      return varDeclaration();
    }

    return statement();
  } catch (const ParseError &error) {
    synchronize();
    return nullptr;
  }
}

auto Parser::parse() -> std::vector<Stmt *> {
  try {
    if (tokens[0].type != TokenType::START) {
      throw std::runtime_error("Expect 'SUGOD' at the beginning of the file.");
    }
    advance();
    advance();

    std::vector<Stmt *> statements;
    while (!isAtEnd()) {
      statements.push_back(declaration());
    }

    if (tokens[current].type != TokenType::END) {
      throw std::runtime_error("Expect 'KATAPUSAN' at the end of the file.");
    }

    return statements;
  } catch (const ParseError &error) {
    return {};
  }
}

auto Parser::expressionStatement() -> Stmt * {
  Expr *value = expression();
  consume(TokenType::SEMICOLON, "Expect newline after expression.");
  return new Expression(value);
}

auto Parser::printStatement() -> Stmt * {
  Expr *value = expression();
  consume(TokenType::SEMICOLON, "Expect newline after value.");
  return new Print(value);
}

auto Parser::statement() -> Stmt * {
  if (match({TokenType::PRINT})) {
    return printStatement();
  }
  if (match({TokenType::LEFT_BRACE})) {
    return new Block(block());
  }

  return expressionStatement();
}

auto Parser::assignment() -> Expr * {
  Expr *expr = equality();

  if (match({TokenType::EQUAL})) {
    Token equals = previous();
    Expr *value = assignment();

    if (dynamic_cast<Variable *>(expr) != nullptr) {
      Token name = static_cast<Variable *>(expr)->name;
      return new Assign(name, value);
    }

    error(equals, "Invalid assignment target.");
  }

  return expr;
}

auto Parser::block() -> std::vector<Stmt *> {
  std::vector<Stmt *> statements;
  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
    statements.push_back(declaration());
  }
  consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
  if (check(TokenType::SEMICOLON)) {
    advance();
  }
  return statements;
}
