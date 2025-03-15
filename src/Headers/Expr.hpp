#pragma once

#include <memory>
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
};

class Expr {
 public:
  virtual ~Expr() = default;
  virtual auto accept(ExprVisitor &visitor) -> void = 0;
};

class Assign : public Expr {
 public:
  Token name;
  std::unique_ptr<Expr> value;

  Assign(const Token &name, std::unique_ptr<Expr> &&value)
      : name(name), value(std::move(value)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitAssignExpr(*this);
  }
};

class Binary : public Expr {
 public:
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  Binary(std::unique_ptr<Expr> &&left, const Token &operatorToken,
         std::unique_ptr<Expr> &&right)
      : left(std::move(left)), op(operatorToken), right(std::move(right)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitBinaryExpr(*this);
  }
};

class Grouping : public Expr {
 public:
  std::unique_ptr<Expr> expression;

  Grouping(std::unique_ptr<Expr> &&expression)
      : expression(std::move(expression)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitGroupingExpr(*this);
  }
};

class Literal : public Expr {
 public:
  std::any value;
  TokenType type;

  Literal(std::any value, TokenType type)
      : value(std::move(value)), type(type) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitLiteralExpr(*this);
  }
};

class Logical : public Expr {
 public:
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  Logical(std::unique_ptr<Expr> &&left, const Token &operatorToken,
          std::unique_ptr<Expr> &&right)
      : left(std::move(left)), op(operatorToken), right(std::move(right)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitLogicalExpr(*this);
  }
};

class Unary : public Expr {
 public:
  Token op;
  std::unique_ptr<Expr> right;

  Unary(const Token &operatorToken, std::unique_ptr<Expr> &&right)
      : op(operatorToken), right(std::move(right)) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitUnaryExpr(*this);
  }
};

class Variable : public Expr {
 public:
  Token name;

  Variable(const Token &name) : name(name) {}

  auto accept(ExprVisitor &visitor) -> void override {
    visitor.visitVariableExpr(*this);
  }
};
