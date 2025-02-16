#pragma once

#include <utility>

#include "Token.hpp"
class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor {
 public:
  virtual auto visitBinaryExpr(const Binary& Expr) -> std::string = 0;
  virtual auto visitGroupingExpr(const Grouping& Expr) -> std::string = 0;
  virtual auto visitLiteralExpr(const Literal& Expr) -> std::string = 0;
  virtual auto visitUnaryExpr(const Unary& Expr) -> std::string = 0;
};

class Expr {
 public:
  virtual ~Expr() = default;
  virtual auto accept(ExprVisitor& visitor) -> std::string = 0;
};

class Binary : public Expr {
 public:
  Expr* left;
  Token op;
  Expr* right;

  Binary(Expr* left, Token operatorToken, Expr* right)
      : left(left), op(std::move(operatorToken)), right(right) {}

  auto accept(ExprVisitor& visitor) -> std::string override {
    return visitor.visitBinaryExpr(*this);
  }
};

class Grouping : public Expr {
 public:
  Expr* expression;

  Grouping(Expr* expression) : expression(expression) {}

  auto accept(ExprVisitor& visitor) -> std::string override {
    return visitor.visitGroupingExpr(*this);
  }
};

class Literal : public Expr {
 public:
  std::any value;

  Literal(std::any value) : value(std::move(value)) {}

  auto accept(ExprVisitor& visitor) -> std::string override {
    return visitor.visitLiteralExpr(*this);
  }
};

class Unary : public Expr {
 public:
  Token op;
  Expr* right;

  Unary(Token operatorToken, Expr* right) : op(std::move(operatorToken)), right(right) {}

  auto accept(ExprVisitor& visitor) -> std::string override {
    return visitor.visitUnaryExpr(*this);
  }
};
