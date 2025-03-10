#pragma once

#include <utility>

#include "Token.hpp"

class Assign;
class Binary;
class Grouping;
class Literal;
class Logical;
class Unary;
class Variable;

class ExprVisitor {
 public:
  virtual auto visitAssignExpr(const Assign &Expr) -> void = 0;
  virtual auto visitBinaryExpr(const Binary &Expr) -> void = 0;
  virtual auto visitGroupingExpr(const Grouping &Expr) -> void = 0;
  virtual auto visitLiteralExpr(const Literal &Expr) -> void = 0;
  virtual auto visitLogicalExpr(const Logical &Expr) -> void = 0;
  virtual auto visitUnaryExpr(const Unary &Expr) -> void = 0;
  virtual auto visitVariableExpr(const Variable &Expr) -> void = 0;
  virtual ~ExprVisitor() = default;
};

class Expr {
 public:
  virtual ~Expr() = default;
  virtual auto accept(ExprVisitor &visitor) -> void = 0;
};

class Assign : public Expr {
 public:
  Token name;
  Expr *value;

  Assign(Token name, Expr *value) : name(std::move(name)), value(value) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitAssignExpr(*this);
  }
};

class Binary : public Expr {
 public:
  Expr *left;
  Token op;
  Expr *right;

  Binary(Expr *left, Token tokenOperator, Expr *right)
      : left(left), op(std::move(tokenOperator)), right(right) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitBinaryExpr(*this);
  }
};

class Grouping : public Expr {
 public:
  Expr *expression;

  Grouping(Expr *expression) : expression(expression) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitGroupingExpr(*this);
  }
};

class Literal : public Expr {
 public:
  std::any value;
  TokenType type;

  Literal(std::any value, TokenType type) : value(std::move(value)), type(type) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitLiteralExpr(*this);
  }
};

class Logical : public Expr {
 public:
  Expr *left;
  Token op;
  Expr *right;

  Logical(Expr *left, Token tokenOperator, Expr *right)
      : left(left), op(std::move(tokenOperator)), right(right) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitLogicalExpr(*this);
  }
};

class Unary : public Expr {
 public:
  Token op;
  Expr *right;

  Unary(Token tokenOperator, Expr *right) : op(std::move(tokenOperator)), right(right) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitUnaryExpr(*this);
  }
};

class Variable : public Expr {
 public:
  Token name;

  Variable(Token name) : name(std::move(name)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitVariableExpr(*this);
  }
};
