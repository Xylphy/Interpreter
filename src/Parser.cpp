#include "Headers/Parser.hpp"

#include <algorithm>

#include "Headers/Expr.hpp"
#include "Headers/Token.hpp"
#include "Headers/interpreter.hpp"

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

Parser::Parser(std::vector<Token> &&tokens) : tokens(std::move(tokens)) {}

auto Parser::expression() -> Expr * { return equality(); }

auto Parser::equality() -> Expr * {
  Expr *expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    Token op = previous();
    Expr *right = comparison();
    expr = new Binary(expr, op, right);
  }

  return expr;
}

auto Parser::match(std::initializer_list<TokenType> types) -> bool {
  if (std::ranges::any_of(types,
                          [this](TokenType type) -> bool { return check(type); })) {
    advance();
    return true;
  }
  return false;
}

auto Parser::check(TokenType type) -> bool{
  if (isAtEnd()) return false;
  return peek().type == type;
}

auto Parser::advance() -> Token{
  if (!isAtEnd()) current++;
  return previous();
}

bool Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }

Token Parser::peek() { return tokens[current]; }

Token Parser::previous() { return tokens[current - 1]; }

Expr *Parser::comparison() {
  Expr *expr = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                TokenType::LESS_EQUAL})) {
    Token op = previous();
    Expr *right = term();
    expr = new Binary(expr, op, right);
  }

  return expr;
}

Expr *Parser::term() {
  Expr *expr = factor();

  while (match({TokenType::MINUS, TokenType::PLUS})) {
    Token op = previous();
    Expr *right = factor();
    expr = new Binary(expr, op, right);
  }

  return expr;
}

Expr *Parser::factor() {
  Expr *expr = unary();

  while (match({TokenType::SLASH, TokenType::STAR})) {
    Token op = previous();
    Expr *right = unary();
    expr = new Binary(expr, op, right);
  }

  return expr;
}

Expr *Parser::unary() {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token op = previous();
    Expr *right = unary();
    return new Unary(op, right);
  }

  return primary();
}

Expr *Parser::primary() {
  if (match({TokenType::FALSE})) return new Literal(false);
  if (match({TokenType::TRUE})) return new Literal(true);
  /*     if (match({TokenType::NIL}))
      return new Literal(nullptr); */
  if (match({TokenType::NUMBER, TokenType::STRING}))
    return new Literal(previous().literal);

  if (match({TokenType::LEFT_PAREN})) {
    Expr *expr = expression();
    if (!match({TokenType::RIGHT_PAREN}))
      throw std::runtime_error("Expect ')' after expression.");
    return new Grouping(expr);
  }

  throw std::runtime_error("Expect expression.");
}

Token Parser::consume(TokenType type, std::string message) {
  if (check(type)) return advance();

  throw std::runtime_error(message);
}

ParseError Parser::error(Token token, std::string message) {
  BisayaPP::error(token, message);

  return ParseError(message);
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOLON) return;

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

Expr *Parser::parse() {
  try {
    return expression();
  } catch (ParseError &error) {
    return nullptr;
  }
}