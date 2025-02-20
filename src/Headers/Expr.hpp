#pragma once

#include <utility>

#include "Token.hpp"
class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor {
 public:
  virtual auto visitBinaryExpr(const Binary& Expr) -> void = 0;
  virtual auto visitGroupingExpr(const Grouping& Expr) -> void = 0;
  virtual auto visitLiteralExpr(const Literal& Expr) -> void = 0;
  virtual auto visitUnaryExpr(const Unary& Expr) -> void = 0;
};

class Expr {
 public:
  virtual ~Expr() = default;
  virtual auto accept(ExprVisitor& visitor) -> void = 0;
};

class Binary : public Expr {
 public:
  Expr* left;
  Token op;
  Expr* right;

  Binary(Expr* left, Token operatorToken, Expr* right)
      : left(left), op(std::move(operatorToken)), right(right) {}

  auto accept(ExprVisitor& visitor) -> void override {
    visitor.visitBinaryExpr(*this);
  }
};

class Grouping : public Expr {
 public:
  Expr* expression;

  Grouping(Expr* expression) : expression(expression) {}

  auto accept(ExprVisitor& visitor) -> void override {
    visitor.visitGroupingExpr(*this);
  }
};

class Literal : public Expr {
 public:
  std::any value;
  TokenType type;

  Literal(std::any value, TokenType type)
      : value(std::move(value)), type(type) {}

  auto accept(ExprVisitor& visitor) -> void override {
    visitor.visitLiteralExpr(*this);
  }
};

class Unary : public Expr {
 public:
  Token op;
  Expr* right;

  Unary(Token operatorToken, Expr* right)
      : op(std::move(operatorToken)), right(right) {}

  auto accept(ExprVisitor& visitor) -> void override {
    visitor.visitUnaryExpr(*this);
  }
};
