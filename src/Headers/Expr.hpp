#pragma once

#include "Token.hpp"

class Assign;
class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;

class ExprVisitor {
 public:
  virtual auto visitAssignExpr(const Assign &Expr) -> void = 0;
  virtual auto visitBinaryExpr(const Binary &Expr) -> void = 0;
  virtual auto visitGroupingExpr(const Grouping &Expr) -> void = 0;
  virtual auto visitLiteralExpr(const Literal &Expr) -> void = 0;
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

  Assign(Token name, Expr *value) : name(name), value(value) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitAssignExpr(*this);
  }
};

class Binary : public Expr {
 public:
  Expr *left;
  Token op;
  Expr *right;

  Binary(Expr *left, Token op, Expr *right)
      : left(left), op(op), right(right) {}

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

  Literal(std::any value, TokenType type) : value(value), type(type) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitLiteralExpr(*this);
  }
};

class Unary : public Expr {
 public:
  Token op;
  Expr *right;

  Unary(Token op, Expr *right) : op(op), right(right) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitUnaryExpr(*this);
  }
};

class Variable : public Expr {
 public:
  Token name;

  Variable(Token name) : name(name) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitVariableExpr(*this);
  }
};
